#include <iostream>
#include <ctime>
#include <cstdlib>
#include <algorithm>
#define FRONT 	1
#define BACK 	2
#define LEFT 	3
#define RIGHT	4
#define UP 		5
#define DOWN 	6

using namespace std;

class WeightedCube{
	float c1[6][3][3];
	float c2[6][3][3];
	float c3[6][3][3];
	float c4[6][3][3];
	float c5[6][3][3];
	float c6[6][3][3];
	
	void shift8by2n(float a[6],float b[6],float c[6],float d[6], float e[6],float f[6],float g[6],float h[6],int& n);							//Methode zum Rotieren einer Fläche
	void shift12by3n(float a[6],float b[6],float c[6],float d[6], float e[6],float f[6],float g[6],float h[6],float i[6],float j[6],float k[6],float l[6],int& n); //Methode zum Rotieren einer der Felder um eine Fläche
	public:
		WeightedCube();	
		void rotate(int,int);
		void rotateAll(int,int);
};

WeightedCube::WeightedCube()
{
	for(int i=0;i<6;i++)
		for(int j=0;j<3;j++)
			for(int k=0;k<3;k++)
			{
				c1[i][j][k]=(float)1/6;
				c2[i][j][k]=(float)1/6;
				c3[i][j][k]=(float)1/6;
				c4[i][j][k]=(float)1/6;
				c5[i][j][k]=(float)1/6;
				c6[i][j][k]=(float)1/6;
			}
					
}

void WeightedCube::rotateAll(int side,int howOften)
{
}

void WeightedCube::rotate(int side,int howOften)
{
	howOften+=4;
	howOften=howOften%4;
	switch (side)
	{
		case FRONT:
			//cout<<"FRONT:"<<howOften<<endl;
			shift8by2n(colors[0][0][0],colors[0][0][1],colors[0][0][2],colors[0][1][2],colors[0][2][2],colors[0][2][1],colors[0][2][0],colors[0][1][0],howOften);
			shift12by3n(colors[1][2][0],colors[1][2][1],colors[1][2][2],colors[2][0][0],colors[2][1][0],colors[2][2][0],
						colors[4][0][2],colors[4][0][1],colors[4][0][0],colors[3][2][2],colors[3][1][2],colors[3][0][2],howOften);
			break;
		case BACK:
			//cout<<"BACK:"<<howOften<<endl;
			shift8by2n(colors[5][0][0],colors[5][0][1],colors[5][0][2],colors[5][1][2],colors[5][2][2],colors[5][2][1],colors[5][2][0],colors[5][1][0],howOften);
			shift12by3n(colors[1][0][2],colors[1][0][1],colors[1][0][0],colors[3][0][0],colors[3][1][0],colors[3][2][0],
						colors[4][2][0],colors[4][2][1],colors[4][2][2],colors[2][2][2],colors[2][1][2],colors[2][0][2],howOften);
			break;
		case LEFT:
			//cout<<"LEFT:"<<howOften<<endl;
			shift8by2n(colors[3][0][0],colors[3][0][1],colors[3][0][2],colors[3][1][2],colors[3][2][2],colors[3][2][1],colors[3][2][0],colors[3][1][0],howOften);
			shift12by3n(colors[1][0][0],colors[1][1][0],colors[1][2][0],colors[0][0][0],colors[0][1][0],colors[0][2][0],
						colors[4][0][0],colors[4][1][0],colors[4][2][0],colors[5][2][2],colors[5][1][2],colors[5][0][2],howOften);
			break;
		case RIGHT:
			//cout<<"RIGHT:"<<howOften<<endl;
			shift8by2n(colors[2][0][0],colors[2][0][1],colors[2][0][2],colors[2][1][2],colors[2][2][2],colors[2][2][1],colors[2][2][0],colors[2][1][0],howOften);
			shift12by3n(colors[1][2][2],colors[1][1][2],colors[1][0][2],colors[5][0][0],colors[5][1][0],colors[5][2][0],
						colors[4][2][2],colors[4][1][2],colors[4][0][2],colors[0][2][2],colors[0][1][2],colors[0][0][2],howOften);
			break;
		case UP:
			//cout<<"UP:"<<howOften<<endl;
			shift8by2n(colors[1][0][0],colors[1][0][1],colors[1][0][2],colors[1][1][2],colors[1][2][2],colors[1][2][1],colors[1][2][0],colors[1][1][0],howOften);
			shift12by3n(colors[5][0][2],colors[5][0][1],colors[5][0][0],colors[2][0][2],colors[2][0][1],colors[2][0][0],
						colors[0][0][2],colors[0][0][1],colors[0][0][0],colors[3][0][2],colors[3][0][1],colors[3][0][0],howOften);
			break;
		case DOWN:
			//cout<<"DOWN:"<<howOften<<endl;
			shift8by2n(colors[4][0][0],colors[4][0][1],colors[4][0][2],colors[4][1][2],colors[4][2][2],colors[4][2][1],colors[4][2][0],colors[4][1][0],howOften);
			shift12by3n(colors[5][2][0],colors[5][2][1],colors[5][2][2],colors[3][2][0],colors[3][2][1],colors[3][2][2],
						colors[0][2][0],colors[0][2][1],colors[0][2][2],colors[2][2][0],colors[2][2][1],colors[2][2][2],howOften);
			break;
		default:
			break;					
	}
	//printCubeStd();
}
void WeightedCube::shift8by2n(float a[6],float b[6],float c[6],float d[6], float e[6],float f[6],float g[6],float h[6],int& n)
{				
	float temp[6];
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
void WeightedCube::shift12by3n(float a[6],float b[6],float c[6],float d[6], float e[6],float f[6],float g[6],float h[6],float i[6],float j[6],float k[6],float l[6],int& n)
{
	float temp[6];	
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















