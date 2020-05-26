#include <assert.h>
#include <stdbool.h>
#include <stdio.h>
#include <time.h>

#ifdef _WIN32
#include <windows.h>
#endif

#include <SDL2/SDL.h>

#define NO_UNDERSCORE_HACK

#include "global.h"
#include "platform.h"
#include "rtc.h"
#include "gba/defines.h"
#include "gba/m4a_internal.h"
//#include "gba/flash_internal.h"

extern void (*const gIntrTable[])(void);

u16 INTR_CHECK;
void *INTR_VECTOR;
unsigned char REG_BASE[0x400] __attribute__ ((aligned (4)));
unsigned char PLTT[PLTT_SIZE] __attribute__ ((aligned (4)));
unsigned char VRAM_[VRAM_SIZE] __attribute__ ((aligned (4)));
unsigned char OAM[OAM_SIZE] __attribute__ ((aligned (4)));
unsigned char FLASH_BASE[131072] __attribute__ ((aligned (4)));

SDL_Window *sdlWindow;
SDL_Renderer *sdlRenderer;
SDL_Texture *sdlTexture;
SDL_sem *vBlankSemaphore;
SDL_atomic_t isFrameAvailable;
bool speedUp = false;
unsigned int videoScale = 1;
bool videoScaleChanged = false;
bool isRunning = true;
double simTime = 0;
double lastGameTime = 0;
double curGameTime = 0;
double fixedTimestep = 1.0 / 60.0; // 16.666667ms
double timeScale = 1.0;
struct SiiRtcInfo internalClock;

extern void AgbMain(void);
extern void DoSoftReset(void);

int DoMain(void *param);
void ProcessEvents(void);
void VDraw(SDL_Texture *texture);
static void UpdateInternalClock(void);

int main(int argc, char **argv)
{
    // Open an output console on Windows
#ifdef _WIN32
    AllocConsole() ;
    AttachConsole( GetCurrentProcessId() ) ;
    freopen( "CON", "w", stdout ) ;
#endif

    if(SDL_Init(SDL_INIT_VIDEO) < 0)
    {
        fprintf(stderr, "SDL could not initialize! SDL_Error: %s\n", SDL_GetError());
        return 1;
    }

    sdlWindow = SDL_CreateWindow("pokeemerald", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, DISPLAY_WIDTH * videoScale, DISPLAY_HEIGHT * videoScale, SDL_WINDOW_SHOWN | SDL_WINDOW_RESIZABLE);
    if (sdlWindow == NULL)
    {
        fprintf(stderr, "Window could not be created! SDL_Error: %s\n", SDL_GetError());
        return 1;
    }

    sdlRenderer = SDL_CreateRenderer(sdlWindow, -1, SDL_RENDERER_PRESENTVSYNC);
    if (sdlRenderer == NULL)
    {
        fprintf(stderr, "Renderer could not be created! SDL_Error: %s\n", SDL_GetError());
        return 1;
    }

    SDL_SetRenderDrawColor(sdlRenderer, 255, 255, 255, 255);
    SDL_RenderClear(sdlRenderer);
    SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "0");
    SDL_RenderSetLogicalSize(sdlRenderer, DISPLAY_WIDTH, DISPLAY_HEIGHT);

    sdlTexture = SDL_CreateTexture(sdlRenderer,
                                   SDL_PIXELFORMAT_ARGB8888,
                                   SDL_TEXTUREACCESS_STREAMING,
                                   240, 160);
    if (sdlTexture == NULL)
    {
        fprintf(stderr, "Texture could not be created! SDL_Error: %s\n", SDL_GetError());
        return 1;
    }

    simTime = curGameTime = lastGameTime = SDL_GetPerformanceCounter();

    isFrameAvailable.value = 0;
    vBlankSemaphore = SDL_CreateSemaphore(0);

    VDraw(sdlTexture);
    SDL_CreateThread(DoMain, "AgbMain", NULL);

    double accumulator = 0.0;

    memset(&internalClock, 0, sizeof(internalClock));
    internalClock.status = SIIRTCINFO_24HOUR;
    UpdateInternalClock();

    while (isRunning)
    {
        ProcessEvents();
        double dt = fixedTimestep / timeScale; // TODO: Fix speedup

        curGameTime = SDL_GetPerformanceCounter();
        double deltaTime = (double)((curGameTime - lastGameTime) / (double)SDL_GetPerformanceFrequency());
        if (deltaTime > (dt * 5))
            deltaTime = dt;
        lastGameTime = curGameTime;

        accumulator += deltaTime;

        while (accumulator >= dt)
        {
            if (SDL_AtomicGet(&isFrameAvailable))
            {
                VDraw(sdlTexture);
                SDL_RenderClear(sdlRenderer);
                SDL_RenderCopy(sdlRenderer, sdlTexture, NULL, NULL);
                SDL_AtomicSet(&isFrameAvailable, 0);

                if (gIntrTable[4] != NULL)
                    gIntrTable[4]();

                SDL_SemPost(vBlankSemaphore);

                accumulator -= dt;
            }
        }

        if (videoScaleChanged)
        {
            SDL_SetWindowSize(sdlWindow, DISPLAY_WIDTH * videoScale, DISPLAY_HEIGHT * videoScale);
            videoScaleChanged = false;
        }

        SDL_RenderPresent(sdlRenderer);
    }

    SDL_DestroyWindow(sdlWindow);
    SDL_Quit();
    return 0;
}

// Key mappings
#define KEY_A_BUTTON      SDLK_x
#define KEY_B_BUTTON      SDLK_z
#define KEY_START_BUTTON  SDLK_RSHIFT
#define KEY_SELECT_BUTTON SDLK_BACKSLASH
#define KEY_L_BUTTON      SDLK_a
#define KEY_R_BUTTON      SDLK_s
#define KEY_DPAD_UP       SDLK_UP
#define KEY_DPAD_DOWN     SDLK_DOWN
#define KEY_DPAD_LEFT     SDLK_LEFT
#define KEY_DPAD_RIGHT    SDLK_RIGHT

#define HANDLE_KEYUP(key) \
case KEY_##key:  keys &= ~key; break;

#define HANDLE_KEYDOWN(key) \
case KEY_##key:  keys |= key; break;

static u16 keys;

