#include "global.h"
#include "battle.h"
#include "malloc.h"
#include "pokemon.h"
#include "util.h"
#include "event_data.h"
#include "constants/species.h"
#include "constants/items.h"

#define KIND_EVO_MEGA 0
#define KIND_EVO_PRIMAL 1
#define KIND_EVO_RAY 2
#define KIND_EVO_COUNT 3

struct EvoEntry
{
    u16 speciesPre;
    u16 speciesPost;
    u8 evoKind;
    u16 parameter; // itemId or moveId
};

struct MegaEvo
{
    u8 aboutToEvo; // battler Ids as bits
    u8 megaEvolved[2]; // party Ids as bits per side

    // species saved
    u16 speciesPreEvo[2];
    u16 speciesPostEvo[2];
};

static EWRAM_DATA struct MegaEvo *sMegaEvo = NULL;

static const struct EvoEntry sMegaEvoEntries[] =
{
    {SPECIES_ODDISH, SPECIES_VILEPLUME, KIND_EVO_MEGA, ITEM_POTION},
    {},
};

void AllocateMegaEvo(void)
{
    sMegaEvo = AllocZeroed(sizeof(*sMegaEvo));
}

void FreeMegaEvo(void)
{
    FREE_AND_SET_NULL(sMegaEvo);
}

static const struct EvoEntry *TryGetBattlerMegaEntry(u8 battlerId)
{
    u32 i, j;
    u16 species = gBattleMons[battlerId].species;
    u16 item = gBattleMons[battlerId].item;

    for (i = 0; i < ARRAY_COUNT(sMegaEvoEntries); i++)
    {
        if (sMegaEvoEntries[i].speciesPre == species)
        {
            switch (sMegaEvoEntries[i].evoKind)
            {
            case KIND_EVO_MEGA:
            case KIND_EVO_PRIMAL:
                if (sMegaEvoEntries[i].parameter == item)
                    return &sMegaEvoEntries[i];
                break;
            case KIND_EVO_RAY:
                for (j = 0; j < 4; j++)
                {
                    if (sMegaEvoEntries[i].parameter == gBattleMons[battlerId].moves[j])
                        return &sMegaEvoEntries[i];
                }
                break;
            }
        }
    }

    return NULL;
}

bool32 CanMegaEvolve(u8 battlerId)
{
    const struct EvoEntry *entryInfo = TryGetBattlerMegaEntry(battlerId);

    // check if any entry exists and holds the right item
    if (entryInfo == NULL)
        return FALSE;
    // check if any other party mon already mega evolved
    if (sMegaEvo->megaEvolved[GetBattlerSide(battlerId)])
        return FALSE;
    // check if 'Key Stone' flag set
    if (GetBattlerSide(battlerId) == B_SIDE_PLAYER && !FlagGet(FLAG_ABLE_TO_MEGA_EVO))
        return FALSE;

    sMegaEvo->speciesPreEvo[GetBattlerSide(battlerId)] = entryInfo->speciesPre;
    sMegaEvo->speciesPostEvo[GetBattlerSide(battlerId)] = entryInfo->speciesPost;
    return TRUE;
}

void SetBattlerToMegaEvolve(u8 battlerId)
{
    sMegaEvo->aboutToEvo |= gBitTable[battlerId];
}

void ClearBattlersToMegaEvolve(void)
{
    sMegaEvo->aboutToEvo = 0;
}

bool32 IsBattlerToMegaEvolve(u8 battlerId)
{
    if (sMegaEvo->aboutToEvo & gBitTable[battlerId])
        return TRUE;
    else
        return FALSE;
}
