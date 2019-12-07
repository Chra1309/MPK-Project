#include "Cube.hpp"
#include <iostream>
#include <ctime>
#include <cstdlib>
#include <algorithm>

int main()
{
	srand(time(NULL));
	Cube x(1);
	string y=CubeToString(x);
	cout<<y;
	
	
	
	
	
	
	
	
	return 0;
}

