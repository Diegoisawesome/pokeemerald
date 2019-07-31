#include <assert.h>
#include <stdbool.h>
#include <stdio.h>

//#include <windows.h>

#include <SDL/SDL.h>

#define NO_UNDERSCORE_HACK

#include "global.h"
#include "platform.h"

extern void (*const gIntrTable[])(void);

// GBA memory
struct SoundInfo *SOUND_INFO_PTR;
u16 INTR_CHECK;
void *INTR_VECTOR;
unsigned char REG_BASE[0x400] __attribute__ ((aligned (4)));
unsigned char PLTT[PLTT_SIZE] __attribute__ ((aligned (4)));
unsigned char VRAM_[VRAM_SIZE] __attribute__ ((aligned (4)));
unsigned char OAM[OAM_SIZE] __attribute__ ((aligned (4)));

SDL_Surface *surface;
bool speedUp = false;
unsigned int videoScale = 1;

extern void AgbMain(void);

int main(int argc, char **argv)
{
    SDL_Init(SDL_INIT_VIDEO);
    surface = SDL_SetVideoMode(DISPLAY_WIDTH, DISPLAY_HEIGHT, 32, SDL_HWSURFACE | SDL_RESIZABLE);
    if (surface == NULL)
    {
        fputs("SDL_SetVideoMode failed.\n", stderr);
        return 1;
    }
    SDL_WM_SetCaption("pokeemerald", NULL);

    AgbMain();
    return 0;
}

// Key mappings
#define KEY_A_BUTTON      SDLK_c
#define KEY_B_BUTTON      SDLK_x
#define KEY_START_BUTTON  SDLK_RETURN
#define KEY_SELECT_BUTTON SDLK_BACKSPACE
#define KEY_L_BUTTON      SDLK_s
#define KEY_R_BUTTON      SDLK_f
#define KEY_DPAD_UP       SDLK_UP
#define KEY_DPAD_DOWN     SDLK_DOWN
#define KEY_DPAD_LEFT     SDLK_LEFT
#define KEY_DPAD_RIGHT    SDLK_RIGHT

#define HANDLE_KEYUP(key) \
case KEY_##key:  keys &= ~key; break;

#define HANDLE_KEYDOWN(key) \
case KEY_##key:  keys |= key; break;

u16 Platform_GetKeyInput(void)
{
    static u16 keys;
    SDL_Event event;

    while (SDL_PollEvent(&event))
    {
        switch (event.type)
        {
        case SDL_QUIT:
            exit(0);
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
            case SDLK_TAB:
                speedUp = false;
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
            case SDLK_TAB:
                speedUp = true;
                break;
            }
            break;
        case SDL_VIDEORESIZE:
            {
                unsigned int w = event.resize.w;
                unsigned int h = event.resize.h;
                
                videoScale = 0;
                if (w / DISPLAY_WIDTH > videoScale)
                    videoScale = w / DISPLAY_WIDTH;
                if (h / DISPLAY_HEIGHT > videoScale)
                    videoScale = h / DISPLAY_HEIGHT;
                if (videoScale < 1)
                    videoScale = 1;
                surface = SDL_SetVideoMode(DISPLAY_WIDTH * videoScale, DISPLAY_HEIGHT * videoScale, 32, SDL_HWSURFACE | SDL_RESIZABLE);
            }
            break;
        }
    }
    
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

