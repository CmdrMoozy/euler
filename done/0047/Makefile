CFLAGS = -Wall -Wextra -ansi -pedantic -Wshadow -Wpointer-arith -Wcast-qual -pipe -fomit-frame-pointer -Wall -W -O2 -std=c++0x
CC = g++

PROG = Problem

all: $(PROG)

$(PROG): main.cpp
	$(CC) $(CFLAGS) main.cpp -o $(PROG)

clean:
	@rm -fr $(PROG)
