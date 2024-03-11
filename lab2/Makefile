CXX=gcc
CFLAGS=-c -O0 -Wall

.PHONY: clean all

all: main_static main_dynamic main_shared

test: main_static main_dynamic main_shared
	./main_static
	./main_dynamic
	./main_shared

collatz.o: collatz.c
	$(CXX) $(CFLAGS) collatz.c

collatz_d.o: collatz.c
	$(CXX) -fPIC $(CFLAGS) collatz.c -o collatz_d.o

libcollatz.a: collatz.o
	ar rcs libcollatz.a collatz.o

libcollatz.so: collatz_d.o
	$(CXX) -shared collatz_d.o -o libcollatz.so

main_static: main.c libcollatz.a
	$(CXX) main.c libcollatz.a -o main_static

main_dynamic: main.c libcollatz.so
	$(CXX) main.c -L. -lcollatz -Wl,-rpath=. -o main_dynamic

main_shared: main.c
	$(CXX) main.c -o main_shared -ldl -D DLL

clean:
	rm *.o libcollatz.a libcollatz.so main_static main_dynamic main_shared