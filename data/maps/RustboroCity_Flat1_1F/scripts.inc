RustboroCity_Flat1_1F_MapScripts::
	.byte 0

RustboroCity_Flat1_1F_EventScript_Man::
	msgbox RustboroCity_Flat1_1F_Text_EveryPokemonHasAbility, MSGBOX_NPC
	end

RustboroCity_Flat1_1F_EventScript_Woman::
	msgbox RustboroCity_Flat1_1F_Text_PokemonStrange, MSGBOX_NPC
	end

RustboroCity_Flat1_1F_Text_EveryPokemonHasAbility:
	.string "{COLOR BLUE}Every POKéMON has a special ability\n"
	.string "that it can use.{COLOR DARK_GRAY}$"

RustboroCity_Flat1_1F_Text_PokemonStrange:
	.string "{COLOR RED}POKéMON are such strange creatures.{COLOR DARK_GRAY}$"

