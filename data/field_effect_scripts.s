	.include "asm/macros.inc"
	.include "constants/constants.inc"

	.section script_data, "aw"

	.align 2
gFieldEffectScriptPointers:: @ 82DB9D4
	.int gFieldEffectScript_ExclamationMarkIcon1
	.int gFieldEffectScript_UseCutOnTallGrass
	.int gFieldEffectScript_UseCutOnTree
	.int gFieldEffectScript_Shadow
	.int gFieldEffectScript_TallGrass
	.int gFieldEffectScript_Ripple
	.int gFieldEffectScript_FieldMoveShowMon
	.int gFieldEffectScript_Ash
	.int gFieldEffectScript_SurfBlob
	.int gFieldEffectScript_UseSurf
	.int gFieldEffectScript_GroundImpactDust
	.int gFieldEffectScript_UseSecretPowerCave
	.int gFieldEffectScript_BikeHopTallGrass
	.int gFieldEffectScript_SandFootprints
	.int gFieldEffectScript_BikeHopBigSplash
	.int gFieldEffectScript_Splash
	.int gFieldEffectScript_BikeHopSmallSplash
	.int gFieldEffectScript_LongGrass
	.int gFieldEffectScript_JumpLongGrass
	.int gFieldEffectScript_Unknown19
	.int gFieldEffectScript_Unknown20
	.int gFieldEffectScript_Unknown21
	.int gFieldEffectScript_Unknown22
	.int gFieldEffectScript_BerryTreeGrowthSparkle
	.int gFieldEffectScript_DeepSandFootprints
	.int gFieldEffectScript_PokeCenterHeal
	.int gFieldEffectScript_UseSecretPowerTree
	.int gFieldEffectScript_UseSecretPowerShrub
	.int gFieldEffectScript_TreeDisguise
	.int gFieldEffectScript_MountainDisguise
	.int gFieldEffectScript_NPCUseFly
	.int gFieldEffectScript_UseFly
	.int gFieldEffectScript_FlyIn
	.int gFieldEffectScript_QuestionMarkIcon
	.int gFieldEffectScript_FeetInFlowingWater
	.int gFieldEffectScript_BikeTireTracks
	.int gFieldEffectScript_SandDisguisePlaceholder
	.int gFieldEffectScript_UseRockSmash
	.int gFieldEffectScript_UseDig
	.int gFieldEffectScript_SandPile
	.int gFieldEffectScript_UseStrength
	.int gFieldEffectScript_ShortGrass
	.int gFieldEffectScript_HotSpringsWater
	.int gFieldEffectScript_UseWaterfall
	.int gFieldEffectScript_UseDive
	.int gFieldEffectScript_Pokeball
	.int gFieldEffectScript_HeartIcon
	.int gFieldEffectScript_Unknown47
	.int gFieldEffectScript_Unknown48
	.int gFieldEffectScript_JumpOutOfAsh
	.int gFieldEffectScript_LavaridgeGymWarp
	.int gFieldEffectScript_SweetScent
	.int gFieldEffectScript_SandPillar
	.int gFieldEffectScript_Bubbles
	.int gFieldEffectScript_Sparkle
	.int gFieldEffectScript_ShowSecretPowerCave
	.int gFieldEffectScript_ShowSecretPowerTree
	.int gFieldEffectScript_ShowSecretPowerShrub
	.int gFieldEffectScript_ShowCutGrass
	.int gFieldEffectScript_FieldMoveShowMonInit
	.int gFieldEffectScript_UsePuzzleEffect
	.int gFieldEffectScript_SecretBaseBootPC
	.int gFieldEffectScript_HallOfFameRecord
	.int gFieldEffectScript_UseTeleport
	.int gFieldEffectScript_Rayquaza
	.int gFieldEffectScript_Unknown65
	.int gFieldEffectScript_MoveDeoxysRock

gFieldEffectScript_ExclamationMarkIcon1:: @ 82DBAE0
	field_eff_callnative FldEff_ExclamationMarkIcon
	field_eff_end

