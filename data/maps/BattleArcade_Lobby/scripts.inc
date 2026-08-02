BattleArcade_Lobby_MapScripts::
	map_script MAP_SCRIPT_ON_FRAME_TABLE, BattleArcade_Lobby_MapScripts_MAP_SCRIPT_ON_FRAME_TABLE
	map_script MAP_SCRIPT_ON_WARP_INTO_MAP_TABLE, BattleArcade_Lobby_MapScripts_MAP_SCRIPT_ON_WARP_INTO_MAP_TABLE
	.byte 0

BattleArcade_Lobby_MapScripts_MAP_SCRIPT_ON_WARP_INTO_MAP_TABLE:
	map_script_2 VAR_TEMP_1, 0, BattleArcade_Lobby_EventScript_PlayerFaceNorth
	.2byte 0

BattleArcade_Lobby_EventScript_PlayerFaceNorth::
	setvar VAR_TEMP_1, 1
	turnobject OBJ_EVENT_ID_PLAYER, DIR_NORTH
	end

BattleArcade_Lobby_MapScripts_MAP_SCRIPT_ON_FRAME_TABLE:
	map_script_2 VAR_TEMP_CHALLENGE_STATUS, 0, BattleArcade_Lobby_EventScript_GetChallengeStatus
	map_script_2 VAR_TEMP_CHALLENGE_STATUS, CHALLENGE_STATUS_SAVING, BattleArcade_Lobby_EventScript_QuitWithoutSaving
	map_script_2 VAR_TEMP_CHALLENGE_STATUS, CHALLENGE_STATUS_PAUSED, BattleArcade_Registration_EventScript_ResumeChallenge
	map_script_2 VAR_TEMP_CHALLENGE_STATUS, CHALLENGE_STATUS_WON, BattleArcade_Lobby_EventScript_WonChallenge
	map_script_2 VAR_TEMP_CHALLENGE_STATUS, CHALLENGE_STATUS_LOST, BattleArcade_Lobby_EventScript_LostChallenge
	.2byte 0

BattleArcade_Lobby_EventScript_GetChallengeStatus::
	frontier_getstatus
	end

BattleArcade_Lobby_EventScript_QuitWithoutSaving::
	lockall
	msgbox BattleArcade_Lobby_Text_QuitWithoutSaving, MSGBOX_DEFAULT
	closemessage
	arcade_set ARCADE_DATA_WIN_STREAK, 0
	arcade_set ARCADE_DATA_WIN_STREAK_ACTIVE, FALSE
	frontier_set FRONTIER_DATA_CHALLENGE_STATUS, 0
	setvar VAR_TEMP_CHALLENGE_STATUS, 255
	releaseall
	end

BattleArcade_Lobby_EventScript_WonChallenge::
	lockall
	frontier_isbrain
	goto_if_eq VAR_RESULT, TRUE, BattleArcade_Lobby_EventScript_DefeatedStar
	msgbox BattleArcade_Lobby_Text_CongratsFor7WinStreak, MSGBOX_DEFAULT
	goto BattleArcade_Lobby_EventScript_GiveBattlePoints

BattleArcade_Lobby_EventScript_DefeatedStar:
	msgbox BattleArcade_Lobby_Text_CongratsDefeatingStar, MSGBOX_DEFAULT
BattleArcade_Lobby_EventScript_GiveBattlePoints::
	msgbox BattleArcade_Lobby_Text_GiveBP, MSGBOX_DEFAULT
	frontier_givepoints
	msgbox BattleFrontier_Text_ObtainedXBattlePoints, MSGBOX_GETPOINTS
	message BatleArcade_Lobby_Text_RecordWillBeRecorded
	waitmessage
	call BattleArcade_Lobby_EventScript_SaveAfterChallenge
	msgbox BattleArcade_Lobby_Text_ReturnAgain, MSGBOX_DEFAULT
	closemessage
	setvar VAR_TEMP_CHALLENGE_STATUS, 255
	releaseall
	end

BattleArcade_Lobby_EventScript_LostChallenge::
	lockall
	message BatleArcade_Lobby_Text_ResultsWillBeRecorded
	waitmessage
	arcade_set ARCADE_DATA_WIN_STREAK_ACTIVE, FALSE
	call BattleArcade_Lobby_EventScript_SaveAfterChallenge
	msgbox BattleArcade_Lobby_Text_ReturnAgain, MSGBOX_DEFAULT
	closemessage
	setvar VAR_TEMP_CHALLENGE_STATUS, 255
	releaseall
	end

