#ifndef RENDER_H
#define RENDER_H

#include "event.h"

void printProgress(double percentage, double max);
void delayedRender(const char *str, const int time);
path renderEvent(const event e);

#endif /* RENDER_H */
