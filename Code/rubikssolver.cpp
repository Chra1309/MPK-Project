//#include "stdafx.h"
#include <iostream>
#include <stdlib.h>
#include <string>
#include <cmath>
#include <time.h>
#include <stdio.h>

#include "rubikssolver_header.hpp"
using namespace std;



/*
 int cube[6][3][3] = {
 { {2, 2, 5}, {0, 0, 0}, {4, 4, 2} }, //yellow side
 { {5, 1, 5}, {2, 1, 1}, {2, 2, 4} }, //orange side
 { {1, 5, 0}, {5, 2, 2}, {5, 5, 1} }, //blue side
 { {1, 4, 3}, {5, 3, 4}, {4, 4, 3} }, //red side
 { {2, 3, 1}, {3, 4, 0}, {0, 3, 3} }, //green side
 { {3, 3, 0}, {1, 5, 1}, {0, 0, 4} } }; //white side
 */
/*
int old[6][3][3] = {
	{ { 0, 0, 0 }, { 0, 0, 0 }, { 0, 0, 0 } }, //yellow side
	{ { 1, 1, 1 }, { 1, 1, 1 }, { 1, 1, 1 } }, //orange side
	{ { 2, 2, 2 }, { 2, 2, 2 }, { 2, 2, 2 } }, //blue side
	{ { 3, 3, 3 }, { 3, 3, 3 }, { 3, 3, 3 } }, //red side
	{ { 4, 4, 4 }, { 4, 4, 4 }, { 4, 4, 4 } }, //green side
};*/
/*
int cube[6][3][3] = {
	{ { 0, 0, 0 }, { 0, 0, 0 }, { 0, 0, 0 } }, //yellow side
	{ { 1, 1, 1 }, { 1, 1, 1 }, { 1, 1, 1 } }, //orange side
	{ { 2, 2, 2 }, { 2, 2, 2 }, { 2, 2, 2 } }, //blue side
	{ { 3, 3, 3 }, { 3, 3, 3 }, { 3, 3, 3 } }, //red side
	{ { 4, 4, 4 }, { 4, 4, 4 }, { 4, 4, 4 } }, //green side
	{ { 5, 5, 5 }, { 5, 5, 5 }, { 5, 5, 5 } } }; //white side
*/
int cube[6][3][3] = {
	{ { 5, 0, 4 }, { 2, 0, 5 }, { 1, 3, 2 } }, //yellow side
	{ { 1, 0, 2 }, { 0, 1, 3 }, { 5, 5, 4 } }, //orange side
	{ { 5, 0, 3 }, { 2, 2, 3 }, { 5, 1, 2 } }, //blue side
	{ { 0, 4, 1 }, { 4, 3, 1 }, { 5, 5, 3 } }, //red side
	{ { 0, 3, 4 }, { 2, 4, 1 }, { 0, 4, 3 } }, //green side
	{ { 3, 4, 1 }, { 2, 5, 1 }, { 2, 0, 4 } } }; //white side

int cube_customcolor[6][3][3];

////////////////////////////////      ////////////////////////////////
//////////////////////////////// MAIN ////////////////////////////////
////////////////////////////////      ////////////////////////////////


int main()
{
    inputCube();
    mapforsolver();
    //printCubeColor();
    //print();
	//scramble();
	//cout << "scramble: " << moves << endl;
	//clearMoves();
    //printCubeColor();
	solveTopCross();
	cout << "cross: " << moves << endl;
	clearMoves();
    mapforcustomcolor();
    printCubeColor(cube_customcolor);
	solveTopCorners();
	cout << "corners: " << moves << endl;
	clearMoves();
    mapforcustomcolor();
    printCubeColor(cube_customcolor);
	solveMiddleLayer();
	cout << "middle layer: " << moves << endl;
	clearMoves();
    mapforcustomcolor();
    printCubeColor(cube_customcolor);
	solveBottomLayer();
	cout << "Bottom: " << moves << endl;
	clearMoves();
    mapforcustomcolor();
    printCubeColor(cube_customcolor);
	return 0;
}

