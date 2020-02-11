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
void changeAnswer(string& strAnswer, int* arrAnswer);
void getNextEdgeQuestion(list<edge> &edgeComg, int currentQuestion[], int MiddleCode[]);
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
			
			cout << "\nFrage Feld" << i-1 <<" :" << currentGuess[0] << "\nFrage Feld" << i <<" :" << currentGuess[1] << endl;
			
			//Server Question 
			askTwo(currentAnswer, currentGuess, field1, field2); //void askTwo(int putAnswer [2], int question [2], int field1 [3], int field2 [3])

			
			
			sortOutImpossibleCodes(currentGuess, midComb, currentAnswer);

			if(midComb.size()==1)
				break;
		}
		
		
		cout << "Farbe Feld " << i-1 <<" ist: "<< midComb.begin()->field1 << " | Farbe Feld " << i <<" ist: " << midComb.begin()->field2 << endl;
		
		foundColour[i-1]=midComb.begin()->field1;
		foundColour[i]=midComb.begin()->field2;	
	}

	cout << "Mittelfelder:\n";
	
	for(int i=0; i<6; i++)
	{
		 cout << foundColour[i] << endl;

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
			
			cout << midComb.back().field1 << midComb.back().field2 << endl;
		}
	}
}

void buildCombOfCorner(list<corner> CornerCodes[], int MiddleCodes[])
{
	cout << "In funktion build Comb of Corner" << endl;
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
	
					tmp.field1 = cornerGeometrie[i].field1;
					tmp.field2 = cornerGeometrie[i].field2;
					tmp.field3 = cornerGeometrie[i].field3;

					CornerCodes[k].push_back(tmp);
					
					tmp.field1 = cornerGeometrie[i].field3;
					tmp.field2 = cornerGeometrie[i].field1;
					tmp.field3 = cornerGeometrie[i].field2;

					CornerCodes[k].push_back(tmp);

					tmp.field1 = cornerGeometrie[i].field2;
					tmp.field2 = cornerGeometrie[i].field3;
					tmp.field3 = cornerGeometrie[i].field1;

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
				
				tmp.field1=i;
				tmp.field2=j;
				
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


void getNextEdgeQuestion(list<edge> &edgeComb, int currentQuestion[], int MiddleCode[])
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
					if( it->field1 == i && i == MiddleCode[0] && it->field2 == j && j == MiddleCode[1] )
						case0++;

					else if( (it->field1 != i && it->field2 == j && j  == MiddleCode[1]) || (it->field1 == i && i == MiddleCode[0] && it->field2 != j) )
						case1++;
					else if( it->field1 == i && i != MiddleCode[0] && it->field2 == j && j != MiddleCode[1] )
						case2++;
					else if( (it->field1 == i && i != MiddleCode[0] && it->field2 != j) || (it->field1 != i && it->field2 == j && j!= MiddleCode[1]) )
						case3++;
					else if(it->field1 != i && it->field2 != j)
						case4++;

					it++;
				}
				
				it = edgeComb.begin();				

				if(case4>=case3 && case4>=case2 && case4>=case1 && case4>=case0 && case4>=nextQuestionMax)
				{
					if( (containsEdge(edgeComb, i,j) && case4 == nextQuestionMax) || case4 < nextQuestionMax)
					{
						nextQuestionMax = case4;
						changeQuestionFlag = true;
					}
				}
				else if(case3>=case4 && case3>=case2 && case3>=case1 && case3>=case0 && case3>=nextQuestionMax)
				{
					if( (containsEdge(edgeComb, i,j) && case3 == nextQuestionMax) || case3 < nextQuestionMax)
					{
						nextQuestionMax = case3;
						changeQuestionFlag = true;
					}
				}
				else if(case2>=case3 && case2>=case4 && case2>=case1 && case2>=case0 && case2>=nextQuestionMax)
				{
					if( (containsEdge(edgeComb, i,j) && case2 == nextQuestionMax) || case2 < nextQuestionMax)
					{
						nextQuestionMax = case2;
						changeQuestionFlag = true;
					}
				}
				else if(case1>=case3 && case1>=case2 && case1>=case4 && case1>=case0 && case1>=nextQuestionMax)
				{
					if( (containsEdge(edgeComb, i,j) && case1 == nextQuestionMax) || case1 < nextQuestionMax)
					{
						nextQuestionMax = case1,
						changeQuestionFlag = true;
					}	
				}
				else if(case0>=case3 && case0>=case2 && case0>=case1 && case0>=case4 && case0>=nextQuestionMax)
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

void sortOutImpossibleEdges(int currentguess[], list<edge> &edgeComb, int currentAnswer[], int MiddleCode[])
{
	list<edge>::iterator it;
	it = edgeComb.begin();

	int tempAnswer[2] = {0,0};

	while(it != edgeComb.end())
	{
		if(currentguess[0] == it->field1 && currentguess[0] == MiddleCode[0])
			tempAnswer[0]=2;
		else if(currentguess[0] == it ->field1 && currentguess[0] != MiddleCode[0])
			tempAnswer[0]=1;
		else
			tempAnswer[0]=0;

		if(currentguess[1] == it->field2 && currentguess[1] == MiddleCode[1])
                        tempAnswer[1]=2;
                else if(currentguess[1] == it ->field2 && currentguess[1] != MiddleCode[1])
                        tempAnswer[1]=1;
                else
                        tempAnswer[1]=0;

		if(tempAnswer[0]!= currentAnswer[0] || tempAnswer[1] != currentAnswer[1])
		{
			cout << "Combination: " << it->field1 << it->field2 << " sorted out!" << endl;
			
			it = edgeComb.erase(it);
			if(it == edgeComb.end())
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
                if (it->field1 == a && it->field2 == b)
                        return true;

                it++;
        }

        return false;
}


#endif













