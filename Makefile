# Makefile

# Authors: 
# Jan Zarsky (xzarsk03@stud.fit.vutbr.cz)
# Andrei Paplauski (xpapla00@stud.fit.vutbr.cz)

all: tui gui

# make sure that qmake is a qt5 version, on Ubuntu try 'qmake -qt=qt5' if
# this won't work
gui:
	@ cd src && qmake && make

tui:
	g++ -O2 -Wall -W -std=c++11 -DTUI -o hra2017-cli src/Card.cpp src/Game.cpp src/TUIGame.cpp src/Main.cpp src/TUIApp.cpp src/TUIParser.cpp

run:
	./hra2017-cli
	./hra2017

doxygen:
	doxygen 

clean:
	rm -rf hra2017 hra2017-cli xzarsk03-xpapla00.zip doc/* src/Makefile src/.[!.]* src/*.o src/moc_* src/qrc_resources.cpp

pack: clean
	zip -r xzarsk03-xpapla00.zip src/ doc/ examples README.txt Makefile Doxyfile