void ProcessEvents(void)
{
    SDL_Event event;

    while (SDL_PollEvent(&event))
    {
        switch (event.type)
        {
        case SDL_QUIT:
            isRunning = false;
            break;
        case SDL_KEYUP:
            switch (event.key.keysym.sym)
            {
            HANDLE_KEYUP(A_BUTTON)
            HANDLE_KEYUP(B_BUTTON)
            HANDLE_KEYUP(START_BUTTON)
            HANDLE_KEYUP(SELECT_BUTTON)
            HANDLE_KEYUP(L_BUTTON)
            HANDLE_KEYUP(R_BUTTON)
            HANDLE_KEYUP(DPAD_UP)
            HANDLE_KEYUP(DPAD_DOWN)
            HANDLE_KEYUP(DPAD_LEFT)
            HANDLE_KEYUP(DPAD_RIGHT)
            case SDLK_SPACE:
                if (speedUp)
                {
                    speedUp = false;
                    timeScale = 1.0;
                }
                break;
            }
            break;
        case SDL_KEYDOWN:
            switch (event.key.keysym.sym)
            {
            HANDLE_KEYDOWN(A_BUTTON)
            HANDLE_KEYDOWN(B_BUTTON)
            HANDLE_KEYDOWN(START_BUTTON)
            HANDLE_KEYDOWN(SELECT_BUTTON)
            HANDLE_KEYDOWN(L_BUTTON)
            HANDLE_KEYDOWN(R_BUTTON)
            HANDLE_KEYDOWN(DPAD_UP)
            HANDLE_KEYDOWN(DPAD_DOWN)
            HANDLE_KEYDOWN(DPAD_LEFT)
            HANDLE_KEYDOWN(DPAD_RIGHT)
            case SDLK_r:
                if (event.key.keysym.mod & (KMOD_LCTRL | KMOD_RCTRL))
                {
                    DoSoftReset();
                }
                break;
            case SDLK_SPACE:
                if (!speedUp)
                {
                    speedUp = true;
                    timeScale = 5.0;
                }
                break;
            }
            break;
        case SDL_WINDOWEVENT:
            if (event.window.event == SDL_WINDOWEVENT_SIZE_CHANGED)
            {
                unsigned int w = event.window.data1;
                unsigned int h = event.window.data2;
                
                videoScale = 0;
                if (w / DISPLAY_WIDTH > videoScale)
                    videoScale = w / DISPLAY_WIDTH;
                if (h / DISPLAY_HEIGHT > videoScale)
                    videoScale = h / DISPLAY_HEIGHT;
                if (videoScale < 1)
                    videoScale = 1;

                videoScaleChanged = true;
            }
            break;
        }
    }
}

u16 Platform_GetKeyInput(void)
{
    return keys;
}

// BIOS function implementations are based on the VBA-M source code.

static uint32_t CPUReadMemory(const void *src)
{
    return *(uint32_t *)src;
}

static void CPUWriteMemory(void *dest, uint32_t val)
{
    *(uint32_t *)dest = val;
}

static uint16_t CPUReadHalfWord(const void *src)
{
    return *(uint16_t *)src;
}

static void CPUWriteHalfWord(void *dest, uint16_t val)
{
    *(uint16_t *)dest = val;
}

static uint8_t CPUReadByte(const void *src)
{
    return *(uint8_t *)src;
}

static void CPUWriteByte(void *dest, uint8_t val)
{
    *(uint8_t *)dest = val;
}

void DmaSet(int dmaNum, const void *src, void *dest, u32 control)
{
    int i;
    for (i=0; i<(control & 0x1ffff); i++)
    {
        if ((control) & DMA_SRC_FIXED){
            if ((control) & DMA_16BIT)
                    ((vu32 *)(dest))[i] = ((vu32 *)(src))[0];
            else    ((vu16 *)(dest))[i] = ((vu16 *)(src))[0];
        } else {
            if ((control) & DMA_32BIT)
                    ((vu32 *)(dest))[i] = ((vu32 *)(src))[i];
            else    ((vu16 *)(dest))[i] = ((vu16 *)(src))[i];
        }
    }
}

void CpuSet(const void *src, void *dst, u32 cnt)
{
    if(dst == NULL)
    {
        puts("Attempted to CpuSet to NULL\n");
        return;
    }
    
    int count = cnt & 0x1FFFFF;

    const u8 *source = src;
    u8 *dest = dst;

    // 32-bit ?
    if ((cnt >> 26) & 1) {
        
        //assert(((uintptr_t)src & ~3) == (uintptr_t)src);
        //assert(((uintptr_t)dst & ~3) == (uintptr_t)dst);
        
        // needed for 32-bit mode!
        //source = (u8 *)((uint32_t )source & ~3);
        //dest = (u8 *)((uint32_t )dest & ~3);

        // fill ?
        if ((cnt >> 24) & 1) {
            uint32_t value = CPUReadMemory(source);
            while (count) {
                CPUWriteMemory(dest, value);
                dest += 4;
                count--;
            }
        } else {
            // copy
            while (count) {
                CPUWriteMemory(dest, CPUReadMemory(source));
                source += 4;
                dest += 4;
                count--;
            }
        }
    } else {
        // No align on 16-bit fill?
        //assert(((uintptr_t)src & ~1) == (uintptr_t)src);
        //assert(((uintptr_t)dst & ~1) == (uintptr_t)dst);

        // 16-bit fill?
        if ((cnt >> 24) & 1) {
            uint16_t value = CPUReadHalfWord(source);
            while (count) {
                CPUWriteHalfWord(dest, value);
                dest += 2;
                count--;
            }
        } else {
            // copy
            while (count) {
                CPUWriteHalfWord(dest, CPUReadHalfWord(source));
                source += 2;
                dest += 2;
                count--;
            }
        }
    }
}

void CpuFastSet(const void *src, void *dst, u32 cnt)
{
    if(dst == NULL)
    {
        puts("Attempted to CpuFastSet to NULL\n");
        return;
    }
    
    int count = cnt & 0x1FFFFF;

    const u8 *source = src;
    u8 *dest = dst;
    
    //source = (u8 *)((uint32_t )source & ~3);
    //dest = (u8 *)((uint32_t )dest & ~3);

    // fill?
    if((cnt >> 24) & 1) {
        uint32_t value = CPUReadMemory(source);
        while(count > 0) {
            // BIOS always transfers 32 bytes at a time
            for(int i = 0; i < 8; i++) {
                CPUWriteMemory(dest, value);
                dest += 4;
            }
            count -= 8;
        }
    } else {
        // copy
        while(count > 0) {
            // BIOS always transfers 32 bytes at a time
            for(int i = 0; i < 8; i++) {
                uint32_t value = CPUReadMemory(source);
                CPUWriteMemory(dest, value);
                source += 4;
                dest += 4;
            }
            count -= 8;
        }
    }
}

void LZ77UnCompVram(const u32 *src_, void *dest_)
{
    const u8 *src = src_;
    u8 *dest = dest_;
	int destSize = (src[3] << 16) | (src[2] << 8) | src[1];
	int srcPos = 4;
	int destPos = 0;

	for (;;) {
		unsigned char flags = src[srcPos++];

		for (int i = 0; i < 8; i++) {
			if (flags & 0x80) {
				int blockSize = (src[srcPos] >> 4) + 3;
				int blockDistance = (((src[srcPos] & 0xF) << 8) | src[srcPos + 1]) + 1;

				srcPos += 2;

				int blockPos = destPos - blockDistance;

				// Some Ruby/Sapphire tilesets overflow.
				if (destPos + blockSize > destSize) {
					blockSize = destSize - destPos;
					//fprintf(stderr, "Destination buffer overflow.\n");
					puts("Destination buffer overflow.\n");
				}

				if (blockPos < 0)
					goto fail;

				for (int j = 0; j < blockSize; j++)
					dest[destPos++] = dest[blockPos + j];
			} else {
				if (destPos >= destSize)
					goto fail;

				dest[destPos++] = src[srcPos++];
			}

			if (destPos == destSize) {
				return;
			}

			flags <<= 1;
		}
	}

fail:
	puts("Fatal error while decompressing LZ file.\n");
}

