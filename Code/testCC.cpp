#include "ClientCube.hpp"
#include "cubeoperations.hpp"
#include <iostream>
#include <ctime>
#include <cstdlib>
#include <algorithm>

using namespace std;

int main()
{
	srand(time(NULL));
	ClientCube x(1);
	array[6][3][3];
	
	x.cubeToArray(array);
	
	printCubeColor(array);
	
	x.testSolve();
	
	x.cubeToArray(array);
	
	printCubeColor(array);
	
	
	return 0;
}

