#ifndef GAMEINSTANCE_H
#define GAMEINSTANCE_H

#define DATA_INSTANCE 1
#include "event.h"

typedef struct gameConfig
{
    int startID;
    int endID;
} gameConfig;

typedef struct gameData
{
    // 1 -> Player Energy
    char label[DATA_INSTANCE][256];
    int data[DATA_INSTANCE];
} gameData;

typedef struct gameInstance
{
    event *eventList;
    int currentEventID;
    gameData data;
} gameInstance;

gameInstance initGame();
void updateGameData(gameInstance *g, action p);
void Go(gameInstance *g);

#endif