SOURCES=$(filter-out ./test.cpp, $(wildcard ./*.cpp))
HEADERS=./*.hpp


all: Game
	g++ $(SOURCES) -std=c++14 -o $< 
Game: $(HEADERS) $(SOURCES) 
	g++ -std=c++14 -c $(SOURCES)

test:test.cpp
	g++ -std=c++14 -o test test.cpp

test_clean:
	rm test

clean:
	rm *.o Game
