#include "gameInstance.h"
#include "event.h"
#include "eventLoader.h"
#include "render.h"

#include <string.h>

gameInstance initGame()
{
    gameInstance g;
    int eventCount = 0;
    g.currentEventID = 0;
    g.eventList = loadEvents("./events", &eventCount);
    strcpy(g.data.label[0], "ENERGY");

    return g;
}

void updateGameData(gameInstance *g, action p)
{
    for (int i = 0; i < N_ATTRIBUTE; i++)
    {
        g->data.data[i] += p.data[i];
    }
    g->currentEventID = p.destID;
}

void Go(gameInstance *g)
{
    int flag = 1;
    while (flag)
    {

        action p = renderEvent(g->eventList[g->currentEventID], g->data);
        if (g->eventList[g->currentEventID].aCount == 0)
        {
            flag = 0;
            break;
        }
        updateGameData(g, p);
        renderAction(p, g->data);
    }
    freeEvents(g->eventList);
}