gFieldEffectScript_UseCutOnTallGrass:: @ 82DBAE6
	field_eff_callnative FldEff_UseCutOnGrass
	field_eff_end

gFieldEffectScript_UseCutOnTree:: @ 82DBAEC
	field_eff_callnative FldEff_UseCutOnTree
	field_eff_end

gFieldEffectScript_Shadow:: @ 82DBAF2
	field_eff_callnative FldEff_Shadow
	field_eff_end

gFieldEffectScript_TallGrass:: @ 82DBAF8
	field_eff_loadfadedpal_callnative gFieldEffectObjectPaletteInfo1, FldEff_TallGrass
	field_eff_end

gFieldEffectScript_Ripple:: @ 82DBB02
	field_eff_loadfadedpal_callnative gFieldEffectObjectPaletteInfo1, FldEff_Ripple
	field_eff_end

gFieldEffectScript_FieldMoveShowMon:: @ 82DBB0C
	field_eff_callnative FldEff_FieldMoveShowMon
	field_eff_end

gFieldEffectScript_Ash:: @ 82DBB12
	field_eff_loadfadedpal_callnative gFieldEffectObjectPaletteInfo1, FldEff_Ash
	field_eff_end

gFieldEffectScript_SurfBlob:: @ 82DBB1C
	field_eff_callnative FldEff_SurfBlob
	field_eff_end

gFieldEffectScript_UseSurf:: @ 82DBB22
	field_eff_callnative FldEff_UseSurf
	field_eff_end

gFieldEffectScript_GroundImpactDust:: @ 82DBB28
	field_eff_loadfadedpal_callnative gFieldEffectObjectPaletteInfo0, FldEff_Dust
	field_eff_end

gFieldEffectScript_UseSecretPowerCave:: @ 82DBB32
	field_eff_callnative FldEff_UseSecretPowerCave
	field_eff_end

gFieldEffectScript_BikeHopTallGrass:: @ 82DBB38
	field_eff_loadfadedpal_callnative gFieldEffectObjectPaletteInfo1, FldEff_JumpTallGrass
	field_eff_end

gFieldEffectScript_SandFootprints:: @ 82DBB42
	field_eff_loadfadedpal_callnative gFieldEffectObjectPaletteInfo0, FldEff_SandFootprints
	field_eff_end

gFieldEffectScript_BikeHopBigSplash:: @ 82DBB4C
	field_eff_loadfadedpal_callnative gFieldEffectObjectPaletteInfo0, FldEff_JumpBigSplash
	field_eff_end

gFieldEffectScript_Splash:: @ 82DBB56
	field_eff_loadfadedpal_callnative gFieldEffectObjectPaletteInfo0, FldEff_Splash
	field_eff_end

gFieldEffectScript_BikeHopSmallSplash:: @ 82DBB60
	field_eff_loadfadedpal_callnative gFieldEffectObjectPaletteInfo0, FldEff_JumpSmallSplash
	field_eff_end

gFieldEffectScript_LongGrass:: @ 82DBB6A
	field_eff_loadfadedpal_callnative gFieldEffectObjectPaletteInfo1, FldEff_LongGrass
	field_eff_end

gFieldEffectScript_JumpLongGrass:: @ 82DBB74
	field_eff_loadfadedpal_callnative gFieldEffectObjectPaletteInfo1, FldEff_JumpLongGrass
	field_eff_end

gFieldEffectScript_Unknown19:: @ 82DBB7E
	field_eff_loadfadedpal_callnative gFieldEffectObjectPaletteInfo1, FldEff_Unknown19
	field_eff_end

gFieldEffectScript_Unknown20:: @ 82DBB88
	field_eff_loadfadedpal_callnative gFieldEffectObjectPaletteInfo1, FldEff_Unknown20
	field_eff_end

gFieldEffectScript_Unknown21:: @ 82DBB92
	field_eff_loadfadedpal_callnative gFieldEffectObjectPaletteInfo0, FldEff_Unknown21
	field_eff_end

gFieldEffectScript_Unknown22:: @ 82DBB9C
	field_eff_loadfadedpal_callnative gFieldEffectObjectPaletteInfo0, FldEff_Unknown22
	field_eff_end

