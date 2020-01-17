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

class ServerCube{
	int data[6][3][3];
	int n;	
	string moves;
	int lookup[6];
	
	///////////////Methoden Christoph (Bei Bedarf public machen, war ma zu blöd jetz und es sollt net alles default mäßig public sein...)
	
	void shift8by2n(int&, int&, int&, int&, int&, int&, int& ,int& ,int&);							//Methode zum Rotieren einer Fläche
	void shift12by3n(int&, int&, int&, int&, int&, int&, int& ,int& ,int&, int&, int&, int&, int&); //Methode zum Rotieren einer der Felder um eine Fläche

	void randomize(); 		//Methode zum zufälligen verdrehen des ServerCubes
		//Methode zum Rotieren des ServerCubes 1. Param: Seite (1-6), 2. Param: beliebig (wird zu 1-3 umgewandelt
	void toArray(int*);		//gibt dem 1. Parameter den ServerCube in Form eines 1D Feldes zurück

	void getCorner(int&,int&,int&,int&,int&,int&,int&);
	void getEdge(int&,int&,int&,int&,int&);

	public:
		ServerCube(int);	//Konstruktor Cube
		void testSolve();
	    string printColor(int); //Ausgabe von Farbe
	    void printCubeColor(); 	//Ausgabe des Cubes im Terminal in Farbe
	    void printCubeStd();	//Ausgabe des Cubes im Terminal in Zahlen	
		void rotate(int, int);	
		void stringToCube(string&);		//wandelt string in Cube um    
		void compareToQuestion(ServerCube&,int*);	//
	
	
		friend string makeCubeQuestion(ServerCube&);	//erstellt eine Cube Question
		friend string cubeToString(ServerCube&);		//wandelt einen Cube in einen String um
		
		
			
};
ServerCube::ServerCube(int n)
{
	moves="";
	for(int i=0;i<sizeof(lookup);i++) 
		lookup[i]=0;
	this->n=n;
	//int num[6] = {0, 1, 2, 3, 4, 5};
	int num[6] = {0, 1, 2, 3, 4, 5};
	
	//random_shuffle(num, num + 6);//Farben(Zahlen) zufällig am Cube erzeugen)
    
	if(n==0) //Erzeugung des 0-Cubes
	{
		for(int i=0;i<6;i++)
			for(int j=0;j<3;j++)
				for(int k=0;k<3;k++)
					data[i][j][k]=6;
	}else
	{ 
		for(int i=0;i<6;i++)
			for(int j=0;j<3;j++)
				for(int k=0;k<3;k++)
				{
					data[i][j][k]=num[i]; //Erzeugung eines Cubes mit zufälligen Farben (Zahlen)
					//data[i][j][k]=i; //Erzeugung Standardcube
				}
					
			
		if(n)
				randomize(); //Methode zum zufälligen verdrehen des Cubes		rotate(UP,1);//	
	}
}
string ServerCube::printColor(int field)
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
        case 8:
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

void ServerCube::printCubeColor()
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
void ServerCube::printCubeStd()
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
void ServerCube::randomize()
{
	int x=(rand()%6)+1;
	int xOld=0;
	int y;
	
	for(int i=0;i<RANDOM;i++)
	{
		while(x==xOld)
			x=(rand()%6)+1;
		xOld=x;
		y=(rand()%3)+1;
		rotate(x,y);
	}
}
void ServerCube::rotate(int side,int howOften)
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
void ServerCube::shift8by2n(int& a,int& b,int& c,int& d, int& e,int& f,int& g,int& h,int& n)
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
void ServerCube::shift12by3n(int& a,int& b,int& c,int& d, int& e,int& f,int& g,int& h,int& i,int& j,int& k,int& l,int& n)
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

string cubeToString(ServerCube& cube)
{ 
	string returnString="";
	int* a=new int[54];
	cube.toArray(a);	
	for(int i=0;i<54;i++)
    	returnString+=a[i]+'0';
  	
  	delete a;
	return returnString;
	
}
void ServerCube::toArray(int* a)
{
	int x=0;
	for(int i=0;i<6;i++)
	{
		for(int j=0;j<3;j++)
		{
			for(int k=0;k<3;k++)
			{				
				a[x]=data[i][j][k];
				x++;
			}
		}	
	}
}
void ServerCube::stringToCube(string& s)
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
void ServerCube::compareToQuestion(ServerCube& qc,int* answer)
{
	answerB=0; answerS=0; answerW=0;
		
		
	for(int i=0;i<6;i++)
	{
		for(int j=0;j<3;j++)
		{
			for(int k=0;k<3;k++)
			{
				if(qc.data[i][j][k]!=6)
				{	
					if(qc.data[i][j][k]==data[i][j][k])
					{
						if(qc.data[i][j][k]==data[i][1][1])
						{
							if((j+k)%2==0)
							{
								int c1,c2,s1,s2;
								getCorner(i,j,k,c1,c2,s1,s2);
								
								if(c1==data[s1][1][1]&&c2==data[s2][1][1])
								{
									answer[2]++;
								}else{
									answer[1]++;
								}
								
							}else
							{
								int c1,s1;
								
								getEdge(i,j,k,c1,s1);
								
								if(c1==data[s1][1][1])
								{
									answer[2]++;
								}else{
									answer[1]++;
								}
							}	
						}else
						{
							answer[0]++;
						}
					}else
					{
						answer[0]++;
					}
				}
			}
		}	
	}
}


