#ifndef RUBIKSSOLVER_HEADER_HPP
#define RUBIKSSOLVER_HEADER_HPP

//#include "stdafx.h"
#include <iostream>
#include <stdlib.h>
#include <string>
#include <cmath>
#include <time.h>
#include <stdio.h>

#include "cubeoperations.hpp"
using namespace std;


////lookup
int lookup[6] = {0,0,0,0,0,0};

void translateMove();
void r(int cube[6][3][3], int oCube[6][3][3], int iCube[6][3][3]);
void rRotate(int rRotateCube[6][3][3]);
void ri(int cube[6][3][3], int oCube[6][3][3], int iCube[6][3][3]);
void riRotate(int riRotateCube[6][3][3]);

void l(int cube[6][3][3], int oCube[6][3][3], int iCube[6][3][3]);
void lRotate(int lRotateCube[6][3][3]);
void li(int cube[6][3][3], int oCube[6][3][3], int iCube[6][3][3]);
void liRotate(int liRotateCube[6][3][3]);

void u(int cube[6][3][3], int oCube[6][3][3], int iCube[6][3][3]);
void uRotate(int uRotateCube[6][3][3]);
void ui(int cube[6][3][3], int oCube[6][3][3], int iCube[6][3][3]);
void uRotate(int uiRotateCube[6][3][3]);

void d(int cube[6][3][3], int oCube[6][3][3], int iCube[6][3][3]);
void dRotate(int dRotateCube[6][3][3]);
void di(int cube[6][3][3], int oCube[6][3][3], int iCube[6][3][3]);
void diRotate(int diRotateCube[6][3][3]);

void f(int cube[6][3][3], int oCube[6][3][3], int iCube[6][3][3]);
void fRotate(int fRotateCube[6][3][3]);
void fi(int cube[6][3][3], int oCube[6][3][3], int iCube[6][3][3]);
void fiRotate(int fiRotateCube[6][3][3]);

void b(int cube[6][3][3], int oCube[6][3][3], int iCube[6][3][3]);
void bRotate(int bRotateCube[6][3][3]);
void bi(int cube[6][3][3], int oCube[6][3][3], int iCube[6][3][3]);
void biRotate(int biRotateCube[6][3][3]);

void copyCube(int copyofcube[6][3][3]);
void print(int printcube[6][3][3]);

void solveTopCross(int cube[6][3][3], int oCube[6][3][3], int iCube[6][3][3]);
void findNextTopEdge(int & s, int & p);
void moveTopEdges(int cube[6][3][3], int oCube[6][3][3], int iCube[6][3][3]);

void solveTopCorners(int cube[6][3][3], int oCube[6][3][3], int iCube[6][3][3]);
void findNextTopCorner(int & s, int & p);
void moveTopCorners(int cube[6][3][3], int oCube[6][3][3], int iCube[6][3][3]);

void scramble();
void solveMiddleLayer(int cube[6][3][3], int oCube[6][3][3], int iCube[6][3][3]);
int findBottomMatch(int color);
void placeMiddleEdge(int color, int eSide, int cube[6][3][3], int oCube[6][3][3], int iCube[6][3][3]);
void middleAlgorithm(int color, int direction, int cube[6][3][3], int oCube[6][3][3], int iCube[6][3][3]);

string last(); //gets the last move performed
void removeLast(); //removes the last move performed
void clearMoves(); //clears all moves


void mapforcustomcolor();
void printCubeColor();
void solveBottomLayer(int cube[6][3][3], int oCube[6][3][3], int iCube[6][3][3]);
void positionBottomCorners(int cube[6][3][3], int oCube[6][3][3], int iCube[6][3][3]);
int numCorrectCorners();
void getCorner(int num, int corners[]);
void swapCorners(int face, int cube[6][3][3], int oCube[6][3][3], int iCube[6][3][3]);
void positionBottomEdges(int cube[6][3][3], int oCube[6][3][3], int iCube[6][3][3]);
int numEdgesInCorrectPos();
void rotateEdges(int face, bool rotClockwise, int cube[6][3][3], int oCube[6][3][3], int iCube[6][3][3]);
void correctBottomCorners(int cube[6][3][3], int oCube[6][3][3], int iCube[6][3][3]);
int cornerOrientation();
int findBestFace(int cornerNum);
void twoCornerRotate(int face, bool goForward, int cube[6][3][3], int oCube[6][3][3], int iCube[6][3][3]);
void correctBottomEdges(int cube[6][3][3], int oCube[6][3][3], int iCube[6][3][3]);
void twoEdgeRotate(int face, bool isNextTo, int cube[6][3][3], int oCube[6][3][3], int iCube[6][3][3]);

//extern int cube[6][3][3];
//extern int cube_customcolor[6][3][3];
int checkface(int face2check);
int solvercube[6][3][3];

int old[6][3][3] = {
	{ { 0, 0, 0 }, { 0, 0, 0 }, { 0, 0, 0 } }, //yellow side
	{ { 1, 1, 1 }, { 1, 1, 1 }, { 1, 1, 1 } }, //orange side
	{ { 2, 2, 2 }, { 2, 2, 2 }, { 2, 2, 2 } }, //blue side
	{ { 3, 3, 3 }, { 3, 3, 3 }, { 3, 3, 3 } }, //red side
	{ { 4, 4, 4 }, { 4, 4, 4 }, { 4, 4, 4 } }, //green side
};

int cube_customcolor[6][3][3];

string moves = "";

void rRotate(int rRotateCube[6][3][3]){

	copyCube(rRotateCube);
	for (int i = 0; i < 3; i++)
	{
		rRotateCube[2][i][2] = old[5][i][2];
		rRotateCube[0][i][2] = old[2][i][2];
		rRotateCube[4][i][0] = old[0][2 - i][2];
		rRotateCube[5][i][2] = old[4][2 - i][0];
	}
	rRotateCube[3][0][2] = old[3][0][0];
	rRotateCube[3][2][2] = old[3][0][2];
	rRotateCube[3][2][0] = old[3][2][2];
	rRotateCube[3][0][0] = old[3][2][0];
    
	rRotateCube[3][1][2] = old[3][0][1];
	rRotateCube[3][2][1] = old[3][1][2];
	rRotateCube[3][1][0] = old[3][2][1];
	rRotateCube[3][0][1] = old[3][1][0];

}


void r(int cube[6][3][3], int oCube[6][3][3], int iCube[6][3][3])
{
	if (last() == "r  ")
	{
		removeLast();
		moves += "r2 ";
	}
	else if (last() == "r2 ")
	{
		removeLast();
		moves += "ri ";
	}
	else if (last() == "ri ")
	{
		removeLast();
	}
	else
	{
		moves += "r  ";
	}
    
    rRotate(cube);
    rRotate(oCube);
    rRotate(iCube);
    rRotate(solvercube);

}

void riRotate(int riRotateCube[6][3][3]){

	copyCube(riRotateCube);
	for (int i = 0; i < 3; i++)
	{
		riRotateCube[5][i][2] = old[2][i][2];
		riRotateCube[2][i][2] = old[0][i][2];
		riRotateCube[0][2 - i][2] = old[4][i][0];
		riRotateCube[4][2 - i][0] = old[5][i][2];
	}
	riRotateCube[3][0][0] = old[3][0][2];
	riRotateCube[3][0][2] = old[3][2][2];
	riRotateCube[3][2][2] = old[3][2][0];
	riRotateCube[3][2][0] = old[3][0][0];
    
	riRotateCube[3][0][1] = old[3][1][2];
	riRotateCube[3][1][2] = old[3][2][1];
	riRotateCube[3][2][1] = old[3][1][0];
	riRotateCube[3][1][0] = old[3][0][1];

}

void ri(int cube[6][3][3], int oCube[6][3][3], int iCube[6][3][3])
{
	if (last() == "ri ")
	{
		removeLast();
		moves += "r2 ";
	}
	else if (last() == "r2 ")
	{
		removeLast();
		moves += "r  ";
	}
	else if (last() == "r  ")
	{
		removeLast();
	}
	else
	{
		moves += "ri ";
	}

    riRotate(cube);
    riRotate(oCube);
    riRotate(iCube);
    riRotate(solvercube);

}

void lRotate(int lRotateCube[6][3][3]){

	copyCube(lRotateCube);
	for (int i = 0; i < 3; i++)
	{
		lRotateCube[5][i][0] = old[2][i][0];
		lRotateCube[2][i][0] = old[0][i][0];
		lRotateCube[0][i][0] = old[4][2 - i][2];
		lRotateCube[4][2 - i][2] = old[5][i][0];
	}
	lRotateCube[1][0][2] = old[1][0][0];
	lRotateCube[1][2][2] = old[1][0][2];
	lRotateCube[1][2][0] = old[1][2][2];
	lRotateCube[1][0][0] = old[1][2][0];
    
	lRotateCube[1][1][2] = old[1][0][1];
	lRotateCube[1][2][1] = old[1][1][2];
	lRotateCube[1][1][0] = old[1][2][1];
	lRotateCube[1][0][1] = old[1][1][0];

}

void l(int cube[6][3][3], int oCube[6][3][3], int iCube[6][3][3])
{
	if (last() == "l  ")
	{
		removeLast();
		moves += "l2 ";
	}
	else if (last() == "l2 ")
	{
		removeLast();
		moves += "li ";
	}
	else if (last() == "li ")
	{
		removeLast();
	}
	else
	{
		moves += "l  ";
	}

    lRotate(cube);
    lRotate(oCube);
    lRotate(iCube);
    lRotate(solvercube);

}



