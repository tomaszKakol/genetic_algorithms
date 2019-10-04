CXX=g++ -mcmodel=medium
CC=gcc
CXXFLAGS=-g -Wall -I..
LDFLAGS=-L  ../ga -lga -lm
MAINPATH=-L -lga -lm

all: clean clean_raw main analiza
main: main.o
	$(CXX) $^ funkcje_linux.o -o $@ $(LDFLAGS)
main.o: main.cpp
	$(CXX) $^ -c $(CXXFLAGS)
analiza: analiza.o
	$(CXX) $^ funkcje_linux.o -o $@ ${LDFLAGS}
analiza.o: analiza.c
	${CXX} $^ -c ${CXXFLAGS}

clean:
	rm -rf `ls main.o`
	rm -rf `ls analiza.o`

clean_raw:
	rm -rf `ls *.raw`
	rm -rf `ls *.dat`

.PHONY: clean opis
