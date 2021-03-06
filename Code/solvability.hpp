#ifndef SOLVABILITY_HPP
#define SOLVABILITY_HPP

// https://math.stackexchange.com/questions/127577/how-to-tell-if-a-rubiks-cube-is-solvable
// online solver:   https://rubiks-cube-solver.com/
// solver:          http://kociemba.org/cube.htm

#include <iostream>
#include <stdlib.h>
#include <string>
#include <cmath>
#include <time.h>
#include <stdio.h>
#include <ctime>
#include <vector>
#include <list>
#include <iterator>
#include "cubeoperations.hpp"

#define useUIsolvability 0

using namespace std;

int solvable = 0;
int counterPerm = 0; 


//////////////////// PROTOTYPES ////////////////////
void permutationparitytest(int permutationCube[6][3][3]);
int permutationparitytestEdges(int permutationCube[6][3][3]);
int cornerparitytest(int cornercube[6][3][3]);
int edgepartitytest(int edgecube[6][3][3]);
int checksolvability(int checkcube[6][3][3]);

void permutationparitytestCorners(int permutationCube[6][3][3]){
	int cnt=0;
	int visitedCorner[8]={0,0,0,0,0,0,0,0};
	long cornerAdress[8];
	int corner[8][3];
	int i=0;
	int firstIndexSum=0;
	int indexSum=0;
	int whileCnt=0;
	
    getCorners(corner, permutationCube); 

/*
	cornerAdress[0]=14;
	cornerAdress[1]=34;
	cornerAdress[2]=23;
	cornerAdress[3]=12;
	cornerAdress[4]=145;
	cornerAdress[5]=345;
	cornerAdress[6]=235;
	cornerAdress[7]=125;
*/

	cornerAdress[0]=12;
	cornerAdress[1]=14;
	cornerAdress[2]=34;
	cornerAdress[3]=23;
	cornerAdress[4]=125;
	cornerAdress[5]=145;
	cornerAdress[6]=345;
	cornerAdress[7]=235;

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
 //   cout << "sum c-test" << cnt << endl;
// von hier

   // int cnt = 0; 
    int PlaceToBe[12][2]; 
    int NextEdge = 0;
    PlaceToBeEdges(PlaceToBe, permutationCube);

    int EdgeVisits[12] = {0,0,0,0,0,0,0,0,0,0,0,0};

    int EdgesToCheck[12][2];
    getEdges(EdgesToCheck, permutationCube);

    for(int i = 0; i < 12; i++){
            if( ((EdgesToCheck[i][0] == PlaceToBe[i][0]) && (EdgesToCheck[i][1] == PlaceToBe[i][1])) ||        
                ((EdgesToCheck[i][0] == PlaceToBe[i][1]) && (EdgesToCheck[i][1] == PlaceToBe[i][0]))){
                EdgeVisits[i]=1;    
                cnt += 2;  
           //     cout << "edge" << i << " at correct position" << endl;   
            }
    }
      //          cout << "cnt: " << cnt << endl;    
    
    for(int i = 0; i < 12; i++){
  //  cout << "EdgeVisits: "; 
  //  for(int j = 0; j < 12; j++)
  //      cout << EdgeVisits[j] << " | "; 
  //  cout << endl;


        if(EdgeVisits[i]==0){
        NextEdge = i;
            while(1){

                cnt ++;
                //cout << "cnt: " << cnt << endl;

                if(EdgeVisits[NextEdge]!=0){
               //     cout << "break - Edge"<<NextEdge<<"\tvisits: "<< EdgeVisits[NextEdge]<<endl;
                    break;
                }
                EdgeVisits[NextEdge] = 1;
               // cout << "NextEdge:  " << NextEdge << "\tvisits: " << EdgeVisits[NextEdge] << "\tcnt: " << cnt << endl;
                for(int j = 0; j < 12; j++){

                    if( ((EdgesToCheck[NextEdge][0] == PlaceToBe[j][0]) && (EdgesToCheck[NextEdge][1] == PlaceToBe[j][1])) ||        
                        ((EdgesToCheck[NextEdge][0] == PlaceToBe[j][1]) && (EdgesToCheck[NextEdge][1] == PlaceToBe[j][0]))){ 
                        //cout << "nexedgecol: " << PlaceToBe[j][0] << PlaceToBe[j][1] << endl;   
                        NextEdge = j;  
                        break;                  
                    }
                   
                }            

            }
            //cout << "cnt: " << cnt << endl;
        }
   }











  //  cout << "sum gesamt-test" << cnt << endl;


// bis hier
	if(cnt%2||whileCnt>16)
	{
		solvable=0;
        if(useUIsolvability)
		    cout << "Permutation Partity JK.Test \t\033[31mFAIL (Sum: " << cnt<< ")\033[39m" << endl;
	}
	else
	{
		solvable=solvable+1;
        if(useUIsolvability)
		    cout << "Permutation Partity JK.Test \tPASS (Sum: " << cnt << ")" << endl;
	}
	//cout<<"Cycle Summe="<<cnt<<endl;
	return;

}

