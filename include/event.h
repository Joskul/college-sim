#ifndef EVENT_H
#define EVENT_H

typedef struct action action;
typedef struct event event;

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
    char *message;  // Choice message
    char *sMessage; // Summary message
    int energy;     // Energy usage
    int success;    // Success rate for Dijkstra
    event *dest;    // Next event
} action;

#endif /* EVENT_H */
