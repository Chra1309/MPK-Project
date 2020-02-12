#ifndef CUBEOPERATIONS_HPP
#define CUBEOPERATIONS_HPP

#include <iostream>
#include <ctime>
#include <cstdlib>
#include <algorithm>
#include <iostream>
#include <stdlib.h>
#include <string>
#include <cmath>
#include <time.h>
#include <stdio.h>

using namespace std;

int getCorners(int array[8][3], int cubetofind[6][3][3]);
int setCorners(int array[8][3], int cubetofind[6][3][3], int oCube[6][3][3], int iCube[6][3][3]);
void getEdges(int array[12][2], int cubetofind[6][3][3]);
void setEdges(int edge[12][2], int cube[6][3][3], int oCube[6][3][3], int iCube[6][3][3]);
void printCubeColor(int cube_array[6][3][3]);


string printColor(int field)
{
		
    string RESET = "\033[0m";
	string WHITE = "\033[107m";         //  White 
	string RED = "\033[101m";           // Red
	string GREEN = "\033[102m";         // Green 
	string BLUE = "\e[48;5;21m";        // Blue 
	string ORANGE = "\e[48;5;208m";     // Magenta  
	string YELLOW = "\033[103m";        // Yellow 
    string BLACK = "\033[40m"; 
				
	string printcolor;
	switch(field){
        case 6:
			printcolor = BLACK + "  " + RESET;		
			break;
		case 5: 
			printcolor = WHITE + "  " + RESET;		
			break;		
		case 3:
			printcolor = RED + "  " + RESET;					
			break;
		case 4: 
			printcolor = GREEN + "  " + RESET;					
			break;
		case 2:
			printcolor = BLUE + "  " + RESET;									
			break;
		case 1: 				
			printcolor = ORANGE + "  " + RESET;					
			break;			
		case 0: 
			printcolor = YELLOW + "  " + RESET;								
			break;				
	}
	return printcolor;
}

void printCubeColor(int cube_array[6][3][3])
{ 

    //cout<<"PRINTING CUSTOM CUBE"<<endl;
	for(int i=0;i<3;i++)
	{
		cout<<"       "<<printColor(cube_array[0][i][0])<<printColor(cube_array[0][i][1])<<printColor(cube_array[0][i][2])<<endl;
	}
	for(int i=0;i<3;i++)
	{
		cout<<printColor(cube_array[1][i][0])<<printColor(cube_array[1][i][1])<<printColor(cube_array[1][i][2])<<" ";
		cout<<printColor(cube_array[2][i][0])<<printColor(cube_array[2][i][1])<<printColor(cube_array[2][i][2])<<" ";
		cout<<printColor(cube_array[3][i][0])<<printColor(cube_array[3][i][1])<<printColor(cube_array[3][i][2])<<" ";
		cout<<printColor(cube_array[4][i][0])<<printColor(cube_array[4][i][1])<<printColor(cube_array[4][i][2])<<" "<<endl;
	}
	for(int i=0;i<3;i++)
	{
		cout<<"       "<<printColor(cube_array[5][i][0])<<printColor(cube_array[5][i][1])<<printColor(cube_array[5][i][2])<<endl;
	}	
	cout<<endl<<endl;	
}




