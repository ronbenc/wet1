GCC = g++
CXX=/usr/local/bin/g++

OBJS = main.o tNode.o
EXEC = wet1
#DEBUG_FLAG = #Currently none
COMP_FLAG = -std=c++11 -Wall -pedantic-errors -Werror -DNDEBUG

$(EXEC) : $(OBJS)
	$(CXX) $(DEBUG_FLAG) $(OBJS) -o $@

main.o: main.cpp tNode.h List.h
	$(CXX) -c $(DEBUG_FLAG) $(COMP_FLAG) $*.cpp
	
#tar:
#	zip -r gcalc.zip *.cpp *.h Makefile design.pdf test_in.txt test_out.txt
	
clean:
	rm -f $(OBJS) $(EXEC)
	