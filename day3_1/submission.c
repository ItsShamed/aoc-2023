#define _POSIX_C_SOURCE 200809L
#define _DEFAULT_SOURCE

#include <ctype.h>
#include <stdbool.h>
#include <stdlib.h>

#include "boilerplate.h"

static char **schematic = NULL;
static size_t lines = 0;

static unsigned long result = 0;

void process_line(char *str)
{
    schematic = reallocarray(schematic, lines + 1, sizeof(char *));
    if (!schematic)
        return;
    schematic[lines++] = strdup(str);
}

static inline bool issymbol(char c)
{
    return !isdigit(c) && c != '.' && c != '\n';
}

/**
** \brief Checks for the surrounding of a number
**
** \returns Whether one of the digits is surrounded by a symbol
*/
static inline bool check_surroundings(size_t row, size_t col, ssize_t columns)
{
    ssize_t upper_row = row + 1;
    ssize_t upper_col = col + 1;
    ssize_t s_lines = lines;
    for (ssize_t i = row - 1; i <= upper_row; i++)
    {
        if (i < 0 || i >= s_lines)
            continue;
        for (ssize_t j = col - 1; j <= upper_col; j++)
        {
            if (j < 0 || j >= columns)
                continue;
            if (issymbol(schematic[i][j]))
                return true;
        }
    }
    return false;
}

static inline void cleanup(void)
{
    for (size_t i = 0; i < lines; i++)
        free(schematic[i]);
    free(schematic);
}

void finish(void)
{
    const size_t columns = strlen(schematic[0]);

    // Traversing lines
    for (size_t i = 0; i < lines; i++)
    {
        for (size_t j = 0; j < columns; j++)
        {
            // Check beggining of number
            if (isdigit(schematic[i][j]))
            {
                char *endptr;
                unsigned long current = strtoul(schematic[i] + j, &endptr, 10);
                bool is_part = false;
                for (size_t k = j; schematic[i] + k < endptr; k++, j++)
                {
                    if (check_surroundings(i, k, columns))
                    {
                        is_part = true;
                        continue;
                    }
                }
                if (is_part)
                {
                    result += current;
                }
                j--; // Cancel for incrementation
            }
        }
    }
    cleanup();
    printf("%lu\n", result);
}
