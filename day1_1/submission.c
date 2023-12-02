#include <ctype.h>
#include <stdbool.h>

#include "boilerplate.h"

static unsigned int value = 0;

static inline unsigned int to_uint(char c)
{
    return c - '0';
}

void process_line(char *str)
{
    char first = 0;
    char last = 0;

    for (size_t i = 0; str[i]; i++)
    {
        if (isdigit(str[i]))
        {
            if (!first)
                first = str[i];
            last = str[i];
        }
    }

    if (!first || !last)
    {
        warnx("no numbers?");
        return;
    }

    unsigned int a = to_uint(first) * 10 + to_uint(last);
    value += a;
}

void finish(void)
{
    printf("%u\n", value);
}
