	.include "asm/macros.inc"
	.include "constants/constants.inc"

	.section .rodata

	.align 2
gUnknown_082F325C:: @ 82F325C
	.byte 0x01, 0x02, 0x04, 0x08, 0x10, 0x20, 0x40, 0x80

	.align 2
gUnknown_082F3264:: @ 82F3264
	.byte 0x00, 0x01, 0x02, 0x03, 0x05, 0x00, 0x00, 0x00

	.align 2
gUnknown_082F326C:: @ 82F326C
	.byte 0x04, 0x01, 0x00, 0xff, 0x00, 0x00, 0x00, 0x04
	.byte 0x02, 0x00, 0xff, 0x00, 0x00, 0x00, 0x04, 0x02
	.byte 0x00, 0xfe, 0x00, 0x00, 0x00, 0x06, 0x03, 0x01
	.byte 0xff, 0xfd, 0xff, 0x00, 0x06, 0x04, 0x01, 0xfe
	.byte 0xfc, 0xfe, 0x00, 0x00

	.align 2
gUnknown_082F3290:: @ 82F3290
	.byte 0x03, 0x02, 0x01, 0x00, 0x03, 0x03, 0x01, 0x00
	.byte 0x03, 0x03, 0x02, 0x00, 0x03, 0x04, 0x02, 0x00
	.byte 0x03, 0x05, 0x03, 0x00

	.align 2
gUnknown_082F32A4:: @ 82F32A4
	.int gText_ReadyToBerryCrush
	.int gText_WaitForAllChooseBerry
	.int gText_EndedWithXUnitsPowder
	.int gText_RecordingGameResults
	.int gText_PlayBerryCrushAgain
	.int gText_YouHaveNoBerries
	.int gText_MemberDroppedOut
	.int gText_TimesUpNoGoodPowder
	.int gText_CommunicationStandby2

	.align 2
gUnknown_082F32C8:: @ 82F32C8 struct BgTemplate
	.int 0x000000F8

	.align 2
gUnknown_082F32CC:: @ 82F32CC struct BgTemplate? not sure
	.byte 0xd1, 0x14, 0x00, 0x00, 0xc2, 0x20, 0x00, 0x00
	.byte 0xb3, 0x30, 0x00, 0x00

	.align 2
gUnknown_082F32D8:: @ 82F32D8
	.byte 0x01, 0x02, 0x03

gUnknown_082F32DB:: @ 82F32DB
	.byte 0x00, 0x01, 0x02

gUnknown_082F32DE:: @ 82F32DE
	.byte 0x00, 0x03, 0x04

gUnknown_082F32E1:: @ 82F32E1
	.byte 0x01, 0x08, 0x09
	.byte 0x01, 0x06, 0x07

gUnknown_082F32E7:: @ 82F32E7
	.byte 0x01, 0x04, 0x05

	.align 2
gUnknown_082F32EC:: @ 82F32EC
	window_template 0x00, 0x03, 0x04, 0x18, 0x0d, 0x0f, 0x0001

	.align 2
gUnknown_082F32F4:: @ 82F32F4
	window_template 0x00, 0x00, 0x00, 0x09, 0x02, 0x08, 0x03ed
	window_template 0x00, 0x00, 0x03, 0x09, 0x02, 0x08, 0x03db
	window_template 0x00, 0x00, 0x06, 0x09, 0x02, 0x08, 0x03c9
	window_template 0x00, 0x15, 0x03, 0x09, 0x02, 0x08, 0x03b7
	window_template 0x00, 0x15, 0x06, 0x09, 0x02, 0x08, 0x03a5
	null_window_template

	window_template 0x00, 0x05, 0x02, 0x14, 0x10, 0x0f, 0x0001
	window_template 0x00, 0x05, 0x02, 0x14, 0x10, 0x0f, 0x0001
	window_template 0x00, 0x04, 0x02, 0x16, 0x10, 0x0f, 0x0001
	null_window_template

	.align 2
