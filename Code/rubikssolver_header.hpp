//#include "stdafx.h"
#include <iostream>
#include <stdlib.h>
#include <string>
#include <cmath>
#include <time.h>
#include <stdio.h>
using namespace std;

void r();
void ri();

void l();
void li();

void u();
void ui();

void d();
void di();

void f();
void fi();

void b();
void bi();

void copyCube();
void print();

void solveTopCross();
void findNextTopEdge(int & s, int & p);
void moveTopEdges();

void solveTopCorners();
void findNextTopCorner(int & s, int & p);
void moveTopCorners();

void scramble();
void solveMiddleLayer();
int findBottomMatch(int color);
void placeMiddleEdge(int color, int edgeSide);
void middleAlgorithm(int color, int direction);

string last(); //gets the last move performed
void removeLast(); //removes the last move performed
void clearMoves(); //clears all moves


void printCubeColor();
void solveBottomLayer();
void positionBottomCorners();
int numCorrectCorners();
void getCorner(int num, int corners[]);
void swapCorners(int face);
void positionBottomEdges();
int numEdgesInCorrectPos();
void rotateEdges(int face, bool rotClockwise);
void correctBottomCorners();
int cornerOrientation();
int findBestFace(int cornerNum);
void twoCornerRotate(int face, bool goForward);
void correctBottomEdges();
void twoEdgeRotate(int face, bool isNextTo);

/*
 int cube[6][3][3] = {
 { {2, 2, 5}, {0, 0, 0}, {4, 4, 2} }, //yellow side
 { {5, 1, 5}, {2, 1, 1}, {2, 2, 4} }, //orange side
 { {1, 5, 0}, {5, 2, 2}, {5, 5, 1} }, //blue side
 { {1, 4, 3}, {5, 3, 4}, {4, 4, 3} }, //red side
 { {2, 3, 1}, {3, 4, 0}, {0, 3, 3} }, //green side
 { {3, 3, 0}, {1, 5, 1}, {0, 0, 4} } }; //white side
 */

extern int cube[6][3][3];

int old[6][3][3] = {
	{ { 0, 0, 0 }, { 0, 0, 0 }, { 0, 0, 0 } }, //yellow side
	{ { 1, 1, 1 }, { 1, 1, 1 }, { 1, 1, 1 } }, //orange side
	{ { 2, 2, 2 }, { 2, 2, 2 }, { 2, 2, 2 } }, //blue side
	{ { 3, 3, 3 }, { 3, 3, 3 }, { 3, 3, 3 } }, //red side
	{ { 4, 4, 4 }, { 4, 4, 4 }, { 4, 4, 4 } }, //green side
};
/*
int cube[6][3][3] = {
	{ { 0, 0, 0 }, { 0, 0, 0 }, { 0, 0, 0 } }, //yellow side
	{ { 1, 1, 1 }, { 1, 1, 1 }, { 1, 1, 1 } }, //orange side
	{ { 2, 2, 2 }, { 2, 2, 2 }, { 2, 2, 2 } }, //blue side
	{ { 3, 3, 3 }, { 3, 3, 3 }, { 3, 3, 3 } }, //red side
	{ { 4, 4, 4 }, { 4, 4, 4 }, { 4, 4, 4 } }, //green side
	{ { 5, 5, 5 }, { 5, 5, 5 }, { 5, 5, 5 } } }; //white side
*/
/*
int cube[6][3][3] = {
	{ { 5, 0, 4 }, { 2, 0, 5 }, { 1, 3, 2 } }, //yellow side
	{ { 1, 0, 2 }, { 0, 1, 3 }, { 5, 5, 4 } }, //orange side
	{ { 5, 0, 3 }, { 2, 2, 3 }, { 5, 1, 2 } }, //blue side
	{ { 0, 4, 1 }, { 4, 3, 1 }, { 5, 5, 3 } }, //red side
	{ { 0, 3, 4 }, { 2, 4, 1 }, { 0, 4, 3 } }, //green side
	{ { 3, 4, 1 }, { 2, 5, 1 }, { 2, 0, 4 } } }; //white side

*/
string moves = "";



void r()
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
    
	copyCube();
	for (int i = 0; i < 3; i++)
	{
		cube[2][i][2] = old[5][i][2];
		cube[0][i][2] = old[2][i][2];
		cube[4][i][0] = old[0][2 - i][2];
		cube[5][i][2] = old[4][2 - i][0];
	}
	cube[3][0][2] = old[3][0][0];
	cube[3][2][2] = old[3][0][2];
	cube[3][2][0] = old[3][2][2];
	cube[3][0][0] = old[3][2][0];
    
	cube[3][1][2] = old[3][0][1];
	cube[3][2][1] = old[3][1][2];
	cube[3][1][0] = old[3][2][1];
	cube[3][0][1] = old[3][1][0];
}

