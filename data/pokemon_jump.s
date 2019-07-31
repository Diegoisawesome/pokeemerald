#include "constants/species.h"
	.include "asm/macros.inc"
	.include "constants/constants.inc"

	.section .rodata

	.align 2
gUnknown_082FB63C:: @ 82FB63C
	.short 0x001a, 0x001f, 0x0024, 0x0029, 0x002e, 0x0033, 0x0038, 0x003d

	.align 2
gUnknown_082FB64C:: @ 82FB64C
	.short 0x0000, 0x0001, 0x0001, 0x0002

	.align 2
gUnknown_082FB654:: @ 82FB654
	.short 0x005f, 0x0066, 0x00e4, 0x0105

	.align 2
gUnknown_082FB65C:: @ 82FB65C
	.byte 0xfd, 0xfa, 0xf8, 0xf6, 0xf3, 0xf1, 0xef, 0xed
	.byte 0xeb, 0xe9, 0xe7, 0xe5, 0xe4, 0xe3, 0xe2, 0xe2
	.byte 0xe2, 0xe4, 0xe5, 0xe6, 0xe7, 0xe9, 0xea, 0xec
	.byte 0xee, 0xef, 0xf1, 0xf3, 0xf5, 0xf8, 0xfa, 0xfc
	.byte 0xff, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
	.byte 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00

	.byte 0xfd, 0xfa, 0xf7, 0xf5, 0xf2, 0xf0, 0xee, 0xec
	.byte 0xea, 0xe8, 0xe6, 0xe4, 0xe3, 0xe2, 0xe2, 0xe4
	.byte 0xe6, 0xe8, 0xea, 0xec, 0xee, 0xf0, 0xf2, 0xf5
	.byte 0xf7, 0xfa, 0xfc, 0xff, 0x00, 0x00, 0x00, 0x00
	.byte 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
	.byte 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
	
	.byte 0xfd, 0xfa, 0xf7, 0xf5, 0xf3, 0xf1, 0xef, 0xed
	.byte 0xeb, 0xe9, 0xe7, 0xe5, 0xe4, 0xe3, 0xe2, 0xe2
	.byte 0xe2, 0xe2, 0xe3, 0xe3, 0xe4, 0xe4, 0xe5, 0xe5
	.byte 0xe6, 0xe7, 0xe8, 0xea, 0xec, 0xee, 0xf0, 0xf2
	.byte 0xf4, 0xf5, 0xf7, 0xfa, 0xfc, 0xff, 0x00, 0x00
	.byte 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00

	.align 2
gUnknown_082FB6EC:: @ 82FB6EC
	.int 0x00000000, 0x00000000, 0x00000032, 0x00000064
	.int 0x000000c8, 0x000001f4

	.align 2
gUnknown_082FB704:: @ 82FB704
	.short 0x008a, 0x008d, 0x008e, 0x008f, 0x0090, 0x0091, 0x0092, 0x0093

	.align 2
gUnknown_082FB714:: @ 82FB714
	.int 0x00001388, 0x00000001, 0x00001f40, 0x00000002
	.int 0x00002ee0, 0x00000003, 0x00003e80, 0x00000004
	.int 0x00004e20, 0x00000005

	.align 2
gPkmnJumpPal1:: @ 82FB73C
	.incbin "graphics/link_games/pkmnjump_pal1.gbapal"

	.align 2
gPkmnJumpPal2:: @ 82FB75C
	.incbin "graphics/link_games/pkmnjump_pal2.gbapal"

	.align 2
gPkmnJumpRopeGfx1:: @ 82FB77C
	.incbin "graphics/link_games/pkmnjump_rope1.4bpp.lz"

	.align 2
gPkmnJumpRopeGfx2:: @ 82FB89C
	.incbin "graphics/link_games/pkmnjump_rope2.4bpp.lz"

	.align 2
gPkmnJumpRopeGfx3:: @ 82FBA70
	.incbin "graphics/link_games/pkmnjump_rope3.4bpp.lz"

	.align 2
gPkmnJumpRopeGfx4:: @ 82FBBA0
	.incbin "graphics/link_games/pkmnjump_rope4.4bpp.lz"

	.align 2
gPkmnJumpStarGfx:: @ 82FBC9C
	.incbin "graphics/link_games/pkmnjump_star.4bpp.lz"

	.align 2
