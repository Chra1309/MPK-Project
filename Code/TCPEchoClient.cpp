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
#include "DieWithError.hpp"
#include "ClientCube.hpp"
#include "QuestionCube.hpp"
#include "mastermind.hpp"
#include "masterheader.hpp"
#include "rubikssolver_header.hpp"
#include "fillcube.hpp"

using namespace std;

#define RCVBUFSIZE 256   /* Size of receive buffer */

int n = 20;

int changeColor(int col);
void answerConverter(int answer[3], string str_answer);

void DieWithError(string errorMessage);  /* Error handling function */
void askTwo(int putAnswer [2], int question [2], int field1 [3], int field2 [3]);
char echoBuffer[RCVBUFSIZE];     		// Buffer for echo string
int sock;                        		// Socket descriptor
struct sockaddr_in echoServAddr; 		// Echo server address
unsigned short echoServPort = 10000;    // Echo server port
char const *servIP = "127.0.0.1";       // Server IP address (dotted quad) (remove const if not fixed!)
string echoString;                		// String to send to echo server
unsigned int echoStringLen;      		// Length of string to echo
int bytesRcvd, totalBytesRcvd;   		// Bytes read in single recv() and total bytes read

/*if ((argc < 3) || (argc > 4))    // Test for correct number of arguments
{
   fprintf(stderr, "Usage: %s <Server IP> <Echo Word> [<Echo Port>]\n",
		   argv[0]);
   exit(1);
}
if (argc == 4)
	echoServPort = atoi(argv[3]);  //Use given port, if any
else
	echoServPort = 7;   //7 is the well-known port for the echo service */

string doTheClient(string toSend)
{
	
	//concatonate the question
	echoString =toSend;
	//fill empty buffer up to avoid memory leakages
	for (int f= toSend.length(); f <= RCVBUFSIZE; f++)
		echoString += '\0';

	//cout << echoString <<endl;
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
	recv(sock, echoBuffer, RCVBUFSIZE, 0);

	//debug msg:
	//cout <<echoBuffer << endl;

	close(sock);	

	return echoBuffer;
}

int changeColor(int col)
{
	if (col == 0)
		return 1;
	
	return 0;
}

void answerConverter(int answer[3], string str_answer)
{
	string temp_wrong = str_answer.substr(1, 2); // cout << endl << temp_wrong << endl;
	string temp_right = str_answer.substr(3, 2);
	string temp_correct = str_answer.substr(5, 2);

	answer[0] = atoi(temp_wrong.c_str()); // cout << answer[0];
	answer[1] = atoi(temp_right.c_str());
	answer[2] = atoi(temp_correct.c_str());
}

// kodierung putAnswer: 0 flasch, 2 richtig, 2 ganz richtig
void askTwo(int putAnswer [2], int question [2], int field1 [3], int field2 [3])
{
	QuestionCube q;
	int cur_n = 0;
	int not_set = 2;
	int ref_answer[3] = {0};
	int new_answer[3] = {0};

	for (int i=0; i<6; i++) // seite
	{
		for (int j=0; j<3; j++) // reihe
		{
			for (int k=0; k<3; k++) // spalte
			{
				cur_n++;
				
				if (i==field1[0] && j==field1[1] && k==field1[2])
				{
					not_set--;
				}
				else if (i==field2[0] && j==field2[1] && k==field2[2])
				{
					not_set--;
				}
                                else if (n != 2)
				{
					q.accessData(i,j,k,0);
				}

				if ((not_set + cur_n) >= n)
					goto out;
			}
		}
	}
	out:

	q.accessData(field1[0],field1[1],field1[2],changeColor(question[0]));
	q.accessData(field2[0],field2[1],field2[2],changeColor(question[1]));
	answerConverter( ref_answer, doTheClient(q.makeQuestion()) );

	// jetzt die farbe des ersten feldes auf die echte frage aendern!
	q.accessData(field1[0],field1[1],field1[2],question[0]);
	answerConverter( new_answer, doTheClient(q.makeQuestion()) );

	// evaluieren des ergebnises:
	// A) etwas ist gleich geblieben > falsch
	// B) es ist etwas falsches dazugekommen > falsch
	// C) es ist etwas richtiges dazugekommen > richtig

	// A)
	if (ref_answer[0] == new_answer[0] && ref_answer[1] == new_answer[1] && ref_answer[2] == new_answer[2])
	{
		putAnswer[0] = 0;
	}
	// B)
	else if (ref_answer[0] < new_answer[0])
	{
		putAnswer[0] = 0;
	}
	// C)
	else if (ref_answer[1] < new_answer[1])
	{
		putAnswer[0] = 1;
	}
	else if (ref_answer[2] < new_answer[2])
	{
		putAnswer[0] = 2;
	}

	// wiederholen fuer zweites feld!
	q.accessData(field1[0],field1[1],field1[2],changeColor(question[0]));

	q.accessData(field2[0],field2[1],field2[2],question[1]);
	answerConverter( new_answer, doTheClient(q.makeQuestion()) );

	// A)
	if (ref_answer[0] == new_answer[0] && ref_answer[1] == new_answer[1] && ref_answer[2] == new_answer[2])
	{
		putAnswer[1] = 0;
	}
	// B)
	else if (ref_answer[0] < new_answer[0])
	{
		putAnswer[1] = 0;
	}
	// C)
	else if (ref_answer[1] < new_answer[1])
	{
		putAnswer[1] = 1;
	}
	else if (ref_answer[2] < new_answer[2])
	{
		putAnswer[1] = 2;
	}
	

	return;
}

