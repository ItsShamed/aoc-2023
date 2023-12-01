#ifndef BOILERPLATE_H
#define BOILERPLATE_H

#define _POSIX_C_SOURCE 200809L

#include <err.h>
#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>


void process_line(char *str);
void finish(void);

static inline void _process(FILE *input)
{
    char *buf = NULL;
    size_t n;
    ssize_t r = getline(&buf, &n, input);
    while (r != -1)
    {
        process_line(buf);
        r = getline(&buf, &n, input);
    }
    free(buf);
}

int main(int argc, char *argv[])
{
    if (argc != 2)
    {
        warnx("Usage: %s <input file>", argv[0]);
        return 1;
    }

    FILE *file  = fopen(argv[1], "r");
    if (!file)
    {
        warnx("Could not open file: %s", strerror(errno));
        return 1;
    }

    _process(file);
    finish();

    fclose(file);
    return 0;
}

#endif /* ! BOILERPLATE_H */
