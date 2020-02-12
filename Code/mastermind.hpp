#ifndef MMHPP
#define MMHPP

#include "masterheader.hpp"
#include <iostream>
#include <list>
#include <iterator>

using namespace std;

int findMiddle(int n);
void sortAnswer(int answer[]);
void buildCombOfTwo(list<middle> &midComb);
void buildCombOfEdge(list<edge> EdgeCodes[], int MiddleCodes[]);
void buildCombOfConrer(list<corner> CornerCodes[], int MiddleCodes[]);
void eliminateFound(list<middle> &midComb, int foundColours[]);
void getNextQuestion(list<middle> &midComb, int currentQuestion[]);
void sortOutImpossibleCodes(int currentguess[], list<middle> &midComb, int currentAnswer[]);
bool containsMiddle(list<middle> &midComb, int a, int b);
bool containsEdge(list<edge> &edgeComb, int a, int b);
bool containsCorner(list<corner> &cornerComb, int a, int b);
void changeAnswer(string& strAnswer, int* arrAnswer);
void getNextEdgeQuestion(list<edge> &edgeComg, int currentQuestion[], int MiddleCode[], int orienataion[]);
void getNextCornerQuestion(list<corner> &cornerComg, int currentQuestion[], int MiddleCode[]);
void sortOutImpossibleEdges(int currentguess[], list<edge> &edgeComb, int currentAnswer[], int MiddleCode[], int orientation[]);
void sortOutImpossibleCorners(int currentguess[], list<corner> &cornerComb, int currentAnswer[], int MiddleCode[]);
void findEdges(list <edge> EdgeCodes[], int middleColor[]);
void getEdgeInfo(int fields[][3],int n, int orientation[]);
void getCornerInfo(int fields[][3],int n);
void findCorners(list <corner> CornerCodes[], int middleColor[]);
void numberToGerman(int col);

void numberToGerman(int col)
{
	switch (col)
	{
		case 0:
			cout << "Gelb";
			break;
		case 1:
			cout << "Orange";
			break;
		case 2:
			cout << "Blau";
			break;
		case 3:
			cout << "Rot";
			break;
		case 4:
			cout << "Gruen";
			break;
		case 5:
			cout << "Weiss";
			break;
	}
}

void askTwo(int putAnswer [], int question [], int field1 [], int field2 []);

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
	int field1 [3] = {0, 1, 1};
	int field2 [3] = {0, 1, 1};
	int questionOrder[6] = {0, 5, 1, 3, 2, 4};
	
	for (int i=1; i<7; i+=2)
	{
		int currentAnswer[2] = { 0,0 }, currentGuess[2] = {0,1}; // eventuell mit geratenem cube abstimmen
		
		buildCombOfTwo(midComb);
		eliminateFound(midComb, foundColour);
		field1 [0] = questionOrder[i-1];
		field2 [0] = questionOrder[i];

		while(midComb.size()>1)
		{
			getNextQuestion(midComb, currentGuess);
			
			//cout << "\nFrage Feld" << i-1 <<" :" << currentGuess[0] << "\nFrage Feld" << i <<" :" << currentGuess[1] << endl;
			
			//Server Question 
			askTwo(currentAnswer, currentGuess, field1, field2); //void askTwo(int putAnswer [2], int question [2], int field1 [3], int field2 [3])

			
			
			sortOutImpossibleCodes(currentGuess, midComb, currentAnswer);

			if(midComb.size()==1)
				break;
		}
		
		
		//cout << "Farbe Feld " << i-1 <<" ist: "<< midComb.begin()->field1 << " | Farbe Feld " << i <<" ist: " << midComb.begin()->field2 << endl;
		
		foundColour[i-1]=midComb.begin()->field1;
		foundColour[i]=midComb.begin()->field2;	
	}

	cout << "Mittelfelder:\n";
	
	for(int i=0; i<6; i++)
	{
		 numberToGerman(foundColour[i]);
		cout << endl;
	}

	return 0;
}

void getEdgeInfo(int fields[][3],int n, int orientation[])
{
	int i=0;
	int l=0;	
	for(i =0; i<6; i++)
	{
		for(int j =0; j<3; j++)
		{
			for(int k =0; k<3; k++)
			{
				if( indexCube[i][j][k]==n && (j == 1 || k == 1) && j!=k)
				{
					fields[orientationCube[i][j][k]][0]=i;
					fields[orientationCube[i][j][k]][1]=j;
					fields[orientationCube[i][j][k]][2]=k;
				}
			}
		}
	}
}

