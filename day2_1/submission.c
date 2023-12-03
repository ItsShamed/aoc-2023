#include "boilerplate.h"

#include <stdbool.h>

#define MAX_RED 12
#define MAX_GREEN 13
#define MAX_BLUE 14

#define SET_DELIM ";"
#define PICK_DELIM ","
#define FIELD_DELIM ";,"

#define red "red"
#define blue "blue"
#define green "green"

#define streq(one, other) strcmp(one, other) == 0

static unsigned int result = 0;

static inline char *get_data(char *line)
{
    size_t i;
    char *res = NULL;
    for (i = 0; line[i]; i++)
    {
        // Skip semicolon and trailing space, if we reach EOL this is not good
        if (line[i] == ':' && line[i + 2])
            res = line + i + 2;
    }

    if (line[i - 1] == '\n')
        line[i - 1] = 0; // Put null char for strtok_r

    return res;
}

static inline bool check_pick(char *str)
{
    char *saveptr;
    char *data = strtok_r(str, " ", &saveptr);

    if (!data)
    {
        warnx("malformated data");
        return true;
    }

    unsigned int count = atoi(data);
    
    data = strtok_r(NULL, " ", &saveptr);

    if (streq(data, red))
        return count <= MAX_RED;
    if (streq(data, green))
        return count <= MAX_GREEN;
    if (streq(data, blue))
        return count <= MAX_BLUE;

    warnx("unknown object '%s'", data);
    return false;
}


static inline bool check_set(char *set_data)
{
    char *saveptr;
    char *pick_data = strtok_r(set_data, PICK_DELIM, &saveptr);

    while (pick_data)
    {
        if (!check_pick(pick_data))
            return false;

        pick_data = strtok_r(NULL, PICK_DELIM, &saveptr);
    }


    return true;
}

void process_line(char *str)
{
    static unsigned int current_game = 0;
    current_game++;

    char *data = get_data(str);
    if (!data)
    {
        warnx("malformated data");
        return;
    }

    char *saveptr;
    char *set_data = strtok_r(data, SET_DELIM, &saveptr);

    while (set_data)
    {
        if (!check_set(set_data))
            return;

        set_data = strtok_r(NULL, FIELD_DELIM, &saveptr);
    }
    result += current_game;
}

void finish(void)
{
    printf("%u\n", result);
}
