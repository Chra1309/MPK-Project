#include <iostream>
#include <ctime>
#include <cstdlib>
#include <algorithm>
#define FRONT 	1
#define BACK 	2
#define LEFT 	3
#define RIGHT	4
#define UP 	5
#define DOWN 	6


using namespace std;

class Cube{
	int colors[6][3][3];
	int n;
	public:
		Cube(int n=0,int r=0)//Konstruktor Cube
		{
			this->n=n;
			//int num[6] = {0, 1, 2, 3, 4, 5};
			int num[6] = {1, 2, 3, 4, 5, 6};
			random_shuffle(num, num + 6);//Farben(Zahlen) zufällig am Cube erzeugen)
		    
			if(n==0) //Erzeugung des 0-Cubes
			{
				for(int i=0;i<6;i++)
					for(int j=0;j<3;j++)
						for(int k=0;k<3;k++)
							colors[i][j][k]=0;
			}else
			{ 
				for(int i=0;i<6;i++)
					for(int j=0;j<3;j++)
						for(int k=0;k<3;k++)
						{
							colors[i][j][k]=num[i]; //Erzeugung eines Cubes mit zufälligen Farben (Zahlen)
						}
						
				
				if(r)
					randomize(r); //Methode zum zufälligen verdrehen des Cubes		rotate(UP,1);//	
			}
		
			printCube();
		}
		void printCube(){ //einfache Ausgabe des Cubes
			for(int i=0;i<3;i++)
			{
				cout<<"    "<<colors[1][i][0]<<colors[1][i][1]<<colors[1][i][2]<<endl;
			}
			for(int i=0;i<3;i++)
			{
				cout<<colors[3][i][0]<<colors[3][i][1]<<colors[3][i][2]<<" ";
				cout<<colors[0][i][0]<<colors[0][i][1]<<colors[0][i][2]<<" ";
				cout<<colors[2][i][0]<<colors[2][i][1]<<colors[2][i][2]<<" ";
				cout<<colors[5][i][0]<<colors[5][i][1]<<colors[5][i][2]<<" "<<endl;
			}
			for(int i=0;i<3;i++)
			{
				cout<<"    "<<colors[4][i][0]<<colors[4][i][1]<<colors[4][i][2]<<endl;
			}	
			cout<<endl<<endl;	
		}
		void randomize(int r) //Methode zum zufälligen verdrehen des Cubes
		{
			int x;
			int y;
			
			for(int i=0;i<r;i++)
			{
				cout<<"x"<<endl;
				
				x=(rand()%6)+1;
				y=(rand()%3)+1;
				rotate(x,y);
			}
		}
		void rotate(int side, int howOften)
		{
			howOften+=4;
			howOften=howOften%4;
			switch (side)
			{
				case FRONT:
					cout<<"FRONT:"<<howOften<<endl;
					for(int i=0;i<howOften;i++)
					{
						shift8by2(colors[0][0][0],colors[0][0][1],colors[0][0][2],colors[0][1][2],colors[0][2][2],colors[0][2][1],colors[0][2][0],colors[0][1][0]);
						shift12by3(colors[1][2][0],colors[1][2][1],colors[1][2][2],colors[2][0][0],colors[2][1][0],colors[2][2][0],
									colors[4][0][2],colors[4][0][1],colors[4][0][0],colors[3][2][2],colors[3][1][2],colors[3][0][2]);
					}
					break;
				case BACK:
					cout<<"BACK:"<<howOften<<endl;
					for(int i=0;i<howOften;i++)
					{
						shift8by2(colors[5][0][0],colors[5][0][1],colors[5][0][2],colors[5][1][2],colors[5][2][2],colors[5][2][1],colors[5][2][0],colors[5][1][0]);
						shift12by3(colors[1][0][2],colors[1][0][1],colors[1][0][0],colors[3][0][0],colors[3][1][0],colors[3][2][0],
									colors[4][2][0],colors[4][2][1],colors[4][2][2],colors[2][2][2],colors[2][1][2],colors[2][0][2]);
					}
					break;
				case LEFT:
					cout<<"LEFT:"<<howOften<<endl;
					for(int i=0;i<howOften;i++)
					{
						shift8by2(colors[3][0][0],colors[3][0][1],colors[3][0][2],colors[3][1][2],colors[3][2][2],colors[3][2][1],colors[3][2][0],colors[3][1][0]);
						shift12by3(colors[1][0][0],colors[1][1][0],colors[1][2][0],colors[0][0][0],colors[0][1][0],colors[0][2][0],
									colors[4][0][0],colors[4][1][0],colors[4][2][0],colors[5][2][2],colors[5][1][2],colors[5][0][2]);
					}
					break;
				case RIGHT:
					cout<<"RIGHT:"<<howOften<<endl;
					for(int i=0;i<howOften;i++)
					{
						shift8by2(colors[2][0][0],colors[2][0][1],colors[2][0][2],colors[2][1][2],colors[2][2][2],colors[2][2][1],colors[2][2][0],colors[2][1][0]);
						shift12by3(colors[1][2][2],colors[1][1][2],colors[1][0][2],colors[5][0][0],colors[5][1][0],colors[5][2][0],
									colors[4][2][2],colors[4][1][2],colors[4][0][2],colors[0][2][2],colors[0][1][2],colors[0][0][2]);
					}
					break;
				case UP:
					cout<<"UP:"<<howOften<<endl;
					for(int i=0;i<howOften;i++)
					{
						shift8by2(colors[1][0][0],colors[1][0][1],colors[1][0][2],colors[1][1][2],colors[1][2][2],colors[1][2][1],colors[1][2][0],colors[1][1][0]);
						shift12by3(colors[5][0][2],colors[5][0][1],colors[5][0][0],colors[2][0][2],colors[2][0][1],colors[2][0][0],
									colors[0][0][2],colors[0][0][1],colors[0][0][0],colors[3][0][2],colors[3][0][1],colors[3][0][0]);
					}
					break;
				case DOWN:
					cout<<"DOWN:"<<howOften<<endl;
					for(int i=0;i<howOften;i++)
					{
						shift8by2(colors[4][0][0],colors[4][0][1],colors[4][0][2],colors[4][1][2],colors[4][2][2],colors[4][2][1],colors[4][2][0],colors[4][1][0]);
						shift12by3(colors[5][2][0],colors[5][2][1],colors[5][2][2],colors[3][2][0],colors[3][2][1],colors[3][2][2],
									colors[0][2][0],colors[0][2][1],colors[0][2][2],colors[2][2][0],colors[2][2][1],colors[2][2][2]);
					}
					break;
				default:
					break;
					
				
					
			}
			printCube();
		}
		void shift8by2(int& a,int& b,int& c,int& d, int& e,int& f,int& g,int& h)
		{		
			int temp;	
			temp=g;
			g=e;
			e=c;
			c=a;
			a=temp;
			
			temp=h;
			h=f;
			f=d;
			d=b;
			b=temp;
		}
		void shift12by3(int& a,int& b,int& c,int& d, int& e,int& f,int& g,int& h,int& i,int& j,int& k,int& l)
		{
			int temp;			
			temp=j;
			j=g;
			g=d;
			d=a;
			a=temp;
			temp=k;
			k=h;
			h=e;
			e=b;
			b=temp;
			temp=l;
			l=i;
			i=f;
			f=c;
			c=temp;
		}
		
};




















