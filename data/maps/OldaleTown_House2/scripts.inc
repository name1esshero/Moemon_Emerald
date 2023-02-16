OldaleTown_House2_MapScripts::
	.byte 0

OldaleTown_House2_EventScript_Woman::
	msgbox OldaleTown_House2_Text_PokemonLevelUp, MSGBOX_NPC
	end

OldaleTown_House2_EventScript_Man::
	msgbox OldaleTown_House2_Text_YoullGoFurtherWithStrongPokemon, MSGBOX_NPC
	end

OldaleTown_House2_Text_PokemonLevelUp:
	.string "{COLOR RED}When POKéMON battle, they eventually\n"
	.string "level up and become stronger.{COLOR DARK_GRAY}$"

OldaleTown_House2_Text_YoullGoFurtherWithStrongPokemon:
	.string "{COLOR BLUE}If the POKéMON with you become\n"
	.string "stronger, you'll be able to go farther\l"
	.string "away from here.{COLOR DARK_GRAY}$"

