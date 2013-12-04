CFLAGS = -Wall -Wextra -ansi -pedantic -Wshadow -Wpointer-arith -Wcast-qual -pipe -fomit-frame-pointer -Wall -W -O2 -std=c++0x
LDFLAGS  = -leuler -lgmp -lgmpxx -lmpfr -lrt -lm
INCPATH = ../../libeuler/build/release/include
LIBPATH = ../../libeuler/build/release/lib
CC = g++

PROG = Problem

all: $(PROG)
	
$(PROG): main.cpp
	$(CC) $(CFLAGS) $(LDFLAGS) -I$(INCPATH) -L$(LIBPATH) main.cpp -o $(PROG)

clean:
	@rm -fr $(PROG)
