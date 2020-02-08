CC = g++

all: rubikssolver
all: fillcube
all: solvability

rubikssolver: Code/rubikssolver.cpp
	$(CC) -o executables/rubikssolver Code/rubikssolver.cpp

fillcube: Code/fillcube.cpp
	$(CC) -o executables/fillcube Code/fillcube.cpp

solvability: Code/solvability.cpp
	$(CC) -o executables/solvability Code/solvability.cpp

clean:gi
	rm rubikssolver, fillcube, solvability