/*
void LZ77UnCompVram(const void *src, void *dst)
{
    const uint8_t *source = src;
    uint8_t *dest = dst;

    uint32_t header = CPUReadMemory(source);
    source += 4;

    int byteCount = 0;
    int byteShift = 0;
    uint32_t writeValue = 0;

    int len = header >> 8;

    while (len > 0) {
        uint8_t d = CPUReadByte(source++);

        if (d) {
            for (int i = 0; i < 8; i++) {
                if (d & 0x80) {
                    uint16_t data = CPUReadByte(source++) << 8;
                    data |= CPUReadByte(source++);
                    int length = (data >> 12) + 3;
                    int offset = (data & 0x0FFF);
                    uint8_t *windowOffset = dest + byteCount - offset - 1;
                    for (int i2 = 0; i2 < length; i2++) {
                        writeValue |= (CPUReadByte(windowOffset++) << byteShift);
                        byteShift += 8;
                        byteCount++;

                        if (byteCount == 2) {
                            CPUWriteHalfWord(dest, writeValue);
                            dest += 2;
                            byteCount = 0;
                            byteShift = 0;
                            writeValue = 0;
                        }
                        len--;
                        if (len == 0)
                            return;
                    }
                } else {
                    writeValue |= (CPUReadByte(source++) << byteShift);
                    byteShift += 8;
                    byteCount++;
                    if (byteCount == 2) {
                        CPUWriteHalfWord(dest, writeValue);
                        dest += 2;
                        byteCount = 0;
                        byteShift = 0;
                        writeValue = 0;
                    }
                    len--;
                    if (len == 0)
                        return;
                }
                d <<= 1;
            }
        } else {
            for (int i = 0; i < 8; i++) {
                writeValue |= (CPUReadByte(source++) << byteShift);
                byteShift += 8;
                byteCount++;
                if (byteCount == 2) {
                    CPUWriteHalfWord(dest, writeValue);
                    dest += 2;
                    byteShift = 0;
                    byteCount = 0;
                    writeValue = 0;
                }
                len--;
                if (len == 0)
                    return;
            }
        }
    }
}
*/

void LZ77UnCompWram(const u32 *src, void *dst)
{
    const uint8_t *source = src;
    uint8_t *dest = dst;

    uint32_t header = CPUReadMemory(source);
    source += 4;

    int len = header >> 8;

    while (len > 0) {
        uint8_t d = CPUReadByte(source++);

        if (d) {
            for (int i = 0; i < 8; i++) {
                if (d & 0x80) {
                    uint16_t data = CPUReadByte(source++) << 8;
                    data |= CPUReadByte(source++);
                    int length = (data >> 12) + 3;
                    int offset = (data & 0x0FFF);
                    uint8_t *windowOffset = dest - offset - 1;
                    for (int i2 = 0; i2 < length; i2++) {
                        CPUWriteByte(dest++, CPUReadByte(windowOffset++));
                        len--;
                        if (len == 0)
                            return;
                    }
                } else {
                    CPUWriteByte(dest++, CPUReadByte(source++));
                    len--;
                    if (len == 0)
                        return;
                }
                d <<= 1;
            }
        } else {
            for (int i = 0; i < 8; i++) {
                CPUWriteByte(dest++, CPUReadByte(source++));
                len--;
                if (len == 0)
                    return;
            }
        }
    }
}


const s16 sineTable[256] = {
  (s16)0x0000, (s16)0x0192, (s16)0x0323, (s16)0x04B5, (s16)0x0645, (s16)0x07D5, (s16)0x0964, (s16)0x0AF1,
  (s16)0x0C7C, (s16)0x0E05, (s16)0x0F8C, (s16)0x1111, (s16)0x1294, (s16)0x1413, (s16)0x158F, (s16)0x1708,
  (s16)0x187D, (s16)0x19EF, (s16)0x1B5D, (s16)0x1CC6, (s16)0x1E2B, (s16)0x1F8B, (s16)0x20E7, (s16)0x223D,
  (s16)0x238E, (s16)0x24DA, (s16)0x261F, (s16)0x275F, (s16)0x2899, (s16)0x29CD, (s16)0x2AFA, (s16)0x2C21,
  (s16)0x2D41, (s16)0x2E5A, (s16)0x2F6B, (s16)0x3076, (s16)0x3179, (s16)0x3274, (s16)0x3367, (s16)0x3453,
  (s16)0x3536, (s16)0x3612, (s16)0x36E5, (s16)0x37AF, (s16)0x3871, (s16)0x392A, (s16)0x39DA, (s16)0x3A82,
  (s16)0x3B20, (s16)0x3BB6, (s16)0x3C42, (s16)0x3CC5, (s16)0x3D3E, (s16)0x3DAE, (s16)0x3E14, (s16)0x3E71,
  (s16)0x3EC5, (s16)0x3F0E, (s16)0x3F4E, (s16)0x3F84, (s16)0x3FB1, (s16)0x3FD3, (s16)0x3FEC, (s16)0x3FFB,
  (s16)0x4000, (s16)0x3FFB, (s16)0x3FEC, (s16)0x3FD3, (s16)0x3FB1, (s16)0x3F84, (s16)0x3F4E, (s16)0x3F0E,
  (s16)0x3EC5, (s16)0x3E71, (s16)0x3E14, (s16)0x3DAE, (s16)0x3D3E, (s16)0x3CC5, (s16)0x3C42, (s16)0x3BB6,
  (s16)0x3B20, (s16)0x3A82, (s16)0x39DA, (s16)0x392A, (s16)0x3871, (s16)0x37AF, (s16)0x36E5, (s16)0x3612,
  (s16)0x3536, (s16)0x3453, (s16)0x3367, (s16)0x3274, (s16)0x3179, (s16)0x3076, (s16)0x2F6B, (s16)0x2E5A,
  (s16)0x2D41, (s16)0x2C21, (s16)0x2AFA, (s16)0x29CD, (s16)0x2899, (s16)0x275F, (s16)0x261F, (s16)0x24DA,
  (s16)0x238E, (s16)0x223D, (s16)0x20E7, (s16)0x1F8B, (s16)0x1E2B, (s16)0x1CC6, (s16)0x1B5D, (s16)0x19EF,
  (s16)0x187D, (s16)0x1708, (s16)0x158F, (s16)0x1413, (s16)0x1294, (s16)0x1111, (s16)0x0F8C, (s16)0x0E05,
  (s16)0x0C7C, (s16)0x0AF1, (s16)0x0964, (s16)0x07D5, (s16)0x0645, (s16)0x04B5, (s16)0x0323, (s16)0x0192,
  (s16)0x0000, (s16)0xFE6E, (s16)0xFCDD, (s16)0xFB4B, (s16)0xF9BB, (s16)0xF82B, (s16)0xF69C, (s16)0xF50F,
  (s16)0xF384, (s16)0xF1FB, (s16)0xF074, (s16)0xEEEF, (s16)0xED6C, (s16)0xEBED, (s16)0xEA71, (s16)0xE8F8,
  (s16)0xE783, (s16)0xE611, (s16)0xE4A3, (s16)0xE33A, (s16)0xE1D5, (s16)0xE075, (s16)0xDF19, (s16)0xDDC3,
  (s16)0xDC72, (s16)0xDB26, (s16)0xD9E1, (s16)0xD8A1, (s16)0xD767, (s16)0xD633, (s16)0xD506, (s16)0xD3DF,
  (s16)0xD2BF, (s16)0xD1A6, (s16)0xD095, (s16)0xCF8A, (s16)0xCE87, (s16)0xCD8C, (s16)0xCC99, (s16)0xCBAD,
  (s16)0xCACA, (s16)0xC9EE, (s16)0xC91B, (s16)0xC851, (s16)0xC78F, (s16)0xC6D6, (s16)0xC626, (s16)0xC57E,
  (s16)0xC4E0, (s16)0xC44A, (s16)0xC3BE, (s16)0xC33B, (s16)0xC2C2, (s16)0xC252, (s16)0xC1EC, (s16)0xC18F,
  (s16)0xC13B, (s16)0xC0F2, (s16)0xC0B2, (s16)0xC07C, (s16)0xC04F, (s16)0xC02D, (s16)0xC014, (s16)0xC005,
  (s16)0xC000, (s16)0xC005, (s16)0xC014, (s16)0xC02D, (s16)0xC04F, (s16)0xC07C, (s16)0xC0B2, (s16)0xC0F2,
  (s16)0xC13B, (s16)0xC18F, (s16)0xC1EC, (s16)0xC252, (s16)0xC2C2, (s16)0xC33B, (s16)0xC3BE, (s16)0xC44A,
  (s16)0xC4E0, (s16)0xC57E, (s16)0xC626, (s16)0xC6D6, (s16)0xC78F, (s16)0xC851, (s16)0xC91B, (s16)0xC9EE,
  (s16)0xCACA, (s16)0xCBAD, (s16)0xCC99, (s16)0xCD8C, (s16)0xCE87, (s16)0xCF8A, (s16)0xD095, (s16)0xD1A6,
  (s16)0xD2BF, (s16)0xD3DF, (s16)0xD506, (s16)0xD633, (s16)0xD767, (s16)0xD8A1, (s16)0xD9E1, (s16)0xDB26,
  (s16)0xDC72, (s16)0xDDC3, (s16)0xDF19, (s16)0xE075, (s16)0xE1D5, (s16)0xE33A, (s16)0xE4A3, (s16)0xE611,
  (s16)0xE783, (s16)0xE8F8, (s16)0xEA71, (s16)0xEBED, (s16)0xED6C, (s16)0xEEEF, (s16)0xF074, (s16)0xF1FB,
  (s16)0xF384, (s16)0xF50F, (s16)0xF69C, (s16)0xF82B, (s16)0xF9BB, (s16)0xFB4B, (s16)0xFCDD, (s16)0xFE6E
};

