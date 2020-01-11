CC = g++

all: cube
all: client
all: server



client: Code/TCPEchoClient.cpp
	$(CC) -o executables/client Code/TCPEchoClient.cpp Code/DieWithError.cpp

server: Code/TCPEchoServer.cpp
	$(CC) -o executables/server Code/TCPEchoServer.cpp Code/DieWithError.cpp Code/HandleTCPClient.cpp

cube: Code/rubikssolver.cpp
	$(CC) -o executables/rubikssolver Code/rubikssolver.cpp

clean:
	rm cube, client, server

