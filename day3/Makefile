OBJECTS = part1 part2

.PHONY: all

all: $(OBJECTS)

part1: solution.cpp
	g++ -o part1 -D PART1 solution.cpp

part2: solution.cpp
	g++ -o part2 -D PART2 solution.cpp

debug : solution.cpp
	g++ -o part1 -D PART1 -g solution.cpp
	g++ -o part2 -D PART2 -g solution.cpp

clean:
	rm -f $(OBJECTS)
