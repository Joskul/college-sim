#ifndef EVENT_H
#define EVENT_H

typedef struct path path;
typedef struct event event;

typedef struct event
{
    char *scene;      // ASCII art of the scene
    char *message;    // Event message
    path *choices;    // Array of choices
    int choicesCount; // Number of choices available
    int timeout;      // Timeout in seconds // Default : -1 // If timeout go to choice 0 *Optional*
} event;

typedef struct path
{
    char *message;  // Choice message
    char *sMessage; // Summary message
    int energy;     // Energy usage
    int success;    // Success rate for Dijkstra
    event *dest;    // Next event
} path;

#endif /* EVENT_H */