void liRotate(int liRotateCube[6][3][3]){

	copyCube(liRotateCube);
	for (int i = 0; i < 3; i++)
	{
		liRotateCube[2][i][0] = old[5][i][0];
		liRotateCube[0][i][0] = old[2][i][0];
		liRotateCube[4][i][2] = old[0][2 - i][0];
		liRotateCube[5][i][0] = old[4][2 - i][2];
	}
	liRotateCube[1][0][0] = old[1][0][2];
	liRotateCube[1][0][2] = old[1][2][2];
	liRotateCube[1][2][2] = old[1][2][0];
	liRotateCube[1][2][0] = old[1][0][0];
    
	liRotateCube[1][0][1] = old[1][1][2];
	liRotateCube[1][1][2] = old[1][2][1];
	liRotateCube[1][2][1] = old[1][1][0];
	liRotateCube[1][1][0] = old[1][0][1];

}

void li(int cube[6][3][3], int oCube[6][3][3], int iCube[6][3][3])
{
	if (last() == "li ")
	{
		removeLast();
		moves += "l2 ";
	}
	else if (last() == "l2 ")
	{
		removeLast();
		moves += "l  ";
	}
	else if (last() == "l  ")
	{
		removeLast();
	}
	else
	{
		moves += "li ";
	}

    liRotate(cube);
    liRotate(oCube);
    liRotate(iCube);
    liRotate(solvercube);


}

void uRotate(int uRotateCube[6][3][3]){
	copyCube(uRotateCube);
	for (int i = 0; i < 3; i++)
	{
		uRotateCube[1][0][i] = old[2][0][i];
		uRotateCube[4][0][i] = old[1][0][i];
		uRotateCube[3][0][i] = old[4][0][i];
		uRotateCube[2][0][i] = old[3][0][i];
	}
	uRotateCube[0][0][0] = old[0][2][0];
	uRotateCube[0][0][2] = old[0][0][0];
	uRotateCube[0][2][2] = old[0][0][2];
	uRotateCube[0][2][0] = old[0][2][2];
    
	uRotateCube[0][0][1] = old[0][1][0];
	uRotateCube[0][1][2] = old[0][0][1];
	uRotateCube[0][2][1] = old[0][1][2];
	uRotateCube[0][1][0] = old[0][2][1];
}

void u(int cube[6][3][3], int oCube[6][3][3], int iCube[6][3][3])
{
	if (last() == "u  ")
	{
		removeLast();
		moves += "u2 ";
	}
	else if (last() == "u2 ")
	{
		removeLast();
		moves += "ui ";
	}
	else if (last() == "ui ")
	{
		removeLast();
	}
	else
	{
		moves += "u  ";
	}
    
    uRotate(cube);
    uRotate(oCube);
    uRotate(iCube);
    uRotate(solvercube);
}

void uiRotate(int uiRotateCube[6][3][3]){
	copyCube(uiRotateCube);
	for (int i = 0; i < 3; i++)
	{
		uiRotateCube[2][0][i] = old[1][0][i];
		uiRotateCube[1][0][i] = old[4][0][i];
		uiRotateCube[4][0][i] = old[3][0][i];
		uiRotateCube[3][0][i] = old[2][0][i];
	}
	uiRotateCube[0][2][0] = old[0][0][0];
	uiRotateCube[0][0][0] = old[0][0][2];
	uiRotateCube[0][0][2] = old[0][2][2];
	uiRotateCube[0][2][2] = old[0][2][0];
    
	uiRotateCube[0][1][0] = old[0][0][1];
	uiRotateCube[0][0][1] = old[0][1][2];
	uiRotateCube[0][1][2] = old[0][2][1];
	uiRotateCube[0][2][1] = old[0][1][0];

}

void ui(int cube[6][3][3], int oCube[6][3][3], int iCube[6][3][3])
{
	if (last() == "ui ")
	{
		removeLast();
		moves += "u2 ";
	}
	else if (last() == "u2 ")
	{
		removeLast();
		moves += "u  ";
	}
	else if (last() == "u  ")
	{
		removeLast();
	}
	else
	{
		moves += "ui ";
	}

    uiRotate(cube);
    uiRotate(oCube);
    uiRotate(iCube);
    uiRotate(solvercube);
}

void dRotate(int dRotateCube[6][3][3]){
	copyCube(dRotateCube);
	for (int i = 0; i < 3; i++)
	{
		dRotateCube[2][2][i] = old[1][2][i];
		dRotateCube[1][2][i] = old[4][2][i];
		dRotateCube[4][2][i] = old[3][2][i];
		dRotateCube[3][2][i] = old[2][2][i];
	}
	dRotateCube[5][0][0] = old[5][2][0];
	dRotateCube[5][0][2] = old[5][0][0];
	dRotateCube[5][2][2] = old[5][0][2];
	dRotateCube[5][2][0] = old[5][2][2];
    
	dRotateCube[5][0][1] = old[5][1][0];
	dRotateCube[5][1][2] = old[5][0][1];
	dRotateCube[5][2][1] = old[5][1][2];
	dRotateCube[5][1][0] = old[5][2][1];
}

void d(int cube[6][3][3], int oCube[6][3][3], int iCube[6][3][3])
{
	if (last() == "d  ")
	{
		removeLast();
		moves += "d2 ";
	}
	else if (last() == "d2 ")
	{
		removeLast();
		moves += "di ";
	}
	else if (last() == "di ")
	{
		removeLast();
	}
	else
	{
		moves += "d  ";
	}
    dRotate(cube);
    dRotate(oCube);
    dRotate(iCube);
    dRotate(solvercube);

}

void diRotate(int diRotateCube[6][3][3]){
	copyCube(diRotateCube);
	for (int i = 0; i < 3; i++)
	{
		diRotateCube[1][2][i] = old[2][2][i];
		diRotateCube[4][2][i] = old[1][2][i];
		diRotateCube[3][2][i] = old[4][2][i];
		diRotateCube[2][2][i] = old[3][2][i];
	}
	diRotateCube[5][2][0] = old[5][0][0];
	diRotateCube[5][0][0] = old[5][0][2];
	diRotateCube[5][0][2] = old[5][2][2];
	diRotateCube[5][2][2] = old[5][2][0];
    
	diRotateCube[5][1][0] = old[5][0][1];
	diRotateCube[5][0][1] = old[5][1][2];
	diRotateCube[5][1][2] = old[5][2][1];
	diRotateCube[5][2][1] = old[5][1][0];
}

void di(int cube[6][3][3], int oCube[6][3][3], int iCube[6][3][3])
{
	if (last() == "di ")
	{
		removeLast();
		moves += "d2 ";
	}
	else if (last() == "d2 ")
	{
		removeLast();
		moves += "d  ";
	}
	else if (last() == "d  ")
	{
		removeLast();
	}
	else
	{
		moves += "di ";
	}

    diRotate(cube);
    diRotate(oCube);
    diRotate(iCube);
    diRotate(solvercube);

}

void fRotate(int fRotateCube[6][3][3]){
	copyCube(fRotateCube);
	for (int i = 0; i < 3; i++)
	{
		fRotateCube[0][2][i] = old[1][2 - i][2];
		fRotateCube[3][i][0] = old[0][2][i];
		fRotateCube[5][0][2 - i] = old[3][i][0];
		fRotateCube[1][2 - i][2] = old[5][0][2 - i];
	}
	fRotateCube[2][0][2] = old[2][0][0];
	fRotateCube[2][2][2] = old[2][0][2];
	fRotateCube[2][2][0] = old[2][2][2];
	fRotateCube[2][0][0] = old[2][2][0];
    
	fRotateCube[2][1][2] = old[2][0][1];
	fRotateCube[2][2][1] = old[2][1][2];
	fRotateCube[2][1][0] = old[2][2][1];
	fRotateCube[2][0][1] = old[2][1][0];
}

void f(int cube[6][3][3], int oCube[6][3][3], int iCube[6][3][3])
{
	if (last() == "f  ")
	{
		removeLast();
		moves += "f2 ";
	}
	else if (last() == "f2 ")
	{
		removeLast();
		moves += "fi ";
	}
	else if (last() == "fi ")
	{
		removeLast();
	}
	else
	{
		moves += "f  ";
	}
    fRotate(cube);
    fRotate(oCube);
    fRotate(iCube);
    fRotate(solvercube);

}

void fiRotate(int fiRotateCube[6][3][3]){
	copyCube(fiRotateCube);
	for (int i = 0; i < 3; i++)
	{
		fiRotateCube[1][i][2] = old[0][2][2 - i];
		fiRotateCube[0][2][2 - i] = old[3][2 - i][0];
		fiRotateCube[3][2 - i][0] = old[5][0][i];
		fiRotateCube[5][0][i] = old[1][i][2];
	}
	fiRotateCube[2][0][0] = old[2][0][2];
	fiRotateCube[2][0][2] = old[2][2][2];
	fiRotateCube[2][2][2] = old[2][2][0];
	fiRotateCube[2][2][0] = old[2][0][0];
    
	fiRotateCube[2][0][1] = old[2][1][2];
	fiRotateCube[2][1][2] = old[2][2][1];
	fiRotateCube[2][2][1] = old[2][1][0];
	fiRotateCube[2][1][0] = old[2][0][1];
}

void fi(int cube[6][3][3], int oCube[6][3][3], int iCube[6][3][3])
{
	if (last() == "fi ")
	{
		removeLast();
		moves += "f2 ";
	}
	else if (last() == "f2 ")
	{
		removeLast();
		moves += "f  ";
	}
	else if (last() == "f  ")
	{
		removeLast();
	}
	else
	{
		moves += "fi ";
	}

    fiRotate(cube);
    fiRotate(oCube);
    fiRotate(iCube);
    fiRotate(solvercube);

}