gUnknown_082F3344:: @ 82F3344
	.byte 0x06, 0x08, 0x09, 0x0b, 0x0c, 0x0e, 0x0f, 0x10

	.align 2
gUnknown_082F334C:: @ 82F334C
	.byte 0x80, 0xf0, 0xfa, 0x02, 0x40, 0x78, 0x7d, 0x01
	.byte 0x20, 0xbc, 0xbe, 0x00, 0x10, 0x5e, 0x5f, 0x00
	.byte 0x08, 0xaf, 0x2f, 0x00, 0x84, 0xd7, 0x17, 0x00
	.byte 0xc2, 0xeb, 0x0b, 0x00, 0xe1, 0xf5, 0x05, 0x00

	.align 2
gBerryCrushGrinderBasePal:: @ 82F336C
	.incbin "graphics/link_games/berrycrush_grinder_base.gbapal"

	.align 2
gBerryCrushMiscSpritesPal:: @ 82F338C
	.incbin "graphics/link_games/berrycrush_misc.gbapal"

	.align 2
gBerryCrushTimerDigitsPal:: @ 82F33AC
	.incbin "graphics/link_games/berrycrush_timerdigits.gbapal"

	.align 2
gBerryCrushGrinderBaseGfx:: @ 82F33CC
	.incbin "graphics/link_games/berrycrush_grinder_base.4bpp.lz"

	.align 2
gBerryCrushBtnPressGfx:: @ 82F36F8
	.incbin "graphics/link_games/berrycrush_btnpress.4bpp.lz"

	.align 2
gBerryCrushSparkleGfx:: @ 82F3A74
	.incbin "graphics/link_games/berrycrush_sparkle.4bpp.lz"

	.align 2
gBerryCrushTimerDigitsGfx:: @ 82F3BC0
	.incbin "graphics/link_games/berrycrush_timerdigits.4bpp.lz"

	.align 2
gBerryCrushGrinderTopTilemap:: @ 82F3C8C
	.incbin "graphics/link_games/berrycrush_grinder_top.bin.lz"

	.align 2
gBerryCrushContainerCapTilemap:: @ 82F3DBC
	.incbin "graphics/link_games/berrycrush_container_cap.bin.lz"

	.align 2
gBerryCrushBackgroundTilemap:: @ 82F3F54
	.incbin "graphics/link_games/berrycrush_background.bin.lz"

	.align 2
gUnknown_082F417C:: @ 82F417C
	.byte 0x01, 0x03, 0x00, 0x00, 0x00, 0x00, 0x01, 0x03
	.byte 0x00, 0x00, 0x01, 0x03, 0x02, 0x04, 0x00, 0x00
	.byte 0x01, 0x03, 0x02, 0x04

	.align 2
gUnknown_082F4190:: @ 82F4190
	.byte 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xf0, 0xff
	.byte 0x00, 0x00, 0x00, 0x00, 0x01, 0x00, 0x03, 0x00
	.byte 0xe4, 0xff, 0xfc, 0xff, 0xe8, 0xff, 0x10, 0x00
	.byte 0x02, 0x00, 0x06, 0x00, 0xf0, 0xff, 0x14, 0x00
	.byte 0xf8, 0xff, 0x10, 0x00, 0x03, 0x14, 0x03, 0x00
	.byte 0x1c, 0x00, 0xfc, 0xff, 0x20, 0x00, 0xf8, 0xff
	.byte 0x04, 0x14, 0x06, 0x00, 0x10, 0x00, 0x14, 0x00
	.byte 0x10, 0x00, 0xf8, 0xff

	.align 2
gUnknown_082F41CC:: @ 82F41CC
	.byte 0x00, 0x00
	.byte 0xff, 0x00
	.byte 0x01, 0x01

