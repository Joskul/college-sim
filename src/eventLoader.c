#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <dirent.h>
#include <sys/stat.h>
#include <ctype.h>
#include "event.h"
#include "eventLoader.h"

char *parseScene(FILE *file)
{
    char buffer[1024];
    size_t sectionSize = 1024;
    char *section = malloc(sectionSize);
    size_t len = 0;

    // Skip opening bracket '{'
    fgets(buffer, sizeof(buffer), file);

    while (fgets(buffer, sizeof(buffer), file) != NULL)
    {
        // Check for end of scene (closing bracket '}')
        if (buffer[0] == '}')
            break;

        // Append to section
        size_t bufferLen = strlen(buffer);
        if (len + bufferLen + 1 >= sectionSize)
        {
            sectionSize *= 2;
            section = realloc(section, sectionSize);
        }
        strcpy(section + len, buffer);
        len += bufferLen;
    }

    // printf("%s\n", section);
    return section;
}

char *parseString(FILE *file)
{
    char buffer[1024];
    size_t sectionSize = 1024;
    char *section = malloc(sectionSize);
    size_t len = 0;

    // Skip opening bracket '{'
    fgets(buffer, sizeof(buffer), file);

    while (fgets(buffer, sizeof(buffer), file) != NULL)
    {
        // Trim leading and trailing whitespace
        char *trimmed = buffer;
        while (isspace(*trimmed))
            trimmed++;

        // Remove newline character
        char *newline = strchr(trimmed, '\n');
        if (newline)
            *newline = '\0';

        // Check for end of string
        if (trimmed[0] == '}')
            break;

        // Append to section
        size_t bufferLen = strlen(trimmed);
        if (len + bufferLen + 1 >= sectionSize)
        {
            sectionSize *= 2;
            section = realloc(section, sectionSize);
        }
        strcpy(section + len, trimmed);
        len += bufferLen;
    }
    fscanf(file, " %*[}]");

    // printf("STR: %s\n", section);

    return section;
}

int parseInt(FILE *file)
{
    int value;
    fscanf(file, " { %d }", &value);
    fscanf(file, " %*[}]");

    // printf("INT: %d\n", value);
    return value;
}

action parseAction(FILE *file)
{
    action act;
    memset(&act, 0, sizeof(action));

    char buffer[256];

    while (fgets(buffer, sizeof(buffer), file) != NULL)
    {
        char *bracePos = strchr(buffer, '{');
        if (bracePos != NULL)
        {
            *bracePos = '\0'; // Terminate the string at '{'
        }

        char token[256];
        sscanf(buffer, " %s", token);
        // printf("ATOK: %s\n", token);

        if (strcmp(token, "message") == 0)
        {
            act.message = parseString(file);
        }
        else if (strcmp(token, "sMessage") == 0)
        {
            act.sMessage = parseString(file);
        }
        else if (strcmp(token, "data") == 0)
        {
            for (int i = 0; i < N_ATTRIBUTE; i++)
            {
                fscanf(file, " { %s %d }", act.dataLabel[i], &act.data[i]);
                // printf("%s : %d\n", act.dataLabel[i], act.data[i]);
                fscanf(file, " %*[}]");
            }
        }
        else if (strcmp(token, "condition") == 0)
        {
            for (int i = 0; i < N_ATTRIBUTE; i++)
            {
                act.condition[i] = parseInt(file);
            }
        }
        else if (strcmp(token, "success") == 0)
        {
            act.success = parseInt(file);
        }
        else if (strcmp(token, "destID") == 0)
        {
            fscanf(file, " { %d }", &act.destID);
            // printf("DEST: %d\n", act.destID);
        }
        else if (strcmp(token, "}") == 0)
        {
            fscanf(file, " %*[}]");
            break; // End of action block
        }
    }

    return act;
}

action *parseActions(FILE *file, int aCount)
{
    action *actions = malloc(aCount * sizeof(action));
    char buffer[256]; // Buffer for reading lines

    // Skip the opening bracket '{' of the actions block
    fgets(buffer, sizeof(buffer), file);

    for (int i = 0; i < aCount; ++i)
    {
        // printf("ACT%d\n", i);
        actions[i] = parseAction(file); // Parse the current action

        // Read the next line
        if (fgets(buffer, sizeof(buffer), file) == NULL)
        {
            // If it's the end of file, break the loop
            break;
        }
        else if (strcmp(buffer, "}\n") == 0)
        {
            // If it's the closing bracket, break the loop
            break;
        }
    }

    // Consume any remaining tokens until the end of actions block
    while (fgets(buffer, sizeof(buffer), file) != NULL)
    {
        if (strcmp(buffer, "}\n") == 0)
        {
            // End of actions block
            break;
        }
    }

    return actions;
}

event parseEvent(FILE *file, int id)
{
    event evt;
    memset(&evt, 0, sizeof(event));

    // Default values
    evt.id = id;
    evt.aCount = 0;
    evt.timeout = -1;
    evt.message = NULL;
    evt.actions = NULL;
    evt.scene = NULL;

    char buffer[256];
    while (fgets(buffer, sizeof(buffer), file) != NULL)
    {
        // Find the position of '{' in the buffer
        char *bracePos = strchr(buffer, '{');
        if (bracePos != NULL)
        {
            *bracePos = '\0'; // Terminate the string at '{'
        }

        char token[256];
        sscanf(buffer, " %s", token); // Read token
        // printf("TOK: %s\n", token);

        if (strcmp(token, "scene") == 0)
        {
            evt.scene = parseScene(file);
        }
        else if (strcmp(token, "message") == 0)
        {
            evt.message = parseString(file);
        }
        else if (strcmp(token, "timeout") == 0)
        {
            evt.timeout = parseInt(file);
        }
        else if (strcmp(token, "actions") == 0)
        {
            evt.actions = parseActions(file, evt.aCount);
        }
        else if (strcmp(token, "aCount") == 0)
        {
            evt.aCount = parseInt(file);
        }
    }

    return evt;
}

event *loadEvents(const char *directory, int *eventCount)
{
    DIR *dir = opendir(directory);
    if (!dir)
    {
        perror("Failed to open directory");
        exit(EXIT_FAILURE);
    }

    struct dirent *entry;
    struct stat st;
    char filepath[512];

    *eventCount = 0;
    int capacity = 100;
    event *events = malloc(capacity * sizeof(event));

    while ((entry = readdir(dir)) != NULL)
    {
        snprintf(filepath, sizeof(filepath), "%s/%s", directory, entry->d_name);
        if (stat(filepath, &st) == 0 && S_ISREG(st.st_mode))
        {
            FILE *file = fopen(filepath, "r");
            if (!file)
            {
                perror("Failed to open file");
                continue;
            }

            if (*eventCount >= capacity)
            {
                capacity *= 2;
                events = realloc(events, capacity * sizeof(event));
            }
            events[*eventCount] = parseEvent(file, *eventCount);
            // printEvent(events[*eventCount]);
            (*eventCount)++;
            fclose(file);
        }
    }
    events[*eventCount].scene = NULL; // Mark the end of the events array with a NULL scene
    closedir(dir);
    return events;
}

void freeEvents(event *events)
{
    if (!events)
        return;

    int i = 0;
    while (events[i].scene != NULL)
    {
        // Free the scene and message of the event
        free(events[i].scene);
        free(events[i].message);

        // Free each action's message and sMessage
        for (int j = 0; j < events[i].aCount; j++)
        {
            free(events[i].actions[j].message);
            free(events[i].actions[j].sMessage);
        }

        // Free the actions array
        free(events[i].actions);
        i++;
    }

    // Free the events array itself
    free(events);
}