void sendmoves(){ 

    translateMove();
    doTheClient(movesTranslated);

	cout << "moves: " << moves << endl;
    cout << "translate for server:\t" << movesTranslated << endl;

	clearMoves();

}

int failsafe(int *jump, list<edge> EdgeCodes[], list<corner> CornerCodes[]){

    int listAtZero = 0; 

    //list <edge>::iterator itE = EdgeCodes[j].begin();		
    for (int j=0; j<12; j++)
	{		
		if(EdgeCodes[j].size()==0)
            return 1;
//            listAtZero++;            
	//	itE++;
	}

	//list<corner>::iterator itC = CornerCodes[j].begin();
	for(int j=0;j<8;j++)
	{
        if(CornerCodes[j].size()==0)
            return 1;
           // listAtZero++;
    //    itC++;
	}
/*
    if(listAtZero != 0)
    {
        jump ++;
        
    }*/
    return 0;
}

void solve(bool *error){
    SOLVETOPFUNCTION:
    solveTopCross(cube, orientationCube, indexCube);
    sendmoves();
    cout << "___________________________" << endl;
    cout << "TopCross" << endl;
    printCubeColor(cube);  
  
    solveTopCorners(cube, orientationCube, indexCube);
    sendmoves();
    cout << "___________________________" << endl;
    cout << "TopCorners" << endl;
    printCubeColor(cube);  
    *error = checkface(0);
    if(*error)
        goto SOLVETOPFUNCTION;

	solveMiddleLayer(cube, orientationCube, indexCube);
    sendmoves();
    cout << "___________________________" << endl;
    cout << "MiddleLayer" << endl;
    printCubeColor(cube); 

	solveBottomLayer(cube, orientationCube, indexCube);
    sendmoves();
    cout << "___________________________" << endl;
    cout << "Solved Cube" << endl;
    printCubeColor(cube); 
}

void printlist(list<edge> EdgeCodes[], list<corner> CornerCodes[]){
for (int j=0; j<12; j++)
	{
		cout << endl  << "List number " << j << " ";
		
		list <edge>::iterator it = EdgeCodes[j].begin();
		
		while(it != EdgeCodes[j].end())
		{
			cout << it->field[0] << it->field[1] << " | ";
			
			it++;
		}
		
		cout << endl;
	}

	for(int j=0;j<8;j++)
	{
		cout << endl  << "List number " << j << " ";

		list<corner>::iterator it = CornerCodes[j].begin();

		while(it != CornerCodes[j].end())
		{
			cout << it->field[0] << it->field[1] << it->field[2] << " | ";
			
			it++;
		}

		cout << endl;

	}


}

void cubesback(){

    for(int i = 0; i < 6; i++)
        for(int j = 0; j < 3; j++) 
            for(int k = 0; k < 3; k++)
                {
                orientationCube[i][j][k]=StdOrientationCube[i][j][k];
                indexCube[i][j][k]=StdIndexCube[i][j][k];
                }

}


