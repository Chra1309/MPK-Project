#include "ClientCube.hpp"
#include <iostream>
#include <ctime>
#include <cstdlib>
#include <algorithm>

using namespace std;

int main()
{
	srand(time(NULL));
	ClientCube x(1);
	
	
	x.printCubeColor();
	
	x.testSolve();
	
	x.printCubeColor();
	
	
	return 0;
}