BattleArcade_Lobby_EventScript_SaveAfterChallenge::
	frontier_checkairshow
	special LoadPlayerParty
	special HealPlayerParty
	arcade_save 0
	playse SE_SAVE
	waitse
	call BattleFrontier_EventScript_GetCantRecordBattle
	goto_if_eq VAR_RESULT, TRUE, BattleArcade_Lobby_EventScript_EndSaveAfterChallenge
	message BattleArcade_Lobby_Text_LikeToRecordMatch
	waitmessage
	multichoicedefault 20, 8, MULTI_YESNO, 1, FALSE
	switch VAR_RESULT
	case 1, BattleArcade_Lobby_EventScript_EndSaveAfterChallenge
	case 0, BattleArcade_Lobby_EventScript_RecordMatch
	case MULTI_B_PRESSED, BattleArcade_Lobby_EventScript_SaveAfterChallenge

BattleArcade_Lobby_EventScript_RecordMatch::
	call BattleFrontier_EventScript_SaveBattle
BattleArcade_Lobby_EventScript_EndSaveAfterChallenge::
	return

BattleArcade_Lobby_EventScript_ResumeChallenge::
	lockall
	msgbox BattleArcade_Lobby_Text_WelcomeBack, MSGBOX_DEFAULT
	message BattleArcade_Lobby_Text_SaveBeforeResume
	waitmessage
	arcade_save CHALLENGE_STATUS_SAVING
	playse SE_SAVE
	waitse
	frontier_set FRONTIER_DATA_PAUSED, FALSE
	setvar VAR_TEMP_CHALLENGE_STATUS, 255
	goto BattleArcade_Lobby_EventScript_EnterChallenge

BattleArcade_Lobby_EventScript_SinglesAttendant::
	lock
	faceplayer
	setvar VAR_FRONTIER_FACILITY, FRONTIER_FACILITY_ARCADE
	setvar VAR_FRONTIER_BATTLE_MODE, FRONTIER_MODE_SINGLES
	goto BattleArcade_Lobby_EventScript_Attendant
	end

BattleArcade_Lobby_EventScript_DoublesAttendant::
	lock
	faceplayer
	setvar VAR_FRONTIER_FACILITY, FRONTIER_FACILITY_ARCADE
	setvar VAR_FRONTIER_BATTLE_MODE, FRONTIER_MODE_DOUBLES
	goto BattleArcade_Lobby_EventScript_Attendant
	end

BattleArcade_Lobby_EventScript_Attendant::
	special SavePlayerParty
	call_if_eq VAR_FRONTIER_BATTLE_MODE, FRONTIER_MODE_SINGLES, BattleArcade_Lobby_EventScript_WelcomeForSingleBattle
	call_if_eq VAR_FRONTIER_BATTLE_MODE, FRONTIER_MODE_DOUBLES, BattleArcade_Lobby_EventScript_WelcomeForDoubleBattle
BattleArcade_Lobby_EventScript_AskTakeChallenge::
	call_if_eq VAR_FRONTIER_BATTLE_MODE, FRONTIER_MODE_SINGLES, BattleArcade_Lobby_EventScript_AskSingleBattle
	call_if_eq VAR_FRONTIER_BATTLE_MODE, FRONTIER_MODE_DOUBLES, BattleArcade_Lobby_EventScript_AskDoubleBattle
	waitmessage
	multichoice 17, 6, MULTI_CHALLENGEINFO, FALSE
	switch VAR_RESULT
	case 0, BattleArcade_Lobby_EventScript_TryEnterChallenge
	case 1, BattleArcade_Lobby_EventScript_ExplainChallenge
	case 2, BattleArcade_Lobby_EventScript_CancelChallenge
	case MULTI_B_PRESSED, BattleArcade_Lobby_EventScript_CancelChallenge

