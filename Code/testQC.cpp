#include "QuestionCube.hpp"
#include <iostream>
#include <ctime>
#include <cstdlib>
#include <algorithm>

using namespace std;

int main()
{
	srand(time(NULL));
	QuestionCube x;
	
	int side,row,column,color,numberTurns;
	
	side=0;
	row=0;
	column=0;
	color=1;
	numberTurns=2;
	
	x.accessData(0,0,0,0);
	x.accessData(0,2,2,2);
	x.printCubeColor();
	
	x.rotate(side,numberTurns);
	
	x.printCubeColor();
	
	cout<<x.makeQuestion()<<endl<<x.getColor(0,0,0)<<endl;
	
	return 0;
}

