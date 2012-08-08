# #---------------------------------------------------------------
# # Author: 	Team Exception
# # Date: 	Spring 2012
# #---------------------------------------------------------------
#
CC              = g++
CFLAGS          = -g -Wall -pedantic #-DHASHTABLE
CPPFLAGS        = $(CFLAGS)
OBJS		= BKTree.o Output.o main.o Dictionary.o Word_Count.o
LIBS            = 
#
#
# ################################################################
# # ALL
# #
# # when you run make by itself, this is what it will try to create
# #
all: makeit

%.o: %.C
	$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

#
# ################################################################
# #
# # Dependencies
# #
#
makeit: $(OBJS)
	$(CC) $(CFLAGS) -o $@ $+

#
# ################################################################
# #
# # Clean
# #
#
clean:
	rm -f *.o makeit

rebuild: clean makeit

.PHONY: check-syntax
check-syntax:
	$(CXX) $(CXXFLAGS) -Wall -Wextra -pedantic -fsyntax-only $(CHK_SOURCES)
#
#
#
##EOF