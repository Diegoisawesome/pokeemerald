RustboroCity_Mart_MapScripts:: @ 8214F05
	.byte 0

RustboroCity_Mart_EventScript_214F06:: @ 8214F06
	lock
	faceplayer
	message gUnknown_08272A21
	waitmessage
	goto_if_unset FLAG_MET_DEVON_EMPLOYEE, RustboroCity_Mart_EventScript_214F21
	goto_if_set FLAG_MET_DEVON_EMPLOYEE, RustboroCity_Mart_EventScript_214F48
	end

RustboroCity_Mart_EventScript_214F21:: @ 8214F21
	pokemart RustboroCity_Mart_Pokemart_214F30
	msgbox gUnknown_08272A3F, MSGBOX_DEFAULT
	release
	end

RustboroCity_Mart_Pokemart_214F30: @ 8214F30
	.short ITEM_POKE_BALL
	.short ITEM_POTION
	.short ITEM_SUPER_POTION
	.short ITEM_ANTIDOTE
	.short ITEM_PARALYZE_HEAL
	.short ITEM_ESCAPE_ROPE
	.short ITEM_REPEL
	.short ITEM_X_SPEED
	.short ITEM_X_ATTACK
	.short ITEM_X_DEFEND
	.short ITEM_NONE
	release
	end

RustboroCity_Mart_EventScript_214F48:: @ 8214F48
	pokemart RustboroCity_Mart_Pokemart_214F58
	msgbox gUnknown_08272A3F, MSGBOX_DEFAULT
	release
	end

	.align 2
RustboroCity_Mart_Pokemart_214F58: @ 8214F58
	.short ITEM_POKE_BALL
	.short ITEM_TIMER_BALL
	.short ITEM_REPEAT_BALL
	.short ITEM_POTION
	.short ITEM_SUPER_POTION
	.short ITEM_ANTIDOTE
	.short ITEM_PARALYZE_HEAL
	.short ITEM_ESCAPE_ROPE
	.short ITEM_REPEL
	.short ITEM_X_SPEED
	.short ITEM_X_ATTACK
	.short ITEM_X_DEFEND
	.short ITEM_NONE
	release
	end

RustboroCity_Mart_EventScript_214F74:: @ 8214F74
	msgbox RustboroCity_Mart_Text_214F8F, MSGBOX_NPC
	end

RustboroCity_Mart_EventScript_214F7D:: @ 8214F7D
	msgbox RustboroCity_Mart_Text_214FF1, MSGBOX_NPC
	end

RustboroCity_Mart_EventScript_214F86:: @ 8214F86
	msgbox RustboroCity_Mart_Text_21505C, MSGBOX_NPC
	end

RustboroCity_Mart_Text_214F8F: @ 8214F8F
	.string "I'm buying some PARLYZ HEALS and\n"
	.string "ANTIDOTES.\p"
	.string "Just in case I run into SHROOMISH\n"
	.string "in PETALBURG WOODS.$"

RustboroCity_Mart_Text_214FF1: @ 8214FF1
	.string "My POKéMON evolved.\n"
	.string "It has a lot of HP now.\p"
	.string "I should buy SUPER POTIONS for it\n"
	.string "instead of ordinary POTIONS.$"

RustboroCity_Mart_Text_21505C: @ 821505C
	.string "I'm getting an ESCAPE ROPE just in\n"
	.string "case I get lost in a cave.\p"
	.string "I just need to use it to get back to\n"
	.string "the entrance.$"

