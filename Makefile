all: tui gui

gui:
	@ cd src && qmake && make

tui:
	g++ -O2 -Wall -W -std=c++11 -DTUI -o hra2017-cli src/Card.cpp src/Game.cpp src/TUIGame.cpp src/Main.cpp src/TUIApp.cpp src/TUIParser.cpp

run:
	./hra2017-cli
	./hra2017

doxygen:
	doxygen 

test:
	./test.sh

clean:
	make clean -C src
	rm hra2017 hra2017-cli xzarsk03-xpapla00.zip
	rm -rf doc

pack:
	zip -r xzarsk03-xpapla00.zip src examples README.txt Makefile

