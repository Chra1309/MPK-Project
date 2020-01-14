#include "ServerCube.hpp"
#include <iostream>
#include <ctime>
#include <cstdlib>
#include <algorithm>

int main()
{
	srand(time(NULL));
	ServerCube x(0);
	x.printCubeStd();
	
	//x.testSolve();
	return 0;
	
}

