#include "QuestionCube.hpp"
#include <iostream>
#include <ctime>
#include <cstdlib>
#include <algorithm>

int main()
{
	srand(time(NULL));
	QuestionCube x;
	x.printCubeStd();

	string y=x.makeQuestion();
	
	cout << y;
	
	return 0;
}

