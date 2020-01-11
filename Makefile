CC = g++

all: cube

cube: Code/rubikssolver.cpp
	$(CC) -o executables/rubikssolver Code/rubikssolver.cpp

clean:
	rm cube
