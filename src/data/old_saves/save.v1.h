/**
 * @author Isaac Aronson (Discord: @luigi___) (github.com/aronson)
 * @details Records the v1 save file format structures.
 * original code by tustin2121
 */
#ifndef MOEMON_EMERALD_SAVE_V1_H
#define MOEMON_EMERALD_SAVE_V1_H

#include "global.h"
#include "save.h"

struct ObjectEvent_v1 {
    u32 active: 1;
    u32 singleMovementActive: 1;
    u32 triggerGroundEffectsOnMove: 1;
    u32 triggerGroundEffectsOnStop: 1;
    u32 disableCoveringGroundEffects: 1;
    u32 landingJump: 1;
    u32 heldMovementActive: 1;
    u32 heldMovementFinished: 1;
    u32 frozen: 1;
    u32 facingDirectionLocked: 1;
    u32 disableAnim: 1;
    u32 enableAnim: 1;
    u32 inanimate: 1;
    u32 invisible: 1;
    u32 offScreen: 1;
    u32 trackedByCamera: 1;
    u32 isPlayer: 1;
    u32 hasReflection: 1;
    u32 inShortGrass: 1;
    u32 inShallowFlowingWater: 1;
    u32 inSandPile: 1;
    u32 inHotSprings: 1;
    u32 noShadow: 1;
    u32 spriteAnimPausedBackup: 1;
    u32 spriteAffineAnimPausedBackup: 1;
    u32 disableJumpLandingGroundEffect: 1;
    u32 fixedPriority: 1;
    u32 hideReflection: 1;
    u16 graphicsId;
    u8 movementType;
    u8 trainerType;
    u8 localId;
    u8 mapNum;
    u8 mapGroup;
    u8 currentElevation: 4;
    u8 previousElevation: 4;
    struct Coords16 initialCoords;
    struct Coords16 currentCoords;
    struct Coords16 previousCoords;
    u16 facingDirection: 4; // current direction?
    u16 movementDirection: 4;
    u16 rangeX: 4;
    u16 rangeY: 4;
    u8 fieldEffectSpriteId;
    u8 warpArrowSpriteId;
    u8 movementActionId;
    u8 trainerRange_berryTreeId;
    u8 currentMetatileBehavior;
    u8 previousMetatileBehavior;
    u8 previousMovementDirection;
    u8 directionSequenceIndex;
    union __attribute__((packed)) {
        u8 playerCopyableMovement; // COPY_MOVE_*
        struct __attribute__((packed)) {
            u16 species: 10; // 11 bits; 1024 species
            u16 form: 5; // Used for Deoxys, Unown, etc
            u16 shiny: 1;
        } mon;
        u16 asU16;
    } extra;
    u8 spriteId;
};

