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

int MiddleColor[6] = {0,1,2,3,4,5};

#endif
