#include "global.h"
#include "battle.h"
#include "text.h"
#include "palette.h"
#include "battle_controllers.h"
#include "main.h"
#include "bg.h"
#include "task.h"
#include "window.h"
#include "menu_helpers.h"
#include "menu.h"
#include "strings.h"
#include "gpu_regs.h"
#include "scanline_effect.h"
#include "text_window.h"
#include "strings.h"

extern void sub_809882C(u8, u16, u8);
extern void copy_textbox_border_tile_patterns_to_vram(u8, u16, u8);

// Window Ids
enum
{
    WIN_TEXT_OPTION,
    WIN_OPTIONS
};

static void Task_DebugMenuFadeIn(u8 taskId);
static void Task_DebugMenuProcessInput(u8 taskId);
static void Task_DebugMenuExit(u8 taskId);
static void Task_DebugMenuFadeOut(u8 taskId);
static void DrawTextOption(void);

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

static const u16 sBackdropColor[] = {0x7E51};

// code
static void MainCB2(void)
{
    RunTasks();
    AnimateSprites();
    BuildOamBuffer();
    UpdatePaletteFade();
}

static void VBlankCB(void)
{
    LoadOam();
    ProcessSpriteCopyRequests();
    TransferPlttBuffer();
}

void CB2_OpenBattleDebugMenu(void)
{
    switch (gMain.state)
    {
    default:
    case 0:
        SetVBlankCallback(NULL);
        gMain.state++;
        break;
    case 1:
        DmaClearLarge16(3, (void*)(VRAM), VRAM_SIZE, 0x1000);
        DmaClear32(3, OAM, OAM_SIZE);
        DmaClear16(3, PLTT, PLTT_SIZE);
        SetGpuReg(REG_OFFSET_DISPCNT, 0);
        ResetBgsAndClearDma3BusyFlags(0);
        InitBgsFromTemplates(0, sBgTemplates, ARRAY_COUNT(sBgTemplates));
        ChangeBgX(0, 0, 0);
        ChangeBgY(0, 0, 0);
        ChangeBgX(1, 0, 0);
        ChangeBgY(1, 0, 0);
        ChangeBgX(2, 0, 0);
        ChangeBgY(2, 0, 0);
        ChangeBgX(3, 0, 0);
        ChangeBgY(3, 0, 0);
        InitWindows(sWinTemplates);
        DeactivateAllTextPrinters();
        /*SetGpuReg(REG_OFFSET_WIN0H, 0);
        SetGpuReg(REG_OFFSET_WIN0V, 0);
        SetGpuReg(REG_OFFSET_WININ, 1);
        SetGpuReg(REG_OFFSET_WINOUT, 35);
        SetGpuReg(REG_OFFSET_BLDCNT, 193);
        SetGpuReg(REG_OFFSET_BLDALPHA, 0);
        SetGpuReg(REG_OFFSET_BLDY, 4);*/
        SetGpuReg(REG_OFFSET_DISPCNT, DISPCNT_OBJ_ON | DISPCNT_OBJ_1D_MAP);
        ShowBg(0);
        ShowBg(1);
        gMain.state++;
        break;
    case 2:
        ResetPaletteFade();
        ScanlineEffect_Stop();
        ResetTasks();
        ResetSpriteData();
        gMain.state++;
        break;
    case 3:
        LoadBgTiles(1, GetWindowFrameTilesPal(gSaveBlock2Ptr->optionsWindowFrameType)->tiles, 0x120, 0x1A2);
        gMain.state++;
        break;
    case 4:
        LoadPalette(sBackdropColor, 0, sizeof(sBackdropColor));
        LoadPalette(GetWindowFrameTilesPal(gSaveBlock2Ptr->optionsWindowFrameType)->pal, 0x70, 0x20);
        gMain.state++;
        break;
    case 5:
        //LoadPalette(sUnknown_0855C604, 0x10, sizeof(sUnknown_0855C604));
        gMain.state++;
        break;
    case 6:
        PutWindowTilemap(0);
        DrawTextOption();
        gMain.state++;
        break;
    case 7:
        gMain.state++;
        break;
    case 8:
        //PutWindowTilemap(1);
        //DrawOptionMenuTexts();
        gMain.state++;
    case 9:
        //sub_80BB154();
        gMain.state++;
        break;
    case 10:
    {
        u8 taskId = CreateTask(Task_DebugMenuFadeIn, 0);

        /*gTasks[taskId].data[TD_MENUSELECTION] = 0;
        gTasks[taskId].data[TD_TEXTSPEED] = gSaveBlock2Ptr->optionsTextSpeed;
        gTasks[taskId].data[TD_BATTLESCENE] = gSaveBlock2Ptr->optionsBattleSceneOff;
        gTasks[taskId].data[TD_BATTLESTYLE] = gSaveBlock2Ptr->optionsBattleStyle;
        gTasks[taskId].data[TD_SOUND] = gSaveBlock2Ptr->optionsSound;
        gTasks[taskId].data[TD_BUTTONMODE] = gSaveBlock2Ptr->optionsButtonMode;
        gTasks[taskId].data[TD_FRAMETYPE] = gSaveBlock2Ptr->optionsWindowFrameType;

        TextSpeed_DrawChoices(gTasks[taskId].data[TD_TEXTSPEED]);
        BattleScene_DrawChoices(gTasks[taskId].data[TD_BATTLESCENE]);
        BattleStyle_DrawChoices(gTasks[taskId].data[TD_BATTLESTYLE]);
        Sound_DrawChoices(gTasks[taskId].data[TD_SOUND]);
        ButtonMode_DrawChoices(gTasks[taskId].data[TD_BUTTONMODE]);
        FrameType_DrawChoices(gTasks[taskId].data[TD_FRAMETYPE]);
        HighlightOptionMenuItem(gTasks[taskId].data[TD_MENUSELECTION]);*/

        //CopyWindowToVram(WIN_OPTIONS, 3);
        gMain.state++;
        break;
    }
    case 11:
        BeginNormalPaletteFade(-1, 0, 0x10, 0, 0);
        SetVBlankCallback(VBlankCB);
        SetMainCallback2(MainCB2);
        return;
    }
}

static void Task_DebugMenuFadeIn(u8 taskId)
{
    if (!gPaletteFade.active)
        gTasks[taskId].func = Task_DebugMenuProcessInput;
}

static void Task_DebugMenuProcessInput(u8 taskId)
{
    if (((gMain.heldKeysRaw & L_BUTTON) && (gMain.newKeysRaw & R_BUTTON)) ||
        ((gMain.heldKeysRaw & R_BUTTON) && (gMain.newKeysRaw & L_BUTTON)))
    {
        gTasks[taskId].func = Task_DebugMenuExit;
    }
}

static void Task_DebugMenuExit(u8 taskId)
{
    BeginNormalPaletteFade(-1, 0, 0, 0x10, 0);
    gTasks[taskId].func = Task_DebugMenuFadeOut;
}

static void Task_DebugMenuFadeOut(u8 taskId)
{
    if (!gPaletteFade.active)
    {
        DestroyTask(taskId);
        FreeAllWindowBuffers();
        SetCB2ToReshowScreenAfterMenu2();
    }
}

static void DrawTextOption(void)
{
    FillWindowPixelBuffer(WIN_TEXT_OPTION, 0x11);
    PrintTextOnWindow(WIN_TEXT_OPTION, 1, gText_Option, 8, 1, TEXT_SPEED_FF, NULL);
    CopyWindowToVram(WIN_TEXT_OPTION, 3);
}
