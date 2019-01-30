# 1560733
# heyingge@uw.edu
# "Copyright [2018] <Yingge He>"  [legal/copyright]
# Makefile for Exercise 9

CC = g++
CFLAGS = -Wall -g -std=c++11
PROGS = ex9

all: $(PROGS)

ex9: ex9.o IntPair.o
	$(CC) $(CFLAGS) -o $@ $^

ex9.o: ex9.cc
	$(CC) $(CFLAGS) -c $<

IntPair.o: IntPair.cc
	$(CC) $(CFLAGS) -c $<

clean:
	rm -f $(PROGS) *.o *~
