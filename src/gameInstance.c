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
    g.data.data[0] = 100;

    return g;
}

void updateGameData(gameInstance *g, action p)
{
    for (int i = 0; i < DATA_INSTANCE; i++)
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
        updateGameData(g, p);
        renderAction(p, g->data);

        switch (g->currentEventID)
        {
        case 2:
            flag = 0;
            break;
        }
    }
    freeEvents(g->eventList);
}