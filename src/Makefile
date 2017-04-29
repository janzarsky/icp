SOURCES=$(filter-out ./test.cpp, $(wildcard ./*.cpp))
HEADERS=./*.hpp


all: Game
	g++ -std=c++14 -o $< $(SOURCES)

Game: $(SOURCES) $(HEADERS)



test:test.cpp
	g++ -std=c++14 -o test test.cpp

test_clean:
	rm test

clean:
	rm *.o Game
