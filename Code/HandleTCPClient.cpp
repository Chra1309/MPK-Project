#include <stdio.h>      /* for printf() and fprintf() */
#include <sys/socket.h> /* for recv() and send() */
#include <unistd.h>     /* for close() */
#include <string>
#include <iostream>
#include <cstring>
using namespace std;
#define RCVBUFSIZE 32   /* Size of receive buffer */
#include "Cube.hpp"

void DieWithError(string errorMessage);  /* Error handling function */

void HandleTCPClient(int clntSocket)
{
    char echoBuffer[RCVBUFSIZE];        /* Buffer for echo string */
    int recvMsgSize;                    /* Size of received message */
    //char serverResponse[36]= "server received message\n";

    /* Receive message from client */
    if ((recvMsgSize = recv(clntSocket, echoBuffer, RCVBUFSIZE, 0)) < 0)
        DieWithError("recv() failed");

    //send test message
    //send(clntSocket, serverResponse, 36, 0);
    //print recevied message
    
    int bufferLength = recvMsgSize;
    /* Send received string and receive again until end of transmission */
    while (recvMsgSize > 0)      /* zero indicates end of transmission */
    {
        /* Echo message back to client */
        if (send(clntSocket, echoBuffer, recvMsgSize, 0) != recvMsgSize)
            DieWithError("send() failed");

        /* See if there is more data to receive */
        if ((recvMsgSize = recv(clntSocket, echoBuffer, RCVBUFSIZE, 0)) < 0)
            DieWithError("recv() failed");
    }

    //print inserted digits or characters on server side
    for(int i = 0;i<bufferLength;i++)
	printf("%c",echoBuffer[i]);
    printf("\n");

    //convert the received string to integers
    int scndDigit = 0;
    int firstDigit =0;
    printf("Calling Cube Function\n");

    if(int(echoBuffer[2]-'0'>0))
	scndDigit = int(echoBuffer[2])-'0';

    if (scndDigit !=0)
	firstDigit = 10*(int(echoBuffer[1])-'0');
    else
	firstDigit = int(echoBuffer[1])-'0';

    int numOfRotations = firstDigit+scndDigit;


    Cube x(int(echoBuffer[0])-'0'); //number of questions must be bigger than 0
    string newString = CubeToString(x);
    x.printCubeColor();
	

    close(clntSocket);    /* Close client socket */
}