BattleArcade_Lobby_EventScript_TryEnterChallenge::
	message BattleArcade_Lobby_Text_WhichChallenge
	waitmessage
	multichoice 17, 6, MULTI_LEVEL_MODE, FALSE
	switch VAR_RESULT
	case MULTI_B_PRESSED, BattleArcade_Lobby_EventScript_CancelChallenge
	frontier_checkineligible
	goto_if_eq VAR_0x8004, TRUE, BattleArcade_Lobby_EventScript_NotEnoughValidMons
	frontier_set FRONTIER_DATA_LVL_MODE, VAR_RESULT
	msgbox BattleArcade_Lobby_Text_SelectThreeMons, MSGBOX_DEFAULT
	fadescreen FADE_TO_BLACK
	call BattleFrontier_EventScript_GetLvlMode
	copyvar VAR_0x8004, VAR_RESULT
	setvar VAR_0x8005, FRONTIER_PARTY_SIZE
	special ChoosePartyForBattleFrontier
	goto_if_eq VAR_RESULT, 0, BattleArcade_Lobby_EventScript_LoadPartyAndCancelChallenge
	msgbox BattleArcade_Lobby_Text_SaveBeforeChallenge, MSGBOX_YESNO
	switch VAR_RESULT
	case NO, BattleArcade_Lobby_EventScript_LoadPartyAndCancelChallenge
	case YES, BattleArcade_Lobby_EventScript_SaveBeforeChallenge
	case MULTI_B_PRESSED, BattleArcade_Lobby_EventScript_LoadPartyAndCancelChallenge

BattleArcade_Lobby_EventScript_SaveBeforeChallenge::
	setvar VAR_TEMP_CHALLENGE_STATUS, 0
	frontier_set FRONTIER_DATA_SELECTED_MON_ORDER
	arcade_init
	arcade_set ARCADE_DATA_WIN_STREAK_ACTIVE, TRUE
	frontier_set FRONTIER_DATA_CHALLENGE_STATUS, CHALLENGE_STATUS_SAVING
	frontier_set FRONTIER_DATA_PAUSED, FALSE
	special LoadPlayerParty
	closemessage
	delay 2
	call Common_EventScript_SaveGame
	setvar VAR_TEMP_CHALLENGE_STATUS, 255
	goto_if_eq VAR_RESULT, 0, BattleArcade_Lobby_EventScript_CancelChallengeSaveFailed
BattleArcade_Lobby_EventScript_EnterChallenge::
	special SavePlayerParty
	frontier_setpartyorder FRONTIER_PARTY_SIZE
	msgbox BattleArcade_Lobby_Text_FollowMe, MSGBOX_DEFAULT
	closemessage
	call BattleArcade_Lobby_EventScript_WalkToDoor
	warp MAP_BATTLE_ARCADE_HALLWAY, 1, 3
	setvar VAR_TEMP_CHALLENGE_STATUS, 0
	waitstate
	end

BattleArcade_Lobby_EventScript_ExplainChallenge::
	goto_if_eq VAR_FRONTIER_BATTLE_MODE, FRONTIER_MODE_DOUBLES, BattleArcade_Lobby_EventScript_ExplainDoublesChallenge
	msgbox BattleArcade_Lobby_Text_ExplainSinglesChallenge, MSGBOX_DEFAULT
	goto BattleArcade_Lobby_EventScript_AskTakeChallenge

BattleArcade_Lobby_EventScript_ExplainDoublesChallenge::
	msgbox BattleArcade_Lobby_Text_ExplainDoublesChallenge, MSGBOX_DEFAULT
	goto BattleArcade_Lobby_EventScript_AskTakeChallenge

BattleArcade_Lobby_EventScript_NotEnoughValidMons::
	switch VAR_RESULT
	case FRONTIER_LVL_50, BattleArcade_Lobby_EventScript_NotEnoughValidMonsLv50
	case FRONTIER_LVL_OPEN, BattleArcade_Lobby_EventScript_NotEnoughValidMonsLvOpen

BattleArcade_Lobby_EventScript_NotEnoughValidMonsLv50::
	msgbox BattleArcade_Lobby_Text_NotEnoughValidMonsLv50, MSGBOX_DEFAULT
	goto BattleArcade_Lobby_EventScript_CancelChallenge

BattleArcade_Lobby_EventScript_NotEnoughValidMonsLvOpen::
	msgbox BattleArcade_Lobby_Text_NotEnoughValidMonsLvOpen, MSGBOX_DEFAULT
	goto BattleArcade_Lobby_EventScript_CancelChallenge

