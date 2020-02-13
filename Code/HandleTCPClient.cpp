#include <stdio.h>      /* for printf() and fprintf() */
#include <sys/socket.h> /* for recv() and send() */
#include <unistd.h>     /* for close() */
#include <string>
#include <iostream>
#include <cstring>
using namespace std;
#define RCVBUFSIZE 256   /* Size of receive buffer */
#define TOSENDSIZE 64    //size of to send buffer
#include "ServerCube.hpp"

char echoBuffer[RCVBUFSIZE];        /* Buffer for echo string */
int recvMsgSize;                    /* Size of received message */
char toSend[TOSENDSIZE];			//Buffer for send string		


void DieWithError(string errorMessage);  /* Error handling function */
/*
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
}*/

void getActions(ServerCube& myCube){

	int n = 0;
	for (int i = 1; echoBuffer[i]!='\0';i+=2){
		myCube.rotate(echoBuffer[i]-'0',echoBuffer[i+1]-'0');
		n++;
	}
	myCube.print();
	if(myCube.checkDone())
		toSend[0]=1+'0';
	else
		toSend[0]=0+'0';
	
	toSend[1]='\0';
}	
void makeAnswer(ServerCube myCube)
{	
	char temp[54];
	for(int i=0;i<54;i++)
		temp[i]=echoBuffer[i+1];
	string temp2(temp);
	ServerCube* question=new ServerCube(0);
	question->stringToCube(temp2);

	//cout<<temp2<<endl;
	
	int answer[3];
	//question->print(); // print answer

	
	myCube.compareToQuestion(*question,answer);
	delete question;
	
	//Array==>Answer schicken(a;answer[0];answer[1];answer[2]\0
	toSend[0]= 'a';
	toSend[1]=answer[0]/10+'0';
	toSend[2]=answer[0]%10+'0';
	toSend[3]=answer[1]/10+'0';
	toSend[4]=answer[1]%10+'0';
	toSend[5]=answer[2]/10+'0';
	toSend[6]=answer[2]%10+'0';
	toSend[7]='\0';
}

void printReceivedBuffer(){
	//PRINT ECHO BUFFER
	echoBuffer[RCVBUFSIZE] = '\0';  /* Terminate the string! */
    cout << echoBuffer << endl;      /* Print the echo buffer */
}

ServerCube y(1); //Create an random cube

bool HandleTCPClient(int clntSocket)
{

    /* Receive message from client */
    if ((recvMsgSize = recv(clntSocket, echoBuffer, RCVBUFSIZE, 0)) < 0)
        DieWithError("recv() failed");

    //send test message
    //print recevied message
	
    cout << "_____________________________________________________________________________" << endl;	
	cout << "Received from Client: ";
	printReceivedBuffer();
	//getActions(y);
	//convert to String


	if(echoBuffer[0]=='q')
		makeAnswer(y);
	if(echoBuffer[0]=='r')
		getActions(y);
    cout << "Answer:\t";
	cout << toSend <<endl;
    if(toSend[0] == '1')
        {
            cout << "\033[92m___________________________" << endl << endl; 
            cout <<         "         solved!" << endl;
            cout <<         "___________________________\033[39m" << endl << endl;
            close(clntSocket);
            return 1; 
        }

    
    int bufferLength = recvMsgSize;
    /* Send received string and receive again until end of transmission */
    while (recvMsgSize > 0)      /* zero indicates end of transmission */
    {
        /* Echo message back to client */
        if (send(clntSocket, toSend, recvMsgSize, 0) != recvMsgSize)
            DieWithError("send() failed");
		
		
        /* See if there is more data to receive */
        if ((recvMsgSize = recv(clntSocket, echoBuffer, RCVBUFSIZE, 0)) < 0)
            DieWithError("recv() failed");
    }

    close(clntSocket);    /* Close client socket */	
    return 0; 

}
