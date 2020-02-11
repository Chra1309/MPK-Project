#ifndef QC
#define QC

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
#include "cubeoperations.hpp"


#define UP	 	0
#define LEFT 	1
#define FRONT 	2
#define RIGHT	3
#define BACK	4
#define DOWN 	5
#define RANDOM	100


using namespace std;

class QuestionCube{
	
	int n;	
	int data[6][3][3];
	
	void shift8by2n(int&, int&, int&, int&, int&, int&, int& ,int& ,int&);							//Methode zum Rotieren einer Fläche
	void shift12by3n(int&, int&, int&, int&, int&, int&, int& ,int& ,int&, int&, int&, int&, int&); //Methode zum Rotieren einer der Felder um eine Fläche


		//gibt dem 1. Parameter den ServerCube in Form eines 1D Feldes zurück


	public:
		QuestionCube();	
		void stringToCube(string&);	
		string cubeToString();
		void cubeToArray(int array[6][3][3]);
		void accessData(int, int, int, int);
		void rotate(int, int);	//Methode zum Rotieren des Cubes 1. Param: Seite (1-6), 2. Param: beliebig (wird zu 1-3 umgewandelt
		int getColor(int, int, int);
		void print();
	
	
		string makeQuestion();			//wandelt einen Cube in einen String um
		
		
			
};
QuestionCube::QuestionCube()
{
	for(int i=0;i<6;i++)
		for(int j=0;j<3;j++)
			for(int k=0;k<3;k++)
				data[i][j][k]=6;
	
}
void QuestionCube::print()
{
	printCubeColor(data);
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

string QuestionCube::cubeToString()
{ 
	string returnString="";	
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

void QuestionCube::cubeToArray(int array[6][3][3])
{
	for(int i=0;i<6;i++)
	{
		for(int j=0;j<3;j++)
		{
			for(int k=0;k<3;k++)
			{				
				array[i][j][k]=data[i][j][k];
			}
		}	
	}
}
void QuestionCube::rotate(int side,int howOften)
{

	howOften+=4;
	howOften=howOften%4;
	
	switch (side)
	{
		case FRONT:
			//cout<<"FRONT:"<<howOften<<endl;
			shift8by2n(data[2][0][0],data[2][0][1],data[2][0][2],data[2][1][2],data[2][2][2],data[2][2][1],data[2][2][0],data[2][1][0],howOften);
			shift12by3n(data[0][2][0],data[0][2][1],data[0][2][2],data[3][0][0],data[3][1][0],data[3][2][0],
						data[5][0][2],data[5][0][1],data[5][0][0],data[1][2][2],data[1][1][2],data[1][0][2],howOften);
			break;
		case BACK:
			//cout<<"BACK:"<<howOften<<endl;
			shift8by2n(data[4][0][0],data[4][0][1],data[4][0][2],data[4][1][2],data[4][2][2],data[4][2][1],data[4][2][0],data[4][1][0],howOften);
			shift12by3n(data[0][0][2],data[0][0][1],data[0][0][0],data[1][0][0],data[1][1][0],data[1][2][0],
						data[5][2][0],data[5][2][1],data[5][2][2],data[3][2][2],data[3][1][2],data[3][0][2],howOften);
			break;
		case LEFT:
			//cout<<"LEFT:"<<howOften<<endl;
			shift8by2n(data[1][0][0],data[1][0][1],data[1][0][2],data[1][1][2],data[1][2][2],data[1][2][1],data[1][2][0],data[1][1][0],howOften);
			shift12by3n(data[0][0][0],data[0][1][0],data[0][2][0],data[2][0][0],data[2][1][0],data[2][2][0],
						data[5][0][0],data[5][1][0],data[5][2][0],data[4][2][2],data[4][1][2],data[4][0][2],howOften);
			break;
		case RIGHT:
			//cout<<"RIGHT:"<<howOften<<endl;
			shift8by2n(data[3][0][0],data[3][0][1],data[3][0][2],data[3][1][2],data[3][2][2],data[3][2][1],data[3][2][0],data[3][1][0],howOften);
			shift12by3n(data[0][2][2],data[0][1][2],data[0][0][2],data[4][0][0],data[4][1][0],data[4][2][0],
						data[5][2][2],data[5][1][2],data[5][0][2],data[2][2][2],data[2][1][2],data[2][0][2],howOften);
			break;
		case UP:
			//cout<<"UP:"<<howOften<<endl;
			shift8by2n(data[0][0][0],data[0][0][1],data[0][0][2],data[0][1][2],data[0][2][2],data[0][2][1],data[0][2][0],data[0][1][0],howOften);
			shift12by3n(data[4][0][2],data[4][0][1],data[4][0][0],data[3][0][2],data[3][0][1],data[3][0][0],
						data[2][0][2],data[2][0][1],data[2][0][0],data[1][0][2],data[1][0][1],data[1][0][0],howOften);
			break;
		case DOWN:
			//cout<<"DOWN:"<<howOften<<endl;
			shift8by2n(data[5][0][0],data[5][0][1],data[5][0][2],data[5][1][2],data[5][2][2],data[5][2][1],data[5][2][0],data[5][1][0],howOften);
			shift12by3n(data[4][2][0],data[4][2][1],data[4][2][2],data[1][2][0],data[1][2][1],data[1][2][2],
						data[2][2][0],data[2][2][1],data[2][2][2],data[3][2][0],data[3][2][1],data[3][2][2],howOften);
			break;
		default:
			break;					
	}
	//printCubeStd();
}

void QuestionCube::shift8by2n(int& a,int& b,int& c,int& d, int& e,int& f,int& g,int& h,int& n)
{				
	int temp;
	switch(n)
	{
		case 1:
			temp=g; g=e; e=c; c=a; a=temp;
			temp=h; h=f; f=d; d=b; b=temp;
			break;
		case 2:	
			temp=a;	a=e; e=temp;
			temp=b;	b=f; f=temp;
			temp=c;	c=g; g=temp;
			temp=d;	d=h; h=temp;					
			break;
		case 3:
			temp=a; a=c; c=e; e=g; g=temp;
			temp=b; b=d; d=f; f=h; h=temp;
			break;
		default:
			break;
	}
}
void QuestionCube::shift12by3n(int& a,int& b,int& c,int& d, int& e,int& f,int& g,int& h,int& i,int& j,int& k,int& l,int& n)
{
	int temp;	
	switch(n)
	{
		case 1:
			temp=j; j=g; g=d; d=a; a=temp;
			temp=k; k=h; h=e; e=b; b=temp;
			temp=l; l=i; i=f; f=c; c=temp;
			break;
		case 2:
			temp=a; a=g; g=temp;
			temp=b; b=h; h=temp;
			temp=c; c=i; i=temp;
			temp=d; d=j; j=temp;
			temp=e; e=k; k=temp;
			temp=f; f=l; l=temp;
			break;
		case 3:
			temp=a; a=d; d=g; g=j; j=temp;
			temp=b; b=e; e=h; h=k; k=temp;
			temp=c; c=f; f=i; i=l; l=temp;
			break;
		default:
			break;
	}		
}

int QuestionCube::getColor(int i, int j,int k)
{
	return data[i][j][k];
}
















#endif