void ri()
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
	copyCube();
	for (int i = 0; i < 3; i++)
	{
		cube[5][i][2] = old[2][i][2];
		cube[2][i][2] = old[0][i][2];
		cube[0][2 - i][2] = old[4][i][0];
		cube[4][2 - i][0] = old[5][i][2];
	}
	cube[3][0][0] = old[3][0][2];
	cube[3][0][2] = old[3][2][2];
	cube[3][2][2] = old[3][2][0];
	cube[3][2][0] = old[3][0][0];
    
	cube[3][0][1] = old[3][1][2];
	cube[3][1][2] = old[3][2][1];
	cube[3][2][1] = old[3][1][0];
	cube[3][1][0] = old[3][0][1];
}

void l()
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
	copyCube();
	for (int i = 0; i < 3; i++)
	{
		cube[5][i][0] = old[2][i][0];
		cube[2][i][0] = old[0][i][0];
		cube[0][i][0] = old[4][2 - i][2];
		cube[4][2 - i][2] = old[5][i][0];
	}
	cube[1][0][2] = old[1][0][0];
	cube[1][2][2] = old[1][0][2];
	cube[1][2][0] = old[1][2][2];
	cube[1][0][0] = old[1][2][0];
    
	cube[1][1][2] = old[1][0][1];
	cube[1][2][1] = old[1][1][2];
	cube[1][1][0] = old[1][2][1];
	cube[1][0][1] = old[1][1][0];
}

void li()
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
	copyCube();
	for (int i = 0; i < 3; i++)
	{
		cube[2][i][0] = old[5][i][0];
		cube[0][i][0] = old[2][i][0];
		cube[4][i][2] = old[0][2 - i][0];
		cube[5][i][0] = old[4][2 - i][2];
	}
	cube[1][0][0] = old[1][0][2];
	cube[1][0][2] = old[1][2][2];
	cube[1][2][2] = old[1][2][0];
	cube[1][2][0] = old[1][0][0];
    
	cube[1][0][1] = old[1][1][2];
	cube[1][1][2] = old[1][2][1];
	cube[1][2][1] = old[1][1][0];
	cube[1][1][0] = old[1][0][1];
}

void u()
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
    
	copyCube();
	for (int i = 0; i < 3; i++)
	{
		cube[1][0][i] = old[2][0][i];
		cube[4][0][i] = old[1][0][i];
		cube[3][0][i] = old[4][0][i];
		cube[2][0][i] = old[3][0][i];
	}
	cube[0][0][0] = old[0][2][0];
	cube[0][0][2] = old[0][0][0];
	cube[0][2][2] = old[0][0][2];
	cube[0][2][0] = old[0][2][2];
    
	cube[0][0][1] = old[0][1][0];
	cube[0][1][2] = old[0][0][1];
	cube[0][2][1] = old[0][1][2];
	cube[0][1][0] = old[0][2][1];
}

void ui()
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
	copyCube();
	for (int i = 0; i < 3; i++)
	{
		cube[2][0][i] = old[1][0][i];
		cube[1][0][i] = old[4][0][i];
		cube[4][0][i] = old[3][0][i];
		cube[3][0][i] = old[2][0][i];
	}
	cube[0][2][0] = old[0][0][0];
	cube[0][0][0] = old[0][0][2];
	cube[0][0][2] = old[0][2][2];
	cube[0][2][2] = old[0][2][0];
    
	cube[0][1][0] = old[0][0][1];
	cube[0][0][1] = old[0][1][2];
	cube[0][1][2] = old[0][2][1];
	cube[0][2][1] = old[0][1][0];
}

void d()
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
	copyCube();
	for (int i = 0; i < 3; i++)
	{
		cube[2][2][i] = old[1][2][i];
		cube[1][2][i] = old[4][2][i];
		cube[4][2][i] = old[3][2][i];
		cube[3][2][i] = old[2][2][i];
	}
	cube[5][0][0] = old[5][2][0];
	cube[5][0][2] = old[5][0][0];
	cube[5][2][2] = old[5][0][2];
	cube[5][2][0] = old[5][2][2];
    
	cube[5][0][1] = old[5][1][0];
	cube[5][1][2] = old[5][0][1];
	cube[5][2][1] = old[5][1][2];
	cube[5][1][0] = old[5][2][1];
}

