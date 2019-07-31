LavaridgeTown_Mart_MapScripts:: @ 81FF9CD
	.byte 0

LavaridgeTown_Mart_EventScript_1FF9CE:: @ 81FF9CE
	lock
	faceplayer
	message gUnknown_08272A21
	waitmessage
	pokemart LavaridgeTown_Mart_Pokemart_1FF9E8
	msgbox gUnknown_08272A3F, MSGBOX_DEFAULT
	release
	end

	.align 2
LavaridgeTown_Mart_Pokemart_1FF9E8: @ 81FF9E8
	.short ITEM_GREAT_BALL
	.short ITEM_SUPER_POTION
	.short ITEM_ANTIDOTE
	.short ITEM_PARALYZE_HEAL
	.short ITEM_AWAKENING
	.short ITEM_BURN_HEAL
	.short ITEM_REVIVE
	.short ITEM_SUPER_REPEL
	.short ITEM_X_SPEED
	.short ITEM_NONE
	release
	end

LavaridgeTown_Mart_EventScript_1FF9FE:: @ 81FF9FE
	msgbox LavaridgeTown_Mart_Text_1FFA10, MSGBOX_NPC
	end

LavaridgeTown_Mart_EventScript_1FFA07:: @ 81FFA07
	msgbox LavaridgeTown_Mart_Text_1FFA83, MSGBOX_NPC
	end

LavaridgeTown_Mart_Text_1FFA10: @ 81FFA10
	.string "Use X SPEED to add to a POKéMON's\n"
	.string "SPEED in battle.\p"
	.string "That will help it get in the first\n"
	.string "strike--a decided advantage!$"

LavaridgeTown_Mart_Text_1FFA83: @ 81FFA83
	.string "On MT. CHIMNEY's peak, there's a local\n"
	.string "specialty that you can buy only there.\p"
	.string "Give it to a POKéMON--it will be elated.$"