void getCornerInfo(int fields[][3],int n)
{
	int i=0;
	int l=0;	
	for(i =0; i<6; i++)
	{
		for(int j =0; j<3; j++)
		{
			for(int k =0; k<3; k++)
			{
				if( indexCube[i][j][k]==n && j != 1 &&  k != 1)
				{
					fields[orientationCube[i][j][k]][0]=i;
					fields[orientationCube[i][j][k]][1]=j;
					fields[orientationCube[i][j][k]][2]=k;
				}
			}
		}
	}
}

void findEdges(list <edge> EdgeCodes[], int middleColor[])
{
	int fields[2][3]={{0,0,0},{0,0,0}};
	int orientation[2];
	int i = 0;
	for(i = 0; i<12; i++)
	{
		if(EdgeCodes[i].size()>1)
		break;
	}
	
	if(i>11) return;
	
	//cout << endl << "Liste Nr.: " << i << " wird bearbeitet" << endl; 

	getEdgeInfo(fields,i,orientation);
	int currentGuess[2];
	int currentAnswer[2];
	int MiddleCode[2]={middleColor[fields[0][0]],middleColor[fields[1][0]]};

	while(EdgeCodes[i].size()>1)
	{
		getNextEdgeQuestion(EdgeCodes[i], currentGuess, MiddleCode, orientation);
		
		//cout << endl << "Next Question is Field "<< fields[0][0] << fields[0][1] << fields[0][2]<< " = " << currentGuess[0] << " Field  " 
   		//					 << fields[1][0] << fields[1][1] << fields[1][2]<< " = "  << currentGuess[1] << endl;
		
		askTwo(currentAnswer, currentGuess, fields[0], fields[1]);

		//cout << endl << "Anwser is " << currentAnswer[0] << currentAnswer[1] << endl;

		sortOutImpossibleEdges(currentGuess, EdgeCodes[i],currentAnswer,MiddleCode, orientation);
	}

	cout << endl << "Edge Number: " << i << " is" << endl;

	numberToGerman(EdgeCodes[i].begin()->field[0]);
	cout << endl;
	numberToGerman(EdgeCodes[i].begin()->field[1]);
	cout << endl;

}