gUnknown_082FBE08:: @ 82FBE08
	obj_tiles gPkmnJumpRopeGfx1, 0x0600, 0x0005

	.align 2
	obj_tiles gPkmnJumpRopeGfx2, 0x0c00, 0x0006

	.align 2
	obj_tiles gPkmnJumpRopeGfx3, 0x0600, 0x0007

	.align 2
	obj_tiles gPkmnJumpRopeGfx4, 0x0600, 0x0008

	.align 2
	obj_tiles gPkmnJumpStarGfx, 0x0200, 0x000a

	.align 2
gUnknown_082FBE30:: @ 82FBE30
	obj_pal gPkmnJumpPal1, 0x0005

	.align 2
	obj_pal gPkmnJumpPal2, 0x0006

	.align 2
gUnknown_082FBE40:: @ 82FBE40
	spr_template 0x0000, 0x0000, gUnknown_082FBEC8, gDummySpriteAnimTable, NULL, gDummySpriteAffineAnimTable, SpriteCallbackDummy

gUnknown_082FBE58:: @ 82FBE58
	.short 0x0060, 0x0060, 0x0060, 0x0072, 0x0078, 0x0078, 0x0078, 0x0072
	.short 0x0060, 0x0060, 0x0046, 0x0050, 0x0060, 0x0072, 0x0078, 0x0080
	.short 0x0078, 0x0072, 0x0060, 0x0050, 0x0032, 0x0048, 0x0060, 0x0072
	.short 0x0080, 0x0088, 0x0080, 0x0072, 0x0060, 0x0048, 0x002a, 0x0048
	.short 0x0060, 0x0072, 0x0080, 0x0088, 0x0080, 0x0072, 0x0060, 0x0048

gUnknown_082FBEA8:: @ 82FBEA8
	.short 0x0010, 0x0028, 0x0048, 0x0068, 0x0088, 0x00a8, 0x00c8, 0x00e0

	.align 2
gUnknown_082FBEB8:: @ 82FBEB8
	.int gUnknown_082FBF78
	.int gUnknown_082FBF90
	.int gUnknown_082FBFA8
	.int gUnknown_082FBFC0

	.align 2
gUnknown_082FBEC8:: @ 82FBED0
	.byte 0x00, 0x00, 0x00, 0xc0, 0x00, 0x08, 0x00, 0x00

	.align 2
gUnknown_082FBED0:: @ 82FBED0
	.byte 0x00, 0x80, 0x00, 0x80, 0x00, 0x08, 0x00, 0x00

	.align 2
gUnknown_082FBED8:: @ 82FBED8
	.byte 0x00, 0x00, 0x00, 0x80, 0x00, 0x08, 0x00, 0x00

	.align 2
gUnknown_082FBEE0:: @ 82FBEE0
	.byte 0x00, 0x40, 0x00, 0x80, 0x00, 0x08, 0x00, 0x00

	.align 2
gUnknown_082FBEE8:: @ 82FBEE8
	.short 0x0000, 0x0001
	.short 0xffff, 0x0000

	.align 2
gUnknown_082FBEF0:: @ 82FBEF0
	.short 0x0008, 0x0001
	.short 0xffff, 0x0000

	.align 2
gUnknown_082FBEF8:: @ 82FBEF8
	.short 0x0010, 0x0001
	.short 0xffff, 0x0000

	.align 2
gUnknown_082FBF00:: @ 82FBF00
	.short 0x0018, 0x0001
	.short 0xffff, 0x0000

	.align 2
gUnknown_082FBF08:: @ 82FBF08
	.short 0x0020, 0x0001
	.short 0xffff, 0x0000

	.align 2
gUnknown_082FBF10:: @ 82FBF10
	.short 0x0028, 0x0001
	.short 0xffff, 0x0000

	.align 2
gUnknown_082FBF18:: @ 82FBF18
	.short 0x0000, 0x0001
	.short 0xffff, 0x0000

	.align 2
gUnknown_082FBF20:: @ 82FBF20
	.short 0x0010, 0x0001
	.short 0xffff, 0x0000

	.align 2
gUnknown_082FBF28:: @ 82FBF28
	.short 0x0020, 0x0001
	.short 0xffff, 0x0000

	.align 2
gUnknown_082FBF30:: @ 82FBF30
	.short 0x0030, 0x0001
	.short 0xffff, 0x0000

	.align 2
gUnknown_082FBF38:: @ 82FBF38
	.short 0x0040, 0x0001
	.short 0xffff, 0x0000

	.align 2
gUnknown_082FBF40:: @ 82FBF40
	.short 0x0050, 0x0001
	.short 0xffff, 0x0000

	.align 2
gUnknown_082FBF48:: @ 82FBF48
	.int gUnknown_082FBEE8
	.int gUnknown_082FBEF0
	.int gUnknown_082FBEF8
	.int gUnknown_082FBF00
	.int gUnknown_082FBF08
	.int gUnknown_082FBF10

	.align 2
