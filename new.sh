#!/bin/sh

if [ $# -ne 1 ]; then
    echo "Name is required" 1>&2
    exit 1
fi

mkdir "$1"
mkdir "$1/inputs"
touch "$1/inputs/.gitkeep"

echo "		 $1 \\" >> dirs.mk

cat <<EOF > "$1/submission.c"
#define _POSIX_C_SOURCE 200809L

#include "boilerplate.h"

void process_line(char *str)
{
    // TODO: implement something
}

void finish(void)
{
    // TODO: implement something
}
EOF

cat <<EOF > "$1/Makefile"
CFLAGS += -I..

run: submission
	./../run.sh
	\$(RM) submission

.PHONY: run
EOF
