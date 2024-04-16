CC=gcc
CFLAGS = -Wall -Wextra -pedantic

# C flags common in all build configurations
# -Wall - enable all warnings
# -std=c11 - set c standard to 11
cflags.common := -std=c11 -Wall
# disable all optimizations and add debug information in debug build
cflags.debug := -g -O0
# enable O2 optimization in release mode
cflags.release := -Ofast
# build CFLAGS variable based on selected build configuration
CFLAGS := ${cflags.${BUILD}} ${cflags.common}
# using direct path to time binary to be able to format time output
TIME := /usr/bin/time

.PHONY: all clean


all: integrate reader calculator

integrate: integrate.c
	$(CC) $(CFLAGS) -o $@ $< -lm

reader: reader.c
	$(CC) $(CFLAGS) -o $@ $< -lm

calculator: calculator.c
	$(CC) $(CFLAGS) -o $@ $< -lm


clean:
	rm -f integrate calculator reader