BattleArcade_Lobby_EventScript_CancelChallengeSaveFailed::
	frontier_set FRONTIER_DATA_CHALLENGE_STATUS, 0
	goto BattleArcade_Lobby_EventScript_CancelChallenge

BattleArcade_Lobby_EventScript_LoadPartyAndCancelChallenge::
	special LoadPlayerParty
BattleArcade_Lobby_EventScript_CancelChallenge::
	msgbox BattleArcade_Lobby_Text_ReturnAgain, MSGBOX_DEFAULT
BattleArcade_Lobby_EventScript_EndCancelChallenge::
	release
	end

BattleArcade_Lobby_EventScript_WelcomeForSingleBattle::
	msgbox BattleArcade_Lobby_Text_WelcomeForSingleBattle, MSGBOX_DEFAULT
	return

BattleArcade_Lobby_EventScript_WelcomeForDoubleBattle::
	msgbox BattleArcade_Lobby_Text_WelcomeForDoubleBattle, MSGBOX_DEFAULT
	return

BattleArcade_Lobby_EventScript_AskSingleBattle:
	message BattleArcade_Lobby_Text_TakeSingleChallenge
	return

BattleArcade_Lobby_EventScript_AskDoubleBattle::
	message BattleArcade_Lobby_Text_TakeDoubleChallenge
	return

BattleArcade_Lobby_EventScript_WalkToDoor::
	call_if_eq VAR_FRONTIER_BATTLE_MODE, FRONTIER_MODE_SINGLES, BattleArcade_Lobby_EventScript_TalkedToSinglesAttendant
	call_if_eq VAR_FRONTIER_BATTLE_MODE, FRONTIER_MODE_DOUBLES, BattleArcade_Lobby_EventScript_TalkedToDoublesAttendant
	applymovement VAR_LAST_TALKED, BattleArcade_Lobby_Movement_WalkToDoor
	applymovement LOCALID_PLAYER, BattleArcade_Lobby_Movement_WalkToDoor
	waitmovement 0
	call_if_eq VAR_FRONTIER_BATTLE_MODE, FRONTIER_MODE_SINGLES, BattleArcade_Lobby_EventScript_OpenSinglesDoor
	call_if_eq VAR_FRONTIER_BATTLE_MODE, FRONTIER_MODE_DOUBLES, BattleArcade_Lobby_EventScript_OpenDoublesDoor
	waitdooranim
	applymovement VAR_LAST_TALKED, BattleArcade_Lobby_Movement_AttendantEnterDoor
	applymovement LOCALID_PLAYER, BattleArcade_Lobby_Movement_PlayerEnterDoor
	waitmovement 0
	call_if_eq VAR_FRONTIER_BATTLE_MODE, FRONTIER_MODE_SINGLES, BattleArcade_Lobby_EventScript_CloseSinglesDoor
	call_if_eq VAR_FRONTIER_BATTLE_MODE, FRONTIER_MODE_DOUBLES, BattleArcade_Lobby_EventScript_CloseDoublesDoor
	waitdooranim
	return

BattleArcade_Lobby_EventScript_TalkedToSinglesAttendant::
	setvar VAR_LAST_TALKED, LOCALID_ARCADE_ATTENDANT_SINGLES
	return

BattleArcade_Lobby_EventScript_TalkedToDoublesAttendant::
	setvar VAR_LAST_TALKED, LOCALID_ARCADE_ATTENDANT_DOUBLES
	return

BattleArcade_Lobby_EventScript_OpenSinglesDoor::
	opendoor 3 3
	return

BattleArcade_Lobby_EventScript_OpenDoublesDoor::
	opendoor 11 3
	return

BattleArcade_Lobby_EventScript_CloseSinglesDoor::
	closedoor 3 3
	return

BattleArcade_Lobby_EventScript_CloseDoublesDoor::
	closedoor 11 3
	return

BattleArcade_Lobby_Movement_WalkToDoor::
	walk_up
	walk_up
	step_end

BattleArcade_Lobby_Movement_AttendantEnterDoor::
	walk_up
	set_invisible
	step_end

BattleArcade_Lobby_Movement_PlayerEnterDoor::
	walk_up
	walk_up
	set_invisible
	step_end

