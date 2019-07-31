PetalburgCity_Mart_MapScripts:: @ 8207D68
	.byte 0

PetalburgCity_Mart_EventScript_207D69:: @ 8207D69
	lock
	faceplayer
	message gUnknown_08272A21
	waitmessage
	goto_if_set FLAG_PETALBURG_MART_EXPANDED_ITEMS, PetalburgCity_Mart_EventScript_207DA6
	pokemart PetalburgCity_Mart_Pokemart_207D8C
	msgbox gUnknown_08272A3F, MSGBOX_DEFAULT
	release
	end

	.align 2
PetalburgCity_Mart_Pokemart_207D8C: @ 8207D8C
	.short ITEM_POKE_BALL
	.short ITEM_POTION
	.short ITEM_ANTIDOTE
	.short ITEM_PARALYZE_HEAL
	.short ITEM_AWAKENING
	.short ITEM_ESCAPE_ROPE
	.short ITEM_REPEL
	.short ITEM_X_SPEED
	.short ITEM_X_ATTACK
	.short ITEM_X_DEFEND
	.short ITEM_ORANGE_MAIL
	.short ITEM_NONE
	release
	end

PetalburgCity_Mart_EventScript_207DA6:: @ 8207DA6
	pokemart PetalburgCity_Mart_Pokemart_207DB8
	msgbox gUnknown_08272A3F, MSGBOX_DEFAULT
	release
	end

	.align 2
PetalburgCity_Mart_Pokemart_207DB8: @ 8207DB8
	.short ITEM_POKE_BALL
	.short ITEM_GREAT_BALL
	.short ITEM_POTION
	.short ITEM_SUPER_POTION
	.short ITEM_ANTIDOTE
	.short ITEM_PARALYZE_HEAL
	.short ITEM_AWAKENING
	.short ITEM_ESCAPE_ROPE
	.short ITEM_REPEL
	.short ITEM_X_SPEED
	.short ITEM_X_ATTACK
	.short ITEM_X_DEFEND
	.short ITEM_ORANGE_MAIL
	.short ITEM_NONE
	release
	end

PetalburgCity_Mart_EventScript_207DD6:: @ 8207DD6
	msgbox PetalburgCity_Mart_Text_207DF1, MSGBOX_NPC
	end

PetalburgCity_Mart_EventScript_207DDF:: @ 8207DDF
	msgbox PetalburgCity_Mart_Text_207E60, MSGBOX_NPC
	end

PetalburgCity_Mart_EventScript_207DE8:: @ 8207DE8
	msgbox PetalburgCity_Mart_Text_207EB0, MSGBOX_NPC
	end

PetalburgCity_Mart_Text_207DF1: @ 8207DF1
	.string "Even if a POKéMON is weak now,\n"
	.string "it will grow stronger.\p"
	.string "The most important thing is love!\n"
	.string "Love for your POKéMON!$"

PetalburgCity_Mart_Text_207E60: @ 8207E60
	.string "Do you use REPEL?\n"
	.string "It keeps POKéMON away, so it's\l"
	.string "useful when you're in a hurry.$"

PetalburgCity_Mart_Text_207EB0: @ 8207EB0
	.string "Do you have any ANTIDOTES with\n"
	.string "you?\p"
	.string "If you walk around with a poisoned\n"
	.string "POKéMON, it will lose HP until it faints.\l"
	.string "Take some ANTIDOTES with you.$"