int permutationparitytestEdges(int permutationCube[6][3][3]){

    int counter = 0; 
    int PlaceToBe[12][2]; 
    int NextEdge = 0;
    PlaceToBeEdges(PlaceToBe, permutationCube);

    int EdgeVisits[12] = {0,0,0,0,0,0,0,0,0,0,0,0};

    int EdgesToCheck[12][2];
    getEdges(EdgesToCheck, permutationCube);

    for(int i = 0; i < 12; i++){
            if( ((EdgesToCheck[i][0] == PlaceToBe[i][0]) && (EdgesToCheck[i][1] == PlaceToBe[i][1])) ||        
                ((EdgesToCheck[i][0] == PlaceToBe[i][1]) && (EdgesToCheck[i][1] == PlaceToBe[i][0]))){
                EdgeVisits[i]=1;    
                counter += 2;  
           //     cout << "edge" << i << " at correct position" << endl;   
            }
    }
      //          cout << "counter: " << counter << endl;    
    
    for(int i = 0; i < 12; i++){
  //  cout << "EdgeVisits: "; 
  //  for(int j = 0; j < 12; j++)
  //      cout << EdgeVisits[j] << " | "; 
  //  cout << endl;


        if(EdgeVisits[i]==0){
        NextEdge = i;
            while(1){

                counter ++;
                //cout << "counter: " << counter << endl;

                if(EdgeVisits[NextEdge]!=0){
               //     cout << "break - Edge"<<NextEdge<<"\tvisits: "<< EdgeVisits[NextEdge]<<endl;
                    break;
                }
                EdgeVisits[NextEdge] = 1;
               // cout << "NextEdge:  " << NextEdge << "\tvisits: " << EdgeVisits[NextEdge] << "\tcounter: " << counter << endl;
                for(int j = 0; j < 12; j++){

                    if( ((EdgesToCheck[NextEdge][0] == PlaceToBe[j][0]) && (EdgesToCheck[NextEdge][1] == PlaceToBe[j][1])) ||        
                        ((EdgesToCheck[NextEdge][0] == PlaceToBe[j][1]) && (EdgesToCheck[NextEdge][1] == PlaceToBe[j][0]))){ 
                        //cout << "nexedgecol: " << PlaceToBe[j][0] << PlaceToBe[j][1] << endl;   
                        NextEdge = j;  
                        break;                  
                    }
                   
                }            

            }
            //cout << "counter: " << counter << endl;
        }
   }
	if(counter%2 != 0)
	{
		solvable=0;
        if(useUIsolvability)
		    cout << "Permutation Partity E-Test \t\033[31mFAIL (Sum: " << counter<< ")\033[39m" << endl;
	}
	else
	{
		solvable=solvable+1;
        if(useUIsolvability)
		    cout << "Permutation Partity E-Test \tPASS (Sum: " << counter << ")" << endl;
	}

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
            if(useUIsolvability)
                cout << "\033[31munsolvable: multiple colors on corners \t\t(position: " << i << ")\033[39m" << endl;
            break;
        }
    }

    for(int i = 0; i < 8; i++){    
        if(corner[i][0] == topcol || corner[i][0] == botcol)
            {
                sum += 0;
                //cout << "corner" << i << ": "<< sum << endl;
            }
        else if(corner[i][1] == topcol || corner[i][1] == botcol)
            {
                sum += 1;
                //cout << "corner" << i << ": "<< sum << endl;
            }
        else if(corner[i][2] == topcol || corner[i][2] == botcol)
            {
                sum += 2;
                //cout << "corner" << i << ": "<< sum << endl;
            }
        else{
                if(useUIsolvability)
                    cout << "\033[31munsolvable: Error at corner orientation\t(position: " << i << ")\033[39m" << endl;
                solvable = 0; 
                return solvable; 
                break;
            }

    }    

    if(sum%3 == 0){
        if(useUIsolvability)
            cout << "Corner Partity Test \t\tPASS (Sum: " << sum << ")" << endl;
        solvable += 1; 
        }
    else{ 
        if(useUIsolvability)
            cout << "Corner Partity Test \t\t\033[31mFAIL (Sum: " << sum << ")\033[39m" << endl;
        solvable = 0;
        }
//t\033[31mFAIL (Sum: " << sum << ")\033[39m"
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

    if(            edge[i][0] == topcol || edge[i][0] == botcol ) 
    {
            sum += 1; 
    }
    else if(  edge[i][1] == topcol || edge[i][1] == botcol )
        sum += 0;
     else if (      edge[i][0] == frocol || edge[i][0] == baccol ) sum +=1;
      else if(  edge[i][1] == frocol || edge[i][1] == baccol )
        sum += 0;
     else{
        if(useUIsolvability)
            cout << "\033[31munsolvable: Error at Edge Partity Test \t(position: " << i << ")\033[39m" << endl;
        solvable = 0; 
        return solvable;
        }

    }

    if(sum%2 == 0){
        if(useUIsolvability)        
            cout << "Edge Partity Test \t\tPASS (Sum: " << sum << ")" << endl;
        solvable += 1;
    }
    else 
        if(useUIsolvability)
            cout << "Edge Partity Test \t\t\033[31mFAIL (Sum: " << sum << ")\033[39m" << endl;

    

}


int checksolvability(int checkcube[6][3][3])
{
    int solved = 0;
    int error = 0; 
    int counter = 0; 

    solvable = 0; 

    
    edgepartitytest(checkcube);
    cornerparitytest(checkcube);
    permutationparitytestCorners(checkcube);
  //  permutationparitytestEdges(checkcube);  // wird jetzt im Corners gefragt

    counter ++;
    if(solvable !=3){
        if(useUIsolvability){
            cout << "\033[31m___________________________"       <<      endl << endl; 
            cout <<         "       unsolvable" << endl;
            cout <<         "___________________________\033[39m" << endl << endl;
        }
        error = 1; 
        return 0;
    }
    else{
        if(useUIsolvability){
            cout << "\033[92m___________________________" << endl << endl; 
            cout <<         "        solvable" << endl;
            cout <<         "___________________________\033[39m" << endl << endl;
        }
        return 1;
    }

    //usleep(1000000*0.25);  
              
}

#endif
