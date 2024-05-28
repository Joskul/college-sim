#ifndef EVENT_LOADER_H
#define EVENT_LOADER_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <dirent.h>
#include <sys/stat.h>
#include "event.h"

// Function to load all events from a directory
event *loadEvents(const char *directory, int *eventCount);

void freeEvents(event *events);

#endif /* EVENT_LOADER_H */
