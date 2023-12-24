#ifndef MOEMON_EMERALD_SAVE_V0_H
#define MOEMON_EMERALD_SAVE_V0_H

#include "global.h"
#include "save.h"
#include "malloc.h"

struct ObjectEvent_v0
{
    /*0x00*/ u32 active:1;
    u32 singleMovementActive:1;
    u32 triggerGroundEffectsOnMove:1;
    u32 triggerGroundEffectsOnStop:1;
    u32 disableCoveringGroundEffects:1;
    u32 landingJump:1;
    u32 heldMovementActive:1;
    u32 heldMovementFinished:1;
    /*0x01*/ u32 frozen:1;
    u32 facingDirectionLocked:1;
    u32 disableAnim:1;
    u32 enableAnim:1;
    u32 inanimate:1;
    u32 invisible:1;
    u32 offScreen:1;
    u32 trackedByCamera:1;
    /*0x02*/ u32 isPlayer:1;
    u32 hasReflection:1;
    u32 inShortGrass:1;
    u32 inShallowFlowingWater:1;
    u32 inSandPile:1;
    u32 inHotSprings:1;
    u32 noShadow:1;
    u32 spriteAnimPausedBackup:1;
    /*0x03*/ u32 spriteAffineAnimPausedBackup:1;
    u32 disableJumpLandingGroundEffect:1;
    u32 fixedPriority:1;
    u32 hideReflection:1;
    //u32 padding:4;
    /*0x04*/ u8 spriteId;
    /*0x05*/ u8 graphicsId;
    /*0x06*/ u8 movementType;
    /*0x07*/ u8 trainerType;
    /*0x08*/ u8 localId;
    /*0x09*/ u8 mapNum;
    /*0x0A*/ u8 mapGroup;
    /*0x0B*/ u8 currentElevation:4;
    u8 previousElevation:4;
    /*0x0C*/ struct Coords16 initialCoords;
    /*0x10*/ struct Coords16 currentCoords;
    /*0x14*/ struct Coords16 previousCoords;
    /*0x18*/ u16 facingDirection:4; // current direction?
    u16 movementDirection:4;
    u16 rangeX:4;
    u16 rangeY:4;
    /*0x1A*/ u8 fieldEffectSpriteId;
    /*0x1B*/ u8 warpArrowSpriteId;
    /*0x1C*/ u8 movementActionId;
    /*0x1D*/ u8 trainerRange_berryTreeId;
    /*0x1E*/ u8 currentMetatileBehavior;
    /*0x1F*/ u8 previousMetatileBehavior;
    /*0x20*/ u8 previousMovementDirection;
    /*0x21*/ u8 directionSequenceIndex;
    /*0x22*/ union __attribute__((packed)) {
        u8 playerCopyableMovement; // COPY_MOVE_*
        struct __attribute__((packed)) {
            u16 species:10; // 11 bits; 1024 species
            u16 form:5; // Used for Deoxys, Unown, etc
            u16 shiny:1;
        } mon;
        u16 asU16;
    } extra;
    /*size = 0x24*/
};

struct SaveBlock2_v0 {
    /*0x00*/ u8 playerName[7 + 1];
    /*0x08*/ u8 playerGender; // MALE, FEMALE
    /*0x09*/ u8 specialSaveWarpFlags;
    /*0x0A*/ u8 playerTrainerId[4];
    /*0x0E*/ u16 playTimeHours;
    /*0x10*/ u8 playTimeMinutes;
    /*0x11*/ u8 playTimeSeconds;
    /*0x12*/ u8 playTimeVBlanks;
    /*0x13*/ u8 optionsButtonMode;  // OPTIONS_BUTTON_MODE_[NORMAL/LR/L_EQUALS_A]
    /*0x14*/ u16 optionsTextSpeed: 3; // OPTIONS_TEXT_SPEED_[SLOW/MID/FAST]
    u16 optionsWindowFrameType: 5; // Specifies one of the 20 decorative borders for text boxes
    u16 optionsSound: 1; // OPTIONS_SOUND_[MONO/STEREO]
    u16 optionsBattleStyle: 1; // OPTIONS_BATTLE_STYLE_[SHIFT/SET]
    u16 optionsBattleSceneOff: 1; // whether battle animations are disabled
    u16 regionMapZoom: 1; // whether the map is zoomed in
    //u16 padding1:4;
    //u16 padding2;
    /*0x18*/ struct Pokedex pokedex;
    /*0x90*/ u8 filler_90[0x8];
    /*0x98*/ struct Time localTimeOffset;
    /*0xA0*/ struct Time lastBerryTreeUpdate;
    /*0xA8*/ u32 gcnLinkFlags; // Read by Pokemon Colosseum/XD
    /*0xAC*/ u32 encryptionKey;
    /*0xB0*/ struct PlayersApprentice playerApprentice;
    /*0xDC*/ struct Apprentice apprentices[2];   //272 bytes
    /*0x1EC*/ struct BerryCrush berryCrush;
    /*0x1FC*/ struct PokemonJumpRecords pokeJump;
    /*0x20C*/ struct BerryPickingResults berryPick;
    /*0x21C*/ struct RankingHall1P hallRecords1P[9][2][3]; // From record mixing.
    /*0x57C*/ struct RankingHall2P hallRecords2P[2][3]; // From record mixing.
    /*0x624*/ u16 contestLinkResults[5][4];
    /*0x64C*/ struct BattleFrontier frontier;
}; // sizeof=0xF2C