void di()
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
	copyCube();
	for (int i = 0; i < 3; i++)
	{
		cube[1][2][i] = old[2][2][i];
		cube[4][2][i] = old[1][2][i];
		cube[3][2][i] = old[4][2][i];
		cube[2][2][i] = old[3][2][i];
	}
	cube[5][2][0] = old[5][0][0];
	cube[5][0][0] = old[5][0][2];
	cube[5][0][2] = old[5][2][2];
	cube[5][2][2] = old[5][2][0];
    
	cube[5][1][0] = old[5][0][1];
	cube[5][0][1] = old[5][1][2];
	cube[5][1][2] = old[5][2][1];
	cube[5][2][1] = old[5][1][0];
}

void f()
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
	copyCube();
	for (int i = 0; i < 3; i++)
	{
		cube[0][2][i] = old[1][2 - i][2];
		cube[3][i][0] = old[0][2][i];
		cube[5][0][2 - i] = old[3][i][0];
		cube[1][2 - i][2] = old[5][0][2 - i];
	}
	cube[2][0][2] = old[2][0][0];
	cube[2][2][2] = old[2][0][2];
	cube[2][2][0] = old[2][2][2];
	cube[2][0][0] = old[2][2][0];
    
	cube[2][1][2] = old[2][0][1];
	cube[2][2][1] = old[2][1][2];
	cube[2][1][0] = old[2][2][1];
	cube[2][0][1] = old[2][1][0];
}

void fi()
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
	copyCube();
	for (int i = 0; i < 3; i++)
	{
		cube[1][i][2] = old[0][2][2 - i];
		cube[0][2][2 - i] = old[3][2 - i][0];
		cube[3][2 - i][0] = old[5][0][i];
		cube[5][0][i] = old[1][i][2];
	}
	cube[2][0][0] = old[2][0][2];
	cube[2][0][2] = old[2][2][2];
	cube[2][2][2] = old[2][2][0];
	cube[2][2][0] = old[2][0][0];
    
	cube[2][0][1] = old[2][1][2];
	cube[2][1][2] = old[2][2][1];
	cube[2][2][1] = old[2][1][0];
	cube[2][1][0] = old[2][0][1];
}

void b()
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
	copyCube();
	for (int i = 0; i < 3; i++)
	{
		cube[1][2 - i][0] = old[0][0][i];
		cube[0][0][i] = old[3][i][2];
		cube[3][i][2] = old[5][2][2 - i];
		cube[5][2][2 - i] = old[1][2 - i][0];
	}
	cube[4][0][2] = old[4][0][0];
	cube[4][2][2] = old[4][0][2];
	cube[4][2][0] = old[4][2][2];
	cube[4][0][0] = old[4][2][0];
    
	cube[4][1][2] = old[4][0][1];
	cube[4][2][1] = old[4][1][2];
	cube[4][1][0] = old[4][2][1];
	cube[4][0][1] = old[4][1][0];
}

void bi()
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
	copyCube();
	for (int i = 0; i < 3; i++)
	{
		cube[0][0][i] = old[1][2 - i][0];
		cube[3][i][2] = old[0][0][i];
		cube[5][2][2 - i] = old[3][i][2];
		cube[1][2 - i][0] = old[5][2][2 - i];
	}
	cube[4][0][0] = old[4][0][2];
	cube[4][0][2] = old[4][2][2];
	cube[4][2][2] = old[4][2][0];
	cube[4][2][0] = old[4][0][0];
    
	cube[4][0][1] = old[4][1][2];
	cube[4][1][2] = old[4][2][1];
	cube[4][2][1] = old[4][1][0];
	cube[4][1][0] = old[4][0][1];
}

