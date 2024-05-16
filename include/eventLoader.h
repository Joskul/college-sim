#ifndef EVENTLOADER_H
#define EVENTLOADER_H

#include "event.h"
#include <stdio.h>

char *trim(char *str);
char *parseScene(FILE *file);
char *parseString(FILE *file);
int parseInt(FILE *file);
void freeEvent(event e);
event parseEvent(FILE *file);
event readEventFromFile(const char *filename);
event *loadEvents(const char *folder, int *count);

#endif /* EVENTLOADER_H */
