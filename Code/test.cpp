#include "QuestionCube.hpp"
#include <iostream>
#include <ctime>
#include <cstdlib>
#include <algorithm>

int main()
{
	srand(time(NULL));
	QuestionCube x;
	
	
	x.accessData(1,1,1,1);
	
	
	x.printCubeStd();
	string y=x.makeQuestion();
	
	cout << y;
	
	return 0;
}

