// structs gelöscht 
// includes eingefügt

#include <iostream>
#include <list>
#include <iterator>
#include "masterheader.hpp"
//#include "solvability.hpp"
#include "rubikssolver_header.hpp"
#include "fillcube.hpp"

using namespace std;
/*
struct corner;
struct edge;
struct middle;
*/
int findMiddle(int n);
void sortAnswer(int answer[]);
void buildCombOfTwo(list<middle> &midComb);
void buildCombOfEdge(list<edge> EdgeCodes[], int MiddleCodes[]);
void buildCombOfConrer(list<corner> CornerCodes[], int MiddleCodes[]);
void eliminateFound(list<middle> &midComb, int foundColours[]);
void getNextQuestion(list<middle> &midComb, int currentQuestion[]);
void sortOutImpossibleCodes(int currentguess[], list<middle> &midComb, int currentAnswer[]);
bool contains (list<middle> &midComb, int a, int b);
void changeAnswer(string& strAnswer, int* arrAnswer);
/*
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
*/



void changeAnswer(string& strAnswer, int* arrAnswer)
{
	int intTemp[3];
	for (int i=0;i<3;i++)
		intTemp[i]=0;
		
		 
	intTemp[0]+=(strAnswer.at(1)-'0')*10;
	intTemp[0]+=(strAnswer.at(2)-'0');
	intTemp[1]+=(strAnswer.at(3)-'0')*10;
	intTemp[1]+=(strAnswer.at(4)-'0');
	intTemp[2]+=(strAnswer.at(5)-'0')*10;
	intTemp[2]+=(strAnswer.at(6)-'0');
	
	for(int i=0;i<(sizeof(arrAnswer)/sizeof(arrAnswer[0]));i++)
	{ //Reihenfolge evtl noch ändern!!!!
		if(intTemp[0]!=0)
		{
			arrAnswer[i]=0; //nothing
			intTemp[0]--;
		} else if(intTemp[1]!=0)
		{
			arrAnswer[i]=1; //black
			intTemp[1]--;
		} else if(intTemp[2]!=0)
		{
			arrAnswer[i]=2; //white
			intTemp[2]--;	
		}	
	}
}

int findMiddle(int foundColour[])
{	
	list<middle> midComb;
	
	for (int i=1; i<7; i+=2)
	{
		int currentAnswer[2] = { 0,0 }, currentGuess[2] = {1,2}; // eventuell mit geratenem cube abstimmen
		
		buildCombOfTwo(midComb);
		eliminateFound(midComb, foundColour);
		
		cout << "\nFrage Feld" << i <<":" << currentGuess[0] << "\nFrage Feld" << i+1 <<":" << currentGuess[1] << endl;
		
		
		sortOutImpossibleCodes(currentGuess, midComb, currentAnswer);
		
		if(midComb.size()==1)
			goto skip;

		while(1)
		{
			getNextQuestion(midComb, currentGuess);
			
			cout << "\nFrage Feld" << i <<" :" << currentGuess[0] << "\nFrage Feld" << i+1 <<" :" << currentGuess[1] << endl;
			
			// server input
			cin >> currentAnswer[0];
			cin >> currentAnswer[1];
			
			sortOutImpossibleCodes(currentGuess, midComb, currentAnswer);

			if(midComb.size()==1)
				break;
		}
		
		skip:
		
		cout << "Farbe Feld " << i <<" ist: "<< midComb.begin()->field1 << " | Farbe Feld " << i+1 <<" ist: " << midComb.begin()->field2 << endl;
		
		foundColour[i-1]=midComb.begin()->field1;
		foundColour[i]=midComb.begin()->field2;	
	}

	cout << "Mittelfelder:\n";
	
	for(int i=0; i<6; i++)
	{
		 cout << foundColour[i] << endl;
		 foundColour[i]--; // lol
	}

	return 0;
}

void sortAnswer(int answer[])
{
	if (answer[0] > answer[1])
	{
		int temp;
		temp = answer[0];
		answer[0] = answer[1];
		answer[1] = temp;
	}
}

