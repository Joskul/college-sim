#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include <unistd.h>
#include <conio.h>

#include "event.h"
#include "render.h"
#include "pathFinding.h"

#define PBSTR "||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||"
#define PBWIDTH 60

#define ANSI_COLOR_RED "\x1b[31m"
#define ANSI_COLOR_GREEN "\x1b[32m"
#define ANSI_COLOR_YELLOW "\x1b[33m"
#define ANSI_COLOR_BLUE "\x1b[34m"
#define ANSI_COLOR_MAGENTA "\x1b[35m"
#define ANSI_COLOR_CYAN "\x1b[36m"
#define ANSI_COLOR_GREY "\x1b[90m"
#define ANSI_COLOR_RESET "\x1b[0m"

void printProgress(double progress, double max)
{
    int val = (int)(progress * max);
    int lpad = (int)(progress * PBWIDTH);
    int rpad = PBWIDTH - lpad;
    printf("\r%3ds % [%.*s%*s]", val, lpad, PBSTR, rpad, "");
    fflush(stdout);
}

// Render string with delayed time (seconds)
void delayedRenderLine(const char *str, const int time)
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

// Render string with delayed time (seconds)
void delayedRenderText(const char *str, const double time)
{
    int counter = 0;
    while (*str != '\0')
    {
        printf("%c", *(str++));
        counter++;
        usleep(time * 10000);
    }
}

action renderEvent(const event e, const gameInstance gd)
{
    printf("\n");
    delayedRenderLine(e.scene, 3);
    system("@cls||clear");

    // printEvent(e);

    char *choicesBox = malloc((e.aCount * 255 + 16) * sizeof(char));
    choicesBox[0] = 0;

    int suggestion = suggestAction(gd.currentEventID, gd.eventList);

    for (int i = 0; i < e.aCount; i++)
    {
        char index[] = {i + '1', '.', ' ', 0};
        char statBuf[32] = "\0";
        char stats[32 * N_ATTRIBUTE] = "\0";
        int meetsCondition = 1;

        for (int j = 0; j < N_ATTRIBUTE; j++)
        {
            if (gd.data[j] < e.actions[i].condition[j])
            {
                meetsCondition = 0;
                break;
            }
        }

        if (meetsCondition)
        {
            for (int j = 0; j < N_ATTRIBUTE; j++)
            {
                sprintf(statBuf, ANSI_COLOR_YELLOW " (%d %s)" ANSI_COLOR_RESET, e.actions[i].data[0], e.actions[i].dataLabel);
                strcat(stats, statBuf);
            }
            strcat(choicesBox, index);
            if (e.actions[i].success == 1)
            {
                strcat(choicesBox, ANSI_COLOR_GREEN);
            }
            else if (e.actions[i].success == 3)
            {
                strcat(choicesBox, ANSI_COLOR_RED);
            }
        }
        else
        {
            for (int j = 0; j < N_ATTRIBUTE; j++)
            {
                sprintf(statBuf, ANSI_COLOR_YELLOW " (%d %s)" ANSI_COLOR_RESET, e.actions[i].data[0], e.actions[i].dataLabel);
                strcat(stats, statBuf);
            }
            strcat(choicesBox, ANSI_COLOR_GREY);
            strcat(choicesBox, index);
        }

        strcat(choicesBox, e.actions[i].message);
        strcat(choicesBox, ANSI_COLOR_RESET);
        strcat(choicesBox, stats);
        if (i == suggestion)
        {
            strcat(choicesBox, ANSI_COLOR_GREEN "*" ANSI_COLOR_RESET);
        }
        strcat(choicesBox, "\n");
    }

    double progress = 1.0;
    const double interval = 0.01;
    while (progress > 0)
    {
        // Input handling
        if (_kbhit())
        {
            int choice = _getch() - '0';
            if (choice >= 1 && choice <= e.aCount)
            {
                int meetsCondition = 1;
                for (int j = 0; j < N_ATTRIBUTE; j++)
                {
                    if (gd.data[j] < e.actions[choice - 1].condition[j])
                    {
                        meetsCondition = 0;
                        break;
                    }
                }

                if (meetsCondition)
                {
                    free(choicesBox);
                    return e.actions[choice - 1];
                }
            }
        }

        for (int i = 0; i < N_ATTRIBUTE; i++)
        {
            printf(ANSI_COLOR_YELLOW "%s : %d " ANSI_COLOR_RESET, gd.dataLabel[i], gd.data[i]);
        }
        printf("\n%s\n", e.scene);
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
            if (choice >= 1 && choice <= e.aCount)
            {
                int meetsCondition = 1;
                for (int j = 0; j < N_ATTRIBUTE; j++)
                {
                    if (gd.data[j] < e.actions[choice - 1].condition[j])
                    {
                        meetsCondition = 0;
                        break;
                    }
                }

                if (meetsCondition)
                {
                    system("@cls||clear");
                    free(choicesBox);
                    return e.actions[choice - 1];
                }
            }
        }

        if (e.aCount == 0)
        {
            sleep(1);
            free(choicesBox);
            action emptyAction = {"", "", {0}, {""}, {0}, 0, 0};
            return emptyAction;
        }
    }

    free(choicesBox);
    return e.actions[0];
}

int renderAction(const action act, const gameInstance gd)
{
    char *str = malloc((strlen(act.sMessage) * 64) * sizeof(char));

    if (act.success <= 1)
    {
        sprintf(str, ANSI_COLOR_GREEN "%s" ANSI_COLOR_RESET, act.sMessage);
    }
    else if (act.success <= 2)
    {
        sprintf(str, "%s", act.sMessage);
    }
    else
    {
        sprintf(str, ANSI_COLOR_RED "%s" ANSI_COLOR_RESET, act.sMessage);
    }
    delayedRenderText(str, 5);
    sleep(1);
    system("@cls||clear");

    free(str);

    return act.destID;
}