void setEdges(int edge[12][2], int edge_cube[6][3][3], int oCube[6][3][3], int iCube[6][3][3]){


    edge_cube[0][1][0] = edge[iCube[0][1][0]][oCube[0][1][0]];  
    edge_cube[1][0][1] = edge[iCube[1][0][1]][oCube[1][0][1]];  

    edge_cube[0][0][1] = edge[iCube[0][0][1]][oCube[0][0][1]];  
    edge_cube[4][0][1] = edge[iCube[4][0][1]][oCube[4][0][1]];  

    edge_cube[0][1][2] = edge[iCube[0][1][2]][oCube[0][1][2]];  
    edge_cube[3][0][1] = edge[iCube[3][0][1]][oCube[3][0][1]];  

    edge_cube[0][2][1] = edge[iCube[0][2][1]][oCube[0][2][1]];  
    edge_cube[2][0][1] = edge[iCube[2][0][1]][oCube[2][0][1]];  

////////////////////////////

    edge_cube[1][1][2] = edge[iCube[1][1][2]][oCube[1][1][2]];  
    edge_cube[2][1][0] = edge[iCube[2][1][0]][oCube[2][1][0]];  

    edge_cube[1][1][0] = edge[iCube[1][1][0]][oCube[1][1][0]];  
    edge_cube[4][1][2] = edge[iCube[4][1][2]][oCube[4][1][2]];  

    edge_cube[3][1][2] = edge[iCube[3][1][2]][oCube[3][1][2]];  
    edge_cube[4][1][0] = edge[iCube[4][1][0]][oCube[4][1][0]];  

    edge_cube[2][1][2] = edge[iCube[2][1][2]][oCube[2][1][2]];  
    edge_cube[3][1][0] = edge[iCube[3][1][0]][oCube[3][1][0]];  

////////////////////////////

    edge_cube[1][2][1] = edge[iCube[1][2][1]][oCube[1][2][1]];  
    edge_cube[5][1][0] = edge[iCube[5][1][0]][oCube[5][1][0]];  

    edge_cube[4][2][1] = edge[iCube[4][2][1]][oCube[4][2][1]];  
    edge_cube[5][2][1] = edge[iCube[5][2][1]][oCube[5][2][1]];  

    edge_cube[3][2][1] = edge[iCube[3][2][1]][oCube[3][2][1]];  
    edge_cube[5][1][2] = edge[iCube[5][1][2]][oCube[5][1][2]];  

    edge_cube[2][2][1] = edge[iCube[2][2][1]][oCube[2][2][1]];  
    edge_cube[5][0][1] = edge[iCube[5][0][1]][oCube[5][0][1]];  

/*
    edge_cube[0][1][0] = edge[0][0];  
    edge_cube[1][0][1] = edge[0][1];

    edge_cube[0][0][1] = edge[1][0];
    edge_cube[4][0][1] = edge[1][1];

    edge_cube[0][1][2] = edge[2][0];
    edge_cube[3][0][1] = edge[2][1];

    edge_cube[0][2][1] = edge[3][0];
    edge_cube[2][0][1] = edge[3][1]; 

////////////////////////////

    edge_cube[1][1][2] = edge[4][0];
    edge_cube[2][1][0] = edge[4][1];

    edge_cube[1][1][0] = edge[5][0];
    edge_cube[4][1][2] = edge[5][1];

    edge_cube[3][1][2] = edge[6][0];
    edge_cube[4][1][0] = edge[6][1];

    edge_cube[2][1][2] = edge[7][0];
    edge_cube[3][1][0] = edge[7][1];

////////////////////////////

    edge_cube[1][2][1] = edge[8][0];
    edge_cube[5][1][0] = edge[8][1];

    edge_cube[4][2][1] = edge[9][0];
    edge_cube[5][2][1] = edge[9][1];

    edge_cube[3][2][1] = edge[10][0];
    edge_cube[5][1][2] = edge[10][1];

    edge_cube[2][2][1] = edge[11][0];
    edge_cube[5][0][1] = edge[11][1];
*/
}

void getEdges(int edge[12][2], int cube[6][3][3]){

    edge[0][0] = cube[0][1][0]; 
    edge[0][1] = cube[1][0][1];

    edge[1][0] = cube[0][0][1];
    edge[1][1] = cube[4][0][1];

    edge[2][0] = cube[0][1][2];
    edge[2][1] = cube[3][0][1];

    edge[3][0] = cube[0][2][1];
    edge[3][1] = cube[2][0][1];

    ////////////////////////////

    edge[4][1] = cube[1][1][2];
    edge[4][0] = cube[2][1][0];

    edge[5][1] = cube[1][1][0];
    edge[5][0] = cube[4][1][2];

    edge[6][1] = cube[3][1][2];
    edge[6][0] = cube[4][1][0];

    edge[7][0] = cube[2][1][2];
    edge[7][1] = cube[3][1][0];

    ////////////////////////////

    edge[8][1] = cube[1][2][1];
    edge[8][0] = cube[5][1][0];

    edge[9][1] = cube[4][2][1];
    edge[9][0] = cube[5][2][1];

    edge[10][1] = cube[3][2][1];
    edge[10][0] = cube[5][1][2];

    edge[11][1] = cube[2][2][1];
    edge[11][0] = cube[5][0][1];

}

