all:
	cd src; qmake CONFIG+=gui
	make -C src
	make clean -C src
	cd src; qmake CONFIG+=tui
	make -C src
	make clean -C src

gui:
	cd src; qmake CONFIG+=gui
	make -C src

tui:
	g++ -Wall -DTUI -o hra2017-cli src/Card.cpp src/Game.cpp src/GameUI.cpp src/Main.cpp src/Pile.cpp src/TextApp.cpp src/TextUIParser.cpp

run:
	./hra2017-cli

test:
	./test.sh

clean:
	make clean -C src
	rm hra2017 hra2017-cli

pack:
	zip -r xzarsk03-xpapla00.zip src examples doc README.txt Makefile

