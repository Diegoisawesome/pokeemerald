	.section script_data, "aw"

	.align 2
gMysteryEventScriptCmdTable:: @ 82DED2C
	.int MEScrCmd_nop
	.int MEScrCmd_checkcompat
	.int MEScrCmd_end
	.int MEScrCmd_setmsg
	.int MEScrCmd_setstatus
	.int MEScrCmd_runscript
	.int MEScrCmd_initramscript
	.int MEScrCmd_setenigmaberry
	.int MEScrCmd_giveribbon
	.int MEScrCmd_givenationaldex
	.int MEScrCmd_addrareword
	.int MEScrCmd_setrecordmixinggift
	.int MEScrCmd_givepokemon
	.int MEScrCmd_addtrainer
	.int MEScrCmd_enableresetrtc
	.int MEScrCmd_checksum
	.int MEScrCmd_crc
gMysteryEventScriptCmdTableEnd::
