#ifndef MOEMON_EMERALD_SAVE_V1_H
#define MOEMON_EMERALD_SAVE_V1_H

#include "constants/vars.h"
#include "constants/flags.h"

#define NUM_DEX_FLAG_BYTES ROUND_BITS_TO_BYTES(NUM_SPECIES)
#define NUM_FLAG_BYTES ROUND_BITS_TO_BYTES(FLAGS_COUNT)
#define NUM_ADDITIONAL_PHRASE_BYTES ROUND_BITS_TO_BYTES(NUM_ADDITIONAL_PHRASES)

struct SaveBlock2_v1
{
    u8 _saveSentinel; // 0xFF
    // u8 unused;
    u16 saveVersion;
    u8 playerName[7 + 1];
    u8 playerGender; // MALE, FEMALE
    u8 specialSaveWarpFlags;
    u8 playerTrainerId[4];
    u16 playTimeHours;
    u8 playTimeMinutes;
    u8 playTimeSeconds;
    u8 playTimeVBlanks;
    u8 optionsButtonMode;  // OPTIONS_BUTTON_MODE_[NORMAL/LR/L_EQUALS_A]
    u16 optionsTextSpeed:3; // OPTIONS_TEXT_SPEED_[SLOW/MID/FAST]
    u16 optionsWindowFrameType:5; // Specifies one of the 20 decorative borders for text boxes
    u16 optionsSound:1; // OPTIONS_SOUND_[MONO/STEREO]
    u16 optionsBattleStyle:1; // OPTIONS_BATTLE_STYLE_[SHIFT/SET]
    u16 optionsBattleSceneOff:1; // whether battle animations are disabled
    u16 regionMapZoom:1; // whether the map is zoomed in
    //u16 padding1:4;
    //u16 padding2;
    struct Pokedex pokedex;
    u8 filler_90[0x8];
    struct Time localTimeOffset;
    struct Time lastBerryTreeUpdate;
    u32 gcnLinkFlags; // Read by Pokemon Colosseum/XD
    u32 encryptionKey;
    struct PlayersApprentice playerApprentice;
    struct Apprentice apprentices[2];   //272 bytes
    struct BerryCrush berryCrush;
    struct PokemonJumpRecords pokeJump;
    struct BerryPickingResults berryPick;
    struct RankingHall1P hallRecords1P[9][2][3]; // From record mixing.
    struct RankingHall2P hallRecords2P[2][3]; // From record mixing.
    u16 contestLinkResults[5][4];
    struct BattleFrontier frontier;
    u8 itemFlags[50];
};

