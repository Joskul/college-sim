#ifndef GAMEINSTANCE_H
#define GAMEINSTANCE_H

#define N_ATTRIBUTE 1
#include "event.h"

typedef struct gameInstance
{
    event *eventList;

    int eventCount; // number of events
    int currentEventID;
    int turnCount; // number of events occured

    char dataLabel[N_ATTRIBUTE][256];
    int data[N_ATTRIBUTE];
} gameInstance;

gameInstance initGame();
void updateGameData(gameInstance *g, action p);
void Go(gameInstance *g);

#endif