gUnknown_082F41D2::
	.byte 0x00, 0x00
	.byte 0xf0, 0xfc
	.byte 0x10, 0xfc
	.byte 0xf8, 0xfe
	.byte 0x08, 0xfe
	.byte 0xe8, 0xf8
	.byte 0x18, 0xf8
	.byte 0xe0, 0xf4
	.byte 0x20, 0xf4
	.byte 0xd8, 0xf0
	.byte 0x28, 0xf0

	.align 2
gUnknown_082F41E8:: @ 82F41E8
	.short 0x0005, 0x0006, 0x0007, 0x0008, 0x0009, 0x0000

	.align 2
gUnknown_082F41F4:: @ 82F41F4
	.int gBerryCrushGrinderBaseGfx
	.short 0x0800, 0x0001

	.int gBerryCrushBtnPressGfx
	.short 0x0e00, 0x0002

	.int gBerryCrushSparkleGfx
	.short 0x0700, 0x0003

	.align 2
gUnknown_082F420C:: @ 82F420C
	.int gBerryCrushTimerDigitsGfx
	.short 0x02c0, 0x0004

	.int NULL
	.short 0x0000, 0x0000

	.align 2
gUnknown_082F421C:: @ 82F421C
	.int gBerryCrushGrinderBasePal
	.short 0x0001

	.align 2
	.int gBerryCrushMiscSpritesPal
	.short 0x0002

	.align 2
gUnknown_082F422C:: @ 82F422C
	.align 2
	.int gBerryCrushTimerDigitsPal
	.short 0x0004

	.align 2
	.int NULL
	.short 0x0000

	.align 2
gUnknown_082F423C:: @ 82F423C
	.short 0x0000, 0x0000, 0xffff, 0x0000

	.align 2
gUnknown_082F4244:: @ 82F4244
	.short 0x0000, 0x0004, 0x0010, 0x0004, 0x0020, 0x0004, 0xffff, 0x0000

	.align 2
gUnknown_082F4254:: @ 82F4254
	.short 0x0030, 0x0002, 0x0040, 0x0002, 0x0050, 0x0002, 0x0060, 0x0002
	.short 0xffff, 0x0000

	.align 2
gUnknown_082F4268:: @ 82F4268
	.short 0x0000, 0x0002, 0x0004, 0x0002, 0x0008, 0x0002, 0x000c, 0x0002
	.short 0x0010, 0x0002, 0x0014, 0x0002, 0xfffe, 0x0000

	.align 2
gUnknown_082F4284:: @ 82F4284
	.short 0x0018, 0x0004, 0x001c, 0x0004, 0x0020, 0x0004, 0x0024, 0x0004
	.short 0x0028, 0x0004, 0x002c, 0x0004, 0x0030, 0x0004, 0x0034, 0x0004
	.short 0xfffe, 0x0000

	.align 2
gUnknown_082F42A8:: @ 82F42A8
	.short 0x0014, 0x0000, 0xffff, 0x0000

	.align 2
gUnknown_082F42B0:: @ 82F42B0
	.short 0x0000, 0x0000, 0xffff, 0x0000

	.align 2
gUnknown_082F42B8:: @ 82F42B8
	.short 0x0100, 0x0100, 0x0000, 0x0000, 0x0000, 0x0000, 0x0102, 0x0000
	.short 0x7ffe, 0x0001, 0x0000, 0x0000

	.align 2
gUnknown_082F42D0:: @ 82F42D0
	.short 0x0100, 0x0100, 0x0000, 0x0000, 0x0000, 0x0000, 0x01fe, 0x0000
	.short 0x7ffe, 0x0001, 0x0000, 0x0000

	.align 2
gUnknown_082F42E8:: @ 82F42E8
	.int gUnknown_082F423C

	.align 2
gUnknown_082F42EC:: @ 82F42EC
	.int gUnknown_082F4244
	.int gUnknown_082F4254

	.align 2
