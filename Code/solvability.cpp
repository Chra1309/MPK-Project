#include <iostream>
#include <stdlib.h>
#include <string>
#include <cmath>
#include <time.h>
#include <stdio.h>

#include "rubikssolver_header.hpp"

using namespace std;


int cube_customcolor[6][3][3];
string printColor(int); //Ausgabe von Farbe
void printCubeColor(); 	//Ausgabe des Cubes im Terminal in Farbe
void printCubeStd();	//Ausgabe des Cubes im Terminal in Zahlen		
int edgepartitytest();		    
int cornerparitytest();
void permutationpartiytest();
int solveable = 0;

int cube[6][3][3] = {
	{ { 0, 0, 0 }, { 0, 0, 0 }, { 0, 0, 0 } },   //yellow side
	{ { 1, 1, 1 }, { 1, 1, 1 }, { 1, 1, 1 } },   //orange side
	{ { 2, 2, 2 }, { 2, 2, 2 }, { 2, 2, 2 } },   //blue side
	{ { 3, 3, 3 }, { 3, 3, 3 }, { 3, 3, 3 } },   //red side
	{ { 4, 4, 4 }, { 4, 4, 4 }, { 4, 4, 4 } },   //green side
	{ { 5, 5, 5 }, { 5, 5, 5 }, { 5, 5, 5 } } }; //white side

void fillrandom(){
  srand(time(NULL));
    for(int i = 0; i < 6; i++){
        for(int j = 0; j <3; j++){
            for(int k = 0; k < 3; k++){
                cube[i][j][k] = rand() % 6;
            }    
        }
    }
}

int cornerparitytest(){
    int topcol = cube[0][1][1];
    int botcol = cube[5][1][1];

    int corner[8][3];
    int sum = 0;

    corner[0][0] = cube[0][0][0];
    corner[0][1] = cube[1][0][0];
    corner[0][2] = cube[4][0][2];

    corner[1][0] = cube[0][0][2];
    corner[1][1] = cube[4][0][0];
    corner[1][2] = cube[3][0][2];

    corner[2][0] = cube[0][2][2];
    corner[2][1] = cube[3][0][0];
    corner[2][2] = cube[2][0][2];

    corner[3][0] = cube[0][2][0];
    corner[3][1] = cube[2][0][0];
    corner[3][2] = cube[1][0][2];

    corner[4][0] = cube[5][2][0];
    corner[4][1] = cube[4][2][2];
    corner[4][2] = cube[1][2][0];

    corner[5][0] = cube[5][2][2];
    corner[5][1] = cube[3][2][2];
    corner[5][2] = cube[4][2][0];

    corner[6][0] = cube[5][0][2];
    corner[6][1] = cube[2][2][2];
    corner[6][2] = cube[3][2][0];

    corner[7][0] = cube[5][0][0];
    corner[7][1] = cube[1][2][2];
    corner[7][2] = cube[2][2][0];

    /*
    for(int i = 0; i < 8; i++){
        cout << "conrner" << i << ":" << endl;
        cout << corner[i][0] << " - " << corner[i][1] << " - " << corner[i][2] << endl;
    
    }
    */

    for(int i = 0; i < 8; i++){
        if( corner[i][0] == corner[i][1] || 
            corner[i][1] == corner[i][2] || 
            corner[i][2] == corner[i][0]){ 
            cout << "\033[31munsolveable: multiple colors on corners \t\t(position: " << i << ")\033[39m" << endl;
            break;
        }
    }

    for(int i = 0; i < 8; i++){    
        if(corner[i][0] == topcol || corner[i][0] == botcol)
            {
                sum += 0;
                //cout << "corner" << i << ": "<< sum << endl;
            }
        else if(corner[i][2] == topcol || corner[i][2] == botcol)
            {
                sum += 1;
                //cout << "corner" << i << ": "<< sum << endl;
            }
        else if(corner[i][1] == topcol || corner[i][1] == botcol)
            {
                sum += 2;
                //cout << "corner" << i << ": "<< sum << endl;
            }
        else{
                cout << "\033[31munsolveable: Error at corner orientation\t(position: " << i << ")\033[39m" << endl;
                solveable = 0; 
                return solveable; 
                break;
            }

    }    

    if(sum%3 == 0)
        cout << "Corner Partity Test \tPASS (Sum: " << sum << ")" << endl;
    else 
        cout << "Corner Partity Test \t\033[101m FAIL (Sum: " << sum << ")\033[0m" << endl;


}

void permutationpartiytest(){



    


}


int edgepartitytest(){

 int topcol = cube[0][1][1];
 int botcol = cube[5][1][1];
 int frocol = cube[2][1][1];
 int baccol = cube[4][1][1];

 int edge[12][2];
 
 edge[0][0] = cube[0][1][0]; 
 edge[0][1] = cube[1][0][1];

 edge[1][0] = cube[0][0][1];
 edge[1][1] = cube[4][0][1];

 edge[2][0] = cube[0][1][2];
 edge[2][1] = cube[3][0][1];

 edge[3][0] = cube[0][2][1];
 edge[3][1] = cube[2][0][1];

////////////////////////////

 edge[4][0] = cube[1][1][0];
 edge[4][1] = cube[4][1][2];

 edge[5][0] = cube[3][1][2];
 edge[5][1] = cube[4][1][0];

 edge[6][0] = cube[2][1][2];
 edge[6][1] = cube[3][1][0];

 edge[7][0] = cube[1][1][2];
 edge[7][1] = cube[2][1][0];

////////////////////////////

 edge[8][0] = cube[1][2][1];
 edge[8][1] = cube[5][1][0];

 edge[9][0] = cube[4][2][1];
 edge[9][1] = cube[5][2][1];

 edge[10][0] = cube[3][2][1];
 edge[10][1] = cube[5][1][2];

 edge[11][0] = cube[2][2][1];
 edge[11][1] = cube[5][0][1];
    

 int sum = 0; 
    
    for(int i = 0; i <12; i++){ 

     if(            edge[i][0] == topcol || edge[i][0] == botcol
                ||  edge[i][1] == topcol || edge[i][1] == botcol )
        sum += 0;
     else if (      edge[i][0] == frocol || edge[i][0] == baccol
                ||  edge[i][1] == frocol || edge[i][1] == baccol )
        sum += 1;
     else{
        cout << "\033[31munsolveable: Error at Edge Partity Test \t(position: " << i << ")\033[39m" << endl;
        solveable = 0; 
        return solveable;
        }

    }

    if(sum%2 == 0)
        cout << "Edge Partity Test \tPASS (Sum: " << sum << ")" << endl;
    else 
        cout << "Edge Partity Test \t\033[31mFAIL (Sum: " << sum << ")\033[39m" << endl;

    solveable += 1;

}





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
    int solved;
    //for(int i = 0; i <10; i++){
        //scramble();
    do{
        fillrandom();
        //clearMoves();
        printCubeColor(cube);

        // generate black cube 
        printCubeStd(cube);
        edgepartitytest();
        cornerparitytest();
    //}

        if(solveable != 3){
            cout << "\033[31m___________________________" << endl << endl; 
            cout <<         "       unsolveable" << endl;
            cout <<         "___________________________\033[39m" << endl << endl;


        }
        else
            solved = 1;

    }
    while(solved <= 1);
    




return 0;
}