void findCorners(list <corner> CornerCodes[], int middleColor[])
{
	int fields[3][3]={{0,0,0},{0,0,0}};
	int i = 0;
	for(i = 0; i<8; i++)
	{
		if(CornerCodes[i].size()>1)
		break;
	}
	
	if(i>7) return;
	
	//cout << endl << "Liste Nr.: " << i << " wird bearbeitet" << endl; 

	getCornerInfo(fields,i);
	int currentGuess[2];
	int currentAnswer[2];
	int MiddleCode[3]={middleColor[fields[0][0]],middleColor[fields[1][0]], middleColor[fields[2][0]]};

	while(CornerCodes[i].size()>1)
	{
		getNextCornerQuestion(CornerCodes[i], currentGuess, MiddleCode); // besser machen
		
		//cout << endl << "Next Question is Field "<< fields[0][0] << fields[0][1] << fields[0][2]<< " = " << currentGuess[0] << " Field  " 
   		//					 << fields[1][0] << fields[1][1] << fields[1][2]<< " = "  << currentGuess[1] << endl;
		
		askTwo(currentAnswer, currentGuess, fields[0], fields[1]);

		//cout << endl << "Anwser is " << currentAnswer[0] << currentAnswer[1] << endl;

		//cout << "hilfe";

		sortOutImpossibleCorners(currentGuess, CornerCodes[i], currentAnswer, MiddleCode); // anlegen
	}
	
	cout << endl << "Corner Number: " << i << " is" << endl;

	numberToGerman(CornerCodes[i].begin()->field[0]);
	cout << endl;
	numberToGerman(CornerCodes[i].begin()->field[1]);
	cout << endl;
	numberToGerman(CornerCodes[i].begin()->field[2]);
	cout << endl;
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
	//cout << "In funktion buildCombOfTwo: generating combos:" << endl;
	for (int i = 0; i < 6; i++)
	{
		for (int j = 0; j < 6; j++)
		{
			if (i == j)
				continue;
				
            middle tmp;
            
            tmp.field1=i;
            tmp.field2=j;
			midComb.push_back(tmp);
			
			//cout << midComb.back().field1 << midComb.back().field2 << endl;
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
					tmp.field[1]= cornerGeometrie[i].field[2];
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

	//cout << "In funktion eliminateFound:" << endl;

	for (int i=0; i<6; i++)
	{
		while(it != midComb.end())
		{
			if(it->field1 == foundColour[i] || it->field2 == foundColour[i])
			{
				//cout << "erased field : " << it->field1 << it->field2 << endl;
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
	bool changeQuestionFlag = false;
	list<middle>::iterator it = midComb.begin();


	for(int i=0;i<6;i++)
	{
		for(int j=0;j<6;j++)
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
					if ( (containsMiddle(midComb, i, j) && nextQuestionMax == case1) || case1 < nextQuestionMax)
					{
						nextQuestionMax=case1;
						changeQuestionFlag = true;
						
					}
				}
				else if(case2>=case1 && case2>=case3 && case2<=nextQuestionMax)
				{
					if ( (containsMiddle(midComb, i, j) && nextQuestionMax == case2) || case1 < nextQuestionMax)
					{
						nextQuestionMax=case2;
						changeQuestionFlag = true;
					}
				}
				else if(case3>=case1 && case3>=case2 && case3<=nextQuestionMax)
				{
					if ( (containsMiddle(midComb, i, j) && nextQuestionMax == case3) || case1 < nextQuestionMax)
					{
						nextQuestionMax=case3;
						changeQuestionFlag = true;
						
					}
				}

				if(changeQuestionFlag)
				{
					currentQuestion[0] = i;
					currentQuestion[1] = j;
					changeQuestionFlag = false;
				}
				
				case1=0;
				case2=0;
				case3=0;
			}
		}
	}
}


void getNextEdgeQuestion(list<edge> &edgeComb, int currentQuestion[], int MiddleCode[], int orientation[])
{
	int case0=0, case1=0, case2=0, case3=0, case4=0; // case0 = {2,2} case1 = {0,2} case2 = {1,1} case3 = {0,1} case4 = {0,0}
	int nextQuestionMax = 39439;
	bool changeQuestionFlag = false;
	list<edge>::iterator it = edgeComb.begin();

	for(int i = 0; i<6 ; i++)
	{
		for(int j = 0; j<6; j++)
		{
			if(j!=i)
			{
				while(it!=edgeComb.end())
				{
					if( it->field[0] == i && i == MiddleCode[0] && it->field[1] == j && j == MiddleCode[1] )
						case0++;
					else if( (it->field[0] != i && it->field[1] == j && j  == MiddleCode[1]) || (it->field[0] == i && i == MiddleCode[0] && it->field[1] != j) )
						case1++;
					else if( it->field[0] == i && i != MiddleCode[0] && it->field[1] == j && j != MiddleCode[1])
						case2++;
					else if( (it->field[0] == i && i != MiddleCode[0] && it->field[1] != j) || (it->field[0] != i && it->field[1] == j && j!= MiddleCode[1]) )
						case3++;
					else if(it->field[0] != i && it->field[1] != j)
						case4++;

					it++;
				}
				
				it = edgeComb.begin();				

				if(case4>=case3 && case4>=case2 && case4>=case1 && case4>=case0 && case4<=nextQuestionMax)
				{
					if( (containsEdge(edgeComb, i,j) && case4 == nextQuestionMax) || case4 < nextQuestionMax)
					{
						nextQuestionMax = case4;
						changeQuestionFlag = true;
					}
				}
				else if(case3>=case4 && case3>=case2 && case3>=case1 && case3>=case0 && case3<=nextQuestionMax)
				{
					if( (containsEdge(edgeComb, i,j) && case3 == nextQuestionMax) || case3 < nextQuestionMax)
					{
						nextQuestionMax = case3;
						changeQuestionFlag = true;
					}
				}
				else if(case2>=case3 && case2>=case4 && case2>=case1 && case2>=case0 && case2<=nextQuestionMax)
				{
					if( (containsEdge(edgeComb, i,j) && case2 == nextQuestionMax) || case2 < nextQuestionMax)
					{
						nextQuestionMax = case2;
						changeQuestionFlag = true;
					}
				}
				else if(case1>=case3 && case1>=case2 && case1>=case4 && case1>=case0 && case1<=nextQuestionMax)
				{
					if( (containsEdge(edgeComb, i,j) && case1 == nextQuestionMax) || case1 < nextQuestionMax)
					{
						nextQuestionMax = case1;
						changeQuestionFlag = true;
					}	
				}
				else if(case0>=case3 && case0>=case2 && case0>=case1 && case0>=case4 && case0<=nextQuestionMax)
				{
					if( (containsEdge(edgeComb, i,j) && case0 == nextQuestionMax) || case0 < nextQuestionMax)
					{
						nextQuestionMax = case0;
						changeQuestionFlag = true;
					}
				}
				
				if(changeQuestionFlag)
				{
					currentQuestion[0]=i;
					currentQuestion[1]=j;
					changeQuestionFlag = false;
				}

				case4 = case3 = case2 = case1 = case0 = 0;
			}
							
		}

	}

}

void getNextCornerQuestion(list<corner> &cornerComb, int currentQuestion[], int MiddleCode[])
{
	int case0=0, case1=0, case2=0, case3=0, case4=0; // case0 = {2,2} case1 = {0,2} case2 = {1,1} case3 = {0,1} case4 = {0,0}
	int nextQuestionMax = 39439;
	bool changeQuestionFlag = false;
	list<corner>::iterator it = cornerComb.begin();

	for(int i = 0; i<6 ; i++)
	{
		for(int j = 0; j<6; j++)
		{
			if(j!=i)
			{
				while(it!=cornerComb.end())
				{
					if( it->field[0] == i && i == MiddleCode[0] && it->field[1] == j && j == MiddleCode[1] )
						case0++;
					else if( (it->field[0] != i && it->field[1] == j && j  == MiddleCode[1]) || (it->field[0] == i && i == MiddleCode[0] && it->field[1] != j) )
						case1++;
					else if( it->field[0] == i && i != MiddleCode[0] && it->field[1] == j && j != MiddleCode[1])
						case2++;
					else if( (it->field[0] == i && i != MiddleCode[0] && it->field[1] != j) || (it->field[0] != i && it->field[1] == j && j!= MiddleCode[1]) )
						case3++;
					else if(it->field[0] != i && it->field[1] != j)
						case4++;

					it++;
				}
				
				it = cornerComb.begin();
			
				// neue funktionen
				if(case4>=case3 && case4>=case2 && case4>=case1 && case4>=case0 && case4<=nextQuestionMax)
				{
					if( (containsCorner(cornerComb, i,j) && case4 == nextQuestionMax) || case4 < nextQuestionMax)
					{
						nextQuestionMax = case4;
						changeQuestionFlag = true;
					}
				}
				else if(case3>=case4 && case3>=case2 && case3>=case1 && case3>=case0 && case3<=nextQuestionMax)
				{
					if( (containsCorner(cornerComb, i,j) && case3 == nextQuestionMax) || case3 < nextQuestionMax)
					{
						nextQuestionMax = case3;
						changeQuestionFlag = true;
					}
				}
				else if(case2>=case3 && case2>=case4 && case2>=case1 && case2>=case0 && case2<=nextQuestionMax)
				{
					if( (containsCorner(cornerComb, i,j) && case2 == nextQuestionMax) || case2 < nextQuestionMax)
					{
						nextQuestionMax = case2;
						changeQuestionFlag = true;
					}
				}
				else if(case1>=case3 && case1>=case2 && case1>=case4 && case1>=case0 && case1<=nextQuestionMax)
				{
					if( (containsCorner(cornerComb, i,j) && case1 == nextQuestionMax) || case1 < nextQuestionMax)
					{
						nextQuestionMax = case1;
						changeQuestionFlag = true;
					}	
				}
				else if(case0>=case3 && case0>=case2 && case0>=case1 && case0>=case4 && case0<=nextQuestionMax)
				{
					if( (containsCorner(cornerComb, i,j) && case0 == nextQuestionMax) || case0 < nextQuestionMax)
					{
						nextQuestionMax = case0;
						changeQuestionFlag = true;
					}
				}
				
				if(changeQuestionFlag)
				{
					currentQuestion[0]=i;
					currentQuestion[1]=j;
					changeQuestionFlag = false;
				}

				case4 = case3 = case2 = case1 = case0 = 0;
			}
							
		}

	}

}

void sortOutImpossibleCodes(int currentguess[], list<middle> &midComb, int currentAnswer[])
{
	//cout << "In Funktion sortOutImpossibleCodes:" << endl;
	
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
			//cout << "Combination: " << it->field1 << it->field2 <<" sorted out!"<<endl;
			
			it = midComb.erase(it);
			if (it == midComb.end())
				return;
			continue;
		}
        it++;
	}
}

