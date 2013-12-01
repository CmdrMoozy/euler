CFLAGS = -pipe -fomit-frame-pointer -Wall -W -O2 -std=c++0x
LDFLAGS = -lgmp -lgmpxx
CC = g++

PROG = Problem

all: $(PROG)

$(PROG): main.cpp
	$(CC) $(CFLAGS) $(LDFLAGS) -I$(INCPATH) -L$(LIBPATH) main.cpp -o $(PROG)

clean:
	@rm -fr $(PROG)
