LilycoveCity_DepartmentStore_2F_MapScripts:: @ 821FB2C
	.byte 0

LilycoveCity_DepartmentStore_2F_EventScript_21FB2D:: @ 821FB2D
	msgbox LilycoveCity_DepartmentStore_2F_Text_21FBAC, MSGBOX_NPC
	end

LilycoveCity_DepartmentStore_2F_EventScript_21FB36:: @ 821FB36
	msgbox LilycoveCity_DepartmentStore_2F_Text_21FBDF, MSGBOX_NPC
	end

LilycoveCity_DepartmentStore_2F_EventScript_21FB3F:: @ 821FB3F
	msgbox LilycoveCity_DepartmentStore_2F_Text_21FC23, MSGBOX_NPC
	end

LilycoveCity_DepartmentStore_2F_EventScript_21FB48:: @ 821FB48
	lock
	faceplayer
	message gUnknown_08272A21
	waitmessage
	pokemart LilycoveCity_DepartmentStore_2F_Pokemart_21FB60
	msgbox gUnknown_08272A3F, MSGBOX_DEFAULT
	release
	end

	.align 2
LilycoveCity_DepartmentStore_2F_Pokemart_21FB60: @ 821FB60
	.short ITEM_POKE_BALL
	.short ITEM_GREAT_BALL
	.short ITEM_ULTRA_BALL
	.short ITEM_ESCAPE_ROPE
	.short ITEM_FULL_HEAL
	.short ITEM_ANTIDOTE
	.short ITEM_PARALYZE_HEAL
	.short ITEM_BURN_HEAL
	.short ITEM_ICE_HEAL
	.short ITEM_AWAKENING
	.short ITEM_FLUFFY_TAIL
	.short ITEM_NONE
	release
	end

LilycoveCity_DepartmentStore_2F_EventScript_21FB7A:: @ 821FB7A
	lock
	faceplayer
	message gUnknown_08272A21
	waitmessage
	pokemart LilycoveCity_DepartmentStore_2F_Pokemart_21FB94
	msgbox gUnknown_08272A3F, MSGBOX_DEFAULT
	release
	end

	.align 2
LilycoveCity_DepartmentStore_2F_Pokemart_21FB94: @ 821FB94
	.short ITEM_POTION
	.short ITEM_SUPER_POTION
	.short ITEM_HYPER_POTION
	.short ITEM_MAX_POTION
	.short ITEM_REVIVE
	.short ITEM_REPEL
	.short ITEM_SUPER_REPEL
	.short ITEM_MAX_REPEL
	.short ITEM_WAVE_MAIL
	.short ITEM_MECH_MAIL
	.short ITEM_NONE
	release
	end

LilycoveCity_DepartmentStore_2F_Text_21FBAC: @ 821FBAC
	.string "Learn to use items properly.\n"
	.string "That's basic, really.$"

LilycoveCity_DepartmentStore_2F_Text_21FBDF: @ 821FBDF
	.string "My husband is waiting at home.\n"
	.string "What would make a good gift for him?$"

LilycoveCity_DepartmentStore_2F_Text_21FC23: @ 821FC23
	.string "I'm leaving on a long journey soon.\n"
	.string "I need to stock up on items.$"

