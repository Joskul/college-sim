#include "gameInstance.h"
#include "event.h"
#include "eventLoader.h"
#include "render.h"

#include <string.h>

gameInstance initGame()
{
    gameInstance g;
    g.currentEventID = 0;
    g.eventList = loadEvents("./events", &g.eventCount);
    strcpy(g.dataLabel[0], "ENERGY");
    g.data[0] = 100;

    return g;
}

void updateGameData(gameInstance *g, action p)
{
    for (int i = 0; i < N_ATTRIBUTE; i++)
    {
        g->data[i] += p.data[i];
    }
    g->currentEventID = p.destID;
}

void Go(gameInstance *g)
{
    int flag = 1;
    while (flag)
    {

        action p = renderEvent(g->eventList[g->currentEventID], *g);
        if (g->eventList[g->currentEventID].aCount == 0)
        {
            flag = 0;
            break;
        }
        updateGameData(g, p);
        renderAction(p, *g);
    }
    freeEvents(g->eventList);
}