BattleArcade_Lobby_EventScript_ShowSinglesResults::
	lockall
	frontier_results FRONTIER_FACILITY_ARCADE, FRONTIER_MODE_SINGLES
	waitbuttonpress
	special RemoveRecordsWindow
	releaseall
	end

BattleArcade_Lobby_EventScript_ShowDoublesResults::
	lockall
	frontier_results FRONTIER_FACILITY_ARCADE, FRONTIER_MODE_DOUBLES
	waitbuttonpress
	special RemoveRecordsWindow
	releaseall
	end

BattleArcade_Lobby_EventScript_Man::
	msgbox BattleArcade_Lobby_Text_Man, MSGBOX_NPC
	end

BattleArcade_Lobby_EventScript_Lady::
	msgbox BattleArcade_Lobby_Text_Lady, MSGBOX_NPC
	end

BattleArcade_Lobby_EventScript_Hiker::
	msgbox BattleArcade_Lobby_Text_Hiker, MSGBOX_NPC
	end


BattleArcade_Lobby_EventScript_WalkToElevator::
	closemessage
	applymovement VAR_LAST_TALKED, BattleArcade_Lobby_EventScript_WalkToElevator_Movement_0
	applymovement OBJ_EVENT_ID_PLAYER, BattleArcade_Lobby_EventScript_WalkToElevator_Movement_1
	waitmovement OBJ_EVENT_ID_PLAYER
	return


BattleArcade_Lobby_EventScript_WalkToElevator_Movement_0:
	walk_up
	walk_up
	set_invisible
	step_end

BattleArcade_Lobby_EventScript_WalkToElevator_Movement_1:
	walk_up
	walk_up
	walk_up
	set_invisible
	step_end


BattleArcade_Lobby_Text_WelcomeForSingleBattle:
	.string "Where the adaptability of TRAINERS\n"
	.string "is put to the test.\p"
	.string "Welcome to the BATTLE ARCADE.\p"
	.string "I can help you sign up for the\n"
	.string "SINGLE BATTLE STREAK.$"

BattleArcade_Lobby_Text_WelcomeForDoubleBattle:
	.string "Where the adaptability of TRAINERS\n"
	.string "is put to the test.\p"
	.string "Welcome to the BATTLE ARCADE.\p"
	.string "I can help you sign up for the\n"
	.string "DOUBLE BATTLE STREAK.$"

BattleArcade_Lobby_Text_TakeSingleChallenge:
	.string "Would you like to take the SINGLE\n"
	.string "BATTLE STREAK challenge?$"

BattleArcade_Lobby_Text_TakeDoubleChallenge:
	.string "Would you like to take the DOUBLE\n"
	.string "BATTLE STREAK challenge?$"

BattleArcade_Lobby_Text_QuitWithoutSaving:
	.string "Excuse me! You didn't save before you\n"
	.string "quit your challenge last time. Because\l"
	.string "of that, you have been disqualified\l"
	.string "from your challenge!$"

BattleArcade_Lobby_Text_CongratsFor7WinStreak::
	.string "You have cleared your seventh battle!\n"
	.string "Congratulations!$"

BattleArcade_Lobby_Text_CongratsDefeatingStar::
	.string "Congratulations on your triumph\n"
	.string "over the ARCADE STAR!$"

BattleArcade_Lobby_Text_GiveBP::
	.string "You have earned BP as your prize!$"

BatleArcade_Lobby_Text_RecordWillBeRecorded::
	.string "Your record will be recorded.\n"
	.string "Please wait…$"

BatleArcade_Lobby_Text_ResultsWillBeRecorded::
	.string "The results of your last game\n"
	.string "will be recorded. Please wait…$"

BattleArcade_Lobby_Text_LikeToRecordMatch:
	.string "Would you like to record your latest\n"
	.string "BATTLE ARCADE match on your\l"
	.string "FRONTIER PASS?$"

BattleArcade_Lobby_Text_ReturnAgain::
	.string "You must return to play again!$"

BattleArcade_Lobby_Text_WelcomeBack::
	.string "Welcome back TRAINER.$"

BattleArcade_Lobby_Text_SaveBeforeResume::
	.string "I must save before we can return\n"
	.string "to the BATTLE HALL. Please wait.$$"

BattleArcade_Lobby_Text_SelectThreeMons:
	.string "Please select three POKéMON\n"
	.string "to use.$"