void bRotate(int bRotateCube[6][3][3]){
	copyCube(bRotateCube);
	for (int i = 0; i < 3; i++)
	{
		bRotateCube[1][2 - i][0] = old[0][0][i];
		bRotateCube[0][0][i] = old[3][i][2];
		bRotateCube[3][i][2] = old[5][2][2 - i];
		bRotateCube[5][2][2 - i] = old[1][2 - i][0];
	}
	bRotateCube[4][0][2] = old[4][0][0];
	bRotateCube[4][2][2] = old[4][0][2];
	bRotateCube[4][2][0] = old[4][2][2];
	bRotateCube[4][0][0] = old[4][2][0];
    
	bRotateCube[4][1][2] = old[4][0][1];
	bRotateCube[4][2][1] = old[4][1][2];
	bRotateCube[4][1][0] = old[4][2][1];
	bRotateCube[4][0][1] = old[4][1][0];


}

void b(int cube[6][3][3], int oCube[6][3][3], int iCube[6][3][3])
{
	if (last() == "b  ")
	{
		removeLast();
		moves += "b2 ";
	}
	else if (last() == "b2 ")
	{
		removeLast();
		moves += "bi ";
	}
	else if (last() == "bi ")
	{
		removeLast();
	}
	else
	{
		moves += "b  ";
	}

    bRotate(cube);
    bRotate(oCube);
    bRotate(iCube);
    bRotate(solvercube);

}

void biRotate(int biRotateCube[6][3][3]){
	copyCube(biRotateCube);
	for (int i = 0; i < 3; i++)
	{
		biRotateCube[0][0][i] = old[1][2 - i][0];
		biRotateCube[3][i][2] = old[0][0][i];
		biRotateCube[5][2][2 - i] = old[3][i][2];
		biRotateCube[1][2 - i][0] = old[5][2][2 - i];
	}
	biRotateCube[4][0][0] = old[4][0][2];
	biRotateCube[4][0][2] = old[4][2][2];
	biRotateCube[4][2][2] = old[4][2][0];
	biRotateCube[4][2][0] = old[4][0][0];
    
	biRotateCube[4][0][1] = old[4][1][2];
	biRotateCube[4][1][2] = old[4][2][1];
	biRotateCube[4][2][1] = old[4][1][0];
	biRotateCube[4][1][0] = old[4][0][1];
}

void bi(int cube[6][3][3], int oCube[6][3][3], int iCube[6][3][3])
{
	if (last() == "bi ")
	{
		removeLast();
		moves += "b2 ";
	}
	else if (last() == "b2 ")
	{
		removeLast();
		moves += "b  ";
	}
	else if (last() == "b  ")
	{
		removeLast();
	}
	else
	{
		moves += "bi ";
	}
    biRotate(cube);
    biRotate(oCube);
    biRotate(iCube);
    biRotate(solvercube);

}

void solveTopCross(int cube[6][3][3], int oCube[6][3][3], int iCube[6][3][3])
{

    //cout << "checkpoint1" << endl;
	moveTopEdges(cube, oCube, iCube);
    //cout << "checkpoint2" << endl;
	//look for the 4 yellow edges
	for (int i = 1; i < 5; i++)
	{
		int side = 0; //side that the yellow sticker is on
		int pos = 0; //position (1-4) of the yellow sticker
		findNextTopEdge(side, pos);
		int numTurns = 0; //keeps track of how many times we turn the cube to put pieces on the bottom layer so we can undo the turns
		if (side == 1)
		{
			while (solvercube[5][1][0] == 0)
			{
				d(cube, oCube, iCube);
			}
			while (solvercube[0][1][0] == 0)
			{
				u(cube, oCube, iCube);
				numTurns++;
			}
			if (pos == 1)
			{
				l(cube, oCube, iCube);
				l(cube, oCube, iCube);
			}
			else if (pos == 2)
			{
				l(cube, oCube, iCube);
			}
			else if (pos == 4)
			{
				li(cube, oCube, iCube);
			}
		}
		else if (side == 2)
		{
			while (solvercube[5][0][1] == 0)
			{
				d(cube, oCube, iCube);
			}
			while (solvercube[0][2][1] == 0)
			{
				u(cube, oCube, iCube);
				numTurns++;
			}
			if (pos == 1)
			{
				f(cube, oCube, iCube);
				f(cube, oCube, iCube);
			}
			else if (pos == 2)
			{
				f(cube, oCube, iCube);
			}
			else if (pos == 4)
			{
				fi(cube, oCube, iCube);
			}
			di(cube, oCube, iCube);
		}
		else if (side == 3)
		{
			while (solvercube[5][1][2] == 0)
			{
				d(cube, oCube, iCube);
			}
			while (solvercube[0][1][2] == 0)
			{
				u(cube, oCube, iCube);
				numTurns++;
			}
			if (pos == 1)
			{
				r(cube, oCube, iCube);
				r(cube, oCube, iCube);
			}
			else if (pos == 2)
			{
				r(cube, oCube, iCube);
			}
			else if (pos == 4)
			{
				ri(cube, oCube, iCube);
			}
			d(cube, oCube, iCube);
			d(cube, oCube, iCube);
		}
		else if (side == 4)
		{
			while (solvercube[5][2][1] == 0)
			{
				d(cube, oCube, iCube);
			}
			while (solvercube[0][0][1] == 0)
			{
				u(cube, oCube, iCube);
				numTurns++;
			}
			if (pos == 1)
			{
				b(cube, oCube, iCube);
				b(cube, oCube, iCube);
			}
			else if (pos == 2)
			{
				b(cube, oCube, iCube);
			}
			else if (pos == 4)
			{
				bi(cube, oCube, iCube);
			}
			d(cube, oCube, iCube);
		}
		else if (side == 5)
		{
			for (int j = 0; j < 4 - pos; j++)
			{
				d(cube, oCube, iCube);
			}
		}
		for (int j = 0; j < numTurns; j++)
		{
			ui(cube, oCube, iCube);
		}
		if (side == 5) //algorithm for when the sticker is on the bottom
		{
			int color = solvercube[1][2][1];
			for (int a = 1; a < color; a++) //set-up so that the edge goes into the right spot
			{
				u(cube, oCube, iCube);
			}
			l(cube, oCube, iCube);
			l(cube, oCube, iCube);
			for (int a = 1; a < color; a++) //undo set-up
			{
				ui(cube, oCube, iCube);
			}
		}
		else //algorithm for when th esticker is not on the bottom
		{
			int color = solvercube[5][1][0];
			if (color < 4) //set-up so that the sticker goes into the right spot
			{
				for (int a = 1; a < color + 1; a++)
				{
					u(cube, oCube, iCube);
				}
			}
			l(cube, oCube, iCube);
			bi(cube, oCube, iCube);
			li(cube, oCube, iCube);
			if (color < 4) //undo set-up
			{
				for (int a = 1; a < color + 1; a++)
				{
					ui(cube, oCube, iCube);
				}
			}
		}
	}
}

void moveTopEdges(int cube[6][3][3], int oCube[6][3][3], int iCube[6][3][3]) //move all yellow edge stickers on top to the bottom
{
	for (int i = 0; i < 4; i++)
	{
		if (solvercube[0][2][1] == 0)
		{
			while (solvercube[5][0][1] == 0)
			{
				d(cube, oCube, iCube);
			}
			f(cube, oCube, iCube);
			f(cube, oCube, iCube);
		}
		u(cube, oCube, iCube);
	}
}

void findNextTopEdge(int & s, int & p)
{
	for (s = 1; s < 6; s++)
	{
		if (solvercube[s][0][1] == 0)
		{
			p = 1;
			break;
		}
		else if (solvercube[s][1][2] == 0)
		{
			p = 2;
			break;
		}
		else if (solvercube[s][2][1] == 0)
		{
			p = 3;
			break;
		}
		else if (solvercube[s][1][0] == 0)
		{
			p = 4;
			break;
		}
	}
}

int checkface(int face2check){
    int col = solvercube[face2check][1][1];

    for(int j = 0; j < 3; j++)
        for(int k = 0; k < 3; k++)
            if(col != solvercube[face2check][j][k])
                return 1;
    return 0;
}



void solveTopCorners(int cube[6][3][3], int oCube[6][3][3], int iCube[6][3][3])
{
	moveTopCorners(cube, oCube, iCube);
	for (int i = 1; i < 5; i++)
	{
		bool bottom = false; //holds whether the yellow sticker is on the bottom face
		bool rig = false; //holds whether the yellow sticker is on the right face
		int side = 0; //what face the yellow sticker is on
		int pos = 0; //which corner the piece is in
		findNextTopCorner(side, pos);
		if (side < 5) //puts the corner in the back bottom right corner
		{
			if (pos == 2)
			{
				rig = true;
			}
			for (int t = 0; t < side + pos - 1; t++)
			{
				di(cube, oCube, iCube);
			}
		}
		else //puts the corner in the back bottom right corner
		{
			bottom = true;
			for (int t = 0; t < pos; t++)
			{
				di(cube, oCube, iCube);
			}
		}
		if (rig) //algorithm for when yellow is on the right
		{
			int color = solvercube[4][2][0];
			if (color < 4) //move the top so that the corner goes into the correct position
			{
				for (int t = 0; t < color; t++)
				{
					u(cube, oCube, iCube);
				}
			}
			r(cube, oCube, iCube);
			d(cube, oCube, iCube);
			ri(cube, oCube, iCube);
			if (color < 4) //undo the setup moves to put the corner in the right position
			{
				for (int t = 0; t < color; t++)
				{
					ui(cube, oCube, iCube);
				}
			}
		}
		else if (bottom) //algorithm for when yellow is on bottom
		{
			int color = solvercube[3][2][2];
			if (color < 4) //move the top so that the corner goes into the correct position
			{
				for (int t = 0; t < color; t++)
				{
					u(cube, oCube, iCube);
				}
			}
			r(cube, oCube, iCube);
			d(cube, oCube, iCube);
			d(cube, oCube, iCube);
			ri(cube, oCube, iCube);
			di(cube, oCube, iCube);
			r(cube, oCube, iCube);
			d(cube, oCube, iCube);
			ri(cube, oCube, iCube);
			if (color < 4) //undo the setup moves to put the corner in the right position
			{
				for (int t = 0; t < color; t++)
				{
					ui(cube, oCube, iCube);
				}
			}
		}
		else //algorithm for when yellow is on back
		{
			int color = solvercube[5][2][2];
			if (color < 4) //move the top so that the corner goes into the correct position
			{
				for (int t = 0; t < color; t++)
				{
					u(cube, oCube, iCube);
				}
			}
			bi(cube, oCube, iCube);
			di(cube, oCube, iCube);
			b(cube, oCube, iCube);
			if (color < 4) //undo the setup moves to put the corner in the right position
			{
				for (int t = 0; t < color; t++)
				{
					ui(cube, oCube, iCube);
				}
			}
		}
	}
}

