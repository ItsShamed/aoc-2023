export CC = gcc
export CFLAGS = -Wall -Wextra -Wvla -Werror -std=c99 -pedantic -g -fsanitize=address
export LDFLAGS = -fsanitize=address

include dirs.mk


all: $(BUILDS)

day%:
	$(MAKE) -C $@

clean:
	$(RM) **/submission

.PHONY: all day_% clean
