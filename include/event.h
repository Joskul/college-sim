#ifndef EVENT_H
#define EVENT_H

typedef struct action action;
typedef struct event event;

#include <stdio.h>
#include "gameInstance.h"

typedef struct event
{
    char *scene;     // ASCII art of the scene
    char *message;   // Event message
    int timeout;     // Timeout in seconds // Default : -1 // If timeout go to choice 0 *Optional*
    action *actions; // Array of actions
    int aCount;      // Number of actions available
} event;

typedef struct action
{
    char *message;                    // Choice message
    char *sMessage;                   // Summary message
    int data[N_ATTRIBUTE];            // Game data that will be modified
    char dataLabel[N_ATTRIBUTE][128]; // Game data label
    int condition[N_ATTRIBUTE];       // Minimum energy required
    int success;                      // Success rate for Dijkstra
    int destID;                       // Next event
} action;

void printEvent(event evt);

#endif /* EVENT_H */
