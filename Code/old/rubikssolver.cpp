
#include <iostream>
#include <stdlib.h>
#include <string>
#include <cmath>
#include <time.h>
#include <stdio.h>

#include "rubikssolver_header.hpp"
using namespace std;

int cube[6][3][3] = {
	{ { 0, 0, 0 }, { 0, 0, 0 }, { 0, 0, 0 } }, //yellow side
	{ { 1, 1, 1 }, { 1, 1, 1 }, { 1, 1, 1 } }, //orange side
	{ { 2, 2, 2 }, { 2, 2, 2 }, { 2, 2, 2 } }, //blue side
	{ { 3, 3, 3 }, { 3, 3, 3 }, { 3, 3, 3 } }, //red side
	{ { 4, 4, 4 }, { 4, 4, 4 }, { 4, 4, 4 } }, //green side
	{ { 5, 5, 5 }, { 5, 5, 5 }, { 5, 5, 5 } } }; //white side

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

