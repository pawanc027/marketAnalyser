IDIR     = inc
SDIR     = src
BDIR     = bin

BIN	 = $(BDIR)/market
CC	 = g++
CFLAGS	 = -std=c++14 -c -Wall -I$(IDIR)

OBJS	 = main.o market.o
SOURCE	 = main.cpp market.cpp
DEPS     = market.hpp

all:     $(OBJS)
	 $(CC) -g $(OBJS) -o $(BIN) 

main.o:  $(SDIR)/main.cpp
	 $(CC) $(CFLAGS) $(SDIR)/main.cpp 

market.o: $(SDIR)/market.cpp
	  $(CC) $(CFLAGS) $(SDIR)/market.cpp 

.PHONY: clean

clean:
	rm -f $(OBJS) $(BIN)