void sortOutImpossibleEdges(int currentguess[], list<edge> &edgeComb, int currentAnswer[], int MiddleCode[], int orientation[])
{
	list<edge>::iterator it;
	it = edgeComb.begin();

	int tempAnswer[2] = {0,0};

	while(it != edgeComb.end())
	{
		if(currentguess[0] == it->field[0] && it->field[0] == MiddleCode[0] && it->field[1] == MiddleCode[1])
			tempAnswer[0]=2;

		else if(currentguess[0] != it->field[0])
			tempAnswer[0]=0;

		else
			tempAnswer[0]=1;

		if(currentguess[1] == it->field[1] && it->field[1] == MiddleCode[1] && it->field[0] == MiddleCode[0])
                        tempAnswer[1]=2;

                else if(currentguess[1] != it->field[1])
                        tempAnswer[1]=0;

                else
                        tempAnswer[1]=1;

		sortAnswer(tempAnswer);
		sortAnswer(currentAnswer);

		if(tempAnswer[0]!= currentAnswer[0] || tempAnswer[1] != currentAnswer[1])
		{
		//	cout << endl << "Guess " << currentguess[0] << currentguess[1] << "Muster" << MiddleCode[0] << it->field[0] << it->field[1]<< MiddleCode[1] <<"   ";
		//	cout << "TempAnswer" << tempAnswer[0] << tempAnswer[1] << " RealAnswer"<< currentAnswer[0] << currentAnswer [1] << " Combination: " << it->field[0] << it->field[1] << " sorted out!" << endl;
			
						
			it = edgeComb.erase(it);
			if(it == edgeComb.end())
				return;
			continue;

		}
		it++;
	}

}

