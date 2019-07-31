VerdanturfTown_Mart_MapScripts:: @ 8202586
	.byte 0

VerdanturfTown_Mart_EventScript_202587:: @ 8202587
	lock
	faceplayer
	message gUnknown_08272A21
	waitmessage
	pokemart VerdanturfTown_Mart_Pokemart_2025A0
	msgbox gUnknown_08272A3F, MSGBOX_DEFAULT
	release
	end

	.align 2
VerdanturfTown_Mart_Pokemart_2025A0: @ 82025A0
	.short ITEM_GREAT_BALL
	.short ITEM_NEST_BALL
	.short ITEM_SUPER_POTION
	.short ITEM_ANTIDOTE
	.short ITEM_PARALYZE_HEAL
	.short ITEM_AWAKENING
	.short ITEM_BURN_HEAL
	.short ITEM_ICE_HEAL
	.short ITEM_REPEL
	.short ITEM_X_SPECIAL
	.short ITEM_FLUFFY_TAIL
	.short ITEM_NONE
	release
	end

VerdanturfTown_Mart_EventScript_2025BA:: @ 82025BA
	msgbox VerdanturfTown_Mart_Text_2025D5, MSGBOX_NPC
	end

VerdanturfTown_Mart_EventScript_2025C3:: @ 82025C3
	msgbox VerdanturfTown_Mart_Text_20264C, MSGBOX_NPC
	end

VerdanturfTown_Mart_EventScript_2025CC:: @ 82025CC
	msgbox VerdanturfTown_Mart_Text_2026C9, MSGBOX_NPC
	end

VerdanturfTown_Mart_Text_2025D5: @ 82025D5
	.string "For any POKéMON match, X SPECIAL\n"
	.string "is crucial.\p"
	.string "It jacks up the power of some moves\n"
	.string "even though it's only for one battle.$"

VerdanturfTown_Mart_Text_20264C: @ 820264C
	.string "They don't seem to sell any winning\n"
	.string "strategy guides for the BATTLE TENT…\p"
	.string "It seems one must rely on one's\n"
	.string "own wits after all…$"

VerdanturfTown_Mart_Text_2026C9: @ 82026C9
	.string "The NEST BALL works better on\n"
	.string "weakened POKéMON.\p"
	.string "VERDANTURF is the only place you can\n"
	.string "buy it.$"