void moveTopCorners(int cube[6][3][3], int oCube[6][3][3], int iCube[6][3][3]) //moves all yellow corners on the top to the bottom face
{
	for (int i = 0; i < 4; i++)
	{
		if (solvercube[0][2][2] == 0 || solvercube[2][0][2] == 0 || solvercube[3][0][0] == 0)
		{
			while (solvercube[1][2][2] == 0 || solvercube[2][2][0] == 0 || solvercube[5][0][0] == 0) //make sure not to push a different yellow corner back to the top
			{
				d(cube, oCube, iCube);
			}
			ri(cube, oCube, iCube);
			d(cube, oCube, iCube);
			r(cube, oCube, iCube);
		}
		u(cube, oCube, iCube);
	}
}

void findNextTopCorner(int & s, int & p) //locates the next corner that is not in its correct spot (guaranteed to be one of the bottom four corners)
//updates pos and side in solveTopCorners() to hold the side and position of the yellow sticker
{
	for (s = 1; s < 5; s++)
	{
		if (solvercube[s][2][0] == 0)
		{
			p = 1;
			return;
		}
		else if (solvercube[s][2][2] == 0)
		{
			p = 2;
			return;
		}
	}
	if (solvercube[5][0][0] == 0)
	{
		p = 2;
	}
	else if (solvercube[5][0][2] == 0)
	{
		p = 3;
	}
	else if (solvercube[5][2][2] == 0)
	{
		p = 0;
	}
	else
	{
		p = 1;
	}
}

void solveMiddleLayer(int cube[6][3][3], int oCube[6][3][3], int iCube[6][3][3])
{
	int side = -1;
	int color = -1;
	int count = 0;
    
beginning:
	if (side != -1)
	{
		placeMiddleEdge(color, side, cube, oCube, iCube);
		//print();
		count++;
		side = -1;
		color = -1;
	}
    
	for (int i = 1; i <= 4; i++)
	{
    //cout << "checkpoint3" << endl;
		side = findBottomMatch(i);
        
		if (side != -1)
		{
			color = i;
			goto beginning;
		}
	}
    
	for (int i = 1; i <= 4; i++)
	{
		if (solvercube[i][1][0] != (i))
		{
			middleAlgorithm(i, 1, cube, oCube, iCube);
			if(count >= 15)
			{
				solveTopCross(cube, oCube, iCube);
				solveTopCorners(cube, oCube, iCube);
			}
            
			goto beginning;
		}
		else if (solvercube[i][1][2] != i)
		{
			middleAlgorithm(i, 2, cube, oCube, iCube);
            
			if(count >= 10)
			{
				solveTopCross(cube, oCube, iCube);
				solveTopCorners(cube, oCube, iCube);
			}
            
			goto beginning;
		}
	}
    
	int done = 0;
}

int findBottomMatch(int color)
{
	for (int i = 1; i <= 4; i++)
	{
		if (solvercube[i][2][1] == color)
		{
			if (i % 2 == 0)
			{
				if (solvercube[5][abs(2 - i)][1] != 5)
				{
					return i;
				}
			}
			else
			{
				if (solvercube[5][abs(2 - i)][i - 1] != 5)
				{
					return i;
				}
			}
		}
	}
    
	return -1;
}

void placeMiddleEdge(int color, int eSide, int cube[6][3][3], int oCube[6][3][3], int iCube[6][3][3])
{
	if (eSide - color == 0)
	{
		middleAlgorithm(color, -1, cube, oCube, iCube);
	}
	else if (eSide - color == 1)
	{
		di(cube, oCube, iCube);
		middleAlgorithm(color, -1, cube, oCube, iCube);
	}
	else if (eSide - color == 2)
	{
		di(cube, oCube, iCube);
		di(cube, oCube, iCube);
		middleAlgorithm(color, -1, cube, oCube, iCube);
	}
	else if (eSide - color == 3)
	{
		d(cube, oCube, iCube);
		middleAlgorithm(color, -1, cube, oCube, iCube);
	}
	else if (eSide - color == -1)
	{
		d(cube, oCube, iCube);
		middleAlgorithm(color, -1, cube, oCube, iCube);
	}
	else if (eSide - color == -2)
	{
		d(cube, oCube, iCube);
		d(cube, oCube, iCube);
		middleAlgorithm(color, -1, cube, oCube, iCube);
	}
	else if (eSide - color == -3)
	{
		di(cube, oCube, iCube);
		//print();
		middleAlgorithm(color, -1, cube, oCube, iCube);
	}
}

void middleAlgorithm(int color, int direction, int cube[6][3][3], int oCube[6][3][3], int iCube[6][3][3]) //1 - L 2 - R -1 for nothing
{
	if (color == 1)
	{
		if (solvercube[5][1][0] == 4 || direction == 1)
		{
			d(cube, oCube, iCube);
			b(cube, oCube, iCube);
			di(cube, oCube, iCube);
			bi(cube, oCube, iCube);
			di(cube, oCube, iCube);
			li(cube, oCube, iCube);
			d(cube, oCube, iCube);
			l(cube, oCube, iCube);
		}
		else if (solvercube[5][1][0] == 2 || direction == 2)
		{
			di(cube, oCube, iCube);
			fi(cube, oCube, iCube);
			d(cube, oCube, iCube);
			f(cube, oCube, iCube);
			d(cube, oCube, iCube);
			l(cube, oCube, iCube);
			di(cube, oCube, iCube);
			li(cube, oCube, iCube);
		}
	}
	else if (color == 2)
	{
		if (solvercube[5][0][1] == 1 || direction == 1)
		{
			d(cube, oCube, iCube);
			l(cube, oCube, iCube);
			di(cube, oCube, iCube);
			li(cube, oCube, iCube);
			di(cube, oCube, iCube);
			fi(cube, oCube, iCube);
			d(cube, oCube, iCube);
			f(cube, oCube, iCube);
		}
		else if (solvercube[5][0][1] == 3 || direction == 2)
		{
			di(cube, oCube, iCube);
			ri(cube, oCube, iCube);
			d(cube, oCube, iCube);
			r(cube, oCube, iCube);
			d(cube, oCube, iCube);
			f(cube, oCube, iCube);
			di(cube, oCube, iCube);
			fi(cube, oCube, iCube);
		}
	}
	else if (color == 3)
	{
		if (solvercube[5][1][2] == 2 || direction == 1)
		{
			d(cube, oCube, iCube);
			f(cube, oCube, iCube);
			di(cube, oCube, iCube);
			fi(cube, oCube, iCube);
			di(cube, oCube, iCube);
			ri(cube, oCube, iCube);
			d(cube, oCube, iCube);
			r(cube, oCube, iCube);
		}
		else if (solvercube[5][1][2] == 4 || direction == 2)
		{
			di(cube, oCube, iCube);
			bi(cube, oCube, iCube);
			d(cube, oCube, iCube);
			b(cube, oCube, iCube);
			d(cube, oCube, iCube);
			r(cube, oCube, iCube);
			di(cube, oCube, iCube);
			ri(cube, oCube, iCube);
		}
	}
	else if (color == 4)
	{
		if (solvercube[5][2][1] == 3 || direction == 1)
		{
			d(cube, oCube, iCube);
			r(cube, oCube, iCube);
			di(cube, oCube, iCube);
			ri(cube, oCube, iCube);
			di(cube, oCube, iCube);
			bi(cube, oCube, iCube);
			d(cube, oCube, iCube);
			b(cube, oCube, iCube);
		}
		else if (solvercube[5][2][1] == 1 || direction == 2)
		{
			di(cube, oCube, iCube);
			li(cube, oCube, iCube);
			d(cube, oCube, iCube);
			l(cube, oCube, iCube);
			d(cube, oCube, iCube);
			b(cube, oCube, iCube);
			di(cube, oCube, iCube);
			bi(cube, oCube, iCube);
		}
	}
}

void solveBottomLayer(int cube[6][3][3], int oCube[6][3][3], int iCube[6][3][3])
{
	positionBottomCorners(cube, oCube, iCube);
	//print();
	positionBottomEdges(cube, oCube, iCube);
	//print();
	correctBottomCorners(cube, oCube, iCube);
	//print();
	correctBottomEdges(cube, oCube, iCube);
    //	print();
}