gFieldEffectScript_BerryTreeGrowthSparkle:: @ 82DBBA6
	field_eff_callnative FldEff_BerryTreeGrowthSparkle
	field_eff_end

gFieldEffectScript_DeepSandFootprints:: @ 82DBBAC
	field_eff_loadfadedpal_callnative gFieldEffectObjectPaletteInfo0, FldEff_DeepSandFootprints
	field_eff_end

gFieldEffectScript_PokeCenterHeal:: @ 82DBBB6
	field_eff_loadfadedpal gFieldEffectObjectPaletteInfo4
	field_eff_loadfadedpal_callnative gFieldEffectObjectPaletteInfo0, FldEff_PokecenterHeal
	field_eff_end

gFieldEffectScript_UseSecretPowerTree:: @ 82DBBC5
	field_eff_callnative FldEff_UseSecretPowerTree
	field_eff_end

gFieldEffectScript_UseSecretPowerShrub:: @ 82DBBCB
	field_eff_callnative FldEff_UseSecretPowerShrub
	field_eff_end

gFieldEffectScript_TreeDisguise:: @ 82DBBD1
	field_eff_callnative ShowTreeDisguiseFieldEffect
	field_eff_end

gFieldEffectScript_MountainDisguise:: @ 82DBBD7
	field_eff_callnative ShowMountainDisguiseFieldEffect
	field_eff_end

gFieldEffectScript_NPCUseFly:: @ 82DBBDD
	field_eff_callnative FldEff_NPCFlyOut
	field_eff_end

gFieldEffectScript_UseFly:: @ 82DBBE3
	field_eff_callnative FldEff_UseFly
	field_eff_end

gFieldEffectScript_FlyIn:: @ 82DBBE9
	field_eff_callnative FldEff_FlyIn
	field_eff_end

gFieldEffectScript_QuestionMarkIcon:: @ 82DBBEF
	field_eff_callnative FldEff_QuestionMarkIcon
	field_eff_end

gFieldEffectScript_FeetInFlowingWater:: @ 82DBBF5
	field_eff_loadfadedpal_callnative gFieldEffectObjectPaletteInfo0, FldEff_FeetInFlowingWater
	field_eff_end

gFieldEffectScript_BikeTireTracks:: @ 82DBBFF
	field_eff_loadfadedpal_callnative gFieldEffectObjectPaletteInfo0, FldEff_BikeTireTracks
	field_eff_end

gFieldEffectScript_SandDisguisePlaceholder:: @ 82DBC09
	field_eff_callnative ShowSandDisguiseFieldEffect
	field_eff_end

gFieldEffectScript_UseRockSmash:: @ 82DBC0F
	field_eff_callnative FldEff_UseRockSmash
	field_eff_end

gFieldEffectScript_UseStrength:: @ 82DBC15
	field_eff_callnative sub_8145E2C
	field_eff_end

gFieldEffectScript_UseDig:: @ 82DBC1B
	field_eff_callnative FldEff_UseDig
	field_eff_end

gFieldEffectScript_SandPile:: @ 82DBC21
	field_eff_loadfadedpal_callnative gFieldEffectObjectPaletteInfo0, FldEff_SandPile
	field_eff_end

gFieldEffectScript_ShortGrass:: @ 82DBC2B
	field_eff_loadfadedpal_callnative gFieldEffectObjectPaletteInfo1, FldEff_ShortGrass
	field_eff_end

gFieldEffectScript_HotSpringsWater:: @ 82DBC35
	field_eff_loadfadedpal_callnative gFieldEffectObjectPaletteInfo1, FldEff_HotSpringsWater
	field_eff_end

gFieldEffectScript_UseWaterfall:: @ 82DBC3F
	field_eff_callnative FldEff_UseWaterfall
	field_eff_end

gFieldEffectScript_UseDive:: @ 82DBC45
	field_eff_callnative FldEff_UseDive
	field_eff_end

gFieldEffectScript_Pokeball:: @ 82DBC4B
	field_eff_loadpal gFieldEffectObjectPaletteInfo10
	field_eff_callnative FldEff_Pokeball
	field_eff_end

