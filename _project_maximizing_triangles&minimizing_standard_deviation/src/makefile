CXX=g++
GA_INC_DIR= ../src/ga
GA_LIB_DIR= ../src/ga/ga
CXXFLAGS=-g -Wall -I$(GA_INC_DIR) 
LDFLAGS= -L$(GA_LIB_DIR) -lga -lm

all: 
	make main
	make clean

main: main.o
	$(CXX) $^ -o ../exe/$@ $(LDFLAGS)

main.o: main.cpp
	$(CXX) $(CXXFLAGS) -c $^

run: 
	../exe/main

clean:
	rm main.o

