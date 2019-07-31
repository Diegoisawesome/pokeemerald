	.include "asm/macros.inc"
	.include "constants/constants.inc"

	.section .rodata



.align 2
gUnref_82EC784:: @ 82EC784
    .int 0x00000000
    .int 0x00000000
    .int 0x04000008
    .int 0x0400000A
    .int 0x0400000C
    .int 0x0400000E
    .int 0x04000010
    .int 0x04000014
    .int 0x04000018
    .int 0x0400001C
    .int 0x04000012
    .int 0x04000016
    .int 0x0400001A
    .int 0x0400001E
    .int 0x02000100
    .int 0x08000400

gOverworldBackgroundLayerFlags:: @ 82EC7C4
	.short 0x0100 /* BLDCNT_TGT2_BG0 */
	.short 0x0200 /* BLDCNT_TGT2_BG1 */
	.short 0x0400 /* BLDCNT_TGT2_BG2 */
	.short 0x0800 /* BLDCNT_TGT2_BG3 */

gUnknown_82EC7CC:: @ 82EC7CC
	.short 0x0001
	.short 0x0002
	.short 0x0004
	.short 0x0008
