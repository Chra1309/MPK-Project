#include "Cube.hpp"
#include <iostream>
#include <ctime>
#include <cstdlib>
#include <algorithm>

int main()
{
	srand(time(NULL));
	Cube x(1);
	Cube y(0);
	string temp=CubeToString(x);
	
	y=StringToCube(temp);
	cout<<"print Cube X"<<endl;
	x.printCubeStd();
	cout<<"print Cube Y"<<endl;
	y.printCubeStd();
	//cout<<y;
	
	
	
	
	
	
	
	
	return 0;
}

