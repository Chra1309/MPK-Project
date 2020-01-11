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
#include "Cube_old.hpp"


using namespace std;

#define RCVBUFSIZE 64   /* Size of receive buffer */

void DieWithError(string errorMessage);  /* Error handling function */

int main(int argc, char *argv[])
{
    int sock;                        /* Socket descriptor */
    struct sockaddr_in echoServAddr; /* Echo server address */
    unsigned short echoServPort;     /* Echo server port */
    char const *servIP;                    // Server IP address (dotted quad) !!! remove const if not fixed!!!!!!!!
    string echoString;                /* String to send to echo server */
    char echoBuffer[RCVBUFSIZE];     /* Buffer for echo string */
    unsigned int echoStringLen;      /* Length of string to echo */
    int bytesRcvd, totalBytesRcvd;   /* Bytes read in single recv() 
                                        and total bytes read */
	
    /*if ((argc < 3) || (argc > 4))    // Test for correct number of arguments
    {
       fprintf(stderr, "Usage: %s <Server IP> <Echo Word> [<Echo Port>]\n",
               argv[0]);
       exit(1);
    }*/
	
	if (argc != 1){
		cout << "Fixed Server IP is 127.0.0.1 and Port 10000" << endl;	
		exit(1);
	}
	
    /*servIP = argv[1];              First arg: server IP address (dotted quad) */
	servIP = "127.0.0.1";
	
    /*if (argc == 4)
        echoServPort = atoi(argv[3]);  //Use given port, if any
    else
        echoServPort = 7;   //7 is the well-known port for the echo service */
	echoServPort = 10000;

	///////////////////////////////////input rotate actions here/////////////////////////////////////////
    echoString = "u2";        

    /* Create a reliable, stream socket using TCP */
    if ((sock = socket(PF_INET, SOCK_STREAM, IPPROTO_TCP)) < 0)
        DieWithError("socket() failed");

    /* Construct the server address structure */
    memset(&echoServAddr, 0, sizeof(echoServAddr));     /* Zero out structure */
    echoServAddr.sin_family      = AF_INET;             /* Internet address family */
    echoServAddr.sin_addr.s_addr = inet_addr(servIP);   /* Server IP address */
    echoServAddr.sin_port        = htons(echoServPort); /* Server port */

    /* Establish the connection to the echo server */
    if (connect(sock, (struct sockaddr *) &echoServAddr, sizeof(echoServAddr)) < 0)
        DieWithError("connect() failed");

    echoStringLen = RCVBUFSIZE;         /* Determine input length */
    //echoStringLen = echoString.length();
	
    /* Send the string to the server */
    if (send(sock, echoString.c_str(), echoStringLen, 0) != echoStringLen)
        DieWithError("send() sent a different number of bytes than expected");
		
    /* Receive the same string back from the server */
    totalBytesRcvd = 0;
    printf("Received Random Cube from Server: ");                /* Setup to print the echoed string */
    while (totalBytesRcvd < echoStringLen)
    {
        /* Receive up to the buffer size (minus 1 to leave space for
           a null terminator) bytes from the sender */
        if ((bytesRcvd = recv(sock, echoBuffer, RCVBUFSIZE - 1, 0)) <= 0)
            DieWithError("recv() failed or connection closed prematurely");
        totalBytesRcvd += bytesRcvd;   /* Keep tally of total bytes */
        echoBuffer[bytesRcvd] = '\0';  /* Terminate the string! */
        printf("%s", echoBuffer);      /* Print the echo buffer */
    }

    printf("\n");    /* Print a final linefeed */

    
    cout << "von array: " << echoBuffer[2] << endl; 

    //// wird funktion: 
    

	//loop here to make more than one question

	
	
    close(sock);
    exit(0);
}
