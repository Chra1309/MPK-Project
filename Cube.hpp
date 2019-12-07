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
#define RANDOM	100


using namespace std;

class Cube{
	int colors[6][3][3];
	int n;
	void shift8by2n(int&, int&, int&, int&, int&, int&, int& ,int& ,int&);							//Methode zum Rotieren einer Fläche
	void shift12by3n(int&, int&, int&, int&, int&, int&, int& ,int& ,int&, int&, int&, int&, int&); //Methode zum Rotieren einer der Felder um eine Fläche
	public:
		Cube(int);				//Konstruktor Cube
		string printColor(int); //Ausgabe von Farbe
		void printCubeColor(); 	//Ausgabe des Cubes im Terminal in Farbe
		void printCubeStd();	//Ausgabe des Cubes im Terminal in Zahlen
		void randomize(); 		//Methode zum zufälligen verdrehen des Cubes
		void rotate(int, int);	//Methode zum Rotieren des Cubes 1. Param: Seite (1-6), 2. Param: beliebig (wird zu 1-3 umgewandelt
		void ToArray(int*);		//gibt dem 1. Parameter den Cube in Form eines 1D Feldes zurück
		friend int* sendCubeQuestion(Cube&);	//sendet eine Cube Question TODO!!!!!!!!!!
		friend string CubeToString(Cube&);		//wandelt einen Cube in einen String um
		friend Cube StringToCube(string);		//TODO!!!!!!!!!!
};

