OBJECTS = part1 part2

.PHONY: all

all: $(OBJECTS)

part1: solution.cpp
	g++ -Wall -std=c++11 -o part1 -D PART1 solution.cpp

part2: solution.cpp
	g++ -Wall -std=c++11 -o part2 -D PART2 solution.cpp

debug: solution.cpp
	g++ -Wall -std=c++11 -o part1 -D PART1 -g solution.cpp
	g++ -Wall -std=c++11 -o part2 -D PART2 -g solution.cpp

clean:
	rm -f $(OBJECTS)