BattleArcade_Lobby_Text_WhichChallenge:
	.string "The BATTLE ARCADE has two levels\n"
	.string "of challenge, Level 50 and Open Level.\l"
	.string "Which would you like to take on?$"

BattleArcade_Lobby_Text_FollowMe:
	.string "Thank you.\n"
	.string "Please follow me.$"

BattleArcade_Lobby_Text_SaveBeforeChallenge:
	.string "Before beginning a STREAK, your\n"
	.string "progress must be saved. Is that okay?$"

BattleArcade_Lobby_Text_ExplainSinglesChallenge::
	.string "At the BATTLE ARCADE, you may take\n"
	.string "part in a SINGLE BATTLE STREAK.\p"
	.string "Here, a game board is activated\n"
	.string "before every match.\p"
	.string "Depending on what comes up on the\n"
	.string "game board, an event takes place.\p"
	.string "Some events will be good for the\n"
	.string "challenger, while others won't be.\p"
	.string "The objective is to keep a winning\n"
	.string "streak alive as long as possible.\p"
	.string "During your challenge, any items held\n"
	.string "by your POKéMON will be kept in storage.\p"
	.string "If you manage to win seven matches in\n"
	.string "a row, you will earn Battle Points.\p"
	.string "If you want to interrupt your\n"
	.string "challenge, please save the game.\p"
	.string "If you don't save before interrupting,\n"
	.string "you will be disqualified.$"

BattleArcade_Lobby_Text_ExplainDoublesChallenge::
	.string "At the BATTLE ARCADE, you may take\n"
	.string "part in a DOUBLE BATTLE STREAK.\p"
	.string "Here, a game board is activated\n"
	.string "before every match.\p"
	.string "Depending on what comes up on the\n"
	.string "game board, an event takes place.\p"
	.string "Some events will be good for the\n"
	.string "challenger, while others won't be.\p"
	.string "The objective is to keep a winning\n"
	.string "streak alive as long as possible.\p"
	.string "During your challenge, any items held\n"
	.string "by your POKéMON will be kept in storage.\p"
	.string "If you manage to win seven matches in\n"
	.string "a row, you will earn Battle Points.\p"
	.string "If you want to interrupt your\n"
	.string "challenge, please save the game.\p"
	.string "If you don't save before interrupting,\n"
	.string "you will be disqualified.$"

BattleArcade_Lobby_Text_NotEnoughValidMonsLv50:
	.string "Excuse me!\p"
	.string "You do not have the three POKéMON\n"
	.string "required for the challenge.\p"
	.string "To enter, you must provide three\n"
	.string "different kinds of POKéMON.\p"
	.string "These POKéMON must all be of\n"
	.string "Level 50 or lower.\p"
	.string "They also must not be holding\n"
	.string "the same kinds of items.\p"
	.string "EGGS{STR_VAR_1} ineligible.\p"
	.string "Come back when you have made\n"
	.string "your preparations.$"

BattleArcade_Lobby_Text_NotEnoughValidMonsLvOpen:
	.string "Excuse me!\p"
	.string "You do not have the three POKéMON\n"
	.string "required for the challenge.\p"
	.string "To enter, you must provide three\n"
	.string "different kinds of POKéMON.\p"
	.string "They also must not be holding\n"
	.string "the same kinds of items.\p"
	.string "EGGS{STR_VAR_1} ineligible.\p"
	.string "Come back when you have made\n"
	.string "your preparations.$"

BattleArcade_Lobby_Text_Man::
	.string "The game board is like your life.\p"
	.string "It goes round and round\n"
	.string "as your fortune goes up and down…\l"
	.string "How did that sound?\p"
	.string "It almost made some kind of sense,\n"
	.string "didn't it?$"

BattleArcade_Lobby_Text_Hiker::
	.string "I'll tell you something.\p"
	.string "Poisoning or freezing events\n"
	.string "can be made ineffective.\p"
	.string "…If the POKéMON's type or ability\n"
	.string "protects it form such statuses.\p"
	.string "Might be worth knowing!$"

BattleArcade_Lobby_Text_Lady::
	.string "I thought I was fully prepared\n"
	.string "with my prized POKéMON…\p"
	.string "But I had to swap them and use my\n"
	.string "opponent's instead!\p"
	.string "I need to rethink all my strategies.$"
