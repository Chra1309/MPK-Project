#include "ServerCube.hpp"
#include <iostream>
#include <ctime>
#include <cstdlib>
#include <algorithm>

using namespace std;

int main()
{
	srand(time(NULL));
	ServerCube x(1),y;
	
	
	
	
	
	x.printCubeColor();
	
	y.stringToCube("006660000116661111222266622366633333444444466556665555");
	
	y.printCubeColor();
	
	int a[3];
	
	x.compareToQuestion(y,a);
	for(int i=0;i<3;i++)
	{
		cout<<a[i]<<" ";
	}
	cout<<endl;
	return 0;
}

