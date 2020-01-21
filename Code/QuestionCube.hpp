#ifndef A_H
#define A_H
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


#define UP	 	1
#define LEFT 	2
#define FRONT 	3
#define RIGHT	4
#define BACK	5
#define DOWN 	6
#define RANDOM	100


using namespace std;

class QuestionCube{
	
	int n;	
	int data[6][3][3];
	

		//gibt dem 1. Parameter den ServerCube in Form eines 1D Feldes zurück


	public:
		QuestionCube();
	    string printColor(int); //Ausgabe von Farbe
	    void printCubeColor(); 	//Ausgabe des Cubes im Terminal in Farbe
	    void printCubeStd();	//Ausgabe des Cubes im Terminal in Zahlen		
		void stringToCube(string&);	
		void accessData(int, int, int, int);
	
	
		string makeQuestion();			//wandelt einen Cube in einen String um
		
		
			
};
QuestionCube::QuestionCube()
{
	for(int i=0;i<6;i++)
		for(int j=0;j<3;j++)
			for(int k=0;k<3;k++)
				data[i][j][k]=6;
	
}
string QuestionCube::printColor(int field)
{
	
	//			1 white			2 red			3 green			4 blue			5 orange			6 yellow	
    // neuer farbenversuch		
    string RESET = "\033[0m";
	string WHITE = "\033[107m";      /* White */
	string RED = "\033[101m";      /* Red */
	string GREEN = "\033[102m";      /* Green */
	string BLUE = "\e[48;5;21m";      /* Blue */
	string ORANGE = "\e[48;5;208m";      /* Magenta */	 
	string YELLOW = "\033[103m";      /* Yellow */
    string BLACK = "\033[40m"; 
				
	string printcolor;
	switch(field){
        case 6:
			printcolor = BLACK + "  " + RESET;		
			break;
		case 5: 
			printcolor = WHITE + "  " + RESET;		
			break;		
		case 4:
			printcolor = RED + "  " + RESET;					
			break;
		case 3: 
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

void QuestionCube::printCubeColor()
{ 
	for(int i=0;i<3;i++)
	{
		cout<<"       "<<printColor(data[0][i][0])<<printColor(data[0][i][1])<<printColor(data[0][i][2])<<endl;
	}
	for(int i=0;i<3;i++)
	{
		cout<<printColor(data[1][i][0])<<printColor(data[1][i][1])<<printColor(data[1][i][2])<<" ";
		cout<<printColor(data[2][i][0])<<printColor(data[2][i][1])<<printColor(data[2][i][2])<<" ";
		cout<<printColor(data[3][i][0])<<printColor(data[3][i][1])<<printColor(data[3][i][2])<<" ";
		cout<<printColor(data[4][i][0])<<printColor(data[4][i][1])<<printColor(data[4][i][2])<<" "<<endl;
	}
	for(int i=0;i<3;i++)
	{
		cout<<"       "<<printColor(data[5][i][0])<<printColor(data[5][i][1])<<printColor(data[5][i][2])<<endl;
	}	
	cout<<endl<<endl;	
}
void QuestionCube::printCubeStd()
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
void QuestionCube::accessData(int i, int j, int k, int value)
{
	data[i][j][k]=value;
}
	
string QuestionCube::makeQuestion()
{ 
	string returnString="q";
	for(int i=0;i<6;i++)
	{
		for(int j=0;j<3;j++)
		{
			for(int k=0;k<3;k++)
			{				
				returnString+=data[i][j][k]+'0';
			}
		}	
	}
	return returnString;
	
}

void QuestionCube::stringToCube(string& s)
{
	int a[54];
	int x=0;
	for(int i=0;i<54;i++)
    	a[i]=s[i]-'0';
	for(int i=0;i<6;i++)
	{
		for(int j=0;j<3;j++)
		{
			for(int k=0;k<3;k++)
			{				
				data[i][j][k]=a[x];
				x++;
			}
		}	
	}
}




















#endif
