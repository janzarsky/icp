all:
	g++ -o hra2017-cli src/*.cpp

run:
	./hra2017-cli

test:
	./test.sh

clean:
	rm hra2017-cli

pack:
	zip -r xzarsk03-xpapla00.zip src examples doc README.txt Makefile

