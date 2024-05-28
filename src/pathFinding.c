#include <limits.h>
#include <stdlib.h>
#include "event.h"
#include "pathFinding.h"

// Helper function to find the index of an event by its ID
int findEventIndexByID(event *events, int eventID)
{
    int i = 0;
    while (events[i].scene != NULL)
    {
        if (events[i].id == eventID)
        {
            return i;
        }
        i++;
    }
    return -1; // Event not found
}

// Recursive function to find the shortest path to an ending event
int findShortestPath(int currentIndex, event *events, int *visited)
{
    if (events[currentIndex].aCount == 0)
    {
        return 0; // Reached an ending event
    }

    visited[currentIndex] = 1;
    int minDistance = INT_MAX;

    for (int i = 0; i < events[currentIndex].aCount; i++)
    {
        int nextEventID = events[currentIndex].actions[i].destID;
        int nextIndex = findEventIndexByID(events, nextEventID);

        if (nextIndex != -1 && !visited[nextIndex])
        {
            int distance = events[currentIndex].actions[i].success +
                           findShortestPath(nextIndex, events, visited);

            if (distance < minDistance)
            {
                minDistance = distance;
            }
        }
    }

    visited[currentIndex] = 0;
    return minDistance;
}

int findClosestEndingEvent(int currentEventID, event *events)
{
    int closestEventID = -1;
    int minDistance = INT_MAX;

    // Find the index of the current event
    int currentIndex = findEventIndexByID(events, currentEventID);
    if (currentIndex == -1)
    {
        return -1; // Current event ID not found
    }

    // Determine the number of events
    int eventCount = 0;
    while (events[eventCount].scene != NULL)
    {
        eventCount++;
    }

    // Array to track visited events
    int *visited = (int *)calloc(eventCount, sizeof(int));

    // Traverse the events to find the closest ending event
    for (int i = 0; events[i].scene != NULL; i++)
    {
        if (events[i].aCount == 0)
        {
            // Calculate the distance from the current event to this ending event
            int distance = findShortestPath(currentIndex, events, visited);

            if (distance < minDistance)
            {
                minDistance = distance;
                closestEventID = events[i].id;
            }
        }
    }

    free(visited);
    return closestEventID;
}

int findActionToTarget(int currentEventID, int targetEventID, event *events)
{
    int currentIndex = findEventIndexByID(events, currentEventID);
    if (currentIndex == -1)
    {
        return -1; // Current event ID not found
    }

    // Array to track visited events
    int eventCount = 0;
    while (events[eventCount].scene != NULL)
    {
        eventCount++;
    }
    int *visited = (int *)calloc(eventCount, sizeof(int));

    int actionIndex = -1;
    int minDistance = INT_MAX;

    for (int i = 0; i < events[currentIndex].aCount; i++)
    {
        int nextEventID = events[currentIndex].actions[i].destID;
        int nextIndex = findEventIndexByID(events, nextEventID);

        if (nextIndex != -1 && !visited[nextIndex])
        {
            int distance = events[currentIndex].actions[i].success +
                           findShortestPath(nextIndex, events, visited);

            if (distance < minDistance)
            {
                minDistance = distance;
                actionIndex = i;
            }
        }
    }

    free(visited);
    return actionIndex;
}

int suggestAction(int currentEventID, event *events)
{
    return findActionToTarget(currentEventID, findClosestEndingEvent(currentEventID, events), events);
}