void buildCombOfTwo(list<middle> &midComb)
{
	cout << "In funktion buildCombOfTwo: generating combos:" << endl;
	for (int i = 1; i < 7; i++)
	{
		for (int j = 1; j < 7; j++)
		{
			if (i == j)
				continue;
				
            middle tmp;
            
            tmp.field1=i;
            tmp.field2=j;
			midComb.push_back(tmp);
			
			cout << midComb.back().field1 << midComb.back().field2 << endl;
		}
	}
}

void buildCombOfCorner(list<corner> CornerCodes[], int MiddleCodes[])
{
	//cout << "In funktion build Comb of Corner" << endl;
	corner cornerGeometrie[8]={	{MiddleCodes[0],MiddleCodes[2],MiddleCodes[4]},
					{MiddleCodes[0],MiddleCodes[4],MiddleCodes[3]},
					{MiddleCodes[0],MiddleCodes[3],MiddleCodes[5]},
					{MiddleCodes[0],MiddleCodes[5],MiddleCodes[2]},
					{MiddleCodes[2],MiddleCodes[1],MiddleCodes[4]},
					{MiddleCodes[4],MiddleCodes[1],MiddleCodes[3]},
					{MiddleCodes[3],MiddleCodes[1],MiddleCodes[5]},
					{MiddleCodes[2],MiddleCodes[5],MiddleCodes[1]}	};
	// jakobnode: reihenfolge so bebsichtigt? 
    // wie kommen hier die farben der mittelpunkte ins spiel? 

	for(int k=0; k<8; k++)
	{	
		for(int i = 0; i<8; i++)
		{
								
					corner tmp;
	
					tmp.field[0] = cornerGeometrie[i].field[0];
					tmp.field[1] = cornerGeometrie[i].field[1];
					tmp.field[2] = cornerGeometrie[i].field[2];

					CornerCodes[k].push_back(tmp);
					
					tmp.field[0] = cornerGeometrie[i].field[2];
					tmp.field[1] = cornerGeometrie[i].field[0];
					tmp.field[2] = cornerGeometrie[i].field[1];

					CornerCodes[k].push_back(tmp);

					tmp.field[0] = cornerGeometrie[i].field[1];
					tmp.field[1] = cornerGeometrie[i].field[2];
					tmp.field[2] = cornerGeometrie[i].field[0];

					CornerCodes[k].push_back(tmp);				
				
		}
	}
}


void buildCombOfEdge(list<edge> EdgeCodes[], int MiddleCodes[])
{
	for (int k=0; k<12; k++)
	{
		list <edge>::iterator it = EdgeCodes[k].begin();
		
		for (int i = 0; i < 6; i++)
		{
			for (int j = 0; j < 6; j++)
			{
				if (i == j)
					continue;
				
				bool skip = false;
				
				for (int l=0; l<5; l+=2)
				{
					if ( (i == MiddleCodes[l] && j == MiddleCodes[l+1]) || (j == MiddleCodes[l] && i == MiddleCodes[l+1]) )
						skip = true;
				}
				
				if (skip)
					continue;
					
				edge tmp;
				
				tmp.field[0]=i;
				tmp.field[1]=j;
				
				EdgeCodes[k].push_back(tmp);
			}
		}
	}
}

void eliminateFound(list<middle> &midComb, int foundColour[])
{
	list<middle>::iterator it = midComb.begin();

	cout << "In funktion eliminateFound:" << endl;

	for (int i=0; i<6; i++)
	{
		while(it != midComb.end())
		{
			if(it->field1 == foundColour[i] || it->field2 == foundColour[i])
			{
				cout << "erased field : " << it->field1 << it->field2 << endl;
				it = midComb.erase(it);
				if (it == midComb.end())
					return;
				continue;
			}
			it++;
		}
		it = midComb.begin();
	}
}