gUnknown_082FBF60:: @ 82FBF60
	.int gUnknown_082FBF18
	.int gUnknown_082FBF20
	.int gUnknown_082FBF28
	.int gUnknown_082FBF30
	.int gUnknown_082FBF38
	.int gUnknown_082FBF40

	.align 2
gUnknown_082FBF78:: @ 82FBF78
	spr_template 0x0005, 0x0005, gUnknown_082FBED0, gUnknown_082FBF48, NULL, gDummySpriteAffineAnimTable, SpriteCallbackDummy

	.align 2
gUnknown_082FBF90:: @ 82FBF90
	spr_template 0x0006, 0x0005, gUnknown_082FBED8, gUnknown_082FBF60, NULL, gDummySpriteAffineAnimTable, SpriteCallbackDummy

	.align 2
gUnknown_082FBFA8:: @ 82FBFA8
	spr_template 0x0007, 0x0005, gUnknown_082FBEE0, gUnknown_082FBF48, NULL, gDummySpriteAffineAnimTable, SpriteCallbackDummy

	.align 2
gUnknown_082FBFC0:: @ 82FBFC0
	spr_template 0x0008, 0x0005, gUnknown_082FBEE0, gUnknown_082FBF48, NULL, gDummySpriteAffineAnimTable, SpriteCallbackDummy

	.align 2
gUnknown_082FBFD8:: @ 82FBFD8
	.byte 0x00, 0x00, 0x00, 0x40, 0x00, 0x04, 0x00, 0x00

	.align 2
gUnknown_082FBFE0:: @ 82FBFE0
	.short 0x0000, 0x0000
	.short 0xffff, 0x0000

	.align 2
gUnknown_082FBFE8:: @ 82FBFE8
	.short 0x0000, 0x0004
	.short 0x0004, 0x0004
	.short 0x0008, 0x0004
	.short 0x000c, 0x0004
	.short 0xfffd, 0x0001
	.short 0x0000, 0x0004
	.short 0xffff, 0x0000

	.align 2
gUnknown_082FC004:: @ 82FC004
	.int gUnknown_082FBFE0
	.int gUnknown_082FBFE8

	.align 2
gUnknown_082FC00C:: @ 82FC00C
	spr_template 0x000a, 0x0005, gUnknown_082FBFD8, gUnknown_082FC004, NULL, gDummySpriteAffineAnimTable, SpriteCallbackDummy

	.align 2
gPkmnJumpPal3:: @ 82FC024
	.incbin "graphics/link_games/pkmnjump_pal3.gbapal"

	.align 2
gPkmnJumpBgPal:: @ 82FC044
	.incbin "graphics/link_games/pkmnjump_bg.gbapal"

	.align 2
gPkmnJumpBgGfx:: @ 82FC064
	.incbin "graphics/link_games/pkmnjump_bg.4bpp.lz"

	.align 2
gPkmnJumpBgTilemap:: @ 82FC290
	.incbin "graphics/link_games/pkmnjump_bg.bin.lz"

	.align 2
gPkmnJumpVenusaurPal:: @ 82FC440
	.incbin "graphics/link_games/pkmnjump_venusaur.gbapal"

	.align 2
gPkmnJumpVenusaurGfx:: @ 82FC460
	.incbin "graphics/link_games/pkmnjump_venusaur.4bpp.lz"

	.align 2
gPkmnJumpVenusaurTilemap:: @ 82FCDB0
	.incbin "graphics/link_games/pkmnjump_venusaur.bin.lz"

	.align 2
gPkmnJumpResultsPal:: @ 82FD168
	.incbin "graphics/link_games/pkmnjump_results.gbapal"

	.align 2
gPkmnJumpResultsGfx:: @ 82FD188
	.incbin "graphics/link_games/pkmnjump_results.4bpp.lz"

	.align 2
gPkmnJumpResultsTilemap:: @ 82FDC38
	.incbin "graphics/link_games/pkmnjump_results.bin.lz"

	.align 2
gUnknown_082FE164:: @ 82FE164 struct BgTemplate
	.int 0x000001b0, 0x000025e6, 0x000016c9, 0x000031df

	.align 2
gUnknown_082FE174:: @ 82FE174
	window_template 0x00, 0x13, 0x00, 0x06, 0x02, 0x02, 0x0013
	window_template 0x00, 0x08, 0x00, 0x06, 0x02, 0x02, 0x001f
	null_window_template

	.align 2