void BgAffineSet(struct BgAffineSrcData *src, struct BgAffineDstData *dest, s32 count)
{
    for(s32 i=0; i<count; i++)
    {
        s32 cx = src[i].texX;
        s32 cy = src[i].texY;
        s16 dispx = src[i].scrX;
        s16 dispy = src[i].scrY;
        s16 rx = src[i].sx;
        s16 ry = src[i].sy;
        u16 theta = src[i].alpha>>8;
        s32 a = sineTable[(theta+0x40)&255];
        s32 b = sineTable[theta];

        s16 dx =  (rx * a)>>14;
        s16 dmx = (rx * b)>>14;
        s16 dy =  (ry * b)>>14;
        s16 dmy = (ry * a)>>14;

        dest[i].pa = dx;
        dest[i].pb = -dmx;
        dest[i].pc = dy;
        dest[i].pd = dmy;

        s32 startx = cx - dx * dispx + dmx * dispy;
        s32 starty = cy - dy * dispx - dmy * dispy;

        dest[i].dx = startx;
        dest[i].dy = starty;
    }
}

void ObjAffineSet(struct ObjAffineSrcData *src, void *dest, s32 count, s32 offset)
{
    for(s32 i=0; i<count; i++)
    {
        s16 rx = src[i].xScale;
        s16 ry = src[i].yScale;
        u16 theta = src[i].rotation>>8;

        s32 a = (s32)sineTable[(theta+0x40)&255];
        s32 b = (s32)sineTable[theta];

        s16 dx =  ((s32)rx * a)>>14;
        s16 dmx = ((s32)rx * b)>>14;
        s16 dy =  ((s32)ry * b)>>14;
        s16 dmy = ((s32)ry * a)>>14;

        CPUWriteHalfWord(dest, dx);
        dest += offset;
        CPUWriteHalfWord(dest, -dmx);
        dest += offset;
        CPUWriteHalfWord(dest, dy);
        dest += offset;
        CPUWriteHalfWord(dest, dmy);
        dest += offset;
    }
}

void SoftReset(u32 resetFlags)
{
    puts("Soft Reset called. Exiting.");
    exit(0);
}

/*
static inline uint16_t SwapPixel(uint16_t pixel)
{
    uint16_t result = 0;

    result |= (pixel >> 10) & 0x1F;
    result |= pixel & (0x1F << 5);
    result |= (pixel & 0x1F) << 10;
}
*/

static inline uint32_t ConvertPixel(uint16_t pixel)
{
    unsigned int r = (((pixel >> 0) & 0x1F) << 3) ;
    unsigned int g = (((pixel >> 5) & 0x1F) << 3) ;
    unsigned int b = (((pixel >> 10) & 0x1F) << 3);

    return b | (g << 8) | (r << 16) | (0xFF << 24);
}

static const uint16_t bgMapSizes[][2] =
{
    {32, 32},
    {64, 32},
    {32, 64},
    {64, 64},
};

static void RenderBGScanline(uint16_t control, uint16_t hoffs, uint16_t voffs, int lineNum, uint32_t *line)
{
    unsigned int charBaseBlock = (control >> 2) & 3;
    unsigned int screenBaseBlock = (control >> 8) & 0x1F;
    //bool is8bit = (control >> 7) & 1;
    unsigned int mapWidth = bgMapSizes[control >> 14][0];
    unsigned int mapHeight = bgMapSizes[control >> 14][1];

    uint8_t *bgtiles = (uint8_t *)(VRAM_ + charBaseBlock * 0x4000);
    uint16_t *bgmap = (uint16_t *)(VRAM_ + screenBaseBlock * 0x800);
    uint16_t *pal = (uint16_t *)PLTT;

    hoffs &= 0x1FF;
    voffs &= 0x1FF;

    for (unsigned int x = 0; x < DISPLAY_WIDTH; x++)
    {
        // adjust for scroll
        unsigned int xx = x + hoffs;
        unsigned int yy = lineNum + voffs;

        if (xx > mapWidth * 8 || yy > mapHeight * 8)
        {
            //if (!(control & (1 << 13)))
            //    continue;
        }
            
        xx %= mapWidth * 8;
        yy %= mapHeight * 8;

        unsigned int mapX = xx / 8;
        unsigned int mapY = yy / 8;
        uint16_t entry = bgmap[mapY * 32 + mapX];

        unsigned int tileNum = entry & 0x3FF;
        unsigned int paletteNum = (entry >> 12) & 0xF;
        
        unsigned int tileX = xx % 8;
        unsigned int tileY = yy % 8;

        // Flip if necessary
        if (entry & (1 << 10))
            tileX = 7 - tileX;
        if (entry & (1 << 11))
            tileY = 7 - tileY;

        uint8_t pixel = bgtiles[tileNum * 32 + tileY * 4 + tileX / 2];
        if (tileX & 1)
            pixel >>= 4;
        else
            pixel &= 0xF;

        if (pixel != 0 /*&& !(line[x] & (0xFF << 24))*/)
            line[x] = ConvertPixel(pal[16 * paletteNum + pixel]);
    }
}

