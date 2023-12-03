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
#define max(a, b) a > b ? a : b

static unsigned long result = 0;

struct counts
{
    unsigned int r;
    unsigned int g;
    unsigned int b;
};

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

static inline void check_pick(char *str, struct counts *counts)
{
    char *saveptr;
    char *data = strtok_r(str, " ", &saveptr);

    if (!data)
    {
        warnx("malformated data");
        return;
    }

    unsigned int count = atoi(data);
    
    data = strtok_r(NULL, " ", &saveptr);

    if (streq(data, red))
        counts->r = max(counts->r, count);
    else if (streq(data, green))
        counts->g = max(counts->g, count);
    else if (streq(data, blue))
        counts->b = max(counts->b, count);
    else
        warnx("unknown object '%s'", data);
}


static inline void check_set(char *set_data, struct counts *counts)
{
    char *saveptr;
    char *pick_data = strtok_r(set_data, PICK_DELIM, &saveptr);

    while (pick_data)
    {
        check_pick(pick_data, counts);
        pick_data = strtok_r(NULL, PICK_DELIM, &saveptr);
    }
}

static inline unsigned long compute_power(struct counts *counts)
{
    return counts->r * counts->g * counts->b;
}

void process_line(char *str)
{
    char *data = get_data(str);
    if (!data)
    {
        warnx("malformated data");
        return;
    }

    char *saveptr;
    char *set_data = strtok_r(data, SET_DELIM, &saveptr);

    struct counts counts = { 0 };

    while (set_data)
    {
        check_set(set_data, &counts);

        set_data = strtok_r(NULL, FIELD_DELIM, &saveptr);
    }
    result += compute_power(&counts);
}

void finish(void)
{
    printf("%lu\n", result);
}
