#include <iostream>
#include <list>
#include <iterator>
using namespace std;


struct middle;
int findMiddle(int n);
void sortAnswer(int *answer);
void buildCombOfTwo(list<middle> &midComb);
void eliminateFound(list<middle> &midComb, int foundColours[]);
void getNextQuestion(list<middle> &midComb, int currentQuestion[]);
void sortOutImpossibleCodes(int currentguess[], list<middle> &midComb, int currentAnswer[]);

list<middle> midComb;

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


int main()
{
	int n = 2;
	
	findMiddle(n);

	return 0;
}

void sortOutImpossibleCodes(int currentguess[], list<middle> &midComb, int currentAnswer[])
{
	cout << "In funktion sortOut" << endl;
	list<middle>::iterator it;
	it = midComb.begin();
	int tempAnswer[2] = {0,0};
	while(it != midComb.end())
	{
		if (currentguess[0] == it->field1)
			{
			    tempAnswer[0] = 2;
			}
		else
			{
			    tempAnswer[0] = 0;
			}

		if (currentguess[1] == it->field2)
			tempAnswer[1] = 2;
		else
			tempAnswer[1] = 0;

		sortAnswer(tempAnswer);
		sortAnswer(currentAnswer);

		if (tempAnswer[0] != currentAnswer[0] || tempAnswer[1] != currentAnswer[1]) {
			//DELETE ELEMENT of midComb Element flNr
			cout << "Kombination: " << it->field1 << it->field2 <<" sorted out!"<<endl;
			midComb.erase(it);
			it = midComb.begin();
			continue;
		}
        it++;

	}

}

int findMiddle(int n)
{	
	int foundColour[6]={0,0,0,0,0,0};
	
	for (int i=1; i<7; i+=2)
	{
		int currentAnswer[2] = { 0,0 }, currentGuess[2] = {1,2};
		list<middle> midComb;
		
		buildCombOfTwo(midComb); //Bildet alle mˆglichen Farbcombinationen f¸r 2 Mittelfelder in midComb
		cout << "Combos wurden erstellt"<< endl;
		eliminateFound(midComb, foundColour);
		cout << "\nFrage Feld" << i <<":" << currentGuess[0] << "\nFrage Feld" << i+1 <<":" << currentGuess[1] << endl;
		
		cin >> currentAnswer[0];
		cin >> currentAnswer[1];
		
		sortOutImpossibleCodes(currentGuess, midComb, currentAnswer);

		while(1)
		{
			getNextQuestion(midComb, currentGuess);
			
			cout << "\nFrage Feld" << i <<" :" << currentGuess[0] << "\nFrage Feld" << i+1 <<" :" << currentGuess[1] << endl;
			
			cin >> currentAnswer[0];
			cin >> currentAnswer[1];
			
			sortOutImpossibleCodes(currentGuess, midComb, currentAnswer);

			if(midComb.size()==1)
				break;
		}
		
		cout << "Farbe Feld" << i <<" ist: "<< midComb.begin()->field1 << " Farbe Feld" << i+1 <<" ist: " << midComb.begin()->field2;
		
		foundColour[i-1]=midComb.begin()->field1;
		foundColour[i]=midComb.begin()->field2;	
	}

	cout << "Mittelfelder:";
	for(int i=0; i<6; i++)
		 cout << foundColour[i] << endl;

	return 0;
}

void eliminateFound(list<middle> &midComb, int foundColour[])
{
	list<middle>::iterator it = midComb.begin();

	cout << "In funktion Eliminate" << endl;

	while(it != midComb.end())
	{
		for (int i=0; i<6; i++)
		{
			cout << "In funktion Eliminate" << i << endl;
			
			if(it->field1 == foundColour[i] || it->field2 ==foundColour[i])
			{
				cout << "In funktion Eliminate_erase" << endl;
				midComb.erase(it);
				
				it = midComb.begin();
			}
		}
		it++;
	}
}

void buildCombOfTwo(list<middle> &midComb)
{
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


void getNextQuestion(list<middle> &midComb, int *currentQuestion)
{
    int case1=0, case2=0, case3=0; //case1 (0,0) case2(0,2) case3(2,2)
    int *nextQuestion = currentQuestion;
    int nextQuestionMax=7200;
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
				else if(it->field1 == i && it->field2 != j)
					case2++;
				else if(it->field1 != i && it->field2 == j)
					case2++;
				else
					case1++;

				it++;
				}

				if(case1>=case2 && case1>=case3 && case1<=nextQuestionMax)
				{
					nextQuestionMax=case1;
					nextQuestion[0]=i;
					nextQuestion[1]=j;
				}
				else if(case2>=case1 && case2>=case3 && case2<=nextQuestionMax)
				{
					nextQuestionMax=case2;
					nextQuestion[0]=i;
					nextQuestion[1]=j;
				}
				else if(case3>=case1 && case3>=case2 && case3<=nextQuestionMax)
				{
					nextQuestionMax=case3;
					nextQuestion[0]=i;
					nextQuestion[1]=j;
				}
				
				case1=0;
				case2=0;
				case3=0;
				
				it = midComb.begin();
			}
		}
	}
}


