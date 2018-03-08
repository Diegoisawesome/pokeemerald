#include "global.h"
#include "sprite.h"
#include "battle.h"

#define TAG_ICON_PHYSICAL 0x3E1A
#define TAG_ICON_SPECIAL 0x3E1B
#define TAG_ICON_STATUS 0x3E1C

static EWRAM_DATA u8 sPSSIconSpriteId = 0;
static EWRAM_DATA bool8 sWasBuilt = FALSE;

static const u8 sIconPhysicalGfx[] = INCBIN_U8("graphics/misc/icon_physical.4bpp");
static const u16 sIconPhysicalPal[] = INCBIN_U16("graphics/misc/icon_physical.gbapal");

static const u8 sIconSpecialGfx[] = INCBIN_U8("graphics/misc/icon_special.4bpp");
static const u16 sIconSpecialPal[] = INCBIN_U16("graphics/misc/icon_special.gbapal");

static const u8 sIconStatusGfx[] = INCBIN_U8("graphics/misc/icon_status.4bpp");
static const u16 sIconStatusPal[] = INCBIN_U16("graphics/misc/icon_status.gbapal");

static const struct SpriteSheet sSheetSplitIcons[] =
{
    {sIconPhysicalGfx, 0x80, TAG_ICON_PHYSICAL},
    {sIconSpecialGfx,  0x80, TAG_ICON_SPECIAL},
    {sIconStatusGfx,   0x80, TAG_ICON_STATUS},
    {},
};

static const struct SpritePalette sPalsSplitIcons[] =
{
    {sIconPhysicalPal, TAG_ICON_PHYSICAL},
    {sIconSpecialPal,  TAG_ICON_SPECIAL},
    {sIconStatusPal,   TAG_ICON_STATUS},
    {},
};

static const struct OamData sOamData_SplitIcons =
{
    .y = 0,
    .affineMode = 0,
    .objMode = 0,
    .mosaic = 0,
    .bpp = 0,
    .shape = 0,
    .x = 0,
    .matrixNum = 0,
    .size = 1,
    .tileNum = 0,
    .priority = 0,
    .paletteNum = 0,
    .affineParam = 0,
};

static const struct SpriteTemplate sSpriteTemplateSplitIcons[] =
{
    {
        .tileTag = TAG_ICON_PHYSICAL,
        .paletteTag = TAG_ICON_PHYSICAL,
        .oam = &sOamData_SplitIcons,
        .anims = gDummySpriteAnimTable,
        .images = NULL,
        .affineAnims = gDummySpriteAffineAnimTable,
        .callback = SpriteCallbackDummy
    },
    {
        .tileTag = TAG_ICON_SPECIAL,
        .paletteTag = TAG_ICON_SPECIAL,
        .oam = &sOamData_SplitIcons,
        .anims = gDummySpriteAnimTable,
        .images = NULL,
        .affineAnims = gDummySpriteAffineAnimTable,
        .callback = SpriteCallbackDummy
    },
    {
        .tileTag = TAG_ICON_STATUS,
        .paletteTag = TAG_ICON_STATUS,
        .oam = &sOamData_SplitIcons,
        .anims = gDummySpriteAnimTable,
        .images = NULL,
        .affineAnims = gDummySpriteAffineAnimTable,
        .callback = SpriteCallbackDummy
    },
};

static void SpriteCB_DestroyIn(struct Sprite *sprite)
{
    if (sprite->data[7] == 0)
        DestroySprite(sprite);
    else
        sprite->data[7]--;
}

void DestroyPSSIconSpriteIn(s16 frames)
{
    if (sPSSIconSpriteId != MAX_SPRITES)
    {
        gSprites[sPSSIconSpriteId].data[7] = frames;
        gSprites[sPSSIconSpriteId].callback = SpriteCB_DestroyIn;
    }
}

void TryDestroyPSSIconSprite(void)
{
    if (sPSSIconSpriteId != MAX_SPRITES)
    {
        DestroySprite(&gSprites[sPSSIconSpriteId]);
        sPSSIconSpriteId = MAX_SPRITES;
    }
}

void LoadPSSIconsGfx(void)
{
    if (sWasBuilt)
        TryDestroyPSSIconSprite();
    else
        sPSSIconSpriteId = MAX_SPRITES;

    LoadSpriteSheets(sSheetSplitIcons);
    LoadSpritePalettes(sPalsSplitIcons);
}

u8 CreatePSSIconSprite(u32 split, s16 xPos, s16 yPos)
{
    sPSSIconSpriteId = CreateSprite(&sSpriteTemplateSplitIcons[split], xPos, yPos, 0);
    if (sPSSIconSpriteId != MAX_SPRITES)
        sWasBuilt = TRUE;
    return sPSSIconSpriteId;
}
