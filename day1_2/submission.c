#include <ctype.h>
#include <stdbool.h>

#include "boilerplate.h"

static unsigned int value = 0;

static inline unsigned int to_uint(char c)
{
    return c - '0';
}

static inline char lit_to_char(const char *str)
{
    if (strncmp(str, "one", 3) == 0)
        return '1';
    if (strncmp(str, "two", 3) == 0)
        return '2';
    if (strncmp(str, "three", 5) == 0)
        return '3';
    if (strncmp(str, "four", 4) == 0)
        return '4';
    if (strncmp(str, "five", 4) == 0)
        return '5';
    if (strncmp(str, "six", 3) == 0)
        return '6';
    if (strncmp(str, "seven", 5) == 0)
        return '7';
    if (strncmp(str, "eight", 5) == 0)
        return '8';
    if (strncmp(str, "nine", 4) == 0)
        return '9';
    return 0;
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

        if (lit_to_char(&str[i]))
        {
            char lc = lit_to_char(&str[i]);
            if (!first)
                first = lc;
            last = lc;
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
