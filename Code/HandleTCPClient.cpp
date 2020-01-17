#include <stdio.h>      /* for printf() and fprintf() */
#include <sys/socket.h> /* for recv() and send() */
#include <unistd.h>     /* for close() */
#include <string>
#include <iostream>
#include <cstring>
using namespace std;
#define RCVBUFSIZE 256   /* Size of receive buffer */
#define TOSENDSIZE 256    //size of to send buffer
#include "ServerCube.hpp"

char echoBuffer[RCVBUFSIZE];        /* Buffer for echo string */
int recvMsgSize;                    /* Size of received message */
char toSend[TOSENDSIZE];			//Buffer for send string		

void DieWithError(string errorMessage);  /* Error handling function */

int numberOfRotations(){
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

void getActions(ServerCube& myCube){

	int n = 0;
	for (int i = 1; echoBuffer[i]!='\0';i+=2){
		myCube.rotate(echoBuffer[1]-'0',echoBuffer[2]-'0');
		n++;
	}
	//ack schicken
	toSend[0] = 'A';
}	
void makeAnswer(ServerCube myCube)
{	
	char temp[54];
	for(int i=0;i<54;i++)
		temp[i]=echoBuffer[i+1];
	string temp2(temp);
	ServerCube* question=new ServerCube(0);
	question->stringToCube(temp2);

	int answer[3];

	myCube.compareToQuestion(*question,answer[0],answer[1],answer[2]);
	delete question;
	
	//Array==>Answer schicken(a;answer[0];answer[1];answer[2]\0
	toSend[0]= 'a';
	toSend[1]=answer[0]%10+'0';
	toSend[2]=answer[0]/10+'0';
	toSend[3]=answer[1]%10+'0';
	toSend[4]=answer[1]/10+'0';
	toSend[5]=answer[2]%10+'0';
	toSend[6]=answer[2]/10+'0';
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
	ServerCube y(1); //Create an abritary cube

    y.printCubeColor();
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
	getActions(y);
	
    close(clntSocket);    /* Close client socket */
}