Cube::Cube(int n=0)
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
					
			
		if(n)
				randomize(); //Methode zum zufälligen verdrehen des Cubes		rotate(UP,1);//	
	}
}
string Cube::printColor(int field)
{
	
	//			1 white			2 red			3 green			4 blue			5 orange			6 yellow			
	string RESET = "\033[0m";
	string WHITE = "\033[107m";      /* White */
	string RED = "\033[101m";      /* Red */
	string GREEN = "\033[102m";      /* Green */
	string BLUE = "\033[104m";      /* Blue */
	string ORANGE = "\033[43m";      /* Magenta */			
	string YELLOW = "\033[103m";      /* Yellow */
				
	string printcolor;
	switch(field){
		case 1:
			printcolor = WHITE + "  " + RESET;		
			break;		
		case 2:
			printcolor = RED + "  " + RESET;					
			break;
		case 3: 
			printcolor = GREEN + "  " + RESET;					
			break;
		case 4:
			printcolor = BLUE + "  " + RESET;									
			break;
		case 5: 				
			printcolor = ORANGE + "  " + RESET;					
			break;			
		case 6: 
			printcolor = YELLOW + "  " + RESET;								
			break;				
	}
	return printcolor;
}
void Cube::printCubeColor()
{ 
	for(int i=0;i<3;i++)
	{
		cout<<"       "<<printColor(colors[1][i][0])<<printColor(colors[1][i][1])<<printColor(colors[1][i][2])<<endl;
	}
	for(int i=0;i<3;i++)
	{
		cout<<printColor(colors[3][i][0])<<printColor(colors[3][i][1])<<printColor(colors[3][i][2])<<" ";
		cout<<printColor(colors[0][i][0])<<printColor(colors[0][i][1])<<printColor(colors[0][i][2])<<" ";
		cout<<printColor(colors[2][i][0])<<printColor(colors[2][i][1])<<printColor(colors[2][i][2])<<" ";
		cout<<printColor(colors[5][i][0])<<printColor(colors[5][i][1])<<printColor(colors[5][i][2])<<" "<<endl;
	}
	for(int i=0;i<3;i++)
	{
		cout<<"       "<<printColor(colors[4][i][0])<<printColor(colors[4][i][1])<<printColor(colors[4][i][2])<<endl;
	}	
	cout<<endl<<endl;	
}
void Cube::printCubeStd()
{
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
void Cube::randomize()
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
void Cube::rotate(int side,int howOften)
{
	howOften+=4;
	howOften=howOften%4;
	switch (side)
	{
		case FRONT:
			cout<<"FRONT:"<<howOften<<endl;
			shift8by2n(colors[0][0][0],colors[0][0][1],colors[0][0][2],colors[0][1][2],colors[0][2][2],colors[0][2][1],colors[0][2][0],colors[0][1][0],howOften);
			shift12by3n(colors[1][2][0],colors[1][2][1],colors[1][2][2],colors[2][0][0],colors[2][1][0],colors[2][2][0],
						colors[4][0][2],colors[4][0][1],colors[4][0][0],colors[3][2][2],colors[3][1][2],colors[3][0][2],howOften);
			break;
		case BACK:
			cout<<"BACK:"<<howOften<<endl;
			shift8by2n(colors[5][0][0],colors[5][0][1],colors[5][0][2],colors[5][1][2],colors[5][2][2],colors[5][2][1],colors[5][2][0],colors[5][1][0],howOften);
			shift12by3n(colors[1][0][2],colors[1][0][1],colors[1][0][0],colors[3][0][0],colors[3][1][0],colors[3][2][0],
						colors[4][2][0],colors[4][2][1],colors[4][2][2],colors[2][2][2],colors[2][1][2],colors[2][0][2],howOften);
			break;
		case LEFT:
			cout<<"LEFT:"<<howOften<<endl;
			shift8by2n(colors[3][0][0],colors[3][0][1],colors[3][0][2],colors[3][1][2],colors[3][2][2],colors[3][2][1],colors[3][2][0],colors[3][1][0],howOften);
			shift12by3n(colors[1][0][0],colors[1][1][0],colors[1][2][0],colors[0][0][0],colors[0][1][0],colors[0][2][0],
						colors[4][0][0],colors[4][1][0],colors[4][2][0],colors[5][2][2],colors[5][1][2],colors[5][0][2],howOften);
			break;
		case RIGHT:
			cout<<"RIGHT:"<<howOften<<endl;
			shift8by2n(colors[2][0][0],colors[2][0][1],colors[2][0][2],colors[2][1][2],colors[2][2][2],colors[2][2][1],colors[2][2][0],colors[2][1][0],howOften);
			shift12by3n(colors[1][2][2],colors[1][1][2],colors[1][0][2],colors[5][0][0],colors[5][1][0],colors[5][2][0],
						colors[4][2][2],colors[4][1][2],colors[4][0][2],colors[0][2][2],colors[0][1][2],colors[0][0][2],howOften);
			break;
		case UP:
			cout<<"UP:"<<howOften<<endl;
			shift8by2n(colors[1][0][0],colors[1][0][1],colors[1][0][2],colors[1][1][2],colors[1][2][2],colors[1][2][1],colors[1][2][0],colors[1][1][0],howOften);
			shift12by3n(colors[5][0][2],colors[5][0][1],colors[5][0][0],colors[2][0][2],colors[2][0][1],colors[2][0][0],
						colors[0][0][2],colors[0][0][1],colors[0][0][0],colors[3][0][2],colors[3][0][1],colors[3][0][0],howOften);
			break;
		case DOWN:
			cout<<"DOWN:"<<howOften<<endl;
			shift8by2n(colors[4][0][0],colors[4][0][1],colors[4][0][2],colors[4][1][2],colors[4][2][2],colors[4][2][1],colors[4][2][0],colors[4][1][0],howOften);
			shift12by3n(colors[5][2][0],colors[5][2][1],colors[5][2][2],colors[3][2][0],colors[3][2][1],colors[3][2][2],
						colors[0][2][0],colors[0][2][1],colors[0][2][2],colors[2][2][0],colors[2][2][1],colors[2][2][2],howOften);
			break;
		default:
			break;					
	}
	printCubeStd();
}
void Cube::shift8by2n(int& a,int& b,int& c,int& d, int& e,int& f,int& g,int& h,int& n)
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
void Cube::shift12by3n(int& a,int& b,int& c,int& d, int& e,int& f,int& g,int& h,int& i,int& j,int& k,int& l,int& n)
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
int* sendCubeQuestion(Cube& sendCube)
{
	string sendData=CubeToString(sendCube);
	//Manuel bitte Send-Routine einbauen
	return 0;
}
string CubeToString(Cube& cube)
{ 
	string returnString="";
	int* a=new int[54];
	cube.ToArray(a);	
	for(int i=0;i<54;i++)
    	returnString+=a[i]+'0';
  	
  	delete a;
	return returnString;
	
}
void Cube::ToArray(int* a)
{
	int x=0;
	for(int i=0;i<6;i++)
	{
		for(int j=0;j<3;j++)
		{
			for(int k=0;k<3;k++)
			{				
				a[x]=colors[i][j][k];
				x++;
			}
		}	
	}
}
Cube StringToCube(string s)
{
	Cube c(0);
	
	
	
	return c;
}
