static inline uint32_t getBgX(int bgNumber)
{
    if (bgNumber == 2)
    {
        return REG_BG2X;
    }
    else if (bgNumber == 3)
    {
        return REG_BG3X;
    }
}

static inline uint32_t getBgY(int bgNumber)
{
    if (bgNumber == 2)
    {
        return REG_BG2Y;
    }
    else if (bgNumber == 3)
    {
        return REG_BG3Y;
    }
}

static inline uint16_t getBgPA(int bgNumber)
{
    if (bgNumber == 2)
    {
        return REG_BG2PA;
    }
    else if (bgNumber == 3)
    {
        return REG_BG3PA;
    }
}

static inline uint16_t getBgPB(int bgNumber)
{
    if (bgNumber == 2)
    {
        return REG_BG2PB;
    }
    else if (bgNumber == 3)
    {
        return REG_BG3PB;
    }
}

static inline uint16_t getBgPC(int bgNumber)
{
    if (bgNumber == 2)
    {
        return REG_BG2PC;
    }
    else if (bgNumber == 3)
    {
        return REG_BG3PC;
    }
}

static inline uint16_t getBgPD(int bgNumber)
{
    if (bgNumber == 2)
    {
        return REG_BG2PD;
    }
    else if (bgNumber == 3)
    {
        return REG_BG3PD;
    }
}

static void RenderRotScaleBGScanline(int bgNum, uint16_t control, uint16_t x, uint16_t y, int lineNum, uint32_t *line)
{
    vBgCnt *bgcnt = (vBgCnt *)&control;
    unsigned int charBaseBlock = bgcnt->charBaseBlock;
    unsigned int screenBaseBlock = bgcnt->screenBaseBlock;
    unsigned int mapWidth = 1 << (4 + (bgcnt->screenSize)); // number of tiles

    uint8_t *bgtiles = (uint8_t *)(VRAM_ + charBaseBlock * 0x4000);
    uint8_t *bgmap = (uint8_t *)(VRAM_ + screenBaseBlock * 0x800);
    uint16_t *pal = (uint16_t *)PLTT;
    int prio = ((bgcnt->priority) << 25) + 0x1000000;

    u16 pa = getBgPA(bgNum);
    u16 pb = getBgPB(bgNum);
    u16 pc = getBgPC(bgNum);
    u16 pd = getBgPD(bgNum);

    int sizeX = 128;
    int sizeY = 128;

    switch (bgcnt->screenSize)
    {
    case 0:
        break;
    case 1:
        sizeX = sizeY = 256;
        break;
    case 2:
        sizeX = sizeY = 512;
        break;
    case 3:
        sizeX = sizeY = 1024;
        break;
    }

    int maskX = sizeX - 1;
    int maskY = sizeY - 1;

    int yshift = ((control >> 14) & 3) + 4;

    int dx = pa & 0x7FFF;
    if (pa & 0x8000)
        dx |= 0xFFFF8000;
    int dmx = pb & 0x7FFF;
    if (pb & 0x8000)
        dmx |= 0xFFFF8000;
    int dy = pc & 0x7FFF;
    if (pc & 0x8000)
        dy |= 0xFFFF8000;
    int dmy = pd & 0x7FFF;
    if (pd & 0x8000)
        dmy |= 0xFFFF8000;

    int currentX = getBgX(bgNum);
    int currentY = getBgY(bgNum);

    currentX += lineNum * dmx;
    currentY += lineNum * dmy;

    int realX = currentX;
    int realY = currentY;

    if (bgcnt->areaOverflowMode)
    {
        for (int x = 0; x < 240; x++)
        {
            int xxx = (realX >> 8) & maskX;
            int yyy = (realY >> 8) & maskY;

            int tile = bgmap[(xxx >> 3) + ((yyy >> 3) << yshift)];

            int tileX = xxx & 7;
            int tileY = yyy & 7;

            uint8_t pixel = bgtiles[(tile << 6) + (tileY << 3) + tileX];

            if (pixel != 0)
                line[x] = ConvertPixel(pal[pixel]) | prio;

            realX += dx;
            realY += dy;
        }
    }
    else
    {
        for (int x = 0; x < 240; x++)
        {
            int xxx = (realX >> 8);
            int yyy = (realY >> 8);

            if (xxx < 0 || yyy < 0 || xxx >= sizeX || yyy >= sizeY)
            {
                //line[x] = 0x80000000;
            }
            else
            {
                int tile = bgmap[(xxx >> 3) + ((yyy >> 3) << yshift)];

                int tileX = xxx & 7;
                int tileY = yyy & 7;

                uint8_t pixel = bgtiles[(tile << 6) + (tileY << 3) + tileX];

                if (pixel != 0)
                    line[x] = ConvertPixel(pal[pixel]) | prio;
            }
            realX += dx;
            realY += dy;
        }
    }
}

const u8 spriteSizes[][2] =
{
    {8, 16},
    {8, 32},
    {16, 32},
    {32, 64},
};