void solveTopCross()
{
    cout << "checkpoint1" << endl;
	moveTopEdges();
    cout << "checkpoint2" << endl;
	//look for the 4 yellow edges
	for (int i = 1; i < 5; i++)
	{
		int side = 0; //side that the yellow sticker is on
		int pos = 0; //position (1-4) of the yellow sticker
		findNextTopEdge(side, pos);
		int numTurns = 0; //keeps track of how many times we turn the cube to put pieces on the bottom layer so we can undo the turns
		if (side == 1)
		{
			while (cube[5][1][0] == 0)
			{
				d();
			}
			while (cube[0][1][0] == 0)
			{
				u();
				numTurns++;
			}
			if (pos == 1)
			{
				l();
				l();
			}
			else if (pos == 2)
			{
				l();
			}
			else if (pos == 4)
			{
				li();
			}
		}
		else if (side == 2)
		{
			while (cube[5][0][1] == 0)
			{
				d();
			}
			while (cube[0][2][1] == 0)
			{
				u();
				numTurns++;
			}
			if (pos == 1)
			{
				f();
				f();
			}
			else if (pos == 2)
			{
				f();
			}
			else if (pos == 4)
			{
				fi();
			}
			di();
		}
		else if (side == 3)
		{
			while (cube[5][1][2] == 0)
			{
				d();
			}
			while (cube[0][1][2] == 0)
			{
				u();
				numTurns++;
			}
			if (pos == 1)
			{
				r();
				r();
			}
			else if (pos == 2)
			{
				r();
			}
			else if (pos == 4)
			{
				ri();
			}
			d();
			d();
		}
		else if (side == 4)
		{
			while (cube[5][2][1] == 0)
			{
				d();
			}
			while (cube[0][0][1] == 0)
			{
				u();
				numTurns++;
			}
			if (pos == 1)
			{
				b();
				b();
			}
			else if (pos == 2)
			{
				b();
			}
			else if (pos == 4)
			{
				bi();
			}
			d();
		}
		else if (side == 5)
		{
			for (int j = 0; j < 4 - pos; j++)
			{
				d();
			}
		}
		for (int j = 0; j < numTurns; j++)
		{
			ui();
		}
		if (side == 5) //algorithm for when the sticker is on the bottom
		{
			int color = cube[1][2][1];
			for (int a = 1; a < color; a++) //set-up so that the edge goes into the right spot
			{
				u();
			}
			l();
			l();
			for (int a = 1; a < color; a++) //undo set-up
			{
				ui();
			}
		}
		else //algorithm for when th esticker is not on the bottom
		{
			int color = cube[5][1][0];
			if (color < 4) //set-up so that the sticker goes into the right spot
			{
				for (int a = 1; a < color + 1; a++)
				{
					u();
				}
			}
			l();
			bi();
			li();
			if (color < 4) //undo set-up
			{
				for (int a = 1; a < color + 1; a++)
				{
					ui();
				}
			}
		}
	}
}

void moveTopEdges() //move all yellow edge stickers on top to the bottom
{
	for (int i = 0; i < 4; i++)
	{
		if (cube[0][2][1] == 0)
		{
			while (cube[5][0][1] == 0)
			{
				d();
			}
			f();
			f();
		}
		u();
	}
}

void findNextTopEdge(int & s, int & p)
{
	for (s = 1; s < 6; s++)
	{
		if (cube[s][0][1] == 0)
		{
			p = 1;
			break;
		}
		else if (cube[s][1][2] == 0)
		{
			p = 2;
			break;
		}
		else if (cube[s][2][1] == 0)
		{
			p = 3;
			break;
		}
		else if (cube[s][1][0] == 0)
		{
			p = 4;
			break;
		}
	}
}

void solveTopCorners()
{
	moveTopCorners();
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
				di();
			}
		}
		else //puts the corner in the back bottom right corner
		{
			bottom = true;
			for (int t = 0; t < pos; t++)
			{
				di();
			}
		}
		if (rig) //algorithm for when yellow is on the right
		{
			int color = cube[4][2][0];
			if (color < 4) //move the top so that the corner goes into the correct position
			{
				for (int t = 0; t < color; t++)
				{
					u();
				}
			}
			r();
			d();
			ri();
			if (color < 4) //undo the setup moves to put the corner in the right position
			{
				for (int t = 0; t < color; t++)
				{
					ui();
				}
			}
		}
		else if (bottom) //algorithm for when yellow is on bottom
		{
			int color = cube[3][2][2];
			if (color < 4) //move the top so that the corner goes into the correct position
			{
				for (int t = 0; t < color; t++)
				{
					u();
				}
			}
			r();
			d();
			d();
			ri();
			di();
			r();
			d();
			ri();
			if (color < 4) //undo the setup moves to put the corner in the right position
			{
				for (int t = 0; t < color; t++)
				{
					ui();
				}
			}
		}
		else //algorithm for when yellow is on back
		{
			int color = cube[5][2][2];
			if (color < 4) //move the top so that the corner goes into the correct position
			{
				for (int t = 0; t < color; t++)
				{
					u();
				}
			}
			bi();
			di();
			b();
			if (color < 4) //undo the setup moves to put the corner in the right position
			{
				for (int t = 0; t < color; t++)
				{
					ui();
				}
			}
		}
	}
}