int main(int argc, char *argv[])
{
    int jump = 0;
    int jumped = 0;
    bool solved = 0;  
	bool error = 0; // vom solver
	int solvingState = 0;

    /*
    solvingState:
    0 ... solveTopCross
    1 ... solveTopCorners
    2 ... solveMiddleLayer
    3 ... solveBottomEdges
    4 ... solveBottomCorners



    */
	clearMoves();

    if (argc != 2){
		cout << "give me a number of queries as argument (n)" << endl;	
		exit(1);
	}else{
		
		n = atoi(argv[1]);              //number of ns given by user
	}

	int MiddleCode[6] = {6,6,6,6,6,6}; //Vorsicht dieser Array ist nur für das erstellen der Listen zu verwenden 

	list <edge> EdgeCodes[12];
	list <corner> CornerCodes[8];

    LISTRESET:
    for (int i = 0; i < 8; i++)
        CornerCodes[i].clear();
    for (int i = 0; i < 12; i++)
        EdgeCodes[i].clear();
    cubesback();
    for (int i = 0; i < 6; i++)
        MiddleCode[i] = 6;	
    solvingState = 0;


	findMiddle(MiddleCode);

	buildCombOfEdge(EdgeCodes, MiddleCode);
	buildCombOfCorner(CornerCodes, MiddleCode);

	//Convertiert die Farben in einen Array bei dem die Farben dem Jeweiligen Index zugeordnet sind
	int middleColor[6] = {MiddleCode[0], MiddleCode[2], MiddleCode[4], MiddleCode[3], MiddleCode[5], MiddleCode[1]};

/*
l(cube, orientationCube, indexCube);
doTheClient("r11");
r(cube, orientationCube, indexCube);
doTheClient("r31");
	clearMoves();
*/


//print(orientationCube);
//print(indexCube);
//f(cube, orientationCube, indexCube);
/*
    for(int cnt=0;cnt<12;cnt++)
		findEdges(EdgeCodes,middleColor, cnt);


    for(int cnt=0;cnt<8;cnt++)
		findCorners(CornerCodes,middleColor, cnt);
*/



/*
while(solvingState!=5){
   	solvingState = planAction(solvingState,EdgeCodes,CornerCodes,middleColor);
}
*/
    
 //   doTheClient("r00");
  //  fillrandomcube(MiddleCode, middleColor, EdgeCodes, CornerCodes, orientationCube, indexCube);	
   // printCubeColor(cube); 





do
{  
   	solvingState = planAction(solvingState,EdgeCodes,CornerCodes,middleColor);
    cout << "done planAction " << solvingState << endl;
    if(failsafe(&jump, EdgeCodes, CornerCodes)){
        cout << "\033[31mLISTRESET (list at 0)\033[39m" << endl;   
        jumped ++;            
        goto LISTRESET;    
    }

   //printlist(EdgeCodes, CornerCodes);
   //print(indexCube);

    if(fillrandomcube(MiddleCode, middleColor, EdgeCodes, CornerCodes, orientationCube, indexCube)){
        cout << "\033[31mLISTRESET (tries > treshold)\033[39m" << endl;
        jumped ++;            
        goto LISTRESET;
    }
    cout << "done fillrandomcube " << endl;	
    printCubeColor(cube);  
    mapforsolver(cube);

	switch(solvingState)
    {
	    case 0:     
        case 1:
        case 2:
        case 3:
        case 4:
            SOLVETOPFOUR:
            solveTopCross(cube, orientationCube, indexCube);
            sendmoves();
            cout << "___________________________" << endl;
            cout << "TopCross" << endl;
            printCubeColor(cube);  
          
            solveTopCorners(cube, orientationCube, indexCube);
            sendmoves();
            cout << "___________________________" << endl;
            cout << "TopCorners" << endl;
            printCubeColor(cube);  
            error = checkface(0);
            if(error)
                goto SOLVETOPFOUR;

	        solveMiddleLayer(cube, orientationCube, indexCube);
            sendmoves();
            cout << "___________________________" << endl;
            cout << "MiddleLayer" << endl;
            printCubeColor(cube); 

	        solveBottomLayer(cube, orientationCube, indexCube);
            sendmoves();
            cout << "___________________________" << endl;
            cout << "Solved Cube" << endl;
            printCubeColor(cube); 
            break;
    case 5: 
        break;
    }
    cout << "state: " << solvingState << endl; 
    if(jump > 0)
        cout << "JUMP UP, JUMP UP AND GET DOWN: " << jumped << endl; 
    //usleep(1000000*0.25);   
     
}
while(solvingState!=4);
cout << "finalstate: " << solvingState << endl;  
/*
if(solvingState == 5)
{
    cout << "GRANDE FINALE" << endl;
    fillrandomcube(MiddleCode, middleColor, EdgeCodes, CornerCodes, orientationCube, indexCube);	
    printCubeColor(cube);  
    mapforsolver(cube);

            SOLVETOPFIVE:
            solveTopCross(cube, orientationCube, indexCube);

            cout << "___________________________" << endl;
            cout << "TopCross" << endl;
            sendmoves();
            printCubeColor(cube);  
          
            solveTopCorners(cube, orientationCube, indexCube);

            cout << "___________________________" << endl;
            cout << "TopCorners" << endl;
            sendmoves();
            printCubeColor(cube);  
            error = checkface(0);
            if(error)
                goto SOLVETOPFIVE;

	        solveMiddleLayer(cube, orientationCube, indexCube);

            cout << "___________________________" << endl;
            cout << "MiddleLayer" << endl;
            sendmoves();
            printCubeColor(cube); 

	        solveBottomLayer(cube, orientationCube, indexCube);

            cout << "___________________________" << endl;
            cout << "Solved Cube" << endl;
            sendmoves();
            printCubeColor(cube); 
       
}

*/
/*
    {
        int solvedfaces = 6; 
        for(int i = 0; i < 6; i ++){
            solvedfaces -= checkface(i);    
            
        }
        if(solvedfaces == 6 && solvingState == 5)  
        {
          //  solved = 1; 
            cout << "\033[92m___________________________" << endl << endl; 
            cout <<         "         solved!" << endl;
            cout <<         "___________________________\033[39m" << endl << endl; 
        }
    }
*/

	//// THE END ////
	
    exit(0);
}