void getNextQuestion(list<middle> &midComb, int currentQuestion[])
{
    int case1=0, case2=0, case3=0; //case1 (0,0) case2(0,2) case3(2,2)
    int nextQuestionMax=5725775;
    list<middle>::iterator it = midComb.begin();


	for(int i=1;i<7;i++)
	{
		for(int j=1;j<7;j++)
		{
			if(j!=i)
			{
				while(it != midComb.end())
				{
					if(it->field1 == i && it->field2 == j)
						case3++;
					else if( (it->field1 == i && it->field2 != j) || (it->field1 != i && it->field2 == j) )
						case2++;
					else
						case1++;

					it++;
				}
				
				it = midComb.begin();

				if(case1>=case2 && case1>=case3 && case1<=nextQuestionMax)
				{
					if ( (contains(midComb, i, j) && nextQuestionMax == case1) || case1 < nextQuestionMax)
					{
						nextQuestionMax=case1;
						currentQuestion[0]=i;
						currentQuestion[1]=j;
					}
				}
				else if(case2>=case1 && case2>=case3 && case2<=nextQuestionMax)
				{
					if ( (contains(midComb, i, j) && nextQuestionMax == case2) || case1 < nextQuestionMax)
					{
						nextQuestionMax=case2;
						currentQuestion[0]=i;
						currentQuestion[1]=j;
					}
				}
				else if(case3>=case1 && case3>=case2 && case3<=nextQuestionMax)
				{
					if ( (contains(midComb, i, j) && nextQuestionMax == case3) || case1 < nextQuestionMax)
					{
						nextQuestionMax=case3;
						currentQuestion[0]=i;
						currentQuestion[1]=j;
					}
				}
				
				case1=0;
				case2=0;
				case3=0;
			}
		}
	}
}

void sortOutImpossibleCodes(int currentguess[], list<middle> &midComb, int currentAnswer[])
{
	cout << "In Funktion sortOutImpossibleCodes:" << endl;
	
	list<middle>::iterator it;
	it = midComb.begin();
	
	int tempAnswer[2] = {0,0};
	
	while(it != midComb.end())
	{
		if (currentguess[0] == it->field1)
			tempAnswer[0] = 2;
		else
			tempAnswer[0] = 0;

		if (currentguess[1] == it->field2)
			tempAnswer[1] = 2;
		else
			tempAnswer[1] = 0;

		sortAnswer(tempAnswer);
		sortAnswer(currentAnswer);

		if (tempAnswer[0] != currentAnswer[0] || tempAnswer[1] != currentAnswer[1])
		{
			cout << "Combination: " << it->field1 << it->field2 <<" sorted out!"<<endl;
			
			it = midComb.erase(it);
			if (it == midComb.end())
				return;
			continue;
		}
        it++;
	}
}

bool contains (list<middle> &midComb, int a, int b)
{
	list<middle>::iterator it = midComb.begin();
	
	while(it != midComb.end())
	{
		if (it->field1 == a && it->field2 == b)
			return true;
		
		it++;
	}
	
	return false;
}

int main()
{
int error = 0; 
int counter = 0; 

do{
	int MiddleCode[6] = {0,5,1,3,2,4};
	list <edge> EdgeCodes[12];
	list <corner> CornerCodes[8];


	
	//findMiddle(MiddleCode);
	buildCombOfEdge(EdgeCodes, MiddleCode);

	buildCombOfCorner(CornerCodes, MiddleCode);

    fillrandomcube(MiddleCode, MiddleColor, EdgeCodes, CornerCodes, orientationCube, indexCube);
   // cout << "filled" << endl;
    mapforsolver(cube);
    
    //printCubeColor(cube);  
   // print(orientationCube);
   // print(indexCube);     


    SOLVETOP:
	solveTopCross(cube, orientationCube, indexCube);
	//cout << "cross: " << moves << endl;
	clearMoves();
    //printCubeColor(cube);  
 //   mapforcustomcolor();
  //  printCubeColor(cube_customcolor);
	solveTopCorners(cube, orientationCube, indexCube);
	cout << "corners: " << moves << endl;
    translateMove();
    cout << movesTranslated << endl;
	clearMoves();
    error = checktop();
    if(error)
        goto SOLVETOP;
        

    //printCubeColor(cube);  
  //  mapforcustomcolor();
    //printCubeColor(cube_customcolor);
	solveMiddleLayer(cube, orientationCube, indexCube);
	//cout << "middle layer: " << moves << endl;
	clearMoves();
    //printCubeColor(cube);  
    //mapforcustomcolor();
    //printCubeColor(cube_customcolor);
	solveBottomLayer(cube, orientationCube, indexCube);
	//cout << "Bottom: " << moves << endl;
	clearMoves();
    printCubeColor(cube);  
    //mapforcustomcolor();
   // printCubeColor(cube);
    //print(indexCube);



    counter++;
    cout << "counter: " << counter << endl;
    usleep(1000000*0.01);
}
while(1);

	return 0;
}

