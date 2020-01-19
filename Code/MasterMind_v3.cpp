#include <iostream>
#include <list>
#include <iterator>
using namespace std;

struct corner;
struct edge;
struct middle;

int findMiddle(int n);
void sortAnswer(int answer[]);
void buildCombOfTwo(list<middle> &midComb);
void buildCombOfEdge(list<edge> EdgeCodes[], int MiddleCodes[]);
void eliminateFound(list<middle> &midComb, int foundColours[]);
void getNextQuestion(list<middle> &midComb, int currentQuestion[]);
void sortOutImpossibleCodes(int currentguess[], list<middle> &midComb, int currentAnswer[]);
bool contains (list<middle> &midComb, int a, int b);

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

int findMiddle(int foundColour[])
{	
	list<middle> midComb;
	
	for (int i=1; i<7; i+=2)
	{
		int currentAnswer[2] = { 0,0 }, currentGuess[2] = {1,2}; // eventuell mit geratenem cube abstimmen
		
		buildCombOfTwo(midComb);
		eliminateFound(midComb, foundColour);
		
		cout << "\nFrage Feld" << i <<":" << currentGuess[0] << "\nFrage Feld" << i+1 <<":" << currentGuess[1] << endl;
		
		// server input
		cin >> currentAnswer[0];
		cin >> currentAnswer[1];
		
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
/*
int findEdges(int n, list <edge> EdgeComb[12])
{		
	int foundEdges[24]={0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};
	int currentAnswer[2] = {0,0}, currentGuess[2] = {1,2};
	
	eliminateFoundEdges(edgeComb, foundEdges); //sortiert bereits gefundene Kanten aus

		//Hier currentGuess an Server fragen und Antwort erhalten
		cout << "\nFrage Feld" << i <<":" << currentGuess[0] << "\nFrage Feld" << i+1 <<":" << currentGuess[1] << endl;
		cin >> currentAnswer[0];
		cin >> currentAnswer[1];
		
	sortOutImpossibleCodes(currentGuess, edgeComb, currentAnswer); //sortiert alle Kombinationen aus, die nicht zur Antwort passen

		while(1)
		{
			getNextQuestion(edgeComb, currentGuess);//eliminateSidecode(); 
			
			cout << "\nFrage Feld" << i <<" :" << currentGuess[0] << "\nFrage Feld" << i+1 <<" :" << currentGuess[1] << endl;
			
			cin >> currentAnswer[0];
			cin >> currentAnswer[1];
			
			sortOutImpossibleCodes(currentGuess, edgeComb, currentAnswer);

			if(edgeComb.size()==1)
				break;
		}
		
		cout << "Farbe Feld" << i <<" ist: "<< edgeComb.begin()->field1 << " Farbe Feld" << i+1 <<" ist: " << edgeComb.begin()->field2;
		
		foundColour[i-1]=edgeComb.begin()->field1;
		foundColour[i]=edgeComb.begin()->field2;	
	

	cout << "Ecken:";
	for(int i=0; i<6; i++)
		 cout << foundColour[i] << endl;

	return 0;
}
*/

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

void eliminateFoundEdges(list<edge> &edgeComb, int foundEdges[])
{
	list<edge>::iterator it = edgeComb.begin();

	cout << "In funktion EliminateFoundEdges" << endl;

	for (int i=0; i<24; i+=2)
	{
		while(it != edgeComb.end())
		{
			if(it->field1 == foundEdges[i] || it->field2 == foundEdges[i+2])
			{
				cout << "erased Edge : " << it->field1 << it->field2 << endl;
				it = edgeComb.erase(it);
				if (it == edgeComb.end())
					return;
				continue;
			}
			it++;
		}
		it = edgeComb.begin();
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
	int MiddleCode[6] = {0,5,1,3,2,4};
	list <edge> EdgeCodes[12];
	list <corner> CornerCodes[8];
	
	//findMiddle(MiddleCode);
	buildCombOfEdge(EdgeCodes, MiddleCode);
	
	for (int j=0; j<12; j++)
	{
		cout << "List number " << j << " ";
		
		list <edge>::iterator it = EdgeCodes[j].begin();
		
		while(it != EdgeCodes[j].end())
		{
			cout << it->field1 << it->field2 << " | ";
			
			it++;
		}
		
		cout << endl;
	}

	return 0;
}

