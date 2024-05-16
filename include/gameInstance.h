#ifndef GAMEINSTANCE_H
#define GAMEINSTANCE_H

#define N_ATTRIBUTE 1
#include "event.h"

typedef struct gameData
{
    // 1 -> Player Energy
    char label[N_ATTRIBUTE][256];
    int data[N_ATTRIBUTE];
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