void positionBottomCorners(int cube[6][3][3], int oCube[6][3][3], int iCube[6][3][3])
{
	int dTurns[4];
    
	int bestNumDTurns = 0;
	int pos1 = -1;
	int pos2 = -1;
    
	for (int i = 0; i < 4; i++)
	{
		dTurns[i] = numCorrectCorners();
        
		if (dTurns[i] == 4)
		{
			pos1 = 4;
			bestNumDTurns = i;
			break;
		}
		else if (dTurns[i] < 4 && dTurns[i] > -1)
		{
			if (pos2 == -1)
			{
				pos1 = dTurns[i];
				bestNumDTurns = i;
			}
		}
		else if (dTurns[i] > 4)
		{
			int side1 = dTurns[i] % 10 + 1;
			int side2 = (int)(dTurns[i] / 10) + 1;
            
			//Corners are next to each other
			if (side2 == (side1 + 1) || side1 == (side2 + 1) || (side2 == 4 && side1 == 1) || (side2 == 1 && side1 == 4))
			{
				pos1 = side1;
				pos2 = side2;
				bestNumDTurns = i;
			}
			else if (pos2 == -1)
			{
				pos1 = side1;
				pos2 = side2;
				bestNumDTurns = i;
			}
		}
        
		d(cube, oCube, iCube);
		//print();
	}
    
	for (int i = 0; i < bestNumDTurns && pos1 != 4; i++)
	{
		d(cube, oCube, iCube);
	}
    

	//Finally Ready to start positioning corners with algorithm!!!!! OMG WHO KNEW A BRAIN COULD DO SO MUCH SO EASILY!!!!!
    
	if (pos1 == 4)
	{
		//One CRAZY lucky scenario, and is the only way to exit this nightmare :D
		return;
	}
	else if (pos2 != -1 && (pos2 == (pos1 + 1) || pos1 == (pos2 + 1) || (pos2 == 4 && pos1 == 1) || (pos2 == 1 && pos1 == 4)))
	{
		int oppFace = pos2 + 3;
		//int face = oppFace + 2;
        
		if (oppFace > 4)
		{
			oppFace = oppFace - 4;
		}
        
		swapCorners(oppFace, cube, oCube, iCube);
		positionBottomCorners(cube, oCube, iCube);
		return;
	}
	else if (pos2 != -1)
	{
		//Corners opp. corners correct
		int face = pos1 + 4;
        
		if (face > 4)
		{
			face = face - 4;
		}
        
		int face2 = face + 1;
		if (face2 > 4)
		{
			face2 = face2 - 4;
		}
        
		swapCorners(face, cube, oCube, iCube);
		swapCorners(face2, cube, oCube, iCube);
		swapCorners(face, cube, oCube, iCube);
		positionBottomCorners(cube, oCube, iCube);
		return;
	}
	else
	{
		//Only 1 correct, 3 corners wrong... If thats even posible (I'm 99% positive it isnt the way I set the cube up)?????
		//But just in case
		int face = pos1 + 2;
        
		if (face > 4)
		{
			face = face - 4;
		}
        
		swapCorners(face, cube, oCube, iCube); //Eventually One of the previous situations above will occur :D
		positionBottomCorners(cube, oCube, iCube);
		return;
	}
    
}

void swapCorners(int face, int cube[6][3][3], int oCube[6][3][3], int iCube[6][3][3])
{
	if (face == 1)
	{
		di(cube, oCube, iCube);
		fi(cube, oCube, iCube);
		d(cube, oCube, iCube);
		b(cube, oCube, iCube);
		di(cube, oCube, iCube);
		f(cube, oCube, iCube);
		d(cube, oCube, iCube);
		bi(cube, oCube, iCube);
		di(cube, oCube, iCube);
	}
	else if (face == 2)
	{
		di(cube, oCube, iCube);
		ri(cube, oCube, iCube);
		d(cube, oCube, iCube);
		l(cube, oCube, iCube);
		di(cube, oCube, iCube);
		r(cube, oCube, iCube);
		d(cube, oCube, iCube);
		li(cube, oCube, iCube);
		di(cube, oCube, iCube);
	}
	else if (face == 3)
	{
		di(cube, oCube, iCube);
		bi(cube, oCube, iCube);
		d(cube, oCube, iCube);
		f(cube, oCube, iCube);
		di(cube, oCube, iCube);
		b(cube, oCube, iCube);
		d(cube, oCube, iCube);
		fi(cube, oCube, iCube);
		di(cube, oCube, iCube);
	}
	else if (face == 4)
	{
		di(cube, oCube, iCube);
		li(cube, oCube, iCube);
		d(cube, oCube, iCube);
		r(cube, oCube, iCube);
		di(cube, oCube, iCube);
		l(cube, oCube, iCube);
		d(cube, oCube, iCube);
		ri(cube, oCube, iCube);
		di(cube, oCube, iCube);
	}
}

int numCorrectCorners()
{
	//If numCorrect ==  4 it will return 4
	//If numCorrect == 2 it will return 2nd Corner * 10 + 1st corner (i.e. 20)
	//Else if numCorrect == 1 it will return pos of corner
	//Else if 0 are correct return -1
	int cornerColors[3];
	int side1 = 0;
	int side2 = 0;
    
	int count = 0;
    
	int colorsMatch = 0; //if this equals 2 then there is a match per corner
	int position[4] = { -1, -1, -1, -1 }; //-1 means there is no match, 1 means match
    
	for (int i = 0; i < 4; i++)
	{
		getCorner(i, cornerColors);
        
		side1 = i + 1;
		side2 = i + 2;
        
		if (side2 == 5)
		{
			side2 = 1;
		}
        
		for (int j = 0; j < 3; j++)
		{
			if (cornerColors[j] == side1 || cornerColors[j] == side2)
			{
				colorsMatch++;
			}
		}
        
		if (colorsMatch == 2)
		{
			position[i] = 1;
			count++;
		}
        
		colorsMatch = 0;
	}
    
	int pos = 0;
	int multiplier = 1;
    
	if (count == 4)
	{
		return 4;
	}
	else if (count == 2 || count == 1)
	{
		for (int i = 0; i < 4; i++)
		{
			if (position[i] == 1)
			{
				pos += i * multiplier;
				multiplier *= 10;
			}
		}
	}
	else
	{
		pos = -1;
	}
    
	return pos;
}

void getCorner(int num, int corners[])
{
	if (num == 0)
	{
		corners[0] = solvercube[1][2][2];
		corners[1] = solvercube[2][2][0];
		corners[2] = solvercube[5][0][0];
	}
	else if (num == 1)
	{
		corners[0] = solvercube[2][2][2];
		corners[1] = solvercube[3][2][0];
		corners[2] = solvercube[5][0][2];
	}
	else if (num == 2)
	{
		corners[0] = solvercube[3][2][2];
		corners[1] = solvercube[4][2][0];
		corners[2] = solvercube[5][2][2];
	}
	else if (num == 3)
	{
		corners[0] = solvercube[4][2][2];
		corners[1] = solvercube[1][2][0];
		corners[2] = solvercube[5][2][0];
	}
}

void positionBottomEdges(int cube[6][3][3], int oCube[6][3][3], int iCube[6][3][3])
{
	int pos = numEdgesInCorrectPos();
    
	if (pos == 0)
	{
		rotateEdges(2, true, cube, oCube, iCube);
		positionBottomEdges(cube, oCube, iCube);
		return;
	}
	else if (pos == 5)
	{
		return;
	}
	else
	{
		bool clockwise = pos > 0;
        
		int face = abs(pos) + 1;
        
		if (face > 4)
		{
			face = face - 4;
		}
        
		rotateEdges(face, clockwise, cube, oCube, iCube);
		return;
	}
}

int numEdgesInCorrectPos()
{
	//Note this will either be 1, 0 or 4...
	//It will return 0 if none are in correct position
	//If there is one in correct position it will return the corresponding position pos or neg determining rotation
	//Note positions are determined by what side they match with, 1 - 4
	//Return 5 if all are in position
    
	int edges[4][2] = { { solvercube[5][1][0], solvercube[1][2][1] }, { solvercube[5][0][1], solvercube[2][2][1] }, { solvercube[5][1][2], solvercube[3][2][1] }, { solvercube[5][2][1], solvercube[4][2][1] } };
    
	int correctPos = -1;
	int numCorrect = 0;
	bool isOneCorrect = false;
	int positions[4];
    
	for (int i = 1; i <= 4; i++)
	{
		for (int j = 0; j < 2; j++)
		{
			if (edges[i - 1][j] == i)
			{
				isOneCorrect = true;
				correctPos = i - 1;
				numCorrect++;
			}
            
			if (edges[i - 1][j] != 5)
			{
				positions[i - 1] = edges[i - 1][j];
			}
		}
	}
    
	if (numCorrect == 4)
	{
		return 5;
	}
    
	if (isOneCorrect == false)
	{
		return 0;
	}
	else
	{
		bool clockwise = false;
		bool firstTime = true;
		int numTimesThrough = 0;
		numCorrect = 0;
		int temp;
		int temp2;
        
		while (numCorrect != 4)
		{
			firstTime = true;
			numCorrect = 0;
			for (int i = 0; i < 4; i++)
			{
				if (i != correctPos)
				{
					if (firstTime)
					{
						firstTime = false;
						temp = positions[i];
                        
						int j = i - 1;
                        
						if (j < 0)
						{
							j = 4 + j;
						}
                        
						if (j == correctPos)
						{
							j--;
							if (j < 0)
							{
								j = 4 + j;
							}
						}
                        
						positions[i] = positions[j];
					}
					else
					{
						temp2 = positions[i];
						positions[i] = temp;
						temp = temp2;
					}
				}
                
				if (positions[i] == i + 1)
				{
					numCorrect++;
				}
			}
            
			numTimesThrough++;
		}
        
		clockwise = numTimesThrough == 1;
		correctPos++;
        
		if (clockwise == false)
		{
			correctPos = -1 * (correctPos);
		}
	}
    
	return correctPos;
}