void moveTopCorners() //moves all yellow corners on the top to the bottom face
{
	for (int i = 0; i < 4; i++)
	{
		if (cube[0][2][2] == 0 || cube[2][0][2] == 0 || cube[3][0][0] == 0)
		{
			while (cube[1][2][2] == 0 || cube[2][2][0] == 0 || cube[5][0][0] == 0) //make sure not to push a different yellow corner back to the top
			{
				d();
			}
			ri();
			d();
			r();
		}
		u();
	}
}

void findNextTopCorner(int & s, int & p) //locates the next corner that is not in its correct spot (guaranteed to be one of the bottom four corners)
//updates pos and side in solveTopCorners() to hold the side and position of the yellow sticker
{
	for (s = 1; s < 5; s++)
	{
		if (cube[s][2][0] == 0)
		{
			p = 1;
			return;
		}
		else if (cube[s][2][2] == 0)
		{
			p = 2;
			return;
		}
	}
	if (cube[5][0][0] == 0)
	{
		p = 2;
	}
	else if (cube[5][0][2] == 0)
	{
		p = 3;
	}
	else if (cube[5][2][2] == 0)
	{
		p = 0;
	}
	else
	{
		p = 1;
	}
}

void solveMiddleLayer()
{
	int side = -1;
	int color = -1;
	int count = 0;
    
beginning:
	if (side != -1)
	{
		placeMiddleEdge(color, side);
		//print();
		count++;
		side = -1;
		color = -1;
	}
    
	for (int i = 1; i <= 4; i++)
	{
    cout << "checkpoint3" << endl;
		side = findBottomMatch(i);
        
		if (side != -1)
		{
			color = i;
			goto beginning;
		}
	}
    
	for (int i = 1; i <= 4; i++)
	{
		if (cube[i][1][0] != (i))
		{
			middleAlgorithm(i, 1);
			if(count >= 15)
			{
				solveTopCross();
				solveTopCorners();
			}
            
			goto beginning;
		}
		else if (cube[i][1][2] != i)
		{
			middleAlgorithm(i, 2);
            
			if(count >= 10)
			{
				solveTopCross();
				solveTopCorners();
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
		if (cube[i][2][1] == color)
		{
			if (i % 2 == 0)
			{
				if (cube[5][abs(2 - i)][1] != 5)
				{
					return i;
				}
			}
			else
			{
				if (cube[5][abs(2 - i)][i - 1] != 5)
				{
					return i;
				}
			}
		}
	}
    
	return -1;
}

void placeMiddleEdge(int color, int edgeSide)
{
	if (edgeSide - color == 0)
	{
		middleAlgorithm(color, -1);
	}
	else if (edgeSide - color == 1)
	{
		di();
		middleAlgorithm(color, -1);
	}
	else if (edgeSide - color == 2)
	{
		di();
		di();
		middleAlgorithm(color, -1);
	}
	else if (edgeSide - color == 3)
	{
		d();
		middleAlgorithm(color, -1);
	}
	else if (edgeSide - color == -1)
	{
		d();
		middleAlgorithm(color, -1);
	}
	else if (edgeSide - color == -2)
	{
		d();
		d();
		middleAlgorithm(color, -1);
	}
	else if (edgeSide - color == -3)
	{
		di();
		//print();
		middleAlgorithm(color, -1);
	}
}

void middleAlgorithm(int color, int direction) //1 - L 2 - R -1 for nothing
{
	if (color == 1)
	{
		if (cube[5][1][0] == 4 || direction == 1)
		{
			d();
			b();
			di();
			bi();
			di();
			li();
			d();
			l();
		}
		else if (cube[5][1][0] == 2 || direction == 2)
		{
			di();
			fi();
			d();
			f();
			d();
			l();
			di();
			li();
		}
	}
	else if (color == 2)
	{
		if (cube[5][0][1] == 1 || direction == 1)
		{
			d();
			l();
			di();
			li();
			di();
			fi();
			d();
			f();
		}
		else if (cube[5][0][1] == 3 || direction == 2)
		{
			di();
			ri();
			d();
			r();
			d();
			f();
			di();
			fi();
		}
	}
	else if (color == 3)
	{
		if (cube[5][1][2] == 2 || direction == 1)
		{
			d();
			f();
			di();
			fi();
			di();
			ri();
			d();
			r();
		}
		else if (cube[5][1][2] == 4 || direction == 2)
		{
			di();
			bi();
			d();
			b();
			d();
			r();
			di();
			ri();
		}
	}
	else if (color == 4)
	{
		if (cube[5][2][1] == 3 || direction == 1)
		{
			d();
			r();
			di();
			ri();
			di();
			bi();
			d();
			b();
		}
		else if (cube[5][2][1] == 1 || direction == 2)
		{
			di();
			li();
			d();
			l();
			d();
			b();
			di();
			bi();
		}
	}
}

void solveBottomLayer()
{
	positionBottomCorners();
	//print();
	positionBottomEdges();
	//print();
	correctBottomCorners();
	//print();
	correctBottomEdges();
    //	print();
}

void positionBottomCorners()
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
        
		d();
		//print();
	}
    
	for (int i = 0; i < bestNumDTurns && pos1 != 4; i++)
	{
		d();
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
        
		swapCorners(oppFace);
		positionBottomCorners();
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
        
		swapCorners(face);
		swapCorners(face2);
		swapCorners(face);
		positionBottomCorners();
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
        
		swapCorners(face); //Eventually One of the previous situations above will occur :D
		positionBottomCorners();
		return;
	}
    
}