void CpuSet(const void *src, void *dst, u32 cnt)
{
    int count = cnt & 0x1FFFFF;

    const u8 *source = src;
    u8 *dest = dst;

    // 32-bit ?
    if ((cnt >> 26) & 1) {
        // needed for 32-bit mode!
        source = (u8 *)((uint32_t )source & ~3);
        dest = (u8 *)((uint32_t )dest & ~3);

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
					fprintf(stderr, "Destination buffer overflow.\n");
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
        uint16_t entry = bgmap[mapY * mapWidth + mapX];

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

static void RenderRotScaleBGScanline(uint16_t control, uint16_t hoffs, uint16_t voffs, int lineNum, uint32_t *line)
{
    unsigned int charBaseBlock = (control >> 2) & 3;
    unsigned int screenBaseBlock = (control >> 8) & 0x1F;
    //bool is8bit = (control >> 7) & 1;
    unsigned int mapWidth = 1 << (7 + (control >> 14));

    uint8_t *bgtiles = (uint8_t *)(VRAM_ + charBaseBlock * 0x4000);
    uint8_t *bgmap = (uint8_t *)(VRAM_ + screenBaseBlock * 0x800);
    uint16_t *pal = (uint16_t *)PLTT;

    hoffs &= 0x1FF;
    voffs &= 0x1FF;

    mapWidth = 1 << (4 + (control >> 14));  // number of tiles

    for (unsigned int x = 0; x < DISPLAY_WIDTH; x++)
    {
        // adjust for scroll
        unsigned int xx = (x + hoffs) % (mapWidth * 8);
        unsigned int yy = (lineNum + voffs) % (mapWidth * 8);

        unsigned int mapX = xx / 8;
        unsigned int mapY = yy / 8;
        uint8_t entry = bgmap[mapY * mapWidth + mapX];

        unsigned int tileNum = entry;

        unsigned int tileX = xx % 8;
        unsigned int tileY = yy % 8;

        uint8_t pixel = bgtiles[tileNum * 64 + tileY * 8 + tileX];

        if (pixel != 0 /*&& !(line[x] & (0xFF << 24))*/)
            line[x] = ConvertPixel(pal[pixel]);
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

        if (oam->affineMode & 1)  // Rotation/Scaling enabled
        {
            // Don't know how to handle Rotation/Scaling yet
        }
        else
        {
            if (oam->affineMode & 2)  // Sprite disabled
                continue;
        }
        //if (oam->objMode != 0)
        //    continue;  // Don't know how to handle other modes yet

        if (oam->shape == 0)
        {
            width = (1 << oam->size) * 8;
            height = (1 << oam->size) * 8;
        }
        else if (oam->shape == 1)  // wide
        {
            width = spriteSizes[oam->size][1];
            height = spriteSizes[oam->size][0];
        }
        else if (oam->shape == 2)  // tall
        {
            width = spriteSizes[oam->size][0];
            height = spriteSizes[oam->size][1];
        }
        else
            break;  // prohibited

        pixels = layers[oam->priority];

        if (0)
        //if (oam->affineMode & 1)  // Rotation/Scaling enabled
        {
        }
        else  // Normal sprite (no rotation/scaling)
        {
            if (oam->bpp == 0)  // 16-color mode
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
                            
                            if (scrx < DISPLAY_WIDTH && scry < DISPLAY_HEIGHT)
                                pixels[scry * DISPLAY_WIDTH + scrx] = ConvertPixel(palette[pixel]);
                        }
                    }
                }
            }
            else  // 256-color mode
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
                            
                            if (scrx < DISPLAY_WIDTH && scry < DISPLAY_HEIGHT)
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
        RenderBGScanline(bgcnt, bghoffs, bgvoffs, vcount, pixels + vcount * DISPLAY_WIDTH);
}

static void RenderAffineBGLayer(uint16_t bgcnt, uint32_t *pixels)
{
    int vcount;
    
    for (vcount = 0; vcount < DISPLAY_HEIGHT; vcount++)
        RenderRotScaleBGScanline(bgcnt, 0, 0, vcount, pixels + vcount * DISPLAY_WIDTH);
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
            
            RenderAffineBGLayer(bgcnt, layers[priority]);
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

unsigned long int lastTime = 0;

void ScaleImage(const uint32_t *src, uint32_t *dest, unsigned int scale)
{
    unsigned int x, y;

    for (x = 0; x < scale * DISPLAY_WIDTH; x++)
    {
        for (y = 0; y < scale * DISPLAY_HEIGHT; y++)
        {
            dest[y * scale * DISPLAY_WIDTH + x] = src[(y / scale) * DISPLAY_WIDTH + (x / scale)];
        }
    }
}

void VBlankIntrWait(void)
{
    static uint32_t image[DISPLAY_WIDTH * DISPLAY_HEIGHT];

    unsigned long int time = SDL_GetTicks();
    if ((1000 / 60) > (time - lastTime) && !speedUp)
    {
        SDL_Delay((1000 / 60) - (time - lastTime));
    }
    lastTime = SDL_GetTicks();

    if (SDL_MUSTLOCK(surface))
        SDL_LockSurface(surface);
    if (videoScale == 1)
    {
        memset(surface->pixels, 0, surface->h * surface->pitch);
        DrawFrame(surface->pixels);
    }
    else
    {
        memset(image, 0, sizeof(image));
        DrawFrame(image);
        ScaleImage(image, surface->pixels, videoScale);
    }
    if (SDL_MUSTLOCK(surface))
        SDL_UnlockSurface(surface);
    SDL_Flip(surface);
    gIntrTable[3]();
    /*
    if (!speedUp)
        SDL_Delay(1000 / 60);
    */
}