void rotateEdges(int face, bool rotClockwise, int cube[6][3][3], int oCube[6][3][3], int iCube[6][3][3])
{
	if (face == 1)
	{
		if (rotClockwise == true)
		{
			f(cube, oCube, iCube);
			f(cube, oCube, iCube);
			d(cube, oCube, iCube);
			li(cube, oCube, iCube);
			r(cube, oCube, iCube);
			f(cube, oCube, iCube);
			f(cube, oCube, iCube);
			l(cube, oCube, iCube);
			ri(cube, oCube, iCube);
			d(cube, oCube, iCube);
			f(cube, oCube, iCube);
			f(cube, oCube, iCube);
		}
		else
		{
			f(cube, oCube, iCube);
			f(cube, oCube, iCube);
			di(cube, oCube, iCube);
			li(cube, oCube, iCube);
			r(cube, oCube, iCube);
			f(cube, oCube, iCube);
			f(cube, oCube, iCube);
			l(cube, oCube, iCube);
			ri(cube, oCube, iCube);
			di(cube, oCube, iCube);
			f(cube, oCube, iCube);
			f(cube, oCube, iCube);
		}
	}
	else if (face == 2)
	{
		if (rotClockwise == true)
		{
			r(cube, oCube, iCube);
			r(cube, oCube, iCube);
			d(cube, oCube, iCube);
			fi(cube, oCube, iCube);
			b(cube, oCube, iCube);
			r(cube, oCube, iCube);
			r(cube, oCube, iCube);
			f(cube, oCube, iCube);
			bi(cube, oCube, iCube);
			d(cube, oCube, iCube);
			r(cube, oCube, iCube);
			r(cube, oCube, iCube);
		}
		else
		{
			r(cube, oCube, iCube);
			r(cube, oCube, iCube);
			di(cube, oCube, iCube);
			fi(cube, oCube, iCube);
			b(cube, oCube, iCube);
			r(cube, oCube, iCube);
			r(cube, oCube, iCube);
			f(cube, oCube, iCube);
			bi(cube, oCube, iCube);
			di(cube, oCube, iCube);
			r(cube, oCube, iCube);
			r(cube, oCube, iCube);
		}
	}
	else if (face == 3)
	{
		if (rotClockwise == true)
		{
			b(cube, oCube, iCube);
			b(cube, oCube, iCube);
			d(cube, oCube, iCube);
			ri(cube, oCube, iCube);
			l(cube, oCube, iCube);
			b(cube, oCube, iCube);
			b(cube, oCube, iCube);
			r(cube, oCube, iCube);
			li(cube, oCube, iCube);
			d(cube, oCube, iCube);
			b(cube, oCube, iCube);
			b(cube, oCube, iCube);
		}
		else
		{
			b(cube, oCube, iCube);
			b(cube, oCube, iCube);
			di(cube, oCube, iCube);
			ri(cube, oCube, iCube);
			l(cube, oCube, iCube);
			b(cube, oCube, iCube);
			b(cube, oCube, iCube);
			r(cube, oCube, iCube);
			li(cube, oCube, iCube);
			di(cube, oCube, iCube);
			b(cube, oCube, iCube);
			b(cube, oCube, iCube);
		}
	}
	else if (face == 4)
	{
		if (rotClockwise == true)
		{
			l(cube, oCube, iCube);
			l(cube, oCube, iCube);
			d(cube, oCube, iCube);
			bi(cube, oCube, iCube);
			f(cube, oCube, iCube);
			l(cube, oCube, iCube);
			l(cube, oCube, iCube);
			b(cube, oCube, iCube);
			fi(cube, oCube, iCube);
			d(cube, oCube, iCube);
			l(cube, oCube, iCube);
			l(cube, oCube, iCube);
		}
		else
		{
			l(cube, oCube, iCube);
			l(cube, oCube, iCube);
			di(cube, oCube, iCube);
			bi(cube, oCube, iCube);
			f(cube, oCube, iCube);
			l(cube, oCube, iCube);
			l(cube, oCube, iCube);
			b(cube, oCube, iCube);
			fi(cube, oCube, iCube);
			di(cube, oCube, iCube);
			l(cube, oCube, iCube);
			l(cube, oCube, iCube);
		}
	}
}

void correctBottomCorners(int cube[6][3][3], int oCube[6][3][3], int iCube[6][3][3])
{
	int result = cornerOrientation();
    
	while (result != 5)
	{
		twoCornerRotate(abs(findBestFace(result)), *findBestFace > 0, cube, oCube, iCube);
        
		result = cornerOrientation();
	}
}

int cornerOrientation()
{
	int numCorrect = 0;
	int wrongPosition = 0;
    
	int corners[4] = { solvercube[5][0][0], solvercube[5][0][2], solvercube[5][2][2], solvercube[5][2][0] };
    
	for (int i = 0; i < 4; i++)
	{
		if (corners[i] == 5)
		{
			numCorrect++;
		}
		else
		{
			wrongPosition = i;
		}
	}
    
	if (numCorrect == 4)
	{
		return 5;
	}
    
	return wrongPosition;
}

int findBestFace(int cornerNum)
{
	int corners[4] = { solvercube[5][0][0], solvercube[5][0][2], solvercube[5][2][2], solvercube[5][2][0] };
    
	int corner1 = cornerNum + 1;
	int corner2 = cornerNum - 1;
    
	if (corner1 > 3)
	{
		corner1 = 4 - corner1;
	}
    
	if (corner2 < 0)
	{
		corner2 = 4 + corner2;
	}
    
	//First Determine which corner to go with
	int finalCorner = -1;
	int face = -1;
    
	if (corners[cornerNum] == corners[corner1])
	{
		finalCorner = corner1;
        
		face = corners[finalCorner] + 1;
        
		if (face > 4)
		{
			face = face - 4;
		}
        
		return face;
	}
	else if (corners[cornerNum] == corners[corner2])
	{
		finalCorner = corner2;
        
		face = corners[finalCorner] + 1;
        
		if (face > 4)
		{
			face = face - 4;
		}
        
		return face;
	}
	else if (abs(corners[cornerNum] - corners[corner1]) == 2 && corners[corner1] != 5)
	{
		finalCorner = corner1;
		face = corners[finalCorner];
		return -face;
	}
	else if (abs(corners[cornerNum] - corners[corner2]) == 2 && corners[corner2] != 5)
	{
		finalCorner = corner2;
		face = corners[cornerNum];
		return -face;
	}
	else
	{
		face = corners[cornerNum];
		return face;
	}
}

void twoCornerRotate(int face, bool goForward, int cube[6][3][3], int oCube[6][3][3], int iCube[6][3][3])
{
	if (face == 1)
	{
		if (goForward == true)
		{
			bi(cube, oCube, iCube);
			u(cube, oCube, iCube);
			b(cube, oCube, iCube);
			l(cube, oCube, iCube);
			u(cube, oCube, iCube);
			li(cube, oCube, iCube);
			d(cube, oCube, iCube);
			l(cube, oCube, iCube);
			ui(cube, oCube, iCube);
			li(cube, oCube, iCube);
			bi(cube, oCube, iCube);
			ui(cube, oCube, iCube);
			b(cube, oCube, iCube);
			di(cube, oCube, iCube);
		}
		else
		{
			d(cube, oCube, iCube);
			bi(cube, oCube, iCube);
			u(cube, oCube, iCube);
			b(cube, oCube, iCube);
			l(cube, oCube, iCube);
			u(cube, oCube, iCube);
			li(cube, oCube, iCube);
			di(cube, oCube, iCube);
			l(cube, oCube, iCube);
			ui(cube, oCube, iCube);
			li(cube, oCube, iCube);
			bi(cube, oCube, iCube);
			ui(cube, oCube, iCube);
			b(cube, oCube, iCube);
		}
	}
	else if (face == 2)
	{
		if (goForward == true)
		{
			li(cube, oCube, iCube);
			u(cube, oCube, iCube);
			l(cube, oCube, iCube);
			f(cube, oCube, iCube);
			u(cube, oCube, iCube);
			fi(cube, oCube, iCube);
			d(cube, oCube, iCube);
			f(cube, oCube, iCube);
			ui(cube, oCube, iCube);
			fi(cube, oCube, iCube);
			li(cube, oCube, iCube);
			ui(cube, oCube, iCube);
			l(cube, oCube, iCube);
			di(cube, oCube, iCube);
		}
		else
		{
			d(cube, oCube, iCube);
			li(cube, oCube, iCube);
			u(cube, oCube, iCube);
			l(cube, oCube, iCube);
			f(cube, oCube, iCube);
			u(cube, oCube, iCube);
			fi(cube, oCube, iCube);
			di(cube, oCube, iCube);
			f(cube, oCube, iCube);
			ui(cube, oCube, iCube);
			fi(cube, oCube, iCube);
			li(cube, oCube, iCube);
			ui(cube, oCube, iCube);
			l(cube, oCube, iCube);
		}
	}
	else if (face == 3)
	{
		if (goForward == true)
		{
			fi(cube, oCube, iCube);
			u(cube, oCube, iCube);
			f(cube, oCube, iCube);
			r(cube, oCube, iCube);
			u(cube, oCube, iCube);
			ri(cube, oCube, iCube);
			d(cube, oCube, iCube);
			r(cube, oCube, iCube);
			ui(cube, oCube, iCube);
			ri(cube, oCube, iCube);
			fi(cube, oCube, iCube);
			ui(cube, oCube, iCube);
			f(cube, oCube, iCube);
			di(cube, oCube, iCube);
		}
		else
		{
			d(cube, oCube, iCube);
			fi(cube, oCube, iCube);
			u(cube, oCube, iCube);
			f(cube, oCube, iCube);
			r(cube, oCube, iCube);
			u(cube, oCube, iCube);
			ri(cube, oCube, iCube);
			di(cube, oCube, iCube);
			r(cube, oCube, iCube);
			ui(cube, oCube, iCube);
			ri(cube, oCube, iCube);
			fi(cube, oCube, iCube);
			ui(cube, oCube, iCube);
			f(cube, oCube, iCube);
		}
	}
	else if (face == 4)
	{
		if (goForward == true)
		{
			ri(cube, oCube, iCube);
			u(cube, oCube, iCube);
			r(cube, oCube, iCube);
			b(cube, oCube, iCube);
			u(cube, oCube, iCube);
			bi(cube, oCube, iCube);
			d(cube, oCube, iCube);
			b(cube, oCube, iCube);
			ui(cube, oCube, iCube);
			bi(cube, oCube, iCube);
			ri(cube, oCube, iCube);
			ui(cube, oCube, iCube);
			r(cube, oCube, iCube);
			di(cube, oCube, iCube);
		}
		else
		{
			d(cube, oCube, iCube);
			ri(cube, oCube, iCube);
			u(cube, oCube, iCube);
			r(cube, oCube, iCube);
			b(cube, oCube, iCube);
			u(cube, oCube, iCube);
			bi(cube, oCube, iCube);
			di(cube, oCube, iCube);
			b(cube, oCube, iCube);
			ui(cube, oCube, iCube);
			bi(cube, oCube, iCube);
			ri(cube, oCube, iCube);
			ui(cube, oCube, iCube);
			r(cube, oCube, iCube);
		}
	}
}