void swapCorners(int face)
{
	if (face == 1)
	{
		di();
		fi();
		d();
		b();
		di();
		f();
		d();
		bi();
		di();
	}
	else if (face == 2)
	{
		di();
		ri();
		d();
		l();
		di();
		r();
		d();
		li();
		di();
	}
	else if (face == 3)
	{
		di();
		bi();
		d();
		f();
		di();
		b();
		d();
		fi();
		di();
	}
	else if (face == 4)
	{
		di();
		li();
		d();
		r();
		di();
		l();
		d();
		ri();
		di();
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
		corners[0] = cube[1][2][2];
		corners[1] = cube[2][2][0];
		corners[2] = cube[5][0][0];
	}
	else if (num == 1)
	{
		corners[0] = cube[2][2][2];
		corners[1] = cube[3][2][0];
		corners[2] = cube[5][0][2];
	}
	else if (num == 2)
	{
		corners[0] = cube[3][2][2];
		corners[1] = cube[4][2][0];
		corners[2] = cube[5][2][2];
	}
	else if (num == 3)
	{
		corners[0] = cube[4][2][2];
		corners[1] = cube[1][2][0];
		corners[2] = cube[5][2][0];
	}
}

void positionBottomEdges()
{
	int pos = numEdgesInCorrectPos();
    
	if (pos == 0)
	{
		rotateEdges(2, true);
		positionBottomEdges();
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
        
		rotateEdges(face, clockwise);
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
    
	int edges[4][2] = { { cube[5][1][0], cube[1][2][1] }, { cube[5][0][1], cube[2][2][1] }, { cube[5][1][2], cube[3][2][1] }, { cube[5][2][1], cube[4][2][1] } };
    
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

void rotateEdges(int face, bool rotClockwise)
{
	if (face == 1)
	{
		if (rotClockwise == true)
		{
			f();
			f();
			d();
			li();
			r();
			f();
			f();
			l();
			ri();
			d();
			f();
			f();
		}
		else
		{
			f();
			f();
			di();
			li();
			r();
			f();
			f();
			l();
			ri();
			di();
			f();
			f();
		}
	}
	else if (face == 2)
	{
		if (rotClockwise == true)
		{
			r();
			r();
			d();
			fi();
			b();
			r();
			r();
			f();
			bi();
			d();
			r();
			r();
		}
		else
		{
			r();
			r();
			di();
			fi();
			b();
			r();
			r();
			f();
			bi();
			di();
			r();
			r();
		}
	}
	else if (face == 3)
	{
		if (rotClockwise == true)
		{
			b();
			b();
			d();
			ri();
			l();
			b();
			b();
			r();
			li();
			d();
			b();
			b();
		}
		else
		{
			b();
			b();
			di();
			ri();
			l();
			b();
			b();
			r();
			li();
			di();
			b();
			b();
		}
	}
	else if (face == 4)
	{
		if (rotClockwise == true)
		{
			l();
			l();
			d();
			bi();
			f();
			l();
			l();
			b();
			fi();
			d();
			l();
			l();
		}
		else
		{
			l();
			l();
			di();
			bi();
			f();
			l();
			l();
			b();
			fi();
			di();
			l();
			l();
		}
	}
}

void correctBottomCorners()
{
	int result = cornerOrientation();
    
	while (result != 5)
	{
		twoCornerRotate(abs(findBestFace(result)), *findBestFace > 0);
        
		result = cornerOrientation();
	}
}

int cornerOrientation()
{
	int numCorrect = 0;
	int wrongPosition = 0;
    
	int corners[4] = { cube[5][0][0], cube[5][0][2], cube[5][2][2], cube[5][2][0] };
    
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
	int corners[4] = { cube[5][0][0], cube[5][0][2], cube[5][2][2], cube[5][2][0] };
    
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

void twoCornerRotate(int face, bool goForward)
{
	if (face == 1)
	{
		if (goForward == true)
		{
			bi();
			u();
			b();
			l();
			u();
			li();
			d();
			l();
			ui();
			li();
			bi();
			ui();
			b();
			di();
		}
		else
		{
			d();
			bi();
			u();
			b();
			l();
			u();
			li();
			di();
			l();
			ui();
			li();
			bi();
			ui();
			b();
		}
	}
	else if (face == 2)
	{
		if (goForward == true)
		{
			li();
			u();
			l();
			f();
			u();
			fi();
			d();
			f();
			ui();
			fi();
			li();
			ui();
			l();
			di();
		}
		else
		{
			d();
			li();
			u();
			l();
			f();
			u();
			fi();
			di();
			f();
			ui();
			fi();
			li();
			ui();
			l();
		}
	}
	else if (face == 3)
	{
		if (goForward == true)
		{
			fi();
			u();
			f();
			r();
			u();
			ri();
			d();
			r();
			ui();
			ri();
			fi();
			ui();
			f();
			di();
		}
		else
		{
			d();
			fi();
			u();
			f();
			r();
			u();
			ri();
			di();
			r();
			ui();
			ri();
			fi();
			ui();
			f();
		}
	}
	else if (face == 4)
	{
		if (goForward == true)
		{
			ri();
			u();
			r();
			b();
			u();
			bi();
			d();
			b();
			ui();
			bi();
			ri();
			ui();
			r();
			di();
		}
		else
		{
			d();
			ri();
			u();
			r();
			b();
			u();
			bi();
			di();
			b();
			ui();
			bi();
			ri();
			ui();
			r();
		}
	}
}

void correctBottomEdges()
{
	int edges[4] = { cube[5][1][0], cube[5][0][1], cube[5][1][2], cube[5][2][1] };
    
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
		twoEdgeRotate(1, false);
		twoEdgeRotate(2, false);
		return;
	}
	else
	{
		if(pos2 != -1)
		{
			twoEdgeRotate(pos2 + 1, isTogether);
		}
		else
		{
			twoEdgeRotate(pos1 + 1, isTogether);
		}
		return;
	}
}

void twoEdgeRotate(int face, bool isNextTo)
{
	if (face == 1)
	{
		if (isNextTo == true)
		{
			l();
			ui();
			d();
			f();
			f();
			d();
			d();
			u();
			u();
			b();
			d();
			bi();
			u();
			u();
			d();
			d();
			f();
			f();
			di();
			u();
			li();
			di();
		}
		else
		{
			l();
			ui();
			d();
			f();
			f();
			d();
			d();
			u();
			u();
			b();
			d();
			d();
			bi();
			u();
			u();
			d();
			d();
			f();
			f();
			di();
			u();
			li();
			di();
			di();
		}
	}
	else if (face == 2)
	{
		if (isNextTo == true)
		{
			f();
			ui();
			d();
			r();
			r();
			d();
			d();
			u();
			u();
			l();
			d();
			li();
			u();
			u();
			d();
			d();
			r();
			r();
			di();
			u();
			fi();
			di();
		}
		else
		{
			f();
			ui();
			d();
			r();
			r();
			d();
			d();
			u();
			u();
			l();
			d();
			d();
			li();
			u();
			u();
			d();
			d();
			r();
			r();
			di();
			u();
			fi();
			di();
			di();
		}
	}
	else if (face == 3)
	{
		if (isNextTo == true)
		{
			r();
			ui();
			d();
			b();
			b();
			d();
			d();
			u();
			u();
			f();
			d();
			fi();
			u();
			u();
			d();
			d();
			b();
			b();
			di();
			u();
			ri();
			di();
		}
		else
		{
			r();
			ui();
			d();
			b();
			b();
			d();
			d();
			u();
			u();
			f();
			d();
			d();
			fi();
			u();
			u();
			d();
			d();
			b();
			b();
			di();
			u();
			ri();
			di();
			di();
		}
	}
	else if (face == 4)
	{
		if (isNextTo == true)
		{
			b();
			ui();
			d();
			l();
			l();
			d();
			d();
			u();
			u();
			r();
			d();
			ri();
			u();
			u();
			d();
			d();
			l();
			l();
			di();
			u();
			bi();
			di();
		}
		else
		{
			b();
			ui();
			d();
			l();
			l();
			d();
			d();
			u();
			u();
			r();
			d();
			d();
			ri();
			u();
			u();
			d();
			d();
			l();
			l();
			di();
			u();
			bi();
			di();
			di();
		}
	}
}

void copyCube()
{
	for (int i = 0; i < 6; i++)
	{
		for (int j = 0; j < 3; j++)
		{
			for (int k = 0; k < 3; k++)
			{
				old[i][j][k] = cube[i][j][k];
			}
		}
	}
}

void print()
{
	for (int i = 0; i < 6; i++)
	{
		for (int j = 0; j < 3; j++)
		{
			for (int k = 0; k < 3; k++)
			{
				cout << cube[i][j][k];
			}
			cout << endl;
		}
		cout << endl;
	}
}

string printColor(int field)
{
	
	//			1 white			2 red			3 green			4 blue			5 orange			6 yellow	
    // neuer farbenversuch		
    string RESET = "\033[0m";
	string WHITE = "\033[107m";      /* White */
	string RED = "\033[101m";      /* Red */
	string GREEN = "\033[102m";      /* Green */
	string BLUE = "\e[48;5;21m";      /* Blue */
	string ORANGE = "\e[48;5;208m";      /* Magenta */	 
	string YELLOW = "\033[103m";      /* Yellow */
    string BLACK = "\033[40m"; 
				
	string printcolor;
	switch(field){
        case 8:
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

void printCubeColor()
{ 

    cout<<"PRINTING CUSTOM CUBE"<<endl;
	for(int i=0;i<3;i++)
	{
		cout<<"       "<<printColor(cube[0][i][0])<<printColor(cube[0][i][1])<<printColor(cube[0][i][2])<<endl;
	}
	for(int i=0;i<3;i++)
	{
		cout<<printColor(cube[1][i][0])<<printColor(cube[1][i][1])<<printColor(cube[1][i][2])<<" ";
		cout<<printColor(cube[2][i][0])<<printColor(cube[2][i][1])<<printColor(cube[2][i][2])<<" ";
		cout<<printColor(cube[3][i][0])<<printColor(cube[3][i][1])<<printColor(cube[3][i][2])<<" ";
		cout<<printColor(cube[4][i][0])<<printColor(cube[4][i][1])<<printColor(cube[4][i][2])<<" "<<endl;
	}
	for(int i=0;i<3;i++)
	{
		cout<<"       "<<printColor(cube[5][i][0])<<printColor(cube[5][i][1])<<printColor(cube[5][i][2])<<endl;
	}	
	cout<<endl<<endl;	
}














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
void scramble()
{
	srand(time(NULL));
	for (int i = 0; i < 30; i++)
	{
		int num = rand() % 12 + 1;
		switch (num)
		{
            case 1: r(); break;
            case 2: ri(); break;
            case 3: u(); break;
            case 4: ui(); break;
            case 5: f(); break;
            case 6: fi(); break;
            case 7: l(); break;
            case 8: li(); break;
            case 9: b(); break;
            case 10: bi(); break;
            case 11: d(); break;
            case 12: di(); break;
		}
	}
}

void inputCube(){
    
    // generate black cube 
    {
    int i = 0;      
            for(int j = 0; j < 6; j++){    
                for(int k = 0; k < 3; k++){
                    for(int l = 0; l <3; l++){
                            cube[j][k][l] = 8;
                            //cout << cube[j][k][l]; 
                    }
                }
            }
    }
         printCubeColor();   

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
                                                        
                                            cube[j][k][l] = cubesausage[i];
                                            i++;
                                            printCubeColor();
                                 }
                }
            }
         }
    }
   
    //}

}

void mapforsolver(){

            for(int j = 0; j < 6; j++){    
                for(int k = 0; k < 3; k++){
                    for(int l = 0; l <3; l++){
                            cube[j][k][l] += 10;
                    }
                }
            }
    
    for(int i = 0; i <6; i++){
    int changer = cube[i][1][1];
             for(int j = 0; j < 6; j++){    
                for(int k = 0; k < 3; k++){
                    for(int l = 0; l <3; l++){
                            if(cube[j][k][l] == changer)
                                cube[j][k][l]=i;
                    }
                }
            }       
      }
      printCubeColor();            

}

