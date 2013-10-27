CFLAGS = -Wall -Wextra -ansi -pedantic -Wshadow -Wpointer-arith -Wcast-qual -pipe -fomit-frame-pointer -Wall -O2 -std=c++0x
LDFLAGS = -leuler
LIBPATH = ../../libeuler/release/lib
INCPATH = ../../libeuler/release/include
CC = g++

PROG = Problem

all: $(PROG)
	
$(PROG): main.cpp
	$(CC) $(CFLAGS) $(LDFLAGS) -I$(INCPATH) -L$(LIBPATH) main.cpp -o $(PROG)

clean:
	@rm -fr $(PROG)