gUnknown_082FE18C:: @ 82FE18C
	.int 0x00000000, sub_802D150
	.int 0x00000001, sub_802D2E4
	.int 0x00000002, sub_802D350
	.int 0x00000003, sub_802D3BC
	.int 0x00000004, sub_802D448
	.int 0x00000005, sub_802D4F4
	.int 0x00000006, sub_802D598
	.int 0x00000007, sub_802D5E4
	.int 0x00000009, sub_802D72C
	.int 0x00000008, sub_802D688

	.align 2
gUnknown_082FE1DC:: @ 82FE1DC
	.byte 0x00, 0x02, 0x03

gUnknown_082FE1DF:: @ 82FE1DF
	.byte 0x02, 0x02, 0x00, 0x00, 0x01, 0x01, 0x01, 0x00
	.byte 0x00, 0x02, 0x00, 0x00, 0x00

	.align 2
gUnknown_082FE1EC:: @ 82FE1EC
	obj_tiles gUnknown_082FF1F8, 0x0000, 0x0320

	.align 2
gUnknown_082FE1F4:: @ 82FE1F4
	obj_pal gUnknown_082FF1D8, 0x0320

	.align 2
gUnknown_082FE1FC:: @ 82FE1FC
	.short 0x0006, 0x0008, 0x0010, 0x0008

	.align 2
gUnknown_082FE204:: @ 82FE204
	.short 0x0006, 0x0008, 0x000b, 0x0006, 0x0010, 0x0008

	.align 2
gUnknown_082FE210:: @ 82FE210
	.short 0x0002, 0x0006, 0x0006, 0x0008, 0x0010, 0x0008, 0x0014, 0x0006

	.align 2
gUnknown_082FE220:: @ 82FE220
	.short 0x0002, 0x0006, 0x0006, 0x0008, 0x000b, 0x0006
	.short 0x0010, 0x0008, 0x0014, 0x0006

	.align 2
gUnknown_082FE234:: @ 82FE234
	.int gUnknown_082FE1FC
	.int gUnknown_082FE204
	.int gUnknown_082FE210
	.int gUnknown_082FE220

	.align 2
gUnknown_082FE244:: @ 82FE244
	.short 0x0058, 0x0098

gUnknown_082FE248:: @ 82FE248
	.short 0x0058, 0x0078, 0x0098

gUnknown_082FE24E:: @ 82FE24E
	.short 0x0038, 0x0058, 0x0098, 0x00b8

gUnknown_082FE256:: @ 82FE256
	.short 0x0038, 0x0058, 0x0078, 0x0098, 0x00b8

	.align 2
gUnknown_082FE260:: @ 82FE260
	.int gUnknown_082FE244
	.int gUnknown_082FE248
	.int gUnknown_082FE24E
	.int gUnknown_082FE256

	.align 2
gUnknown_082FE270:: @ 82FE270
	.int 0x1c010100, 0x00010f09

	.align 2
gUnknown_082FE278:: @ 82FE278
	.int gText_JumpsInARow
	.int gText_BestScore2
	.int gText_ExcellentsInARow

	.align 2
gPkmnJump321StartPal1:: @ 82FE284
	.incbin "graphics/link_games/pkmnjump_321start1.gbapal"

	.align 2
gPkmnJump321StartGfx1:: @ 82FE2A4
	.incbin "graphics/link_games/pkmnjump_321start1.4bpp.lz"

	.align 2
gUnknown_082FE6C8:: @ 82FE6C8
	obj_tiles gPkmnJump321StartGfx1, 0x0c00, 0x2000
	null_obj_tiles

	.align 2
gUnknown_082FE6D8:: @ 82FE6D8
	obj_pal gPkmnJump321StartPal1, 0x2000
    null_obj_pal

	.align 2
gUnknown_082FE6E8:: @ 82FE6E8
	.short 0x0000, 0x0000
	.short 0xffff, 0x0000

	.align 2
gUnknown_082FE6F0:: @ 82FE6F0
	.short 0x0010, 0x0000
	.short 0xffff, 0x0000

	.align 2
gUnknown_082FE6F8:: @ 82FE6F8
	.short 0x0020, 0x0000
	.short 0xffff, 0x0000

	.align 2
gUnknown_082FE700:: @ 82FE700
	.short 0x0040, 0x0000
	.short 0xffff, 0x0000

	.align 2
gUnknown_082FE708:: @ 82FE708
	.short 0x0030, 0x0000
	.short 0xffff, 0x0000

	.align 2
gUnknown_082FE710:: @ 82FE710
	.short 0x0050, 0x0000
	.short 0xffff, 0x0000

	.align 2