void sortOutImpossibleCorners(int currentguess[], list<corner> &cornerComb, int currentAnswer[], int MiddleCode[])
{
	list<corner>::iterator it;
	it = cornerComb.begin();

	int tempAnswer[2] = {0,0};

	while(it != cornerComb.end())
	{
		if(currentguess[0] == it->field[0] && it->field[0] == MiddleCode[0] && it->field[1] == MiddleCode[1])
			tempAnswer[0]=2;

		else if(currentguess[0] != it->field[0])
			tempAnswer[0]=0;

		else
			tempAnswer[0]=1;

		if(currentguess[1] == it->field[1] && it->field[1] == MiddleCode[1] && it->field[0] == MiddleCode[0])
                        tempAnswer[1]=2;

                else if(currentguess[1] != it->field[1])
                        tempAnswer[1]=0;

                else
                        tempAnswer[1]=1;

		sortAnswer(tempAnswer);
		sortAnswer(currentAnswer);

		if(tempAnswer[0]!= currentAnswer[0] || tempAnswer[1] != currentAnswer[1])
		{
		//	cout << endl << "Guess " << currentguess[0] << currentguess[1] << "Muster" << MiddleCode[0] << it->field[0] << it->field[1]<< MiddleCode[1] <<"   ";
		//	cout << "TempAnswer" << tempAnswer[0] << tempAnswer[1] << " RealAnswer"<< currentAnswer[0] << currentAnswer [1] << " Combination: " << it->field[0] << it->field[1] << " sorted out!" << endl;
			
						
			it = cornerComb.erase(it);
			if(it == cornerComb.end())
				return;
			continue;

		}
		it++;
	}
}

bool containsMiddle(list<middle> &midComb, int a, int b)
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

bool containsEdge(list<edge> &edgeComb, int a, int b)
{
	list<edge>::iterator it = edgeComb.begin();

        while(it != edgeComb.end())
        {
                if (it->field[0] == a && it->field[1] == b)
                        return true;

                it++;
        }

        return false;
}

bool containsCorner(list<corner> &cornerComb, int a, int b)
{
	list<corner>::iterator it = cornerComb.begin();

        while(it != cornerComb.end())
        {
                if (it->field[0] == a && it->field[1] == b)
                        return true;

                it++;
        }

        return false;
}

#endif













