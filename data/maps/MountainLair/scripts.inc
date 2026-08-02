MountainLair_MapScripts::
	map_script MAP_SCRIPT_ON_RESUME, MountainLair_OnResume
	map_script MAP_SCRIPT_ON_LOAD, MountainLair_OnLoad
	map_script MAP_SCRIPT_ON_TRANSITION, MountainLair_OnTransition
	.byte 0

MountainLair_OnResume:
	call_if_set FLAG_SYS_CTRL_OBJ_DELETE, MountainLair_EventScript_TryRemoveRegidrago
	end

MountainLair_EventScript_TryRemoveRegidrago::
	specialvar VAR_RESULT, GetBattleOutcome
	goto_if_ne VAR_RESULT, B_OUTCOME_CAUGHT, Common_EventScript_NopReturn
	removeobject VAR_LAST_TALKED
	return

MountainLair_OnLoad:
	call_if_unset FLAG_SYS_REGIDRAGO_PUZZLE_COMPLETED, MountainLair_EventScript_HideRegiEntrance
	end

MountainLair_EventScript_HideRegiEntrance::
	setmetatile 7, 19, METATILE_Cave_EntranceCover, TRUE
	setmetatile 8, 19, METATILE_Cave_EntranceCover, TRUE
	setmetatile 9, 19, METATILE_Cave_EntranceCover, TRUE
	setmetatile 7, 20, METATILE_Cave_SealedChamberBraille_Mid, TRUE
	setmetatile 8, 20, METATILE_Cave_SealedChamberBraille_Mid, TRUE
	setmetatile 9, 20, METATILE_Cave_SealedChamberBraille_Mid, TRUE
	return

MountainLair_OnTransition:
	setflag FLAG_LANDMARK_ISLAND_CAVE
	call_if_unset FLAG_DEFEATED_REGIDRAGO, MountainLair_EventScript_ShowRegidrago
	end

MountainLair_EventScript_ShowRegidrago::
	clearflag FLAG_HIDE_REGIDRAGO
	return

MountainLair_EventScript_OpenRegiEntrance::
	setmetatile 7, 19, METATILE_Cave_SealedChamberEntrance_TopLeft, TRUE
	setmetatile 8, 19, METATILE_Cave_SealedChamberEntrance_TopMid, TRUE
	setmetatile 9, 19, METATILE_Cave_SealedChamberEntrance_TopRight, TRUE
	setmetatile 7, 20, METATILE_Cave_SealedChamberEntrance_BottomLeft, TRUE
	setmetatile 8, 20, METATILE_Cave_SealedChamberEntrance_BottomMid, FALSE
	setmetatile 9, 20, METATILE_Cave_SealedChamberEntrance_BottomRight, TRUE
	special DrawWholeMapView
	playse SE_BANG
	setflag FLAG_SYS_REGIDRAGO_PUZZLE_COMPLETED
	end

MountainLair_EventScript_CaveEntranceMiddle::
	lockall
	braillemessage MountainLair_Braille_ShowYourMight
	goto MountainLair_EventScript_CloseBrailleMsg
	end

MountainLair_EventScript_BigHoleInWall::
	msgbox gText_BigHoleInTheWall, MSGBOX_DEFAULT
	releaseall
	end

MountainLair_EventScript_CaveEntranceSide::
	lockall
	braillemessage MountainLair_Braille_ShowYourMight
	goto_if_set FLAG_SYS_REGIDRAGO_PUZZLE_COMPLETED, MountainLair_EventScript_CloseBrailleMsg
	goto MountainLair_EventScript_CloseBrailleMsg
	end

MountainLair_EventScript_CloseBrailleMsg::
	waitbuttonpress
	closebraillemessage
	releaseall
	end

MountainLair_EventScript_Regidrago::
	lock
	faceplayer
	waitse
	playmoncry SPECIES_REGIDRAGO, CRY_MODE_ENCOUNTER
	delay 40
	waitmoncry
	setwildbattle SPECIES_REGIDRAGO, 40
	setflag FLAG_SYS_CTRL_OBJ_DELETE
	special StartRegiBattle
	clearflag FLAG_SYS_CTRL_OBJ_DELETE
	specialvar VAR_RESULT, GetBattleOutcome
	goto_if_eq VAR_RESULT, B_OUTCOME_WON, MountainLair_EventScript_DefeatedRegidrago
	goto_if_eq VAR_RESULT, B_OUTCOME_RAN, MountainLair_EventScript_RanFromRegidrago
	goto_if_eq VAR_RESULT, B_OUTCOME_PLAYER_TELEPORTED, MountainLair_EventScript_RanFromRegidrago
	setflag FLAG_DEFEATED_REGIDRAGO
	release
	end

MountainLair_EventScript_DefeatedRegidrago::
	setflag FLAG_DEFEATED_REGIDRAGO
	goto Common_EventScript_RemoveStaticPokemon
	end

MountainLair_EventScript_RanFromRegidrago::
	setvar VAR_0x8004, SPECIES_REGIDRAGO
	goto Common_EventScript_LegendaryFlewAway
	end