gUnknown_082FE718:: @ 82FE718
	.int gUnknown_082FE6E8
	.int gUnknown_082FE6F0
	.int gUnknown_082FE6F8
	.int gUnknown_082FE700
	.int gUnknown_082FE708
	.int gUnknown_082FE710

	.align 2
gUnknown_082FE730:: @ 82FE730
	spr_template 0x2000, 0x2000, gUnknown_08524914, gUnknown_082FE718, NULL, gDummySpriteAffineAnimTable, SpriteCallbackDummy

	.align 2
gUnknown_082FE748:: @ 82FE748
	.int sub_802E83C
	.int sub_802E8C8
	.int sub_802EA50
	.int sub_802EAB0

	.align 2
gPkmnJump321StartPal2:: @ 82FE758
	.incbin "graphics/link_games/pkmnjump_321start2.gbapal"

	.align 2
gPkmnJump321StartGfx2:: @ 82FE778
	.incbin "graphics/link_games/pkmnjump_321start2.4bpp.lz"

	.align 2
gUnknown_082FEBCC:: @ 82FEBCC
	obj_tiles gPkmnJump321StartGfx2, 0x0e00, 0x0000

	.align 2
gUnknown_082FEBD4:: @ 82FEBD4
	obj_pal gPkmnJump321StartPal2, 0x0000

	.align 2
gUnknown_082FEBDC:: @ 82FEBDC
	.byte 0x00, 0x03, 0x00, 0x80, 0x00, 0x00, 0x00, 0x00

	.align 2
gUnknown_082FEBE4:: @ 82FEBE4
	.byte 0x00, 0x40, 0x00, 0xc0, 0x00, 0x00, 0x00, 0x00

	.align 2
gUnknown_082FEBEC:: @ 82FEBEC
	.short 0x0000, 0x0001
	.short 0xffff, 0x0000

	.align 2
gUnknown_082FEBF4:: @ 82FEBF4
	.short 0x0010, 0x0001
	.short 0xffff, 0x0000

	.align 2
gUnknown_082FEBFC:: @ 82FEBFC
	.short 0x0020, 0x0001
	.short 0xffff, 0x0000

	.align 2
gUnknown_082FEC04:: @ 82FEC04
	.int gUnknown_082FEBEC
	.int gUnknown_082FEBF4
	.int gUnknown_082FEBFC

	.align 2
gUnknown_082FEC10:: @ 82FEC10
	.short 0x0030, 0x0001
	.short 0xffff, 0x0000

	.align 2
gUnknown_082FEC18:: @ 82FEC18
	.short 0x0050, 0x0001
	.short 0xffff, 0x0000

	.align 2
gUnknown_082FEC20:: @ 82FEC20
	.int gUnknown_082FEC10
	.int gUnknown_082FEC18

	.align 2
gUnknown_082FEC28:: @ 82FEC28
	.short 0x0100, 0x0100
	.short 0x0000, 0x0000
	.short 0x7fff, 0x0000
	.short 0x0000, 0x0000

	.align 2
gUnknown_082FEC38:: @ 82FEC38
	.short 0x0100, 0x0100
	.short 0x0000, 0x0000
	.short 0x0010, 0xfff0
	.short 0x0800, 0x0000
	.short 0x7fff, 0x0000
	.short 0x0000, 0x0000

	.align 2
gUnknown_082FEC50:: @ 82FEC50
	.short 0xffee, 0x0012
	.short 0x0800, 0x0000
	.short 0x7fff, 0x0000
	.short 0x0000, 0x0000

	.align 2
gUnknown_082FEC60:: @ 82FEC60
	.short 0x0006, 0xfffa
	.short 0x0800, 0x0000
	.short 0xfffc, 0x0004
	.short 0x0800, 0x0000
	.short 0x0100, 0x0100
	.short 0x0000, 0x0000
	.short 0x7fff, 0x0000
	.short 0x0000, 0x0000

	.align 2
gUnknown_082FEC80:: @ 82FEC80
	.int gUnknown_082FEC28
	.int gUnknown_082FEC38
	.int gUnknown_082FEC50
	.int gUnknown_082FEC60

gUnknown_082FEC90:: @ 82FEC90
	spr_template 0x0000, 0x0000, gUnknown_082FEBDC, gUnknown_082FEC04, NULL, gUnknown_082FEC80, SpriteCallbackDummy

gUnknown_082FECA8:: @ 82FECA8
	spr_template 0x0000, 0x0000, gUnknown_082FEBE4, gUnknown_082FEC20, NULL, gDummySpriteAffineAnimTable, SpriteCallbackDummy
