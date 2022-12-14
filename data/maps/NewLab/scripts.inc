NewLab_MapScripts::
	.byte 0


NewLab_EventScript_Pokeball::
	lockall
	showmonpic SPECIES_EEVEE, 10, 3
	msgbox NewLab_EventScript_Pokeball_Text_0, MSGBOX_YESNO
	compare VAR_RESULT, YES
	goto_if_eq NewLab_EventScript_Pokeball_2
	hidemonpic
	msgbox NewLab_NotChosen
NewLab_EventScript_Pokeball_1:
	waitmessage
	releaseall
	end

NewLab_EventScript_Pokeball_2:
	givemon SPECIES_EEVEE, 5, ITEM_CHERISH_BALL
	compare VAR_RESULT, MON_GIVEN_TO_PARTY
	goto_if_eq NewLab_EventScript_Pokeball_6
	compare VAR_RESULT, YES
	goto_if_eq NewLab_EventScript_Pokeball_7
	hidemonpic
	msgbox NewLab_EventScript_Pokeball_Text_2
NewLab_EventScript_Pokeball_5:
	call GivePokedex
	goto NewLab_EventScript_Pokeball_1

NewLab_EventScript_Pokeball_6:
	playfanfare MUS_OBTAIN_ITEM
	msgbox NewLab_EventScript_Pokeball_Text_1
	removeobject 1
	setflag FLAG_POKEMON_GIFT_LITTLEROOT_EEVEE
	setflag FLAG_SYS_POKEMON_GET
	setvar VAR_LITTLEROOT_TOWN_STATE, 4
	call NicknameStarterMon
	goto NewLab_EventScript_Pokeball_5

NewLab_EventScript_Pokeball_7:
	playfanfare MUS_OBTAIN_ITEM
	msgbox NewLab_EventScript_Pokeball_Text_1
	removeobject 1
	setflag FLAG_POKEMON_GIFT_LITTLEROOT_EEVEE
	setflag FLAG_SYS_POKEMON_GET
	setvar VAR_LITTLEROOT_TOWN_STATE, 4
	call NicknameStarterBoxMon
	goto NewLab_EventScript_Pokeball_5


NicknameStarterMon::
	msgbox NicknameStarterMon_Text_0, MSGBOX_YESNO
	hidemonpic
	compare VAR_RESULT, YES
	goto_if_eq NicknameStarterMon_1
	return

NicknameStarterMon_1:
	call Common_EventScript_GetGiftMonPartySlot
	call Common_EventScript_NameReceivedPartyMon
	return


NicknameStarterBoxMon::
	msgbox NicknameStarterMon_Text_0, MSGBOX_YESNO
	hidemonpic
	compare VAR_RESULT, YES
	goto_if_eq NicknameStarterBoxMon_2
NicknameStarterBoxMon_1:
	call Common_EventScript_TransferredToPC
	return

NicknameStarterBoxMon_2:
	call Common_EventScript_NameReceivedBoxMon
	goto NicknameStarterBoxMon_1


GivePokedex::
	lock
	setflag FLAG_SYS_POKEDEX_GET
	setflag FLAG_ADVENTURE_STARTED
	special SetUnlockedPokedexFlags
	setflag FLAG_RECEIVED_POKEDEX_FROM_BIRCH
	setflag FLAG_DISABLE_BAG
	setvar VAR_CABLE_CLUB_TUTORIAL_STATE, 1
	msgbox GivePokedex_Text_0, MSGBOX_DEFAULT
	giveitem ITEM_POKE_BALL, 50
	giveitem ITEM_RARE_CANDY, 1998
	call UpgradeNationalDex
	release
	return


UpgradeNationalDex::
	lock
	setflag FLAG_SYS_NATIONAL_DEX
	special EnableNationalPokedex
	release
	return


NewLab_EventScript_Pokeball_Text_0:
	.string "Are you ready to start your journey?$"

NewLab_EventScript_Pokeball_Text_1:
	.string "Received Eevee$"

NewLab_EventScript_Pokeball_Text_2:
	.string "No room in the party.$"

NicknameStarterMon_Text_0:
	.string "Give it a nickname?$"

GivePokedex_Text_0:
	.string "Good luck {PLAYER}!$"

NewLab_NotChosen::
	.string "You decided you weren't ready yet.$"
