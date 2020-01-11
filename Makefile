CC = g++

all: cube
all: client

client: Code/TCPEchoClient.cpp
	$(CC) -o executables/client Code/TCPEchoClient.cpp Code/DieWithError.cpp

cube: Code/rubikssolver.cpp
	$(CC) -o executables/rubikssolver Code/rubikssolver.cpp

clean:
	rm cube, client

