#include <stdio.h>
#include <time.h>
#include <string.h>
#include <unistd.h>
#include <conio.h>

#include "event.h"
#include "render.h"

#define PBSTR "||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||"
#define PBWIDTH 60

#define PBSTR "||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||"
#define PBWIDTH 60

void printProgress(double percentage, double max)
{
    int val = (int)(percentage * max);
    int lpad = (int)(percentage * PBWIDTH);
    int rpad = PBWIDTH - lpad;
    printf("\r%3ds % [%.*s%*s]", val, lpad, PBSTR, rpad, "");
    fflush(stdout);
}

// Render string with delayed time (seconds)
void delayedRender(const char *str, const int time)
{
    while (*str != '\0')
    {
        printf("%c", *(str++));
        if (*str == '\n')
        {
            usleep(time * 10000);
        }
    }
}

path renderEvent(const event e)
{
    delayedRender(e.scene, 3);
    system("@cls||clear");

    char *choicesBox = malloc((e.choicesCount * 255 + 16) * sizeof(char));
    choicesBox[0] = 0;

    for (int i = 0; i < e.choicesCount; i++)
    {
        char index[] = {i + '1', '.', ' ', 0};
        strcat(choicesBox, index);
        strcat(choicesBox, e.choices[i].message);
        strcat(choicesBox, "\n");
    }

    double progress = 1.0;
    const double interval = 0.01;
    while (progress > 0)
    {
        // input handling
        if (_kbhit())
        {
            int choice = _getch() - '0';
            if (choice >= 1 && choice <= e.choicesCount)
                return e.choices[choice - 1];
        }

        printf("%s\n", e.scene);
        printf("%s\n", e.message);
        printf("%s\n", choicesBox);
        if (e.timeout > 0)
        {
            printProgress(progress, e.timeout);
            progress -= interval;
            usleep(10000 * e.timeout);
            system("@cls||clear");
        }
        else
        {
            int choice = getch() - '0';
            if (choice >= 1 && choice <= e.choicesCount)
            {
                system("@cls||clear");
                return e.choices[choice - 1];
            }
        }
    }

    free(choicesBox);
    return e.choices[0];
}
