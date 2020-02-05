#include <iostream>
#include <stdlib.h>
#include <string>
#include <cmath>
#include <time.h>
#include <stdio.h>
#include <ctime>
#include <algorithm>    // std::random_shuffle
#include <unistd.h>

#include <vector>
#include "rubikssolver_header.hpp"

#include <list>
#include <iterator>
//#include "QuestionCube.hpp"


using namespace std;


int cube_customcolor[6][3][3];

int solveable = 0;
//int getCorners(int** array, int ***cubetofind);
//void getCorners();

struct corner;
struct edge;
struct middle;


//////////////////// PROTOTYPES ////////////////////
int edgepartitytest();		    
int cornerparitytest();
void permutationparitytest(int permutationCube[6][3][3]);

void buildCombOfEdge(list<edge> EdgeCodes[], int MiddleCodes[]);

int cube[6][3][3] = {
	{ { 0, 0, 0 }, { 0, 0, 0 }, { 0, 0, 0 } },   //yellow side
	{ { 1, 1, 1 }, { 1, 1, 1 }, { 1, 1, 1 } },   //orange side
	{ { 2, 2, 2 }, { 2, 2, 2 }, { 2, 2, 2 } },   //blue side
	{ { 3, 3, 3 }, { 3, 3, 3 }, { 3, 3, 3 } },   //red side
	{ { 4, 4, 4 }, { 4, 4, 4 }, { 4, 4, 4 } },   //green side
	{ { 5, 5, 5 }, { 5, 5, 5 }, { 5, 5, 5 } } }; //white side

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



void permutationparitytest(int permutationCube[6][3][3]){
	int cnt=0;
	int visitedCorner[8]={0,0,0,0,0,0,0,0};
	long cornerAdress[8];
	int corner[8][3];
	int i=0;
	int firstIndexSum=0;
	int indexSum=0;
	int whileCnt=0;
	
    getCorners(corner, permutationCube); 

	cornerAdress[0]=14;
	cornerAdress[1]=34;
	cornerAdress[2]=23;
	cornerAdress[3]=12;
	cornerAdress[4]=145;
	cornerAdress[5]=345;
	cornerAdress[6]=235;
	cornerAdress[7]=125;

	while(1)
	{
		whileCnt=0;

		for(i=0; i<8; i++)
		{
			//cout << "bin in for" << endl;
			
			if(visitedCorner[i]==0)
			{
				//cout<<cnt<<endl;
				cnt=cnt+1;
				break;
			}
		}
		if(i==8)
			break;
			//cout<<cnt<<endl;

		visitedCorner[i]=1;
		firstIndexSum=cornerAdress[i];
		
		while(1)
		{
			int index[3];
			for(int j=0; j<3; j++)
			{	
				for(int k=0;k<6; k++)
				{
					if(permutationCube[k][1][1]==corner[i][j])
					{		
						index[j]=k;
						break;
					}
				}
			}
			
			sort(index,index+3);
			
			indexSum=index[0]*100+index[1]*10+index[2];

			for(i=0;i<8;i++)
			{
				if(whileCnt==0 && indexSum==firstIndexSum)
				{
					cnt=cnt+1;
					break;
				}
				if(indexSum==firstIndexSum)
				{
                    cnt ++; 
					break;
				}
				if(cornerAdress[i]==indexSum)
				{
					visitedCorner[i]=1;
					cnt=cnt+1;
					break;	
				}
			}
			
			if(indexSum==firstIndexSum)
			{
				break;
			}
			whileCnt=whileCnt+1;
			if(whileCnt>16)
				break;
		}
		if(whileCnt>16)
			break;

	}
	if(cnt%2||whileCnt>16)
	{
		solveable=0;
		 cout << "Permutation Partity Test \t\033[31mFAIL (Sum: " << cnt<< ")\033[39m" << endl;
	}
	else
	{
		solveable=solveable+1;
		cout << "Permutation Partity Test \tPASS (Sum: " << cnt << ")" << endl;
	}
	//cout<<"Cycle Summe="<<cnt<<endl;
	return;

}


