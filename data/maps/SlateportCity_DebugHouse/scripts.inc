SlateportCity_DebugHouse_MapScripts::
	.byte 0

SlateportCity_DebugHouse_Trader1::
	lock
	faceplayer
	setvar VAR_0x8008, INGAME_TRADE_SEEDOT
	goto SlateportCity_DebugHouse_EventScript_Trading

SlateportCity_DebugHouse_Trader2::
	lock
	faceplayer
	setvar VAR_0x8008, INGAME_TRADE_PLUSLE
	goto SlateportCity_DebugHouse_EventScript_Trading

SlateportCity_DebugHouse_Trader3::
	lock
	faceplayer
	setvar VAR_0x8008, INGAME_TRADE_HORSEA
	goto SlateportCity_DebugHouse_EventScript_Trading

SlateportCity_DebugHouse_Trader4::
	lock
	faceplayer
	setvar VAR_0x8008, INGAME_TRADE_MEOWTH
	goto SlateportCity_DebugHouse_EventScript_Trading

SlateportCity_DebugHouse_Trader5::
	lock
	faceplayer
	setvar VAR_0x8008, INGAME_TRADE_MAKUHITA
	goto SlateportCity_DebugHouse_EventScript_Trading

SlateportCity_DebugHouse_Trader6::
	lock
	faceplayer
	setvar VAR_0x8008, INGAME_TRADE_SKITTY
	goto SlateportCity_DebugHouse_EventScript_Trading

SlateportCity_DebugHouse_Trader7::
	lock
	faceplayer
	setvar VAR_0x8008, INGAME_TRADE_CORSOLA
	goto SlateportCity_DebugHouse_EventScript_Trading

SlateportCity_DebugHouse_Trader8::
	lock
	faceplayer
	setvar VAR_0x8008, INGAME_TRADE_CROAGUNK
	goto SlateportCity_DebugHouse_EventScript_Trading

SlateportCity_DebugHouse_EventScript_Trading::
	copyvar VAR_0x8004, VAR_0x8008
	specialvar VAR_RESULT, GetInGameTradeSpeciesInfo
	copyvar VAR_0x8009, VAR_RESULT
	msgbox SlateportCity_DebugHouse_Text_YouWillTradeWontYou, MSGBOX_YESNO
	goto_if_eq VAR_RESULT, NO, SlateportCity_DebugHouse_EventScript_DeclineTrade
	special ChoosePartyMon
	copyvar VAR_0x800A, VAR_0x8004
	goto_if_eq VAR_0x8004, PARTY_NOTHING_CHOSEN, SlateportCity_DebugHouse_EventScript_DeclineTrade
	copyvar VAR_0x8005, VAR_0x800A
	specialvar VAR_RESULT, GetTradeSpecies
	copyvar VAR_0x800B, VAR_RESULT
	goto_if_ne VAR_RESULT, VAR_0x8009, SlateportCity_DebugHouse_EventScript_NotRequestedMon
	copyvar VAR_0x8004, VAR_0x8008
	copyvar VAR_0x8005, VAR_0x800A
	special CreateInGameTradePokemon
	special DoInGameTradeScene
	bufferspeciesname STR_VAR_1, VAR_0x8009
	msgbox SlateportCity_DebugHouse_Text_MonYouTakeCare, MSGBOX_DEFAULT
	releaseall
	end

SlateportCity_DebugHouse_EventScript_DeclineTrade::
	msgbox SlateportCity_DebugHouse_Text_Goodbye, MSGBOX_DEFAULT
	releaseall
	end

SlateportCity_DebugHouse_EventScript_NotRequestedMon::
	bufferspeciesname STR_VAR_1, VAR_0x8009
	msgbox SlateportCity_DebugHouse_Text_ThisIsntAMon, MSGBOX_DEFAULT
	releaseall
	end

SlateportCity_DebugHouse_Text_YouWillTradeWontYou:
	.string "I am looking for {STR_VAR_1}.\l"
	.string "I am offering {STR_VAR_2}.$\p"

SlateportCity_DebugHouse_Text_MonYouTakeCare:
	.string "Thank you!$\p"

SlateportCity_DebugHouse_Text_ThisIsntAMon:
	.string "That isn't a {STR_VAR_1}.$\p"

SlateportCity_DebugHouse_Text_Goodbye:
	.string "See you again.$\p"

