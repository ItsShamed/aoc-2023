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

static inline unsigned long get_number(size_t row, size_t col)
{
    while (col > 0 && isdigit(schematic[row][col]))
        col--;

    // With the above loop, col would shoot back too far if we're not
    // at the edge
    if (!isdigit(schematic[row][col]))
        col++;
    return strtoul(schematic[row] + col, NULL, 10);
}

static inline void check_surroundings(size_t row, size_t col, ssize_t columns)
{
    ssize_t upper_row = row + 1;
    ssize_t upper_col = col + 1;
    ssize_t s_lines = lines;
    char matches = 0;
    unsigned long gear_ratio = 1;

    for (ssize_t i = row - 1; i <= upper_row; i++)
    {
        if (i < 0 || i >= s_lines)
            continue;
        // Avoid parsing the same number multiple times
        bool last_is_digit = false;
        for (ssize_t j = col - 1; j <= upper_col; j++)
        {
            if (j < 0 || j >= columns)
                continue;
            if (isdigit(schematic[i][j]))
            {
                if (last_is_digit)
                    continue;
                matches++;
                last_is_digit = true;
                unsigned long val = get_number(i, j);
                gear_ratio *= val;
            }
            else
                last_is_digit = false;
        }
    }

    if (matches == 2)
        result += gear_ratio;
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
            if (schematic[i][j] == '*')
                check_surroundings(i, j, columns);
        }
    }
    cleanup();
    printf("%lu\n", result);
}