static void DrawSprites(uint32_t layers[4][DISPLAY_WIDTH * DISPLAY_HEIGHT])
{
    int i;
    unsigned int x;
    unsigned int y;
    void *objtiles = VRAM_ + 0x10000;

    if (!(REG_DISPCNT & (1 << 6)))
    {
        puts("2-D OBJ Character mapping not supported.");
    }

    for (i = 127; i >= 0; i--)
    {
        struct OamData *oam = (struct OamData *)(OAM + 8 * i);
        unsigned int width;
        unsigned int height;
        uint32_t *pixels;
        unsigned int blendMode = (REG_BLDCNT >> 6) & 3;

        if (!(oam->affineMode & 1) && oam->affineMode & 2) // Sprite disabled
        {
            continue;
        }
        //if (oam->objMode != 0)
        //    continue;  // Don't know how to handle other modes yet

        if (oam->shape == 0)
        {
            width = (1 << oam->size) * 8;
            height = (1 << oam->size) * 8;
        }
        else if (oam->shape == 1) // wide
        {
            width = spriteSizes[oam->size][1];
            height = spriteSizes[oam->size][0];
        }
        else if (oam->shape == 2) // tall
        {
            width = spriteSizes[oam->size][0];
            height = spriteSizes[oam->size][1];
        }
        else
            break; // prohibited

        int rect_width = width;
        int rect_height = height;

        int half_width = width / 2;
        int half_height = height / 2;

        pixels = layers[oam->priority];

        // TODO: Still buggy please finish
        if (oam->affineMode & 1) // Rotation/Scaling enabled
        {
            int x, y;
            x = oam->x + half_width;
            y = oam->y + half_height;

            if (oam->affineMode & 2) // double size flag
            {
                x += half_width;
                y += half_height;
                rect_width *= 2;
                rect_height *= 2;
                half_width *= 2;
                half_height *= 2;
            }

            if (oam->bpp == 0) // 16-color mode
            {
                uint8_t *tiledata = (uint8_t *)objtiles;
                uint16_t *palette = (uint16_t *)(PLTT + 0x200) + oam->paletteNum * 16;
                for (int local_y = -half_width; local_y <= half_height; local_y++)
                {
                    for (int local_x = -half_width; local_x <= half_width; local_x++)
                    {
                        int global_x = local_x + x;
                        int global_y = local_y + y;
                        /*
                        if (global_x < 0 || global_x >= 240)
                        {
                            continue;
                        }
                        */
                        u16 pa, pb, pc, pd;

                        //TODO: This is what i (MCboy) thought of for getting the affine parameters
                        //TODO: there is probably a better way to do this
                        u8 matrixNum = oam->matrixNum * 4;

                        struct OamData *oam1 = (struct OamData2 *)(OAM + 8 * (matrixNum));
                        struct OamData *oam2 = (struct OamData2 *)(OAM + 8 * (matrixNum + 1));
                        struct OamData *oam3 = (struct OamData2 *)(OAM + 8 * (matrixNum + 2));
                        struct OamData *oam4 = (struct OamData2 *)(OAM + 8 * (matrixNum + 3));

                        pa = oam1->affineParam;
                        pb = oam2->affineParam;
                        pc = oam3->affineParam;
                        pd = oam4->affineParam;

                        int tex_x = ((pa * local_x + pb * local_y) >> 8) + (width / 2);
                        int tex_y = ((pc * local_x + pd * local_y) >> 8) + (height / 2);

                        /* Check if transformed coordinates are inside bounds. */

                        if (tex_x >= width || tex_y >= height || tex_x < 0 || tex_y < 0)
                            continue;

                        int tile_x = tex_x % 8;
                        int tile_y = tex_y % 8;
                        int block_x = tex_x / 8;
                        int block_y = tex_y / 8;

                        int tile_num = (oam->tileNum + block_y * (REG_DISPCNT & 0x40 ? (width / 8) : 16)) + block_x;

                        uint16_t pixel = tiledata[(tile_num * 32) + (tile_y * 4) + (tile_x / 2)];

                        if (tile_x & 1)
                            pixel >>= 4;
                        else
                            pixel &= 0xF;

                        if (pixel != 0)
                        {
                            unsigned int scrx, scry;
                            uint32_t color;
                            // u8 disHeightBot = REG_WIN0V ? REG_WIN0V : DISPLAY_HEIGHT;
                            // u8 disWidthBot = REG_WIN0H ? REG_WIN0H : DISPLAY_WIDTH;
                            // u8 disHeightTop = REG_WIN0V ? REG_WIN0V >> 8 : 0;
                            // u8 disWidthTop = REG_WIN0H ? REG_WIN0H >> 8 : 0;

                            scrx = (unsigned int)(global_x & 0x1FF);
                            scry = (unsigned int)(global_y & 0xFF);
                            color = ConvertPixel(palette[pixel]);

                            if (scrx < DISPLAY_WIDTH && scry < DISPLAY_HEIGHT && scry > 0 && scrx > 0)
                                pixels[scry * DISPLAY_WIDTH + scrx] = ConvertPixel(palette[pixel]);
                        }
                    }
                }
            }
            else // 256-color mode
            {
                uint8_t *tiledata = (uint8_t *)objtiles;
                uint16_t *palette = (uint16_t *)(PLTT + 0x200);

                for (y = 0; y < height; y++)
                {
                    for (x = 0; x < width; x++)
                    {
                        unsigned int tileNum = oam->tileNum / 2 + (x / 8) + (y / 8) * (width / 8);
                        unsigned int tilex = x % 8;
                        unsigned int tiley = y % 8;
                        uint8_t pixel = tiledata[tileNum * 64 + tiley * 8 + tilex];

                        if (pixel != 0)
                        {
                            unsigned int scrx = (oam->x + x) & 0x1FF;
                            unsigned int scry = (oam->y + y) & 0xFF;

                            // u8 disHeightBot = REG_WIN0V ? REG_WIN0V : DISPLAY_HEIGHT;
                            // u8 disWidthBot = REG_WIN0H ? REG_WIN0H : DISPLAY_WIDTH;
                            // u8 disHeightTop = REG_WIN0V ? REG_WIN0V >> 8 : 0;
                            // u8 disWidthTop = REG_WIN0H ? REG_WIN0H >> 8 : 0;

                            if (scrx < DISPLAY_WIDTH && scry < DISPLAY_HEIGHT && scry > 0 && scrx > 0)
                                pixels[scry * DISPLAY_WIDTH + scrx] = ConvertPixel(palette[pixel]);
                        }
                    }
                }
            }
        }
        else // Normal sprite (no rotation/scaling)
        {
            if (oam->bpp == 0) // 16-color mode
            {
                uint8_t *tiledata = (uint8_t *)objtiles;
                uint16_t *palette = (uint16_t *)(PLTT + 0x200) + oam->paletteNum * 16;

                for (y = 0; y < height; y++)
                {
                    for (x = 0; x < width; x++)
                    {
                        // offset into the sprite
                        unsigned int xx = x;
                        unsigned int yy = y;

                        if (oam->matrixNum & (1 << 3))
                            xx = width - 1 - x;
                        if (oam->matrixNum & (1 << 4))
                            yy = height - 1 - y;

                        unsigned int tileNum = oam->tileNum + (xx / 8) + (yy / 8) * (width / 8);
                        unsigned int tilex = xx % 8;
                        unsigned int tiley = yy % 8;
                        uint8_t pixel = tiledata[tileNum * 32 + tiley * 4 + tilex / 2];

                        if (tilex & 1)
                            pixel >>= 4;
                        else
                            pixel &= 0xF;

                        if (pixel != 0)
                        {
                            unsigned int scrx = (oam->x + x) & 0x1FF;
                            unsigned int scry = (oam->y + y) & 0xFF;

                            // u8 disHeightBot = REG_WIN0V ? REG_WIN0V : DISPLAY_HEIGHT;
                            // u8 disWidthBot = REG_WIN0H ? REG_WIN0H : DISPLAY_WIDTH;
                            // u8 disHeightTop = REG_WIN0V ? REG_WIN0V >> 8 : 0;
                            // u8 disWidthTop = REG_WIN0H ? REG_WIN0H >> 8 : 0;

                            if (scrx < DISPLAY_WIDTH && scry < DISPLAY_HEIGHT && scry > 0 && scrx > 0)
                                pixels[scry * DISPLAY_WIDTH + scrx] = ConvertPixel(palette[pixel]);
                        }
                    }
                }
            }
            else // 256-color mode
            {
                uint8_t *tiledata = (uint8_t *)objtiles;
                uint16_t *palette = (uint16_t *)(PLTT + 0x200);

                for (y = 0; y < height; y++)
                {
                    for (x = 0; x < width; x++)
                    {
                        unsigned int tileNum = oam->tileNum / 2 + (x / 8) + (y / 8) * (width / 8);
                        unsigned int tilex = x % 8;
                        unsigned int tiley = y % 8;
                        uint8_t pixel = tiledata[tileNum * 64 + tiley * 8 + tilex];

                        if (pixel != 0)
                        {
                            unsigned int scrx = (oam->x + x) & 0x1FF;
                            unsigned int scry = (oam->y + y) & 0xFF;

                            //u8 disHeightBot = REG_WIN0V ? REG_WIN0V : DISPLAY_HEIGHT;
                            //u8 disWidthBot = REG_WIN0H ? REG_WIN0H : DISPLAY_WIDTH;
                            //u8 disHeightTop = REG_WIN0V ? REG_WIN0V >> 8 : 0;
                            //u8 disWidthTop = REG_WIN0H ? REG_WIN0H >> 8 : 0;

                            if (scrx < DISPLAY_WIDTH && scry < DISPLAY_HEIGHT && scry > 0 && scrx > 0)
                                pixels[scry * DISPLAY_WIDTH + scrx] = ConvertPixel(palette[pixel]);
                        }
                    }
                }
            }
        }
    }
}