gFieldEffectScript_HeartIcon:: @ 82DBC56
	field_eff_loadfadedpal_callnative gFieldEffectObjectPaletteInfo0, FldEff_HeartIcon
	field_eff_end

gFieldEffectScript_Unknown47:: @ 82DBC60
	field_eff_callnative FldEff_NopA6FC
	field_eff_end

gFieldEffectScript_Unknown48:: @ 82DBC66
	field_eff_callnative FldEff_NopA700
	field_eff_end

gFieldEffectScript_JumpOutOfAsh:: @ 82DBC6C
	field_eff_loadfadedpal_callnative gFieldEffectObjectPaletteInfo2, FldEff_PopOutOfAsh
	field_eff_end

gFieldEffectScript_LavaridgeGymWarp:: @ 82DBC76
	field_eff_loadfadedpal_callnative gFieldEffectObjectPaletteInfo2, FldEff_LavaridgeGymWarp
	field_eff_end

gFieldEffectScript_SweetScent:: @ 82DBC80
	field_eff_callnative FldEff_SweetScent
	field_eff_end

gFieldEffectScript_SandPillar:: @ 82DBC86
	field_eff_loadfadedpal_callnative gFieldEffectObjectPaletteInfo9, FldEff_SandPillar
	field_eff_end

gFieldEffectScript_Bubbles:: @ 82DBC90
	field_eff_loadfadedpal_callnative gFieldEffectObjectPaletteInfo0, FldEff_Bubbles
	field_eff_end

gFieldEffectScript_Sparkle:: @ 82DBC9A
	field_eff_loadfadedpal_callnative gFieldEffectObjectPaletteInfo3, FldEff_Sparkle
	field_eff_end

gFieldEffectScript_ShowSecretPowerCave:: @ 82DBCA4
	field_eff_loadfadedpal_callnative gFieldEffectObjectPaletteInfo7, FldEff_SecretPowerCave
	field_eff_end

gFieldEffectScript_ShowSecretPowerTree:: @ 82DBCAE
	field_eff_loadfadedpal_callnative gFieldEffectObjectPaletteInfo8, FldEff_SecretPowerTree
	field_eff_end

gFieldEffectScript_ShowSecretPowerShrub:: @ 82DBCB8
	field_eff_loadfadedpal_callnative gFieldEffectObjectPaletteInfo8, FldEff_SecretPowerShrub
	field_eff_end

gFieldEffectScript_ShowCutGrass:: @ 82DBCC2
	field_eff_loadfadedpal_callnative gFieldEffectObjectPaletteInfo6, FldEff_CutGrass
	field_eff_end

gFieldEffectScript_FieldMoveShowMonInit:: @ 82DBCCC
	field_eff_callnative FldEff_FieldMoveShowMonInit
	field_eff_end

gFieldEffectScript_UsePuzzleEffect:: @ 82DBCD2
	field_eff_callnative FldEff_UsePuzzleEffect
	field_eff_end

gFieldEffectScript_SecretBaseBootPC:: @ 82DBCD8
	field_eff_callnative FldEff_SecretBasePCTurnOn
	field_eff_end

gFieldEffectScript_HallOfFameRecord:: @ 82DBCDE
	field_eff_loadfadedpal gFieldEffectObjectPaletteInfo4
	field_eff_loadfadedpal_callnative gFieldEffectObjectPaletteInfo5, FldEff_HallOfFameRecord
	field_eff_end

gFieldEffectScript_UseTeleport:: @ 82DBCED
	field_eff_callnative FldEff_UseTeleport
	field_eff_end

gFieldEffectScript_Rayquaza:: @ 82DBCF3
	field_eff_callnative sub_80B8F98
	field_eff_end

gFieldEffectScript_Unknown65:: @ 82DBCF9
	field_eff_callnative sub_80B9ADC
	field_eff_end

gFieldEffectScript_MoveDeoxysRock:: @ 82DBCFF
	field_eff_callnative Fldeff_MoveDeoxysRock
	field_eff_end