void correctBottomEdges(int cube[6][3][3], int oCube[6][3][3], int iCube[6][3][3])
{
	int edges[4] = { solvercube[5][1][0], solvercube[5][0][1], solvercube[5][1][2], solvercube[5][2][1] };
    
	bool isTogether = false;
	bool isStart = false;
	int numWrong = 0;
	int pos1 = -1;
	int pos2 = -1;
	int j = 0;
    
	for (int i = 0; i < 5; i++)
	{
		j = i;
        
		if (i == 4)
		{
			j = 0;
		}
        
		if (edges[j] != 5)
		{
			numWrong++;
			if (isStart == false)
			{
				pos1 = j;
				isStart = true;
			}
			else
			{
				pos2 = j;
				isTogether = true;
			}
		}
		else
		{
			isStart = false;
		}
	}
    
	if (numWrong >= 4)
	{
		twoEdgeRotate(1, false, cube, oCube, iCube);
		twoEdgeRotate(2, false, cube, oCube, iCube);
		return;
	}
	else
	{
		if(pos2 != -1)
		{
			twoEdgeRotate(pos2 + 1, isTogether, cube, oCube, iCube);
		}
		else
		{
			twoEdgeRotate(pos1 + 1, isTogether, cube, oCube, iCube);
		}
		return;
	}
}

void twoEdgeRotate(int face, bool isNextTo, int cube[6][3][3], int oCube[6][3][3], int iCube[6][3][3])
{
	if (face == 1)
	{
		if (isNextTo == true)
		{
			l(cube, oCube, iCube);
			ui(cube, oCube, iCube);
			d(cube, oCube, iCube);
			f(cube, oCube, iCube);
			f(cube, oCube, iCube);
			d(cube, oCube, iCube);
			d(cube, oCube, iCube);
			u(cube, oCube, iCube);
			u(cube, oCube, iCube);
			b(cube, oCube, iCube);
			d(cube, oCube, iCube);
			bi(cube, oCube, iCube);
			u(cube, oCube, iCube);
			u(cube, oCube, iCube);
			d(cube, oCube, iCube);
			d(cube, oCube, iCube);
			f(cube, oCube, iCube);
			f(cube, oCube, iCube);
			di(cube, oCube, iCube);
			u(cube, oCube, iCube);
			li(cube, oCube, iCube);
			di(cube, oCube, iCube);
		}
		else
		{
			l(cube, oCube, iCube);
			ui(cube, oCube, iCube);
			d(cube, oCube, iCube);
			f(cube, oCube, iCube);
			f(cube, oCube, iCube);
			d(cube, oCube, iCube);
			d(cube, oCube, iCube);
			u(cube, oCube, iCube);
			u(cube, oCube, iCube);
			b(cube, oCube, iCube);
			d(cube, oCube, iCube);
			d(cube, oCube, iCube);
			bi(cube, oCube, iCube);
			u(cube, oCube, iCube);
			u(cube, oCube, iCube);
			d(cube, oCube, iCube);
			d(cube, oCube, iCube);
			f(cube, oCube, iCube);
			f(cube, oCube, iCube);
			di(cube, oCube, iCube);
			u(cube, oCube, iCube);
			li(cube, oCube, iCube);
			di(cube, oCube, iCube);
			di(cube, oCube, iCube);
		}
	}
	else if (face == 2)
	{
		if (isNextTo == true)
		{
			f(cube, oCube, iCube);
			ui(cube, oCube, iCube);
			d(cube, oCube, iCube);
			r(cube, oCube, iCube);
			r(cube, oCube, iCube);
			d(cube, oCube, iCube);
			d(cube, oCube, iCube);
			u(cube, oCube, iCube);
			u(cube, oCube, iCube);
			l(cube, oCube, iCube);
			d(cube, oCube, iCube);
			li(cube, oCube, iCube);
			u(cube, oCube, iCube);
			u(cube, oCube, iCube);
			d(cube, oCube, iCube);
			d(cube, oCube, iCube);
			r(cube, oCube, iCube);
			r(cube, oCube, iCube);
			di(cube, oCube, iCube);
			u(cube, oCube, iCube);
			fi(cube, oCube, iCube);
			di(cube, oCube, iCube);
		}
		else
		{
			f(cube, oCube, iCube);
			ui(cube, oCube, iCube);
			d(cube, oCube, iCube);
			r(cube, oCube, iCube);
			r(cube, oCube, iCube);
			d(cube, oCube, iCube);
			d(cube, oCube, iCube);
			u(cube, oCube, iCube);
			u(cube, oCube, iCube);
			l(cube, oCube, iCube);
			d(cube, oCube, iCube);
			d(cube, oCube, iCube);
			li(cube, oCube, iCube);
			u(cube, oCube, iCube);
			u(cube, oCube, iCube);
			d(cube, oCube, iCube);
			d(cube, oCube, iCube);
			r(cube, oCube, iCube);
			r(cube, oCube, iCube);
			di(cube, oCube, iCube);
			u(cube, oCube, iCube);
			fi(cube, oCube, iCube);
			di(cube, oCube, iCube);
			di(cube, oCube, iCube);
		}
	}
	else if (face == 3)
	{
		if (isNextTo == true)
		{
			r(cube, oCube, iCube);
			ui(cube, oCube, iCube);
			d(cube, oCube, iCube);
			b(cube, oCube, iCube);
			b(cube, oCube, iCube);
			d(cube, oCube, iCube);
			d(cube, oCube, iCube);
			u(cube, oCube, iCube);
			u(cube, oCube, iCube);
			f(cube, oCube, iCube);
			d(cube, oCube, iCube);
			fi(cube, oCube, iCube);
			u(cube, oCube, iCube);
			u(cube, oCube, iCube);
			d(cube, oCube, iCube);
			d(cube, oCube, iCube);
			b(cube, oCube, iCube);
			b(cube, oCube, iCube);
			di(cube, oCube, iCube);
			u(cube, oCube, iCube);
			ri(cube, oCube, iCube);
			di(cube, oCube, iCube);
		}
		else
		{
			r(cube, oCube, iCube);
			ui(cube, oCube, iCube);
			d(cube, oCube, iCube);
			b(cube, oCube, iCube);
			b(cube, oCube, iCube);
			d(cube, oCube, iCube);
			d(cube, oCube, iCube);
			u(cube, oCube, iCube);
			u(cube, oCube, iCube);
			f(cube, oCube, iCube);
			d(cube, oCube, iCube);
			d(cube, oCube, iCube);
			fi(cube, oCube, iCube);
			u(cube, oCube, iCube);
			u(cube, oCube, iCube);
			d(cube, oCube, iCube);
			d(cube, oCube, iCube);
			b(cube, oCube, iCube);
			b(cube, oCube, iCube);
			di(cube, oCube, iCube);
			u(cube, oCube, iCube);
			ri(cube, oCube, iCube);
			di(cube, oCube, iCube);
			di(cube, oCube, iCube);
		}
	}
	else if (face == 4)
	{
		if (isNextTo == true)
		{
			b(cube, oCube, iCube);
			ui(cube, oCube, iCube);
			d(cube, oCube, iCube);
			l(cube, oCube, iCube);
			l(cube, oCube, iCube);
			d(cube, oCube, iCube);
			d(cube, oCube, iCube);
			u(cube, oCube, iCube);
			u(cube, oCube, iCube);
			r(cube, oCube, iCube);
			d(cube, oCube, iCube);
			ri(cube, oCube, iCube);
			u(cube, oCube, iCube);
			u(cube, oCube, iCube);
			d(cube, oCube, iCube);
			d(cube, oCube, iCube);
			l(cube, oCube, iCube);
			l(cube, oCube, iCube);
			di(cube, oCube, iCube);
			u(cube, oCube, iCube);
			bi(cube, oCube, iCube);
			di(cube, oCube, iCube);
		}
		else
		{
			b(cube, oCube, iCube);
			ui(cube, oCube, iCube);
			d(cube, oCube, iCube);
			l(cube, oCube, iCube);
			l(cube, oCube, iCube);
			d(cube, oCube, iCube);
			d(cube, oCube, iCube);
			u(cube, oCube, iCube);
			u(cube, oCube, iCube);
			r(cube, oCube, iCube);
			d(cube, oCube, iCube);
			d(cube, oCube, iCube);
			ri(cube, oCube, iCube);
			u(cube, oCube, iCube);
			u(cube, oCube, iCube);
			d(cube, oCube, iCube);
			d(cube, oCube, iCube);
			l(cube, oCube, iCube);
			l(cube, oCube, iCube);
			di(cube, oCube, iCube);
			u(cube, oCube, iCube);
			bi(cube, oCube, iCube);
			di(cube, oCube, iCube);
			di(cube, oCube, iCube);
		}
	}
}

void copyCube(int copyofcube[6][3][3])
{
	for (int i = 0; i < 6; i++)
	{
		for (int j = 0; j < 3; j++)
		{
			for (int k = 0; k < 3; k++)
			{
				old[i][j][k] = copyofcube[i][j][k];
			}
		}
	}
}

