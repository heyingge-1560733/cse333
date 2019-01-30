# Copyright ©2018 Justin Hsia.  All rights reserved.  Permission is
# hereby granted to students registered for University of Washington
# CSE 333 for use solely during Spring Quarter 2018 for purposes of
# the course.  No other use, copying, distribution, or modification
# is permitted without prior written consent. Copyrights for
# third-party components of this work must be honored.  Instructors
# interested in reusing these course materials should contact the
# author.

# define the commands we'll use for compilation and library building
AR = ar
ARFLAGS = rcs
CC = gcc
CXX = g++

# define useful flags to cc/ld/etc.
CFLAGS = -g -Wall -Wpedantic -I. -I.. -O0
LDFLAGS = -L. -L./libhw1/ -lhw2 -lhw1
CPPUNITFLAGS = -L../gtest -lgtest

#define common dependencies
OBJS = fileparser.o filecrawler.o doctable.o memindex.o
HEADERS = fileparser.h filecrawler.h doctable.h memindex.h
TESTOBJS = test_suite.o test_fileparser.o test_doctable.o test_filecrawler.o \
           test_memindex.o
TESTHEADERS = test_fileparser.h test_doctable.h test_filecrawler.h \
              test_memindex.h

# compile everything
all: test_suite searchshell libhw2.a FORCE

libhw2.a: $(OBJS) $(HEADERS) FORCE
	$(AR) $(ARFLAGS) libhw2.a $(OBJS)

searchshell: searchshell.o libhw2.a $(HEADERS) FORCE
	$(CC) $(CFLAGS) -o searchshell searchshell.o $(LDFLAGS)

test_suite: $(TESTOBJS) $(TESTHEADERS) libhw2.a FORCE
	$(CXX) $(CFLAGS) -o test_suite $(TESTOBJS) \
	$(CPPUNITFLAGS) $(LDFLAGS) -lpthread $(LDFLAGS)

%.o: %.cc $(HEADERS) FORCE
	$(CXX) $(CFLAGS) -std=c++11 -c $<

%.o: %.c $(HEADERS) FORCE
	$(CC) $(CFLAGS) -c -std=c11 $<

clean: FORCE
	/bin/rm -f *.o *~ test_suite searchshell libhw2.a

FORCE:
