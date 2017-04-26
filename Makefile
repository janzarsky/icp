all:
	g++ -o hra2017 src/*.cpp

run:
	./hra2017

clean:
	rm hra2017

pack:
	zip -r xzarsk03-xpapla00.zip src examples doc README.txt Makefile

