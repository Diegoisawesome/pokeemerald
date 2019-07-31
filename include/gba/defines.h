#ifndef GUARD_GBA_DEFINES
#define GUARD_GBA_DEFINES

#include <stddef.h>

#define TRUE  1
#define FALSE 0

#define BSS_DATA   __attribute__((section(".bss")))
#define IWRAM_DATA __attribute__((section("iwram_data")))
#define EWRAM_DATA __attribute__((section("ewram_data")))

#if MODERN
#define NOINLINE __attribute__((noinline))
#else
#define NOINLINE
#endif

#define ALIGNED(n) __attribute__((aligned(n)))

//#define SOUND_INFO_PTR (*(struct SoundInfo **)0x3007FF0)
extern struct SoundInfo *SOUND_INFO_PTR;
//#define INTR_CHECK     (*(u16 *)0x3007FF8)
extern unsigned short INTR_CHECK;
//#define INTR_VECTOR    (*(void **)0x3007FFC)
extern void *INTR_VECTOR;

//#define PLTT      0x5000000
#define PLTT_SIZE 0x400
extern unsigned char PLTT[PLTT_SIZE];

#define BG_PLTT      PLTT
#define BG_PLTT_SIZE 0x200

#define OBJ_PLTT      (PLTT + 0x200)
#define OBJ_PLTT_SIZE 0x200

//#define VRAM      0x6000000
#define VRAM_SIZE 0x18000
extern unsigned char VRAM_[VRAM_SIZE];
#define VRAM (u32)VRAM_

#define BG_VRAM           VRAM
#define BG_VRAM_SIZE      0x10000
#define BG_CHAR_SIZE      0x4000
#define BG_SCREEN_SIZE    0x800
#define BG_CHAR_ADDR(n)   (BG_VRAM + (BG_CHAR_SIZE * (n)))
#define BG_SCREEN_ADDR(n) (BG_VRAM + (BG_SCREEN_SIZE * (n)))

#define BG_TILE_H_FLIP(n) (0x400 + (n))
#define BG_TILE_V_FLIP(n) (0x800 + (n))

// text-mode BG
#define OBJ_VRAM0      (VRAM + 0x10000)
#define OBJ_VRAM0_SIZE 0x8000

// bitmap-mode BG
#define OBJ_VRAM1      (VRAM + 0x14000)
#define OBJ_VRAM1_SIZE 0x4000

//#define OAM      0x7000000
#define OAM_SIZE 0x400
extern unsigned char OAM[OAM_SIZE];

#define ROM_HEADER_SIZE   0xC0

#define DISPLAY_WIDTH  240
#define DISPLAY_HEIGHT 160

#define TILE_SIZE_4BPP 32
#define TILE_SIZE_8BPP 64

#define TILE_OFFSET_4BPP(n) ((n) * TILE_SIZE_4BPP)
#define TILE_OFFSET_8BPP(n) ((n) * TILE_SIZE_8BPP)

#define TOTAL_OBJ_TILE_COUNT 1024

#endif // GUARD_GBA_DEFINES
