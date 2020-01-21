#include <stdio.h>      /* for printf() and fprintf() */
#include <sys/socket.h> /* for socket(), connect(), send(), and recv() */
#include <arpa/inet.h>  /* for sockaddr_in and inet_addr() */
#include <stdlib.h>     /* for atoi() and exit() */
#include <string.h>     /* for memset() */
#include <unistd.h>     /* for close() */
#include <string>
#include <stdio.h> 
#include <iostream>
#include <cstring> 
#include "ClientCube.hpp"
#include "rubikssolver_header.hpp"
using namespace std;

#define RCVBUFSIZE 64   /* Size of receive buffer */

void DieWithError(string errorMessage);  /* Error handling function */

int cube[6][3][3] = {
	{ { 0, 0, 0 }, { 0, 0, 0 }, { 0, 0, 0 } }, //yellow side
	{ { 1, 1, 1 }, { 1, 1, 1 }, { 1, 1, 1 } }, //orange side
	{ { 2, 2, 2 }, { 2, 2, 2 }, { 2, 2, 2 } }, //blue side
	{ { 3, 3, 3 }, { 3, 3, 3 }, { 3, 3, 3 } }, //red side
	{ { 4, 4, 4 }, { 4, 4, 4 }, { 4, 4, 4 } }, //green side
	{ { 5, 5, 5 }, { 5, 5, 5 }, { 5, 5, 5 } } }; //white side

int cube_customcolor[6][3][3];
char echoBuffer[RCVBUFSIZE];     /* Buffer for echo string */
int sock;                        /* Socket descriptor */
struct sockaddr_in echoServAddr; /* Echo server address */
unsigned short echoServPort = 10000;     /* Echo server port */
char const *servIP = "127.0.0.1";        // Server IP address (dotted quad) !!! remove const if not fixed!!!!!!!!
string echoString;                		/* String to send to echo server */
string outputAnswer;
int cubestring[54];
unsigned int echoStringLen;      /* Length of string to echo */
int bytesRcvd, totalBytesRcvd;   /* Bytes read in single recv() 
									and total bytes read */

/*if ((argc < 3) || (argc > 4))    // Test for correct number of arguments
{
   fprintf(stderr, "Usage: %s <Server IP> <Echo Word> [<Echo Port>]\n",
		   argv[0]);
   exit(1);
}

servIP = argv[1];              //First arg: server IP address (dotted quad)

if (argc == 4)
	echoServPort = atoi(argv[3]);  //Use given port, if any
else
	echoServPort = 7;   //7 is the well-known port for the echo service */


string doTheClient(string toSend){
	
	//make a random question
	echoString = "q";
	echoString +=toSend;

	cout << echoString <<endl;
	// Create a reliable, stream socket using TCP
	if ((sock = socket(PF_INET, SOCK_STREAM, IPPROTO_TCP)) < 0)
		DieWithError("socket() failed");

	// Construct the server address structure
	memset(&echoServAddr, 0, sizeof(echoServAddr));     // Zero out structure
	echoServAddr.sin_family      = AF_INET;             // Internet address family
	echoServAddr.sin_addr.s_addr = inet_addr(servIP);   // Server IP address 
	echoServAddr.sin_port        = htons(echoServPort); // Server port 

	// Establish the connection to the echo server
	if (connect(sock, (struct sockaddr *) &echoServAddr, sizeof(echoServAddr)) < 0)
		DieWithError("connect() failed");

	echoStringLen = RCVBUFSIZE;         //Determine input length

	// Send the string to the server
	if (send(sock, echoString.c_str(), echoStringLen, 0) != echoStringLen)
	   DieWithError("send() sent a different number of bytes than expected");

	// Receive the answer back from the server
	totalBytesRcvd = 0;
	recv(sock, echoBuffer, 64, 0);

	cout <<echoBuffer << endl;
	//getAnswer();

	close(sock);	
	
	outputAnswer = echoBuffer;
	
	return outputAnswer;
	}


int main(int argc, char *argv[])
{
    if (argc != 1){
	cout << "Fixed Server IP is 127.0.0.1 and Port 10000" << endl;	
	exit(1);
	}	
		
	//make a random cube as question
	srand (time(NULL));
	ClientCube z(1);
	string x = cubeToString(z);

	/////////do the client connection establishment, send, receive and socket closing///////////
	doTheClient(x);
	
    exit(0);
}
