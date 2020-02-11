#ifndef MASTERHEADER_HPP
#define MASTERHEADER_HPP

using namespace std;

struct corner
{
	int field1;
	int field2;
	int field3;
};

struct edge
{
	int field1;
	int field2;
};

struct middle
{
	int field1;
	int field2;
};

int cube[6][3][3] = {
	{ { 6, 6, 6 }, { 6, 6, 6 }, { 6, 6, 6 } },   //yellow side
	{ { 6, 6, 6 }, { 6, 6, 6 }, { 6, 6, 6 } },   //orange side
	{ { 6, 6, 6 }, { 6, 6, 6 }, { 6, 6, 6 } },   //blue side
	{ { 6, 6, 6 }, { 6, 6, 6 }, { 6, 6, 6 } },   //red side
	{ { 6, 6, 6 }, { 6, 6, 6 }, { 6, 6, 6 } },   //green side
	{ { 6, 6, 6 }, { 6, 6, 6 }, { 6, 6, 6 } } }; //white side

int orientationCube[6][3][3] = {
	{ { 0, 0, 0 }, { 0, 0, 0 }, { 0, 0, 0 } },   //yellow side
	{ { 2, 1, 1 }, { 1, 1, 0 }, { 1, 1, 2 } },   //orange side
	{ { 2, 1, 1 }, { 1, 2, 0 }, { 1, 1, 2 } },   //blue side
	{ { 2, 1, 1 }, { 1, 3, 0 }, { 1, 1, 2 } },   //red side
	{ { 2, 1, 1 }, { 1, 4, 0 }, { 1, 1, 2 } },   //green side
	{ { 0, 0, 0 }, { 0, 5, 0 }, { 0, 0, 0 } } }; //white side

int indexCube[6][3][3] = {
	{ { 1, 1, 2 }, { 0, 0, 2 }, { 0, 3, 3 } },   //yellow side
	{ { 1, 0, 0 }, { 5, 1, 4 }, { 5, 8, 4 } },   //orange side
	{ { 0, 3, 3 }, { 4, 2, 7 }, { 4, 11, 7 } },   //blue side
	{ { 3, 2, 2 }, { 7, 3, 6 }, { 7, 10, 6 } },   //red side
	{ { 2, 1, 1 }, { 6, 4, 5 }, { 6, 9, 5 } },   //green side
	{ { 4, 11, 7 }, { 8, 5, 10 }, { 5, 9, 6 } } }; //white side


int MiddleColor[6] = {0,1,2,3,4,5};

#endif
