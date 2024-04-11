CXX=gcc
CFLAGS = -Wall -Wextra -pedantic

.PHONY: all clean

all: sigusr1 sender catcher

sigusr1: sigusr1.c
	$(CXX) $(CFLAGS) -o $@ $<

sender: sender.c
	$(CXX) $(CFLAGS) -o $@ $<

catcher: catcher.c
	$(CXX) $(CFLAGS) -o $@ $<

clean:
	rm -f sigusr1 sender catcher
