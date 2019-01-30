# He Yingge
# 1560733
# heyingge@uw.edu
# Makefile
# default target
ex16: ex16.o network.o
	g++ -Wall -g -std=c++11 -o ex16 ex16.o network.o

# individual source files
network.o: network.cc network.h
	g++ -Wall -g -std=c++11 -c network.cc

ex16.o: ex16.cc network.h
	g++ -Wall -std=c++11 -g -c ex16.cc

# phony target
clean:
	rm -rf ex16 *.o *~ *.dSYM