gUnknown_082F42F4:: @ 82F42F4
	.int gUnknown_082F4268
	.int gUnknown_082F4284

	.align 2
gUnknown_082F42FC:: @ 82F42FC
	.int gUnknown_082F42A8

	.align 2
gUnknown_082F4300:: @ 82F4300
	.int gUnknown_082F42B0

	.align 2
gUnknown_082F4304:: @ 82F4304
	.int gUnknown_082F42B8
	.int gUnknown_082F42D0

	.align 2
gUnknown_082F430C:: @ 82F430C
	spr_template 0x0001, 0x0001, gUnknown_0852491C, gUnknown_082F42E8, NULL, gDummySpriteAffineAnimTable, SpriteCallbackDummy

	.align 2
gUnknown_082F4324:: @ 82F4324
	spr_template 0x0002, 0x0002, gUnknown_08524914, gUnknown_082F42EC, NULL, gDummySpriteAffineAnimTable, sub_8022A20

	.align 2
gUnknown_082F433C:: @ 82F433C
	spr_template 0x0003, 0x0002, gUnknown_0852490C, gUnknown_082F42F4, NULL, gDummySpriteAffineAnimTable, SpriteCallbackDummy

	.align 2
gUnknown_082F4354:: @ 82F4354
	spr_template 0x0004, 0x0004, gUnknown_08524944, gUnknown_082F42FC, NULL, gDummySpriteAffineAnimTable, SpriteCallbackDummy

	.align 2
gUnknown_082F436C:: @ 82F436C
	spr_template 0x0005, 0x0005, gUnknown_085249D4, gUnknown_082F4300, NULL, gUnknown_082F4304, SpriteCallbackDummy

	.align 2
gUnknown_082F4384:: @ 82F4384
	.byte 0x09, 0x02, 0x08, 0x00, 0x9c, 0x00, 0x00, 0x00
	.int gUnknown_082F420C
	.int gUnknown_082F422C

	.byte 0x08, 0x02, 0x08, 0x00, 0xb4, 0x00, 0x00, 0x00
	.int gUnknown_082F420C
	.int gUnknown_082F422C

	.byte 0x08, 0x02, 0x08, 0x00, 0xcc, 0x00, 0x00, 0x00
	.int gUnknown_082F420C
	.int gUnknown_082F422C

	.align 2
gUnknown_082F43B4:: @ 82F43B4
	.int gText_SpaceTimes2
	.int gText_XDotY
	.int gText_Var1Berry
	.int gText_NeatnessRankings
	.int gText_CoopRankings
	.int gText_PressingPowerRankings

	.align 2
gUnknown_082F43CC:: @ 82F43CC
	.int NULL
	.int sub_8022C58
	.int sub_8022CB0
	.int sub_8022D14
	.int sub_8022E1C
	.int sub_8022E3C
	.int sub_8022E5C
	.int sub_8022EAC
	.int sub_8022F04
	.int sub_8022F1C
	.int sub_8023070
	.int sub_80231B8
	.int sub_80232EC
	.int sub_80238F0
	.int sub_8023998
	.int sub_8023A30
	.int sub_8023BC0
	.int sub_8023CAC
	.int sub_8024048
	.int sub_8024134
	.int sub_8024228
	.int sub_80242E0
	.int sub_80243BC
	.int sub_8024444
	.int sub_8024508
	.int sub_8024568

	.align 2
gUnknown_082F4434:: @ 82F4434
	.byte 0x02, 0x04, 0x06, 0x07, 0x03, 0x05, 0x08, 0x0b
	.byte 0x03, 0x07, 0x0b, 0x0f, 0x04, 0x08, 0x0c, 0x11

gUnknown_082F4444:: @ 82F4444
	.byte 0x05, 0x07, 0x09, 0x0c

gUnknown_082F4448:: @ 82F4448
	.byte 0x03, 0x07, 0x0f, 0x1f