int getCorners(int array[8][3], int cubetofind[6][3][3]){

// first top or bottom then counter clockwise

    array[0][0] = cubetofind[0][2][0];
    array[0][1] = cubetofind[1][0][2];
    array[0][2] = cubetofind[2][0][0];

    array[1][0] = cubetofind[0][0][0];
    array[1][1] = cubetofind[4][0][2];
    array[1][2] = cubetofind[1][0][0];

    array[2][0] = cubetofind[0][0][2];
    array[2][1] = cubetofind[3][0][2];
    array[2][2] = cubetofind[4][0][0];

    array[3][0] = cubetofind[0][2][2];
    array[3][1] = cubetofind[2][0][2];
    array[3][2] = cubetofind[3][0][0];
/*
    array[4][0] = cubetofind[1][2][2];
    array[4][1] = cubetofind[5][0][0];
    array[4][2] = cubetofind[2][2][0];

    array[5][0] = cubetofind[1][2][0];
    array[5][1] = cubetofind[4][2][2];
    array[5][2] = cubetofind[5][2][0];

    array[6][0] = cubetofind[3][2][2];
    array[6][1] = cubetofind[5][2][2];
    array[6][2] = cubetofind[4][2][0];

    array[7][0] = cubetofind[2][2][2];
    array[7][1] = cubetofind[5][0][2];
    array[7][2] = cubetofind[3][2][0];
*/

    array[4][2] = cubetofind[1][2][2];
    array[4][0] = cubetofind[5][0][0];
    array[4][1] = cubetofind[2][2][0];

    array[5][1] = cubetofind[1][2][0];
    array[5][2] = cubetofind[4][2][2];
    array[5][0] = cubetofind[5][2][0];

    array[6][2] = cubetofind[3][2][2];
    array[6][0] = cubetofind[5][2][2];
    array[6][1] = cubetofind[4][2][0];

    array[7][2] = cubetofind[2][2][2];
    array[7][0] = cubetofind[5][0][2];
    array[7][1] = cubetofind[3][2][0];

}

