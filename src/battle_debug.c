#include "global.h"
#include "battle.h"
#include "text.h"
#include "palette.h"
#include "reshow_battle_screen.h"
#include "main.h"
#include "bg.h"
#include "task.h"
#include "window.h"
#include "menu_helpers.h"
#include "menu.h"
#include "strings.h"
#include "gpu_regs.h"

extern void sub_809882C(u8, u16, u8);
extern void copy_textbox_border_tile_patterns_to_vram(u8, u16, u8);

static void CB2_Debug(void);

static const struct WindowTemplate sWinTemplates[] =
{
    {0, 2, 1, 9, 2, 0xF, 0x1E},
    DUMMY_WIN_TEMPLATE
};

static const struct BgTemplate sBgTemplates[] =
{
    {
        .bg = 0,
        .charBaseIndex = 0,
        .mapBaseIndex = 31,
        .screenSize = 0,
        .paletteMode = 0,
        .priority = 0,
        .baseTile = 0
    },
};

// code

void CB2_OpenBattleDebugMenu(void)
{
    u32 i;

    switch (gMain.state)
    {
    case 0:
        if (!gPaletteFade.active)
            gMain.state++;
        break;
    case 1:
        ResetSpriteData();
        FreeAllSpritePalettes();
        ResetBgsAndClearDma3BusyFlags(0);
        SetBgMode(0);
        gMain.state++;
        break;
    case 2:
        sub_809882C(0, 1, 0xD0);
        copy_textbox_border_tile_patterns_to_vram(0, 0x14, 0xF0);
        InitDebugWindows();
        ShowBg(0);
        gMain.state++;
        break;
    default:
        SetMainCallback2(CB2_Debug);
        break;
    }
}

static void CB2_Debug(void)
{
    do_scheduled_bg_tilemap_copies_to_vram();
    AnimateSprites();
    BuildOamBuffer();
    RunTextPrinters();
    UpdatePaletteFade();
    RunTasks();

    if (gMain.newKeys == (L_BUTTON | R_BUTTON))
        SetMainCallback2(ReshowBattleScreenAfterMenu);
}
