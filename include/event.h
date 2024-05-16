#ifndef EVENT_H
#define EVENT_H

typedef struct action action;
typedef struct event event;

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
    char *message;           // Choice message
    char *sMessage;          // Summary message
    int data[DATA_INSTANCE]; // Energy usage
    int success;             // Success rate for Dijkstra
    int destID;              // Next event
} action;

#endif /* EVENT_H */
