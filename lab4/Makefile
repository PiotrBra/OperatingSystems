CXX=gcc

CFLAGS = -Wall -Wextra -pedantic

.PHONY: all clean

all: processes error_handling

processes: processes.c
	$(CXX) $(CFLAGS) -o $@ $<

error_handling: error_handling.c
	$(CXX) $(CFLAGS) -o $@ $<

clean:
	rm -f processes error_handling