void print(int printcube[6][3][3])
{

	for(int i=0;i<3;i++)
	{
		cout<<"          "<<printcube[0][i][0]<<"  "<<printcube[0][i][1]<<"  "<<printcube[0][i][2]<<endl<<endl;
	}
	for(int i=0;i<3;i++)
	{
		cout<<printcube[1][i][0]<<"  "<<printcube[1][i][1]<<"  "<<printcube[1][i][2]<<"   ";
		cout<<printcube[2][i][0]<<"  "<<printcube[2][i][1]<<"  "<<printcube[2][i][2]<<"   ";
		cout<<printcube[3][i][0]<<"  "<<printcube[3][i][1]<<"  "<<printcube[3][i][2]<<"   ";
		cout<<printcube[4][i][0]<<"  "<<printcube[4][i][1]<<"  "<<printcube[4][i][2]<<"   "<<endl<<endl;
	}
	for(int i=0;i<3;i++)
	{
		cout<<endl<<"          "<<printcube[5][i][0]<<"  "<<printcube[5][i][1]<<"  "<<printcube[5][i][2]<<endl;
	}	
	cout<<endl<<endl;

/*
	for (int i = 0; i < 6; i++)
	{
		for (int j = 0; j < 3; j++)
		{
			for (int k = 0; k < 3; k++)
			{
				cout << printcube[i][j][k];
			}
			cout << endl;
		}
		cout << endl;
	}
*/

}
/*
string printColor(int field)
{
		
    string RESET = "\033[0m";
	string WHITE = "\033[107m";      // White 
	string RED = "\033[101m";      // Red 
	string GREEN = "\033[102m";      // Green 
	string BLUE = "\e[48;5;21m";      // Blue 
	string ORANGE = "\e[48;5;208m";      /// Magenta 
	string YELLOW = "\033[103m";      /// Yellow 
    string BLACK = "\033[40m"; 
				
	string printcolor;
	switch(field){
        case 6:
			printcolor = BLACK + "  " + RESET;		
			break;
		case 5: 
			printcolor = WHITE + "  " + RESET;		
			break;		
		case 3:
			printcolor = RED + "  " + RESET;					
			break;
		case 4: 
			printcolor = GREEN + "  " + RESET;					
			break;
		case 2:
			printcolor = BLUE + "  " + RESET;									
			break;
		case 1: 				
			printcolor = ORANGE + "  " + RESET;					
			break;			
		case 0: 
			printcolor = YELLOW + "  " + RESET;								
			break;				
	}
	return printcolor;
}

void printCubeColor(int cube_array[6][3][3])
{ 

    //cout<<"PRINTING CUSTOM CUBE"<<endl;
	for(int i=0;i<3;i++)
	{
		cout<<"       "<<printColor(cube_array[0][i][0])<<printColor(cube_array[0][i][1])<<printColor(cube_array[0][i][2])<<endl;
	}
	for(int i=0;i<3;i++)
	{
		cout<<printColor(cube_array[1][i][0])<<printColor(cube_array[1][i][1])<<printColor(cube_array[1][i][2])<<" ";
		cout<<printColor(cube_array[2][i][0])<<printColor(cube_array[2][i][1])<<printColor(cube_array[2][i][2])<<" ";
		cout<<printColor(cube_array[3][i][0])<<printColor(cube_array[3][i][1])<<printColor(cube_array[3][i][2])<<" ";
		cout<<printColor(cube_array[4][i][0])<<printColor(cube_array[4][i][1])<<printColor(cube_array[4][i][2])<<" "<<endl;
	}
	for(int i=0;i<3;i++)
	{
		cout<<"       "<<printColor(cube_array[5][i][0])<<printColor(cube_array[5][i][1])<<printColor(cube_array[5][i][2])<<endl;
	}	
	cout<<endl<<endl;	
}
*/













string last()
{
	if (moves.size() < 3)
	{
		return "";
	}
	int s = moves.size();
	return moves.substr(s - 3, 3);
}

void removeLast()
{
	if (moves.size() < 3)
	{
		return;
	}
	int s = moves.size();
	moves = moves.substr(0, s - 3);
}

void clearMoves()
{
	moves = "";
}
/*
void scramble()
{
/*
cout << "r " ;
r(cube, oCube, iCube);
cout << "u " ;
u(cube, oCube, iCube);
cout << "l " ;
l(cube, oCube, iCube);
cout << "r " ;
r(cube, oCube, iCube);
cout << "ri " ;
ri(cube, oCube, iCube);
cout << "d " ;
d(cube, oCube, iCube);
*/
/*
	srand(time(NULL));
	for (int i = 0; i < 30; i++)
	{
		int num = rand(cube, oCube, iCube) % 12 + 1;
		switch (num)
		{
            case 1: r(cube, oCube, iCube); break;
            case 2: ri(cube, oCube, iCube); break;
            case 3: u(cube, oCube, iCube); break;
            case 4: ui(cube, oCube, iCube); break;
            case 5: f(cube, oCube, iCube); break;
            case 6: fi(cube, oCube, iCube); break;
            case 7: l(cube, oCube, iCube); break;
            case 8: li(cube, oCube, iCube); break;
            case 9: b(cube, oCube, iCube); break;
            case 10: bi(cube, oCube, iCube); break;
            case 11: d(cube, oCube, iCube); break;
            case 12: di(cube, oCube, iCube); break;
		}
	}

}

/*
void inputCube(){
    
    // generate black cube 
    {
    int i = 0;      
            for(int j = 0; j < 6; j++){    
                for(int k = 0; k < 3; k++){
                    for(int l = 0; l <3; l++){
                            solvercube[j][k][l] = 6;
                            //cout << solvercube[j][k][l]; 
                    }
                }
            }
    }
         printCubeColor(solvercube);   

    int cubesausage[54];
    cout << endl << "INPUT CUBE" << endl; 
    cout    << "y ... yellow" << endl 
            << "o ... orange" << endl
            << "b ... blue" << endl 
            << "r ... red " << endl
            << "g ... green" << endl 
            << "w ... white" << endl; 
    cout << "order: UP, LEFT, FRONT, RIGHT, BACK, DOWN" << endl; 

    {
        int i = 0;      
            for(int j = 0; j < 6; j++){    
                for(int k = 0; k < 3; k++){
                    for(int l = 0; l <3; l++){
                                    {

                                            char reader;
                                            cin >> reader;
                                                    switch(reader){
                                                        case 'y': 
                                                            cubesausage[i] = 0;
                                                            break;
                                                        case 'o': 
                                                            cubesausage[i] = 1;
                                                            break;
                                                        case 'b': 
                                                            cubesausage[i] = 2;
                                                            break;
                                                        case 'r': 
                                                            cubesausage[i] = 3;
                                                            break;
                                                        case 'g': 
                                                            cubesausage[i] = 4;
                                                            break;
                                                        case 'w': 
                                                            cubesausage[i] = 5;
                                                            break;
                                                        default: 
                                                            cout << "no valid input" << endl;

                                                    }           
                                            //cout << cubesausage[i] << endl; 
                                            cin.get();
                                                        
                                            solvercube[j][k][l] = cubesausage[i];
                                            i++;
                                            printCubeColor(solvercube);
                                 }
                }
            }
         }
    }
   
    //}

}
*/
void mapforsolver(int cube[6][3][3]){

            for(int j = 0; j < 6; j++){    
                for(int k = 0; k < 3; k++){
                    for(int l = 0; l <3; l++){
                            solvercube[j][k][l] = cube[j][k][l];
                            solvercube[j][k][l] += 10;
                    }
                }
            }
    
    for(int i = 0; i <6; i++){
    int changer = solvercube[i][1][1];
             for(int j = 0; j < 6; j++){    
                for(int k = 0; k < 3; k++){
                    for(int l = 0; l <3; l++){
                            if(solvercube[j][k][l] == changer)
                                solvercube[j][k][l]=i;
                                lookup[i]=changer-10;
                    }
                }
            }       
      }
     // printCubeColor(cube);   

     //printCubeColor(solvercube);           

}


void translateMove() //in TPCEchoClient aufrufen
{
	int cnt=1;
    movesTranslated = "r";	

	/*for(int i =0; i<moves.size();i++)
		cout<<moves[i];
	
	cout<<endl;*///Test
	
	for(int i =0; i<moves.size();i++)
	{
		if(cnt!=3 && moves[i]==' ')
		{
			movesTranslated+='1';
		}
		
		else
		{
			switch(moves[i]){
					case 'u': movesTranslated+='0'; break;
					case 'l': movesTranslated+='1'; break;
					case 'f': movesTranslated+='2'; break;
					case 'r': movesTranslated+='3'; break;
					case 'b': movesTranslated+='4'; break;
					case 'd': movesTranslated+='5'; break;
					case '2': movesTranslated+='2'; break;
					case 'i': movesTranslated+='3'; break;
					
					default: break;
				}
		}
		if(cnt==3)
			cnt=1;

		else
			cnt++;
		
	}
		/*for(int i =0; i<movesTranslated.size();i++)
			cout<<movesTranslated[i];

	cout<<endl; *///test
}

//// mapt die Farben des cubes für den solver auf die Farben des tatsächlichen Wüfel für die Ausgabe
/*
void mapforcustomcolor(cube, oCube, iCube){
    
            for(int j = 0; j < 6; j++){    
                for(int k = 0; k < 3; k++){
                    for(int l = 0; l <3; l++){
                            cube[j][k][l] = lookup[solvercube[j][k][l]];
                    }
                }
            }

}
*/
/*
void cubestring2cube(int stringarray[54]){

int i = 0; 
            for(int j = 0; j < 6; j++){    
                for(int k = 0; k < 3; k++){
                    for(int l = 0; l <3; l++){
                            cube[j][k][l] = stringarray[i];
                            i++;
                    }
                }
            }


}
*/


#endif
