#include "Cube.hpp"
#include <iostream>
#include <ctime>
#include <cstdlib>
#include <algorithm>

int main()
{
	srand(time(NULL));
	Cube x(1); //macht der Client
	Cube y(0); //macht der Server
	string temp=CubeToString(x); //macht der Client
	//Client Schickt String
	y=StringToCube(temp);//macht der Server
	cout<<"print Cube X"<<endl;//macht der Client
	x.printCubeStd(); //macht der Client
	cout<<"print Cube Y"<<endl; //macht der Server
	y.printCubeStd(); //macht der Server
	//cout<<y;
	

	return 0;
}

