#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <dirent.h>
#include <sys/stat.h>
#include <ctype.h>
#include "event.h"
#include "eventLoader.h"

// Function to trim leading and trailing whitespace from a string
char *trim(char *str)
{
    while (isspace((unsigned char)*str))
        str++;
    if (*str == 0)
        return str;
    char *end = str + strlen(str) - 1;
    while (end > str && isspace((unsigned char)*end))
        end--;
    end[1] = '\0';
    return str;
}

// Function to parse the scene from a file
char *parseScene(FILE *file)
{
    char buffer[1024];
    size_t sceneSize = 1024;
    char *scene = malloc(sceneSize);
    size_t len = 0;

    fscanf(file, "%*[^{]"); // Skip until opening bracket
    fgetc(file);            // Consume the opening bracket

    while (fgets(buffer, sizeof(buffer), file) != NULL)
    {
        if (strncmp(buffer, "}", 1) == 0)
            break;
        size_t bufferLen = strlen(buffer);
        if (len + bufferLen >= sceneSize)
        {
            sceneSize *= 2;
            scene = realloc(scene, sceneSize);
        }
        strcpy(scene + len, buffer);
        len += bufferLen;
    }
    return scene;
}

// Function to parse a single string value from a file
char *parseString(FILE *file)
{
    char *value = malloc(100 * sizeof(char)); // Adjust the size according to your needs
    fscanf(file, "%*[^{]");                   // Skip until opening bracket
    fscanf(file, "%*[{]%[^}]s", value);
    return trim(value);
}

// Function to parse an integer value from a file
int parseInt(FILE *file)
{
    int value;
    fscanf(file, "%*[^{]"); // Skip until opening bracket
    fscanf(file, "%*[{]%d", &value);
    return value;
}

// Function to parse an event from a file
event parseEvent(FILE *file)
{
    event e;
    e.scene = parseScene(file);
    e.message = parseString(file);
    e.timeout = parseInt(file);
    e.aCount = parseInt(file);
    e.actions = malloc(e.aCount * sizeof(action));
    for (int i = 0; i < e.aCount; i++)
    {
        e.actions[i].message = parseString(file);
        e.actions[i].sMessage = parseString(file);
        for (int j = 0; j < N_ATTRIBUTE; j++)
        {
            e.actions[i].data[j] = parseInt(file);
        }
        e.actions[i].success = parseInt(file);
        e.actions[i].destID = parseInt(file);
    }
    return e;
}

// Function to free the memory allocated for an event
void freeEvent(event e)
{
    free(e.scene);
    free(e.message);
    for (int i = 0; i < e.aCount; i++)
    {
        free(e.actions[i].message);
        free(e.actions[i].sMessage);
    }
    free(e.actions);
}

// Function to read an event from a file
event readEventFromFile(const char *filename)
{
    FILE *file = fopen(filename, "r");
    if (file == NULL)
    {
        fprintf(stderr, "Error opening file %s\n", filename);
        exit(EXIT_FAILURE);
    }
    event e = parseEvent(file);
    fclose(file);
    return e;
}

// Function to read all events from files within a folder
event *loadEvents(const char *folder, int *count)
{
    DIR *dir;
    struct dirent *ent;
    struct stat fileStat;
    event *events = NULL;
    *count = 0;
    if ((dir = opendir(folder)) != NULL)
    {
        // Count the number of files in the directory
        while ((ent = readdir(dir)) != NULL)
        {
            char filepath[100]; // Adjust size as needed
            snprintf(filepath, sizeof(filepath), "%s/%s", folder, ent->d_name);
            if (stat(filepath, &fileStat) == 0 && S_ISREG(fileStat.st_mode) && strstr(ent->d_name, ".txt") != NULL)
            {
                (*count)++;
            }
            printf("%s", filepath);
        }
        rewinddir(dir);
        // Allocate memory for events array
        events = malloc(*count * sizeof(event));
        int i = 0;
        // Read events from files
        while ((ent = readdir(dir)) != NULL)
        {
            char filepath[100]; // Adjust size as needed
            snprintf(filepath, sizeof(filepath), "%s/%s", folder, ent->d_name);
            if (stat(filepath, &fileStat) == 0 && S_ISREG(fileStat.st_mode) && strstr(ent->d_name, ".txt") != NULL)
            {
                events[i] = readEventFromFile(filepath);
                i++;
            }
        }
        closedir(dir);
    }
    else
    {
        perror("Error opening directory");
        exit(EXIT_FAILURE);
    }
    return events;
}

// Function to free memory allocated for events array
void freeEvents(event *events, int count)
{
    for (int i = 0; i < count; i++)
    {
        freeEvent(events[i]);
    }
    free(events);
}
