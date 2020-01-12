#include "Cube.hpp"
#include <iostream>
#include <ctime>
#include <cstdlib>
#include <algorithm>

int main()
{
	srand(time(NULL));
	Cube x(1);
	
	x.testSolve();
	return 0;
	
}