static void RenderTextBGLayer(uint16_t bgcnt, uint16_t bghoffs, uint16_t bgvoffs, uint32_t *pixels)
{
    int vcount;

    for (vcount = 0; vcount < DISPLAY_HEIGHT; vcount++)
    {
        REG_VCOUNT = vcount;
        RenderBGScanline(bgcnt, bghoffs, bgvoffs, vcount, pixels + vcount * DISPLAY_WIDTH);
    }
}

static void RenderAffineBGLayer(uint32_t bgnum, uint16_t bgcnt, int32_t x, int32_t y, uint32_t *pixels)
{
    int vcount;
    
    for (vcount = 0; vcount < DISPLAY_HEIGHT; vcount++)
    {
        REG_VCOUNT = vcount;
        RenderRotScaleBGScanline(bgnum, bgcnt, x, y, vcount, pixels + vcount * DISPLAY_WIDTH);
    }
}

static uint32_t *target1layer;

#if 0
static void ProcessBGBlending(uint32_t *layer, int bg)
{
    unsigned int effect = (REG_BLDCNT >> 6) & 3;
    unsigned int evy;
    unsigned int eva;
    unsigned int evb;
    int i;

    switch (effect)
    {
    case 0:  // none
        break;
    case 1:  // alpha blending
        if (REG_BLDCNT & (1 << bg))  // BG is in first target
        {
            eva = REG_BLDALPHA & 0x1F;
            for (i = 0; i < DISPLAY_WIDTH * DISPLAY_HEIGHT; i++)
            {
                unsigned int r = (layer[i] >> 0) & 0xFF;
                unsigned int g = (layer[i] >> 8) & 0xFF;
                unsigned int b = (layer[i] >> 16) & 0xFF;
                unsigned int a = (layer[i] >> 24) & 0xFF;

                r = r * eva / 31;
                g = g * eva / 31;
                b = b * eva / 31;
                if (r > 255)
                    r = 255;
                if (g > 255)
                    g = 255;
                if (b > 255)
                    b = 255;
                layer[i] = r | (g << 8) | (b << 16) | (a << 24);
            }
            target1layer = layer;
        }
        if (REG_BLDCNT & (1 << (8 + bg)))  // BG is in second target
        {
            evb = (REG_BLDALPHA >> 8) & 0x1F;
            for (i = 0; i < DISPLAY_WIDTH * DISPLAY_HEIGHT; i++)
            {
                unsigned int r = (layer[i] >> 0) & 0xFF;
                unsigned int g = (layer[i] >> 8) & 0xFF;
                unsigned int b = (layer[i] >> 16) & 0xFF;
                unsigned int a = (layer[i] >> 24) & 0xFF;

                r = r * evb / 31;
                g = g * evb / 31;
                b = b * evb / 31;
                if (r > 255)
                    r = 255;
                if (g > 255)
                    g = 255;
                if (b > 255)
                    b = 255;
                layer[i] = r | (g << 8) | (b << 16) | (a << 24);
            }
        }
        break;
    case 2:  // brightness increase
    #if 0
        if (REG_BLDCNT & (1 << bg))
        {
            evy = REG_BLDY & 0x1F;
            //evy <<= 3;  // we are working with 8-bit instead of 5-bit
            for (i = 0; i < DISPLAY_WIDTH * DISPLAY_HEIGHT; i++)
            {
                unsigned int r = (layer[i] >> 0) & 0xFF;
                unsigned int g = (layer[i] >> 8) & 0xFF;
                unsigned int b = (layer[i] >> 16) & 0xFF;
                unsigned int a = (layer[i] >> 24) & 0xFF;

                /*
                r += ((31 << 3) - r) * evy;
                g += ((31 << 3) - g) * evy;
                b += ((31 << 3) - b) * evy;
                if (r > 255)
                    r = 255;
                if (g > 255)
                    g = 255;
                if (b > 255)
                    b = 255;
                */
                r >>= 3;
                g >>= 3;
                b >>= 3;
                r += evy;
                g += evy;
                b += evy;
                r <<= 3;
                g <<= 3;
                b <<= 3;
                if (r > 255)
                    r = 255;
                if (g > 255)
                    g = 255;
                if (b > 255)
                    b = 255;
                layer[i] = r | (g << 8) | (b << 16) | (a << 24);
            }
        }
    #endif
        break;
    // TODO: support the rest
    }
}
#endif

