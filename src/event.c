#include "event.h"

void printEvent(event evt)
{
    printf("Scene:\n%s\n", evt.scene);
    printf("Message:\n%s\n", evt.message);
    printf("Timeout: %d\n", evt.timeout);
    printf("Number of Actions: %d\n", evt.aCount);

    for (int i = 0; i < evt.aCount; ++i)
    {
        printf("\nAction %d:\n", i + 1);
        printf("  Message: %s\n", evt.actions[i].message);
        printf("  Summary Message: %s\n", evt.actions[i].sMessage);

        printf("  Data:\n");
        for (int j = 0; j < N_ATTRIBUTE; ++j)
        {
            printf("    %s: %d\n", evt.actions[i].dataLabel[j], evt.actions[i].data[j]);
        }

        printf("  Conditions:\n");
        for (int j = 0; j < N_ATTRIBUTE; ++j)
        {
            printf("    Condition %d: %d\n", j, evt.actions[i].condition[j]);
        }

        printf("  Success: %d\n", evt.actions[i].success);
        printf("  Destination ID: %d\n", evt.actions[i].destID);
    }
}
