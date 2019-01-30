# He Yingge
# 1560733
# heyingge@uw.edu
# Makefile
# default target
ex15: ex15.o network.o
	g++ -Wall -g -std=c++11 -o ex15 ex15.o network.o

# individual source files
network.o: network.cc network.h
	g++ -Wall -g -std=c++11 -c network.cc

ex15.o: ex15.cc network.h
	g++ -Wall -std=c++11 -g -c ex15.cc

# phony target
clean:
	rm -rf ex15 *.o *~ *.dSYM
