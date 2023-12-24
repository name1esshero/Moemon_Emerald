/**
 * @author Isaac Aronson (Discord: @luigi___) (github.com/aronson)
 * @details Records the original save file format structures and provides an upgrade method for them to v1.
 * original code by tustin2121
 */
#ifndef MOEMON_EMERALD_SAVE_V0_H
#define MOEMON_EMERALD_SAVE_V0_H

#include "global.h"
#include "save.h"
#include "malloc.h"

struct ObjectEvent_v0 {
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
    //u32 padding:4;
    u8 spriteId;
    u8 graphicsId;
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
};

struct SaveBlock2_v0 {
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
};

struct SaveBlock1_v0 {
    struct Coords16 pos;
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
    struct ObjectEvent_v0 objectEvents[16];
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

/**
 * The following is the function which copies all the data from the old save file to the new one.
 */

bool8 UpdateSave_v0_v1(const struct SaveSectorLocation *locations) {
    /** The passed locations structure has been filled with pointers to the old save data on the heap already.
     * We just need to assign the old save blocks to the pointers on the heap accordingly. (Again I'm using
     * literal numbers here as I'm being overly cautious: what if I change the SECTOR_IDs for the save blocks in
     * later save version?)
     */
    const struct SaveBlock2_v0 *sOldSaveBlock2Ptr = (struct SaveBlock2_v0 *) (locations[0].data); // SECTOR_ID_SAVEBLOCK2
    const struct SaveBlock1_v0 *sOldSaveBlock1Ptr = (struct SaveBlock1_v0 *) (locations[1].data); // SECTOR_ID_SAVEBLOCK1_START
    const struct PokemonStorage *sOldPokemonStoragePtr = (struct PokemonStorage *) (locations[5].data); // SECTOR_ID_PKMN_STORAGE_START
    u32 arg, i, j, k;

#define COPY_FIELD(field) gSaveBlock2Ptr->field = sOldSaveBlock2Ptr->field
#define COPY_BLOCK(field) CpuCopy16(&sOldSaveBlock2Ptr->field, &gSaveBlock2Ptr->field, sizeof(gSaveBlock2Ptr->field))
#define COPY_ARRAY(field) for(i = 0; i < min(ARRAY_COUNT(gSaveBlock2Ptr->field), ARRAY_COUNT(sOldSaveBlock2Ptr->field)); i++) gSaveBlock2Ptr->field[i] = sOldSaveBlock2Ptr->field[i];

    /** We need to fill in any data that's new in this version. */
    gSaveBlock2Ptr->_saveSentinel = 0xFF;
    gSaveBlock2Ptr->saveVersion = 1;

    COPY_ARRAY(playerName);
    COPY_FIELD(playerGender);
    COPY_FIELD(specialSaveWarpFlags);
    COPY_ARRAY(playerTrainerId);
    COPY_FIELD(playTimeHours);
    COPY_FIELD(playTimeMinutes);
    COPY_FIELD(playTimeSeconds);
    COPY_FIELD(playTimeVBlanks);
    COPY_FIELD(optionsButtonMode);
    COPY_FIELD(optionsTextSpeed);
    COPY_FIELD(optionsWindowFrameType);
    COPY_FIELD(optionsSound);
    COPY_FIELD(optionsBattleStyle);
    COPY_FIELD(optionsBattleSceneOff);
    COPY_FIELD(regionMapZoom);

    COPY_FIELD(pokedex);
    COPY_FIELD(localTimeOffset);
    COPY_FIELD(lastBerryTreeUpdate);
    COPY_FIELD(gcnLinkFlags);
    COPY_FIELD(encryptionKey);
    COPY_FIELD(playerApprentice);
    COPY_BLOCK(apprentices);
    COPY_FIELD(berryCrush);
    COPY_FIELD(pokeJump);
    COPY_FIELD(berryPick);
    COPY_BLOCK(hallRecords1P);
    COPY_BLOCK(hallRecords2P);
    COPY_BLOCK(contestLinkResults);
    COPY_FIELD(berryPick);
    COPY_FIELD(berryPick);
    COPY_FIELD(frontier);

#undef COPY_FIELD
#undef COPY_BLOCK
#undef COPY_ARRAY

#define COPY_FIELD(field) gSaveBlock1Ptr->field = sOldSaveBlock1Ptr->field
#define COPY_BLOCK(field) CpuCopy16(&sOldSaveBlock1Ptr->field, &gSaveBlock1Ptr->field, sizeof(gSaveBlock1Ptr->field))
#define COPY_ARRAY(field) for(i = 0; i < min(ARRAY_COUNT(gSaveBlock1Ptr->field), ARRAY_COUNT(sOldSaveBlock1Ptr->field)); i++) gSaveBlock1Ptr->field[i] = sOldSaveBlock1Ptr->field[i];

    COPY_FIELD(pos);
    COPY_FIELD(location);
    COPY_FIELD(continueGameWarp);
    COPY_FIELD(dynamicWarp);
    COPY_FIELD(lastHealLocation);
    COPY_FIELD(escapeWarp);
    COPY_FIELD(weather);
    COPY_FIELD(weatherCycleStage);
    COPY_FIELD(flashLevel);
    COPY_FIELD(savedMusic);
    COPY_FIELD(mapLayoutId);
    COPY_BLOCK(mapView);
    COPY_BLOCK(objectEvents);
    COPY_BLOCK(objectEventTemplates);

    COPY_FIELD(playerPartyCount);
    COPY_ARRAY(playerParty);

    COPY_FIELD(money);
    COPY_FIELD(coins);
    COPY_FIELD(registeredItem);

    COPY_ARRAY(pcItems);
    COPY_ARRAY(bagPocket_Items);
    COPY_ARRAY(bagPocket_KeyItems);
    COPY_ARRAY(bagPocket_PokeBalls);
    COPY_ARRAY(bagPocket_TMHM);
    COPY_ARRAY(bagPocket_Berries);

    COPY_BLOCK(pokeblocks);
    COPY_BLOCK(seen1);
    COPY_BLOCK(berryBlenderRecords);
    COPY_FIELD(trainerRematchStepCounter);
    COPY_BLOCK(trainerRematches);

    COPY_BLOCK(flags);
    COPY_BLOCK(vars);
    COPY_BLOCK(gameStats);
    COPY_BLOCK(berryTrees);
    COPY_BLOCK(secretBases);
    COPY_BLOCK(playerRoomDecorations);
    COPY_BLOCK(playerRoomDecorationPositions);
    COPY_BLOCK(decorationDesks);
    COPY_BLOCK(decorationChairs);
    COPY_BLOCK(decorationPlants);
    COPY_BLOCK(decorationOrnaments);
    COPY_BLOCK(decorationMats);
    COPY_BLOCK(decorationPosters);
    COPY_BLOCK(decorationDolls);
    COPY_BLOCK(decorationCushions);

    COPY_BLOCK(tvShows);
    COPY_BLOCK(pokeNews);
    COPY_FIELD(outbreakPokemonSpecies);
    COPY_FIELD(outbreakLocationMapNum);
    COPY_FIELD(outbreakLocationMapGroup);
    COPY_FIELD(outbreakPokemonLevel);
    COPY_FIELD(outbreakUnused1);
    COPY_FIELD(outbreakUnused2);
    COPY_BLOCK(outbreakPokemonMoves);
    COPY_FIELD(outbreakUnused3);
    COPY_FIELD(outbreakPokemonProbability);
    COPY_FIELD(outbreakDaysLeft);
    COPY_FIELD(gabbyAndTyData);
    COPY_BLOCK(easyChatProfile);
    COPY_BLOCK(easyChatBattleStart);
    COPY_BLOCK(easyChatBattleWon);
    COPY_BLOCK(easyChatBattleLost);
    COPY_BLOCK(mail);
    COPY_BLOCK(additionalPhrases);

    COPY_FIELD(oldMan);
    COPY_BLOCK(dewfordTrends);
    COPY_BLOCK(contestWinners);
    COPY_FIELD(daycare);
    COPY_FIELD(linkBattleRecords);
    COPY_BLOCK(giftRibbons);
    COPY_FIELD(externalEventData);
    COPY_FIELD(externalEventFlags);
    COPY_FIELD(roamer);
    COPY_FIELD(enigmaBerry);
    COPY_FIELD(mysteryGift);
    COPY_ARRAY(unused_3598);
    COPY_BLOCK(trainerHillTimes);
    COPY_FIELD(ramScript);
    COPY_FIELD(recordMixingGift);
    COPY_BLOCK(seen2);
    COPY_FIELD(lilycoveLady);
    COPY_BLOCK(trainerNameRecords);
    COPY_BLOCK(registeredTexts);
    COPY_ARRAY(unused_3D5A);
    COPY_FIELD(trainerHill);
    COPY_FIELD(waldaPhrase);


    COPY_ARRAY(NuzlockeEncounterFlags); //tx_randomizer_and_challenges
    COPY_FIELD(tx_Random_Chaos);
    COPY_FIELD(tx_Random_WildPokemon);
    COPY_FIELD(tx_Random_Similar);
    COPY_FIELD(tx_Random_MapBased);
    COPY_FIELD(tx_Random_IncludeLegendaries);
    COPY_FIELD(tx_Random_Type);
    COPY_FIELD(tx_Random_TypeEffectiveness);
    COPY_FIELD(tx_Random_Abilities);
    //
    COPY_FIELD(tx_Random_Moves);
    COPY_FIELD(tx_Random_Trainer);
    COPY_FIELD(tx_Random_Evolutions);
    COPY_FIELD(tx_Random_EvolutionMethods);
    COPY_FIELD(tx_Challenges_EvoLimit);
    COPY_FIELD(tx_Challenges_Nuzlocke);
    COPY_FIELD(tx_Challenges_NuzlockeHardcore);
    //
    COPY_FIELD(tx_Challenges_OneTypeChallenge);
    COPY_FIELD(tx_Challenges_PartyLimit);
    //
    COPY_FIELD(tx_Challenges_NoItemPlayer);
    COPY_FIELD(tx_Challenges_NoItemTrainer);
    COPY_FIELD(tx_Challenges_PkmnCenter);
    COPY_FIELD(tx_Random_OneForOne); //unused
    COPY_FIELD(tx_Challenges_BaseStatEqualizer);
    COPY_FIELD(tx_Challenges_LevelCap);
    COPY_FIELD(tx_Challenges_ExpMultiplier);
    COPY_FIELD(tx_Random_Items);
    COPY_FIELD(tx_Nuzlocke_SpeciesClause);
    COPY_FIELD(tx_Nuzlocke_ShinyClause);
    COPY_FIELD(tx_Nuzlocke_Nicknaming);
    COPY_FIELD(tx_Challenges_Mirror);
    COPY_FIELD(tx_Challenges_Mirror_Thief);
    COPY_FIELD(tx_Random_Static);
    COPY_FIELD(tx_Challenges_NoEVs);
    COPY_FIELD(tx_Challenges_TrainerScalingIVs);
    COPY_FIELD(tx_Challenges_TrainerScalingEVs);
    COPY_FIELD(tx_Nuzlocke_Deletion);
    COPY_FIELD(tx_Random_Starter);
    COPY_ARRAY(dexNavSearchLevels);
    COPY_FIELD(dexNavChain);

#undef COPY_FIELD
#undef COPY_BLOCK
#undef COPY_ARRAY

    /**
     * The pokemon structure hasn't changed at all this version, so
     * we can just assign across the old box storage to the new.  */
    *gPokemonStoragePtr = *sOldPokemonStoragePtr;

    /**
     * The most common kind of change that might happen between major versions are
     * map changes. The save file usually saves the area around the player and
     * event objects currently on the map, so that when the player resumes play,
     * everything will be exactly where it was when they saved. But if the map has
     * changed at all, this means there could be incongruity between the saved
     * version of the map and the new version in the updated ROM. So to make it so
     * that the map reloads properly, we use the "Continue Game Warp" usually used
     * when the player clears the game to place the player at a known position and
     * with a newly loaded map and event objects. Here, we're using the last location
     * that the player healed, so the player will appear in the same spot they would
     * as if they blacked out. */
    SetContinueGameWarpStatus();
    gSaveBlock1Ptr->continueGameWarp = gSaveBlock1Ptr->lastHealLocation;

    return TRUE;
}


#endif //MOEMON_EMERALD_SAVE_V0_H