struct SaveBlock2_v1 {
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
    u16 optionsTextSpeed: 3; // OPTIONS_TEXT_SPEED_[SLOW/MID/FAST]
    u16 optionsWindowFrameType: 5; // Specifies one of the 20 decorative borders for text boxes
    u16 optionsSound: 1; // OPTIONS_SOUND_[MONO/STEREO]
    u16 optionsBattleStyle: 1; // OPTIONS_BATTLE_STYLE_[SHIFT/SET]
    u16 optionsBattleSceneOff: 1; // whether battle animations are disabled
    u16 regionMapZoom: 1; // whether the map is zoomed in
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

struct SaveBlock1_v1 {
    struct Coords16 pos
    struct WarpData location;
    struct WarpData continueGameWarp;
    struct WarpData dynamicWarp;
    struct WarpData lastHealLocation; // used by white-out and teleport
    struct WarpData escapeWarp; // used by Dig and Escape Rope
    u16 savedMusic;
    u8 weather;
    u8 weatherCycleStage;
    u8 flashLevel;
    //u8 padding1;
    u16 mapLayoutId;
    u16 mapView[0x100];
    u8 playerPartyCount;
    //u8 padding2[3];
    struct Pokemon playerParty[6];
    u32 money;
    u16 coins;
    u16 registeredItem; // registered for use with SELECT button
    struct ItemSlot pcItems[50];
    struct ItemSlot bagPocket_Items[30];
    struct ItemSlot bagPocket_KeyItems[30];
    struct ItemSlot bagPocket_PokeBalls[16];
    struct ItemSlot bagPocket_TMHM[64];
    struct ItemSlot bagPocket_Berries[46];
    struct Pokeblock pokeblocks[40];
    u8 seen1[52];   //52 bytes
    u16 berryBlenderRecords[3];
    u8 unused_9C2[6];
    u16 trainerRematchStepCounter;    //104 bytes
    u8 trainerRematches[100];
    //u8 padding3[2];
    struct ObjectEvent_v1 objectEvents[16];
    struct ObjectEventTemplate objectEventTemplates[64];
    u8 flags[300];
    u16 vars[256];
    u32 gameStats[64];
    struct BerryTree berryTrees[128];
    struct SecretBase secretBases[10];
    u8 playerRoomDecorations[12];
    u8 playerRoomDecorationPositions[12];
    u8 decorationDesks[10];
    u8 decorationChairs[10];
    u8 decorationPlants[10];
    u8 decorationOrnaments[30];
    u8 decorationMats[30];
    u8 decorationPosters[10];
    u8 decorationDolls[40];
    u8 decorationCushions[10];
    TVShow tvShows[10];
    PokeNews pokeNews[16];
    u16 outbreakPokemonSpecies;
    u8 outbreakLocationMapNum;
    u8 outbreakLocationMapGroup;
    u8 outbreakPokemonLevel;
    u8 outbreakUnused1;
    u16 outbreakUnused2;
    u16 outbreakPokemonMoves[4];
    u8 outbreakUnused3;
    u8 outbreakPokemonProbability;
    u16 outbreakDaysLeft;
    struct GabbyAndTyData gabbyAndTyData;
    u16 easyChatProfile[6];
    u16 easyChatBattleStart[6];
    u16 easyChatBattleWon[6];
    u16 easyChatBattleLost[6];
    struct Mail mail[11];
    u8 additionalPhrases[5]; // bitfield for 33 additional phrases in easy chat system
    //u8 padding5[3];
    OldMan oldMan;
    struct DewfordTrend dewfordTrends[5];
    struct ContestWinner contestWinners[13]; // see CONTEST_WINNER_*
    struct DayCare daycare;
    struct LinkBattleRecords linkBattleRecords;
    u8 giftRibbons[11];
    struct ExternalEventData externalEventData;
    struct ExternalEventFlags externalEventFlags;
    struct Roamer roamer;
    struct EnigmaBerry enigmaBerry;
    struct MysteryGiftSave mysteryGift;
    u8 unused_3598[0x180];
    u32 trainerHillTimes[4];
    struct RamScript ramScript;
    struct RecordMixingGift recordMixingGift;
    u8 seen2[52];
    LilycoveLady lilycoveLady;
    struct TrainerNameRecord trainerNameRecords[20];
    u8 registeredTexts[10][21];
    u8 unused_3D5A[10];
    struct TrainerHillSave trainerHill;
    struct WaldaPhrase waldaPhrase;
    // Additional fields beyond retail
    u8 NuzlockeEncounterFlags[9]; //tx_randomizer_and_challenges
    u8 tx_Random_Chaos: 1;
    u8 tx_Random_WildPokemon: 1;
    u8 tx_Random_Similar: 1;
    u8 tx_Random_MapBased: 1;
    u8 tx_Random_IncludeLegendaries: 1;
    u8 tx_Random_Type: 1;
    u8 tx_Random_TypeEffectiveness: 1;
    u8 tx_Random_Abilities: 1;
    //
    u8 tx_Random_Moves: 1;
    u8 tx_Random_Trainer: 1;
    u8 tx_Random_Evolutions: 1;
    u8 tx_Random_EvolutionMethods: 1;
    u8 tx_Challenges_EvoLimit: 2;
    u8 tx_Challenges_Nuzlocke: 1;
    u8 tx_Challenges_NuzlockeHardcore: 1;
    //
    u8 tx_Challenges_OneTypeChallenge: 5;
    u8 tx_Challenges_PartyLimit: 3;
    //
    u8 tx_Challenges_NoItemPlayer: 1;
    u8 tx_Challenges_NoItemTrainer: 1;
    u8 tx_Challenges_PkmnCenter: 2;
    u8 tx_Random_OneForOne: 1; //unused
    u8 tx_Challenges_BaseStatEqualizer: 2;
    u8 tx_Challenges_LevelCap: 2;
    u8 tx_Challenges_ExpMultiplier: 2;
    u8 tx_Random_Items: 1;
    u8 tx_Nuzlocke_SpeciesClause: 1;
    u8 tx_Nuzlocke_ShinyClause: 1;
    u8 tx_Nuzlocke_Nicknaming: 1;
    u8 tx_Challenges_Mirror: 1;
    u8 tx_Challenges_Mirror_Thief: 1;
    u8 tx_Random_Static: 1;
    u8 tx_Challenges_NoEVs: 1;
    u8 tx_Challenges_TrainerScalingIVs: 2;
    u8 tx_Challenges_TrainerScalingEVs: 2;
    u8 tx_Nuzlocke_Deletion: 1;
    u8 tx_Random_Starter: 1;
    u8 dexNavSearchLevels[412];
    u8 dexNavChain;
};

#endif //MOEMON_EMERALD_SAVE_V1_H