void ServerCube::getEdge(int& a,int& b,int& c,int& c1,int& s1)
{
	if(a==2&&b==0&&c==1) {c1=data[0][2][1]; s1=0;}
	if(a==2&&b==1&&c==0) {c1=data[1][1][2]; s1=1;}
	if(a==2&&b==1&&c==2) {c1=data[3][1][0]; s1=3;}
	if(a==2&&b==2&&c==1) {c1=data[5][0][1]; s1=5;}
	
	if(a==0&&b==0&&c==1) {c1=data[4][0][1]; s1=4;}
	if(a==0&&b==1&&c==0) {c1=data[1][0][1]; s1=1;}
	if(a==0&&b==1&&c==2) {c1=data[3][0][1]; s1=3;}
	if(a==0&&b==2&&c==1) {c1=data[2][0][1]; s1=2;}
	
	if(a==3&&b==0&&c==1) {c1=data[0][1][2]; s1=0;}
	if(a==3&&b==1&&c==0) {c1=data[2][1][2]; s1=2;}
	if(a==3&&b==1&&c==2) {c1=data[4][1][0]; s1=4;}
	if(a==3&&b==2&&c==1) {c1=data[5][1][2]; s1=5;}
		
	if(a==1&&b==0&&c==1) {c1=data[0][1][0]; s1=0;}
	if(a==1&&b==1&&c==0) {c1=data[4][1][2]; s1=4;}
	if(a==1&&b==1&&c==2) {c1=data[2][1][0]; s1=2;}
	if(a==1&&b==2&&c==1) {c1=data[5][1][0]; s1=5;}
	
	if(a==5&&b==0&&c==1) {c1=data[2][2][1]; s1=2;}
	if(a==5&&b==1&&c==0) {c1=data[1][2][1]; s1=1;}
	if(a==5&&b==1&&c==2) {c1=data[3][2][1]; s1=3;}
	if(a==5&&b==2&&c==1) {c1=data[4][2][1]; s1=4;}
	
	if(a==4&&b==0&&c==1) {c1=data[0][0][1]; s1=0;}
	if(a==4&&b==1&&c==0) {c1=data[3][1][2]; s1=3;}
	if(a==4&&b==1&&c==2) {c1=data[1][1][0]; s1=1;}
	if(a==4&&b==2&&c==1) {c1=data[5][2][1]; s1=5;}
}

void ServerCube::getCorner(int& a,int& b,int& c,int& c1,int& c2,int& s1, int& s2)
{
	if(a==2&&b==0&&c==0) {c1=data[0][2][0]; c2=data[1][0][2]; s1=0; s2=1;}
	if(a==2&&b==0&&c==2) {c1=data[0][2][2]; c2=data[3][0][0]; s1=0; s2=3;}
	if(a==2&&b==2&&c==0) {c1=data[5][0][0]; c2=data[1][2][2]; s1=5; s2=1;}
	if(a==2&&b==2&&c==2) {c1=data[5][0][2]; c2=data[3][2][0]; s1=5; s2=3;}
	
	if(a==0&&b==0&&c==0) {c1=data[4][0][2]; c2=data[1][0][0]; s1=4; s2=1;}
	if(a==0&&b==0&&c==2) {c1=data[4][0][0]; c2=data[3][0][2]; s1=4; s2=3;}
	if(a==0&&b==2&&c==0) {c1=data[2][0][0]; c2=data[1][0][2]; s1=2; s2=1;}
	if(a==0&&b==2&&c==2) {c1=data[2][0][2]; c2=data[3][0][0]; s1=2; s2=3;}
	
	if(a==3&&b==0&&c==0) {c1=data[0][2][2]; c2=data[2][0][2]; s1=0; s2=2;}
	if(a==3&&b==0&&c==2) {c1=data[4][0][0]; c2=data[0][0][2]; s1=4; s2=0;}
	if(a==3&&b==2&&c==0) {c1=data[5][0][2]; c2=data[2][2][2]; s1=5; s2=0;}
	if(a==3&&b==2&&c==2) {c1=data[4][2][0]; c2=data[5][2][2]; s1=4; s2=5;}
	
	if(a==1&&b==0&&c==0) {c1=data[0][0][0]; c2=data[4][0][2]; s1=0; s2=4;}
	if(a==1&&b==0&&c==2) {c1=data[2][0][0]; c2=data[0][2][0]; s1=2; s2=0;}
	if(a==1&&b==2&&c==0) {c1=data[5][2][0]; c2=data[4][2][2]; s1=5; s2=4;}
	if(a==1&&b==2&&c==2) {c1=data[2][2][0]; c2=data[5][0][0]; s1=2; s2=5;}
	
	if(a==5&&b==0&&c==0) {c1=data[2][2][0]; c2=data[1][2][2]; s1=2; s2=1;}
	if(a==5&&b==0&&c==2) {c1=data[2][2][2]; c2=data[3][2][0]; s1=2; s2=3;}
	if(a==5&&b==2&&c==0) {c1=data[4][2][2]; c2=data[1][2][0]; s1=4; s2=1;}
	if(a==5&&b==2&&c==2) {c1=data[4][2][0]; c2=data[3][2][2]; s1=4; s2=3;}
	
	if(a==4&&b==0&&c==0) {c1=data[0][0][2]; c2=data[3][0][2]; s1=0; s2=3;}
	if(a==4&&b==0&&c==2) {c1=data[0][0][0]; c2=data[1][0][0]; s1=0; s2=1;}
	if(a==4&&b==2&&c==0) {c1=data[5][2][2]; c2=data[3][2][2]; s1=5; s2=3;}
	if(a==4&&b==2&&c==2) {c1=data[5][2][0]; c2=data[1][2][0]; s1=5; s2=1;}
	

}























#endif