int setCorners(int array[8][3], int cubetofind[6][3][3], int oCube[6][3][3], int iCube[6][3][3]){



    //cubetofind[0][2][0] = array[iCube[0][1][0]][oCube[0][1][0]];  


    cubetofind[0][2][0] = array[iCube[0][2][0]][oCube[0][2][0]];  
    cubetofind[1][0][2] = array[iCube[1][0][2]][oCube[1][0][2]];  
    cubetofind[2][0][0] = array[iCube[2][0][0]][oCube[2][0][0]];  

    cubetofind[0][0][0] = array[iCube[0][0][0]][oCube[0][0][0]];  
    cubetofind[4][0][2] = array[iCube[4][0][2]][oCube[4][0][2]];  
    cubetofind[1][0][0] = array[iCube[1][0][0]][oCube[1][0][0]];  

    cubetofind[0][0][2] = array[iCube[0][0][2]][oCube[0][0][2]];  
    cubetofind[3][0][2] = array[iCube[3][0][2]][oCube[3][0][2]];  
    cubetofind[4][0][0] = array[iCube[4][0][0]][oCube[4][0][0]];  

    cubetofind[0][2][2] = array[iCube[0][2][2]][oCube[0][2][2]];  
    cubetofind[2][0][2] = array[iCube[2][0][2]][oCube[2][0][2]];  
    cubetofind[3][0][0] = array[iCube[3][0][0]][oCube[3][0][0]];  

    cubetofind[1][2][2] = array[iCube[1][2][2]][oCube[1][2][2]];  
    cubetofind[5][0][0] = array[iCube[5][0][0]][oCube[5][0][0]];  
    cubetofind[2][2][0] = array[iCube[2][2][0]][oCube[2][2][0]];  

    cubetofind[1][2][0] = array[iCube[1][2][0]][oCube[1][2][0]];  
    cubetofind[4][2][2] = array[iCube[4][2][2]][oCube[4][2][2]];  
    cubetofind[5][2][0] = array[iCube[5][2][0]][oCube[5][2][0]];  

    cubetofind[3][2][2] = array[iCube[3][2][2]][oCube[3][2][2]];  
    cubetofind[5][2][2] = array[iCube[5][2][2]][oCube[5][2][2]];  
    cubetofind[4][2][0] = array[iCube[4][2][0]][oCube[4][2][0]];  

    cubetofind[2][2][2] = array[iCube[2][2][2]][oCube[2][2][2]];  
    cubetofind[5][0][2] = array[iCube[5][0][2]][oCube[5][0][2]];  
    cubetofind[3][2][0] = array[iCube[3][2][0]][oCube[3][2][0]];  

/*
    cubetofind[0][2][0] = array[0][0];
    cubetofind[1][0][2] = array[0][1];
    cubetofind[2][0][0] = array[0][2];

    cubetofind[0][0][0] = array[1][0];
    cubetofind[4][0][2] = array[1][1];
    cubetofind[1][0][0] = array[1][2];

    cubetofind[0][0][2] = array[2][0];
    cubetofind[3][0][2] = array[2][1];
    cubetofind[4][0][0] = array[2][2];

    cubetofind[0][2][2] = array[3][0];
    cubetofind[2][0][2] = array[3][1];
    cubetofind[3][0][0] = array[3][2];

    cubetofind[1][2][2] = array[4][0];
    cubetofind[5][0][0] = array[4][1];
    cubetofind[2][2][0] = array[4][2];

    cubetofind[1][2][0] = array[5][0];
    cubetofind[4][2][2] = array[5][1];
    cubetofind[5][2][0] = array[5][2];

    cubetofind[3][2][2] = array[6][0];
    cubetofind[5][2][2] = array[6][1];
    cubetofind[4][2][0] = array[6][2];

    cubetofind[2][2][2] = array[7][0];
    cubetofind[5][0][2] = array[7][1];
    cubetofind[3][2][0] = array[7][2]
*/

}

void PlaceToBeEdges(int array[12][2], int cubetofind[6][3][3]){
    array[0][0] = cubetofind[0][1][1];
    array[0][1] = cubetofind[1][1][1];    

    array[1][0] = cubetofind[0][1][1];
    array[1][1] = cubetofind[4][1][1]; 

    array[2][0] = cubetofind[0][1][1];
    array[2][1] = cubetofind[3][1][1]; 

    array[3][0] = cubetofind[0][1][1];
    array[3][1] = cubetofind[2][1][1]; 

    array[4][0] = cubetofind[1][1][1];
    array[4][1] = cubetofind[2][1][1]; 

    array[5][0] = cubetofind[1][1][1];
    array[5][1] = cubetofind[4][1][1]; 

    array[6][0] = cubetofind[3][1][1];
    array[6][1] = cubetofind[4][1][1]; 

    array[7][0] = cubetofind[2][1][1];
    array[7][1] = cubetofind[3][1][1]; 

    array[8][0] = cubetofind[1][1][1];
    array[8][1] = cubetofind[5][1][1];

    array[9][0] = cubetofind[4][1][1];
    array[9][1] = cubetofind[5][1][1];  

    array[10][0] = cubetofind[3][1][1];
    array[10][1] = cubetofind[5][1][1]; 

    array[11][0] = cubetofind[2][1][1];
    array[11][1] = cubetofind[5][1][1]; 

}

#endif
