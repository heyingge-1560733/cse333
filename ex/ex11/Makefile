# Yingge He
# 1560733
# heyingge@uw.edu
# Copied from sample solution from ex10.
# Copyright ©2018 Justin Hsia, Yingge He.  All rights reserved.  Permission is
# hereby granted to students registered for University of Washington
# CSE 333 for use solely during Spring Quarter 2018 for purposes of
# the course.  No other use, copying, distribution, or modification
# is permitted without prior written consent. Copyrights for
# third-party components of this work must be honored.  Instructors
# interested in reusing these course materials should contact the
# author.

#  Makefile

CXX = g++
OBJS = Vector.o ex11.o
EXE  = ex11
HEADERS = Vector.h
CPPFLAGS = -Wall -g -std=c++11

# default target
$(EXE): $(OBJS)
	$(CXX) $(CPPFLAGS) -o $(EXE) $(OBJS)

# source files
%.o: %.cc $(HEADERS)
	$(CXX) $(CPPFLAGS) -c $<

# phony target - remove generated files and backups
clean:
	rm -rf $(EXE) *.o *~ *.dSYM
