# #---------------------------------------------------------------
# # Author: 	Team Exception
# # Date: 	Spring 2012
# #---------------------------------------------------------------
#
CC              = g++
CFLAGS          = -g -Wall -pedantic
CPPFLAGS        = $(CFLAGS)
OBJS		= map.o reduce.o Results.o Output.o main.o Dictionary.o Word_Count.o Page.o RateLimiter.o
LIBS            = -lcurl -lrt -lboost_thread
EXE		= crawl
#
#
# ################################################################
# # ALL
# #
# # when you run make by itself, this is what it will try to create
# #
all: $(EXE)

%.o: %.C
	$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@ 

#
# ################################################################
# #
# # Dependencies
# #
#
$(EXE): $(OBJS)
	$(CC) $(CFLAGS) -o $@ $+ $(LIBS)

#
# ################################################################
# #
# # Clean
# #
#
clean:
	rm -f *.o $(EXE)

rebuild: clean $(EXE)

.PHONY: check-syntax
check-syntax:
	$(CXX) $(CXXFLAGS) -Wall -Wextra -pedantic -fsyntax-only $(CHK_SOURCES)
#
#
#
##EOF