static void DrawFrame(uint32_t *pixels)
{
    unsigned int mode = REG_DISPCNT & 3;
    unsigned int bgEnabled = (REG_DISPCNT >> 8) & 0xF;
    int i;
    int j;
    int bg;
    static uint32_t layers[4][DISPLAY_WIDTH * DISPLAY_HEIGHT];
    // I have no clue how blending is supposed to work.
    unsigned int blendMode = (REG_BLDCNT >> 6) & 3;
    int blendPriority1 = -5;
    int blendPriority2 = -5;

    memset(layers, 0, sizeof(layers));

    if (blendMode == 1)
    {
        for (bg = 0; bg <= 3; bg++)
        {
            if (bgEnabled & (1 << bg))
            {
                uint16_t bgcnt = *(uint16_t *)(REG_ADDR_BG0CNT + bg * 2);
                unsigned int priority = bgcnt & 3;

                if (REG_BLDCNT & (1 << bg))
                    blendPriority1 = priority;
                if (REG_BLDCNT & (1 << (8 + bg)))
                    blendPriority2 = priority;
            }
        }
    }

    switch (mode)
    {
    case 0:
        // All backgrounds are text mode
        for (bg = 3; bg >= 0; bg--)
        {
            if (bgEnabled & (1 << bg))
            {
                uint16_t bgcnt = *(uint16_t *)(REG_ADDR_BG0CNT + bg * 2);
                uint16_t bghoffs = *(uint16_t *)(REG_ADDR_BG0HOFS + bg * 4);
                uint16_t bgvoffs = *(uint16_t *)(REG_ADDR_BG0VOFS + bg * 4);
                unsigned int priority = bgcnt & 3;

                RenderTextBGLayer(bgcnt, bghoffs, bgvoffs, layers[priority]);
                //ProcessBGBlending(layers[priority], bg);
            }
        }
        break;
    case 1:
        // BG2 is affine
        bg = 2;
        if (bgEnabled & (1 << bg))
        {
            uint16_t bgcnt = *(uint16_t *)(REG_ADDR_BG0CNT + bg * 2);
            unsigned int priority = bgcnt & 3;

            RenderAffineBGLayer(bg, bgcnt, REG_BG2X, REG_BG2Y, layers[priority]);
            //ProcessBGBlending(layers[priority], bg);
        }
        // BG0 and BG1 are text mode
        for (bg = 1; bg >= 0; bg--)
        {
            if (bgEnabled & (1 << bg))
            {
                uint16_t bgcnt = *(uint16_t *)(REG_ADDR_BG0CNT + bg * 2);
                uint16_t bghoffs = *(uint16_t *)(REG_ADDR_BG0HOFS + bg * 4);
                uint16_t bgvoffs = *(uint16_t *)(REG_ADDR_BG0VOFS + bg * 4);
                unsigned int priority = bgcnt & 3;

                RenderTextBGLayer(bgcnt, bghoffs, bgvoffs, layers[priority]);
                //ProcessBGBlending(layers[priority], bg);
            }
        }
        break;
    default:
        printf("Video mode %u is unsupported.\n", mode);
        break;
    }

    if (REG_DISPCNT & DISPCNT_OBJ_ON)
        DrawSprites(layers);

    // Copy to screen
    
    for (i = 3; i >= 0; i--)
    {
        uint32_t *src = layers[i];
        uint32_t *dest = pixels;

        if (i == blendPriority2 && i - 1 == blendPriority1)
        {
            uint32_t *target1 = layers[i - 1];
            uint32_t *target2 = layers[i];
            unsigned int eva = REG_BLDALPHA & 0x1F;
            unsigned int evb = (REG_BLDALPHA >> 8) & 0x1F;

            for (j = 0; j < DISPLAY_WIDTH * DISPLAY_HEIGHT; j++)
            {
                if ((src[j] & (0xFF << 24)))
                {
                    unsigned int r = ((target1[j] >>  0) & 0xFF) * eva / 31 + ((target2[j] >>  0) & 0xFF) * evb / 31;
                    unsigned int g = ((target1[j] >>  8) & 0xFF) * eva / 31 + ((target2[j] >>  8) & 0xFF) * evb / 31;
                    unsigned int b = ((target1[j] >> 16) & 0xFF) * eva / 31 + ((target2[j] >> 16) & 0xFF) * evb / 31;
                    unsigned int a = (target1[j] >> 24) & 0xFF;
                    
                    if (r > 255)
                        r = 255;
                    if (g > 255)
                        g = 255;
                    if (b > 255)
                        b = 255;
                    target2[j] = r | (g << 8) | (b << 16) | (a << 24);
                    //target2[j] = target1[j];
                }
            }
            i--;
        }

        for (j = 0; j < DISPLAY_WIDTH * DISPLAY_HEIGHT; j++)
        {
            if ((src[j] & (0xFF << 24)))
                dest[j] = src[j];
        }
    }
}

void ScaleImage(const uint32_t *src, uint32_t *dest, unsigned int scale)
{
    unsigned int x, y;

    if (scale == 1)
    {
        memcpy(dest, src, DISPLAY_WIDTH * DISPLAY_HEIGHT * sizeof(uint32_t));
    }
    else
    {
        for (x = 0; x < scale * DISPLAY_WIDTH; x++)
        {
            for (y = 0; y < scale * DISPLAY_HEIGHT; y++)
            {
                dest[y * scale * DISPLAY_WIDTH + x] = src[(y / scale) * DISPLAY_WIDTH + (x / scale)];
            }
        }
    }
}

uint32_t *memsetu32(uint32_t *dst, uint32_t fill, size_t count)
{
    for (int i = 0; i < count; i++)
    {
        *dst++ = fill;
    }
}

void VDraw(SDL_Texture *texture)
{
    static uint32_t image[DISPLAY_WIDTH * DISPLAY_HEIGHT];

    memsetu32(image, ConvertPixel(*(uint16_t *)PLTT), ARRAY_COUNT(image));
    DrawFrame(image);
    SDL_UpdateTexture(texture, NULL, image, DISPLAY_WIDTH * sizeof (Uint32));
    REG_VCOUNT = 161; // prep for being in VBlank period
}

int DoMain(void *data)
{
    AgbMain();
}

void VBlankIntrWait(void)
{
    SDL_AtomicSet(&isFrameAvailable, 1);
    SDL_SemWait(vBlankSemaphore);
}

u8 BinToBcd(u8 bin)
{
    int placeCounter = 1;
    u8 out = 0;
    do
    {
        out |= (bin % 10) * placeCounter;
        placeCounter *= 16;
    }
    while ((bin /= 10) > 0);

    return out;
}

void Platform_GetStatus(struct SiiRtcInfo *rtc)
{
    rtc->status = internalClock.status;
}

void Platform_SetStatus(struct SiiRtcInfo *rtc)
{
    internalClock.status = rtc->status;
}

static void UpdateInternalClock(void)
{
    time_t rawTime = time(NULL);
    struct tm *time = localtime(&rawTime);

    internalClock.year = BinToBcd(time->tm_year - 100);
    internalClock.month = BinToBcd(time->tm_mon) + 1;
    internalClock.day = BinToBcd(time->tm_mday);
    internalClock.dayOfWeek = BinToBcd(time->tm_wday);
    internalClock.hour = BinToBcd(time->tm_hour);
    internalClock.minute = BinToBcd(time->tm_min);
    internalClock.second = BinToBcd(time->tm_sec);
}

void Platform_GetDateTime(struct SiiRtcInfo *rtc)
{
    UpdateInternalClock();

    rtc->year = internalClock.year;
    rtc->month = internalClock.month;
    rtc->day = internalClock.day;
    rtc->dayOfWeek = internalClock.dayOfWeek;
    rtc->hour = internalClock.hour;
    rtc->minute = internalClock.minute;
    rtc->second = internalClock.second;
    printf("GetDateTime: %d-%02d-%02d %02d:%02d:%02d\n", ConvertBcdToBinary(rtc->year),
                                                         ConvertBcdToBinary(rtc->month),
                                                         ConvertBcdToBinary(rtc->day),
                                                         ConvertBcdToBinary(rtc->hour),
                                                         ConvertBcdToBinary(rtc->minute),
                                                         ConvertBcdToBinary(rtc->second));
}

void Platform_SetDateTime(struct SiiRtcInfo *rtc)
{
    internalClock.month = rtc->month;
    internalClock.day = rtc->day;
    internalClock.dayOfWeek = rtc->dayOfWeek;
    internalClock.hour = rtc->hour;
    internalClock.minute = rtc->minute;
    internalClock.second = rtc->second;
}

void Platform_GetTime(struct SiiRtcInfo *rtc)
{
    UpdateInternalClock();

    rtc->hour = internalClock.hour;
    rtc->minute = internalClock.minute;
    rtc->second = internalClock.second;
    printf("GetTime: %02d:%02d:%02d\n", ConvertBcdToBinary(rtc->hour),
                                        ConvertBcdToBinary(rtc->minute),
                                        ConvertBcdToBinary(rtc->second));
}

void Platform_SetTime(struct SiiRtcInfo *rtc)
{
    internalClock.hour = rtc->hour;
    internalClock.minute = rtc->minute;
    internalClock.second = rtc->second;
}

void Platform_SetAlarm(u8 *alarmData)
{
    // TODO
}
