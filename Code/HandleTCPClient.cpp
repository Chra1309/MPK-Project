#include <stdio.h>      /* for printf() and fprintf() */
#include <sys/socket.h> /* for recv() and send() */
#include <unistd.h>     /* for close() */
#include <string>
#include <iostream>
#include <cstring>
using namespace std;
#define RCVBUFSIZE 64   /* Size of receive buffer */
#include "Cube_old.hpp"
//#include "rubikssolver_header.hpp"

char echoBuffer[RCVBUFSIZE];        /* Buffer for echo string */
int recvMsgSize;                    /* Size of received message */

void DieWithError(string errorMessage);  /* Error handling function */

int nmberOfRotations(){
	//convert the received string to integers
	int scndDigit = 0;
	int firstDigit =0;


	if(int(echoBuffer[2]-'0'>0))
	scndDigit = int(echoBuffer[2])-'0';

	if (scndDigit !=0)
	firstDigit = 10*(int(echoBuffer[1])-'0');
	else
	firstDigit = int(echoBuffer[1])-'0';

	//get number of rotations out of recveived string
	int numOfRotations = firstDigit+scndDigit;
	
	return numOfRotations;
}

void printReceivedBuffer(){
	//PRINT ECHO BUFFER
	echoBuffer[RCVBUFSIZE] = '\0';  /* Terminate the string! */
    cout << echoBuffer << endl;      /* Print the echo buffer */
}

void HandleTCPClient(int clntSocket)
{

    /* Receive message from client */
    if ((recvMsgSize = recv(clntSocket, echoBuffer, RCVBUFSIZE, 0)) < 0)
        DieWithError("recv() failed");

    //send test message
    //print recevied message
	srand(time(NULL));
	Cube y(1); //Create an abritary cube
	//convert to String
	string arbritaryCube = cubeToString(y);
	//send(clntSocket, arbritaryCube, 64, 0);
	char sendCube[64];
	// copying the contents of the 
	// string to char array 
	strcpy(sendCube, arbritaryCube.c_str()); 
	cout << sendCube<<endl;
    
    int bufferLength = recvMsgSize;
    /* Send received string and receive again until end of transmission */
    while (recvMsgSize > 0)      /* zero indicates end of transmission */
    {
        /* Echo message back to client */
        if (send(clntSocket, sendCube, recvMsgSize, 0) != recvMsgSize)
            DieWithError("send() failed");
		
		
        /* See if there is more data to receive */
        if ((recvMsgSize = recv(clntSocket, echoBuffer, RCVBUFSIZE, 0)) < 0)
            DieWithError("recv() failed");
    }
	
	cout << "Received from Client: ";
	printReceivedBuffer();
	
    close(clntSocket);    /* Close client socket */
}