struct SaveBlock1_v0 {
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
    /*0xA30*/ struct ObjectEvent_v0 objectEvents[16];
    /*0xC70*/ struct ObjectEventTemplate objectEventTemplates[64];
    /*0x1270*/ u8 flags[300];
    /*0x139C*/ u16 vars[256];
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
    /*0x2E20*/ u8 additionalPhrases[5]; // bitfield for 33 additional phrases in easy chat system
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
    /*0x3B24*/ u8 seen2[52];
    /*0x3B58*/ LilycoveLady lilycoveLady;
    /*0x3B98*/ struct TrainerNameRecord trainerNameRecords[20];
    /*0x3C88*/ u8 registeredTexts[10][21];
    /*0x3D5A*/ u8 unused_3D5A[10];
    /*0x3D64*/ struct TrainerHillSave trainerHill;
    /*0x3D70*/ struct WaldaPhrase waldaPhrase;
    /*0x3D88*/ u8 NuzlockeEncounterFlags[9]; //tx_randomizer_and_challenges
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
    // sizeof: 0x3D88
};

bool8 UpdateObjectEvent_v0_v1(const struct ObjectEvent_v0 *in, struct ObjectEvent *out) {
#define COPY_FIELD(field) out->field = in->field;
    COPY_FIELD(active);
    COPY_FIELD(singleMovementActive);
    COPY_FIELD(triggerGroundEffectsOnMove);
    COPY_FIELD(triggerGroundEffectsOnStop);
    COPY_FIELD(disableCoveringGroundEffects);
    COPY_FIELD(landingJump);
    COPY_FIELD(heldMovementActive);
    COPY_FIELD(heldMovementFinished);
    COPY_FIELD(frozen);
    COPY_FIELD(facingDirectionLocked);
    COPY_FIELD(disableAnim);
    COPY_FIELD(enableAnim);
    COPY_FIELD(inanimate);
    COPY_FIELD(invisible);
    COPY_FIELD(offScreen);
    COPY_FIELD(trackedByCamera);
    COPY_FIELD(isPlayer);
    COPY_FIELD(hasReflection);
    COPY_FIELD(inShortGrass);
    COPY_FIELD(inShallowFlowingWater);
    COPY_FIELD(inSandPile);
    COPY_FIELD(inHotSprings);
    COPY_FIELD(noShadow);
    COPY_FIELD(spriteAnimPausedBackup);
    COPY_FIELD(spriteAffineAnimPausedBackup);
    COPY_FIELD(disableJumpLandingGroundEffect);
    COPY_FIELD(fixedPriority);
    COPY_FIELD(hideReflection);
    COPY_FIELD(graphicsId);
    COPY_FIELD(movementType);
    COPY_FIELD(trainerType);
    COPY_FIELD(localId);
    COPY_FIELD(mapNum);
    COPY_FIELD(mapGroup);
    COPY_FIELD(currentElevation);
    COPY_FIELD(previousElevation);
    out->initialCoords = in->initialCoords;
    out->currentCoords = in->currentCoords;
    out->previousCoords = in->previousCoords;
    COPY_FIELD(facingDirection);
    COPY_FIELD(movementDirection);
    COPY_FIELD(rangeX);
    COPY_FIELD(rangeY);
    COPY_FIELD(fieldEffectSpriteId);
    COPY_FIELD(warpArrowSpriteId);
    COPY_FIELD(movementActionId);
    COPY_FIELD(trainerRange_berryTreeId);
    COPY_FIELD(currentMetatileBehavior);
    COPY_FIELD(previousMetatileBehavior);
    COPY_FIELD(previousMovementDirection);
    COPY_FIELD(directionSequenceIndex);
    CpuCopy16(&in->extra, &out->extra, sizeof(in->extra));
#undef COPY_FIELD
}

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
    /** Convert over all the object events from the old format for the Ghoul expansion */
    for (i = 0; i < ARRAY_COUNT(&sOldSaveBlock1Ptr->objectEvents); i++)
    {
        UpdateObjectEvent_v0_v1(&sOldSaveBlock1Ptr->objectEvents[i], &gSaveBlock1Ptr->objectEvents[i]);
    }
    /** For some reason we also need to copy the block or else sprites won't show up */
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

    return 1;
}


#endif //MOEMON_EMERALD_SAVE_V0_H
