MossdeepCity_Mart_MapScripts:: @ 82223C7
	.byte 0

MossdeepCity_Mart_EventScript_2223C8:: @ 82223C8
	lock
	faceplayer
	message gUnknown_08272A21
	waitmessage
	pokemart MossdeepCity_Mart_Pokemart_2223E0
	msgbox gUnknown_08272A3F, MSGBOX_DEFAULT
	release
	end

	.align 2
MossdeepCity_Mart_Pokemart_2223E0: @ 82223E0
	.short ITEM_ULTRA_BALL
	.short ITEM_NET_BALL
	.short ITEM_DIVE_BALL
	.short ITEM_HYPER_POTION
	.short ITEM_FULL_HEAL
	.short ITEM_REVIVE
	.short ITEM_MAX_REPEL
	.short ITEM_X_ATTACK
	.short ITEM_X_DEFEND
	.short ITEM_NONE
	release
	end

MossdeepCity_Mart_EventScript_2223F6:: @ 82223F6
	msgbox MossdeepCity_Mart_Text_222411, MSGBOX_NPC
	end

MossdeepCity_Mart_EventScript_2223FF:: @ 82223FF
	msgbox MossdeepCity_Mart_Text_2224A0, MSGBOX_NPC
	end

MossdeepCity_Mart_EventScript_222408:: @ 8222408
	msgbox MossdeepCity_Mart_Text_2224FA, MSGBOX_NPC
	end

MossdeepCity_Mart_Text_222411: @ 8222411
	.string "REVIVE is fantastic!\p"
	.string "Give it to a fainted POKéMON,\n"
	.string "and the POKéMON will arise.\p"
	.string "But be careful, REVIVE doesn't restore\n"
	.string "the used-up PP of moves.$"

MossdeepCity_Mart_Text_2224A0: @ 82224A0
	.string "MAX REPEL keeps all weak POKéMON away.\p"
	.string "Out of all the REPEL sprays, it lasts\n"
	.string "the longest.$"

MossdeepCity_Mart_Text_2224FA: @ 82224FA
	.string "The NET and DIVE BALLS are rare POKé\n"
	.string "BALLS that are only made in MOSSDEEP.\p"
	.string "A NET BALL is effective against\n"
	.string "BUG-type and WATER-type POKéMON.\p"
	.string "A DIVE BALL works best on POKéMON\n"
	.string "at the bottom of the sea.$"

