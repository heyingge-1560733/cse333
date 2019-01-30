# 1560733
# heyingge@uw.edu
# "Copyright [2018] <Yingge He>"  [legal/copyright]
# Makefile for Exercise 10

CC = g++
CFLAGS = -Wall -g -std=c++11
PROGS = ex10

all: $(PROGS)

ex10: ex10.o Vector.o
	$(CC) $(CFLAGS) -o $@ $^

ex10.o: ex10.cc
	$(CC) $(CFLAGS) -c $<

Vector.o: Vector.cc
	$(CC) $(CFLAGS) -c $<

clean:
	rm -f $(PROGS) *.o *~