struct SaveBlock1_v1
{
    /*0x00*/ struct Coords16 pos;
    /*0x04*/ struct WarpData location;
    /*0x0C*/ struct WarpData continueGameWarp;
    /*0x14*/ struct WarpData dynamicWarp;
    /*0x1C*/ struct WarpData lastHealLocation; // used by white-out and teleport
    /*0x24*/ struct WarpData escapeWarp; // used by Dig and Escape Rope
    /*0x2C*/ u16 savedMusic;
    /*0x2E*/ u8 weather;
    /*0x2F*/ u8 weatherCycleStage;
    /*0x30*/ u8 flashLevel;
    /*0x31*/ //u8 padding1;
    /*0x32*/ u16 mapLayoutId;
    /*0x34*/ u16 mapView[0x100];
    /*0x234*/ u8 playerPartyCount;
    /*0x235*/ //u8 padding2[3];
    /*0x238*/ struct Pokemon playerParty[6];
    /*0x490*/ u32 money;
    /*0x494*/ u16 coins;
    /*0x496*/ u16 registeredItem; // registered for use with SELECT button
    /*0x498*/ struct ItemSlot pcItems[50];
    /*0x560*/ struct ItemSlot bagPocket_Items[30];
    /*0x5D8*/ struct ItemSlot bagPocket_KeyItems[30];
    /*0x650*/ struct ItemSlot bagPocket_PokeBalls[16];
    /*0x690*/ struct ItemSlot bagPocket_TMHM[64];
    /*0x790*/ struct ItemSlot bagPocket_Berries[46];
    /*0x848*/ struct Pokeblock pokeblocks[40];
    /*0x988*/ u8 seen1[52];   //52 bytes
    /*0x9BC*/ u16 berryBlenderRecords[3];
    /*0x9C2*/ u8 unused_9C2[6];
    /*0x9C8*/ u16 trainerRematchStepCounter;    //104 bytes
    /*0x9CA*/ u8 trainerRematches[100];
    /*0xA2E*/ //u8 padding3[2];
    /*0xA30*/ struct ObjectEvent objectEvents[16];
    /*0xC70*/ struct ObjectEventTemplate objectEventTemplates[64];
    /*0x1270*/ u8 flags[NUM_FLAG_BYTES];
    /*0x139C*/ u16 vars[VARS_COUNT];
    /*0x159C*/ u32 gameStats[64];
    /*0x169C*/ struct BerryTree berryTrees[128];
    /*0x1A9C*/ struct SecretBase secretBases[10];
    /*0x271C*/ u8 playerRoomDecorations[12];
    /*0x2728*/ u8 playerRoomDecorationPositions[12];
    /*0x2734*/ u8 decorationDesks[10];
    /*0x273E*/ u8 decorationChairs[10];
    /*0x2748*/ u8 decorationPlants[10];
    /*0x2752*/ u8 decorationOrnaments[30];
    /*0x2770*/ u8 decorationMats[30];
    /*0x278E*/ u8 decorationPosters[10];
    /*0x2798*/ u8 decorationDolls[40];
    /*0x27C0*/ u8 decorationCushions[10];
    /*0x27CC*/ TVShow tvShows[10];
    /*0x2B50*/ PokeNews pokeNews[16];
    /*0x2B90*/ u16 outbreakPokemonSpecies;
    /*0x2B92*/ u8 outbreakLocationMapNum;
    /*0x2B93*/ u8 outbreakLocationMapGroup;
    /*0x2B94*/ u8 outbreakPokemonLevel;
    /*0x2B95*/ u8 outbreakUnused1;
    /*0x2B96*/ u16 outbreakUnused2;
    /*0x2B98*/ u16 outbreakPokemonMoves[4];
    /*0x2BA0*/ u8 outbreakUnused3;
    /*0x2BA1*/ u8 outbreakPokemonProbability;
    /*0x2BA2*/ u16 outbreakDaysLeft;
    /*0x2BA4*/ struct GabbyAndTyData gabbyAndTyData;
    /*0x2BB0*/ u16 easyChatProfile[6];
    /*0x2BBC*/ u16 easyChatBattleStart[6];
    /*0x2BC8*/ u16 easyChatBattleWon[6];
    /*0x2BD4*/ u16 easyChatBattleLost[6];
    /*0x2BE0*/ struct Mail mail[11];
    /*0x2E20*/ u8 additionalPhrases[NUM_ADDITIONAL_PHRASE_BYTES]; // bitfield for 33 additional phrases in easy chat system
    /*0x2E25*/ //u8 padding5[3];
    /*0x2E28*/ OldMan oldMan;
    /*0x2e64*/ struct DewfordTrend dewfordTrends[5];
    /*0x2e90*/ struct ContestWinner contestWinners[13]; // see CONTEST_WINNER_*
    /*0x3030*/ struct DayCare daycare;
    /*0x3150*/ struct LinkBattleRecords linkBattleRecords;
    /*0x31A8*/ u8 giftRibbons[11];
    /*0x31B3*/ struct ExternalEventData externalEventData;
    /*0x31C7*/ struct ExternalEventFlags externalEventFlags;
    /*0x31DC*/ struct Roamer roamer;
    /*0x31F8*/ struct EnigmaBerry enigmaBerry;
    /*0x322C*/ struct MysteryGiftSave mysteryGift;
    /*0x3598*/ u8 unused_3598[0x180];
    /*0x3718*/ u32 trainerHillTimes[4];
    /*0x3728*/ struct RamScript ramScript;
    /*0x3B14*/ struct RecordMixingGift recordMixingGift;
    /*0x3B24*/ u8 seen2[NUM_DEX_FLAG_BYTES];
    /*0x3B58*/ LilycoveLady lilycoveLady;
    /*0x3B98*/ struct TrainerNameRecord trainerNameRecords[20];
    /*0x3C88*/ u8 registeredTexts[10][21];
    /*0x3D5A*/ u8 unused_3D5A[10];
    /*0x3D64*/ struct TrainerHillSave trainerHill;
    /*0x3D70*/ struct WaldaPhrase waldaPhrase;
    /*0x3D88*/ u8 NuzlockeEncounterFlags[9]; //tx_randomizer_and_challenges
    u8 tx_Random_Chaos:1;
    u8 tx_Random_WildPokemon:1;
    u8 tx_Random_Similar:1;
    u8 tx_Random_MapBased:1;
    u8 tx_Random_IncludeLegendaries:1;
    u8 tx_Random_Type:1;
    u8 tx_Random_TypeEffectiveness:1;
    u8 tx_Random_Abilities:1;
    //
    u8 tx_Random_Moves:1;
    u8 tx_Random_Trainer:1;
    u8 tx_Random_Evolutions:1;
    u8 tx_Random_EvolutionMethods:1;
    u8 tx_Challenges_EvoLimit:2;
    u8 tx_Challenges_Nuzlocke:1;
    u8 tx_Challenges_NuzlockeHardcore:1;
    //
    u8 tx_Challenges_OneTypeChallenge:5;
    u8 tx_Challenges_PartyLimit:3;
    //
    u8 tx_Challenges_NoItemPlayer:1;
    u8 tx_Challenges_NoItemTrainer:1;
    u8 tx_Challenges_PkmnCenter:2;
    u8 tx_Random_OneForOne:1; //unused
    u8 tx_Challenges_BaseStatEqualizer:2;
    u8 tx_Challenges_LevelCap:2;
    u8 tx_Challenges_ExpMultiplier:2;
    u8 tx_Random_Items:1;
    u8 tx_Nuzlocke_SpeciesClause:1;
    u8 tx_Nuzlocke_ShinyClause:1;
    u8 tx_Nuzlocke_Nicknaming:1;
    u8 tx_Challenges_Mirror:1;
    u8 tx_Challenges_Mirror_Thief:1;
    u8 tx_Random_Static:1;
    u8 tx_Challenges_NoEVs:1;
    u8 tx_Challenges_TrainerScalingIVs:2;
    u8 tx_Challenges_TrainerScalingEVs:2;
    u8 tx_Nuzlocke_Deletion:1;
    u8 tx_Random_Starter:1;
    u8 dexNavSearchLevels[412];
    u8 dexNavChain;
    // sizeof: 0x3D88
};


#endif //MOEMON_EMERALD_SAVE_V1_H
