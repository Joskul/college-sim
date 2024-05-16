#ifndef RENDER_H
#define RENDER_H

#include "event.h"

void printProgress(double percentage, double max);
void delayedRenderLine(const char *str, const int time);
void delayedRenderText(const char *str, const double time);
action renderEvent(const event e, const gameData gd);
int renderAction(const action p, const gameData gd);

#endif /* RENDER_H */
