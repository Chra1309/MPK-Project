#include <iostream>
#include <stdlib.h>
#include <string>
#include <cmath>
#include <time.h>
#include <stdio.h>
#include <ctime>
#include <algorithm>    // std::random_shuffle

#include <vector>
#include "rubikssolver_header.hpp"

using namespace std;


int cube_customcolor[6][3][3];

int solveable = 0;
//int getCorners(int** array, int ***cubetofind);
//void getCorners();


//////////////////// PROTOTYPES ////////////////////
string printColor(int); //Ausgabe von Farbe
void printCubeColor(); 	//Ausgabe des Cubes im Terminal in Farbe
void printCubeStd();	//Ausgabe des Cubes im Terminal in Zahlen		
int edgepartitytest();		    
int cornerparitytest();
void permutationpartiytest();
int getCorners(int array[8][3], int cubetofind[6][3][3]);
int setCorners(int array[8][3], int cubetofind[6][3][3]);
void getEdges(int array[12][2], int cubetofind[6][3][3]);
void setEdges(int edge[12][2], int cube[6][3][3]);

int cube[6][3][3] = {
	{ { 0, 0, 0 }, { 0, 0, 0 }, { 0, 0, 0 } },   //yellow side
	{ { 1, 1, 1 }, { 1, 1, 1 }, { 1, 1, 1 } },   //orange side
	{ { 2, 2, 2 }, { 2, 2, 2 }, { 2, 2, 2 } },   //blue side
	{ { 3, 3, 3 }, { 3, 3, 3 }, { 3, 3, 3 } },   //red side
	{ { 4, 4, 4 }, { 4, 4, 4 }, { 4, 4, 4 } },   //green side
	{ { 5, 5, 5 }, { 5, 5, 5 }, { 5, 5, 5 } } }; //white side

int probcube[6][3][3] = {
	{ { 1, 6, 2 }, { 6, 6, 6 }, { 6, 6, 6 } },   //yellow side
	{ { 6, 6, 6 }, { 6, 6, 6 }, { 6, 6, 1 } },   //orange side
	{ { 6, 6, 6 }, { 0, 6, 6 }, { 5, 6, 6 } },   //blue side
	{ { 6, 6, 3 }, { 6, 3, 6 }, { 6, 6, 6 } },   //red side
	{ { 6, 6, 6 }, { 6, 6, 6 }, { 6, 2, 6 } },   //green side
	{ { 6, 6, 6 }, { 4, 6, 6 }, { 6, 6, 6 } } }; //white side







void printCubeStd(int data[6][3][3])
{
	for(int i=0;i<3;i++)
	{
		cout<<"    "<<data[0][i][0]<<data[0][i][1]<<data[0][i][2]<<endl;
	}
	for(int i=0;i<3;i++)
	{
		cout<<data[1][i][0]<<data[1][i][1]<<data[1][i][2]<<" ";
		cout<<data[2][i][0]<<data[2][i][1]<<data[2][i][2]<<" ";
		cout<<data[3][i][0]<<data[3][i][1]<<data[3][i][2]<<" ";
		cout<<data[4][i][0]<<data[4][i][1]<<data[4][i][2]<<" "<<endl;
	}
	for(int i=0;i<3;i++)
	{
		cout<<"    "<<data[5][i][0]<<data[5][i][1]<<data[5][i][2]<<endl;
	}	
	cout<<endl<<endl;
}


int main()
{

    printCubeColor(cube);
   // twoEdgeRotate(2, false);
    //rotateEdges(1, false);
    swapCorners(2);
    printCubeColor(cube);
    

 

    /*
    //for(int i = 0; i <10; i++){
        //scramble();
    do{
        system("clear");
        cout << endl;
        fillrandom();
        //clearMoves();
        printCubeColor(cube);

        // generate black cube 
        //printCubeStd(cube);
    */

    //}


/*
        else{
            solved = 1;
            break;
            }

    }

    //while(solved <= 1);
    */
    





return 0;
}