int cornerparitytest(int cornercube[6][3][3]){
    int topcol = cornercube[0][1][1];
    int botcol = cornercube[5][1][1];

    int corner[8][3];
    int sum = 0;

    getCorners(corner, cornercube);

    for(int i = 0; i < 8; i++){
        if( corner[i][0] == corner[i][1] || 
            corner[i][1] == corner[i][2] || 
            corner[i][2] == corner[i][0]){ 
            cout << "\033[31munsolveable: multiple colors on corners \t\t(position: " << i << ")\033[39m" << endl;
            break;
        }
    }

    for(int i = 0; i < 8; i++){    
        if(corner[i][0] == topcol || corner[i][0] == botcol)
            {
                sum += 0;
                //cout << "corner" << i << ": "<< sum << endl;
            }
        else if(corner[i][2] == topcol || corner[i][2] == botcol)
            {
                sum += 1;
                //cout << "corner" << i << ": "<< sum << endl;
            }
        else if(corner[i][1] == topcol || corner[i][1] == botcol)
            {
                sum += 2;
                //cout << "corner" << i << ": "<< sum << endl;
            }
        else{
                cout << "\033[31munsolveable: Error at corner orientation\t(position: " << i << ")\033[39m" << endl;
                solveable = 0; 
                return solveable; 
                break;
            }

    }    

    if(sum%3 == 0){
        cout << "Corner Partity Test \t\tPASS (Sum: " << sum << ")" << endl;
        solveable += 1; 
        }
    else{ 
        cout << "Corner Partity Test \t\033[101m FAIL (Sum: " << sum << ")\033[0m" << endl;
        solveable = 0;
        }

}



int edgepartitytest(int edgecube[6][3][3]){

    int topcol = edgecube[0][1][1];
    int botcol = edgecube[5][1][1];
    int frocol = edgecube[2][1][1];
    int baccol = edgecube[4][1][1];

    int edge[12][2];
     
    getEdges(edge, edgecube);
       

    int sum = 0; 
    
    for(int i = 0; i <12; i++){ 

     if(            edge[i][0] == topcol || edge[i][0] == botcol
                ||  edge[i][1] == topcol || edge[i][1] == botcol )
        sum += 0;
     else if (      edge[i][0] == frocol || edge[i][0] == baccol
                ||  edge[i][1] == frocol || edge[i][1] == baccol )
        sum += 1;
     else{
        cout << "\033[31munsolveable: Error at Edge Partity Test \t(position: " << i << ")\033[39m" << endl;
        solveable = 0; 
        return solveable;
        }

    }

    if(sum%2 == 0)
        cout << "Edge Partity Test \t\tPASS (Sum: " << sum << ")" << endl;
    else 
        cout << "Edge Partity Test \t\033[31mFAIL (Sum: " << sum << ")\033[39m" << endl;

    solveable += 1;

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



int main()
{


    srand((int)time(0));
    int solved = 0;
    int error = 0; 
    int counter = 0; 

    //printCubeColor(probcube);
    //fillcube();

    
    //for(int i = 0; i <10; i++){
/*
    int MiddleCode[6] = {0,5,1,3,2,4};
	list <edge> EdgeCodes[12];
	list <corner> CornerCodes[8];    

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
*/

    do{
        solveable = 0; 
        scramble();
    
        system("clear");
        cout << endl;
        //fillrandom();
        //clearMoves();
        printCubeColor(cube);

        // generate black cube 
        //printCubeStd(cube);
    
        edgepartitytest(cube);
        cornerparitytest(cube);
        permutationparitytest(cube);

        counter ++;
        if(solveable != 3){
            cout << "\033[31m___________________________"       <<      endl << endl; 
            cout <<         "       unsolveable" << endl;
            cout <<         "___________________________\033[39m" << endl << endl;
            error = 1; 

        }
        else{
            cout << "\033[92m___________________________" << endl << endl; 
            cout <<         "        solveable" << endl;
            cout <<         "___________________________\033[39m" << endl << endl;

        }
        cout << "checked cubes: \t" << counter << endl; 
        //usleep(1000000*0.25);  
              
    }
    while(error == 0);

return 0;
}
