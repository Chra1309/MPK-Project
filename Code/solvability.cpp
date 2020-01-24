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
#include "QuestionCube.hpp"


using namespace std;


int cube_customcolor[6][3][3];

int solveable = 0;
//int getCorners(int** array, int ***cubetofind);
//void getCorners();

struct corner;
struct edge;
struct middle;


//////////////////// PROTOTYPES ////////////////////
string printColor(int); //Ausgabe von Farbe
void printCubeColor(); 	//Ausgabe des Cubes im Terminal in Farbe
void printCubeStd();	//Ausgabe des Cubes im Terminal in Zahlen		
int edgepartitytest();		    
int cornerparitytest();
void permutationparitytest(int permutationCube[6][3][3]);
int getCorners(int array[8][3], int cubetofind[6][3][3]);
int setCorners(int array[8][3], int cubetofind[6][3][3]);
void getEdges(int array[12][2], int cubetofind[6][3][3]);
void setEdges(int edge[12][2], int cube[6][3][3]);
void buildCombOfEdge(list<edge> EdgeCodes[], int MiddleCodes[]);

int cube[6][3][3] = {
	{ { 0, 0, 0 }, { 0, 0, 0 }, { 0, 0, 0 } },   //yellow side
	{ { 1, 1, 1 }, { 1, 1, 1 }, { 1, 1, 1 } },   //orange side
	{ { 2, 2, 2 }, { 2, 2, 2 }, { 2, 2, 2 } },   //blue side
	{ { 3, 3, 3 }, { 3, 3, 3 }, { 3, 3, 3 } },   //red side
	{ { 4, 4, 4 }, { 4, 4, 4 }, { 4, 4, 4 } },   //green side
	{ { 5, 5, 5 }, { 5, 5, 5 }, { 5, 5, 5 } } }; //white side

int probcube[6][3][3] = {
	{ { 1, 6, 2 }, { 6, 6, 6 }, { 6, 6, 6 } },   //yellow side
	{ { 6, 6, 6 }, { 6, 6, 6 }, { 6, 6, 1 } },   //orange side
	{ { 6, 6, 6 }, { 0, 6, 6 }, { 5, 6, 6 } },   //blue side
	{ { 6, 6, 3 }, { 6, 3, 6 }, { 6, 6, 6 } },   //red side
	{ { 6, 6, 6 }, { 6, 6, 6 }, { 6, 2, 6 } },   //green side
	{ { 6, 6, 6 }, { 4, 6, 6 }, { 6, 6, 6 } } }; //white side

void printnumber(int printo[]){
        
    cout << "y: " << printo[0] << " | ";  
    cout << "o: " << printo[1] << " | ";       
    cout << "b: " << printo[2] << " | ";       
    cout << "r: " << printo[3] << " | ";       
    cout << "g: " << printo[4] << " | ";       
    cout << "w: " << printo[5] << endl; 

}


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

int myrandom (int i) { return std::rand()%i;}
/*
int LeftColors(int used[]){
    
    int size; 
    for(int i = 0; i < 6; i++)  
        if(used[i] != 0)
            size ++;
        
}

*/
void fillcube(){
    
    int coluse[6] = {0,0,0,0,0,0};
    
    for(int i = 0; i < 6; i++){
        for(int j = 0; j < 3; j++){
            for(int k = 0; k < 3; k++){
                int curcol = probcube[i][j][k];
                    if(curcol != 6){
                        coluse[curcol] +=1;                       
                    }
            }    
        }
    } 
    cout << endl << "colors used:" << endl;          
    printnumber(coluse);  
 

    //////////////////////////////// fill centers ////////////////////////////////
    {
        int centerUsed[6] = {0,0,0,0,0,0};

        for(int i = 0; i < 6; i++){
            if(probcube[i][1][1] != 6)
                centerUsed[probcube[i][1][1]] += 1;
        } 

        cout << endl << "centers used:" << endl;
        printnumber(centerUsed);  
       
        vector<int> leftColors;
        
        for(int i = 0; i < 6; i++){
            if(centerUsed[i] == 0) 
                leftColors.push_back(i);
        }
        random_shuffle(leftColors.begin(), leftColors.end(), myrandom);

        cout << endl;
        cout << "colors left for center:";
        for(int i=0; i<leftColors.size(); i++)
            cout << ' ' << leftColors.at(i);
        cout << endl;

        for(int i = 0; i < 6; i++){
            //cout << "center is: " << probcube[i][1][1] << endl;
            if(probcube[i][1][1] == 6){
                probcube[i][1][1] = leftColors.back();
            //    cout << "setting center to: " << leftColors.back() << endl;;
                leftColors.pop_back();
            }
            
            //printCubeColor(probcube);
            /*
            cout << "colors left for center:";
                for(int i=0; i<leftColors.size(); i++)
                    cout << ' ' << leftColors.at(i);
         
            cout << endl;
            */
        }
        printCubeColor(probcube); 
                    cout << "________________________ CENTER COMPLETE ________________________" << endl; 
    }
    //////////////////////////////// fill corners ////////////////////////////////     
    {
        int cornerUsed[6] = {0,0,0,0,0,0};

        int corner[8][3];
       // getCorners(corner, probcube);
/*
        for(int i = 0; i < 8; i++){
            for(int j = 0; j < 3; j++){
                if(corner[i][j] != 6)
                    cornerUsed[corner[i][j]] += 1;
            }
            
        } 
        cout << endl << "number of colors in corners:" << endl;
        printnumber(cornerUsed); 
        
         vector<int> leftColors;
        
        for(int i = 0; i < 6; i++){
            for(int j = 0; j < (4-cornerUsed[i]); j++) 
                leftColors.push_back(i);
        }
        //random_shuffle(leftColors.begin(), leftColors.end());      
        cout << endl;
        cout << "colors left for corners:\t";
        for(int i=0; i<leftColors.size(); i++)
            cout << leftColors.at(i) <<  " " ;
        cout << endl;
*/
        int cornerFilled[8] = {0,0,0,0,0,0,0,0};/*
        cout << "numb#1A1A1Aer of filled faces: \t";
        for(int i = 0; i < 8; i++){
            for(int j = 0; j < 3; j++){
                if(corner[i][j] != 6)
                    cornerFilled[i] ++;
            }
            cout << cornerFilled[i] << " ";
        }
        cout << endl;
        */

        getCorners(corner, probcube);
        
        for(int m = 0; m < 6; m++)
            cornerUsed[m] = 0;

        for(int m = 0; m < 8; m++){
            for(int n = 0; n < 3; n++){
                if(corner[m][n] != 6)
                    cornerUsed[corner[m][n]] += 1;
            }
            
        } 
        cout << endl << "coners used:" << endl;
        printnumber(cornerUsed); 


        for(int l = 0; l < 3; l ++){
            for(int k = 0; k < 8; k++){



                int cornerFilled[8] = {0,0,0,0,0,0,0,0};
                //cout << "filled faces: \t\t\t";
                for(int i = 0; i < 8; i++){
                    for(int j = 0; j < 3; j++){
                        if(corner[i][j] != 6)
                            cornerFilled[i] ++;
                    }
                    //cout << cornerFilled[i] << " ";
                }
                //cout << endl;



                //cout << "cornerFilled " << cornerFilled[k] << endl;
                if(cornerFilled[k] == (2-l)){
                    cout << endl << "_________________________________________________________________" << endl;

                    cout << "FILLING UP CORNER: " << k << endl;
                    getCorners(corner, probcube);
                    
                    for(int m = 0; m < 6; m++)
                        cornerUsed[m] = 0;

                    for(int m = 0; m < 8; m++){
                        for(int n = 0; n < 3; n++){
                            if(corner[m][n] != 6)
                                cornerUsed[corner[m][n]] += 1;
                        }
                        
                    } 
                    cout << endl << "coners used:" << endl;
                    printnumber(cornerUsed); 
                    


                    vector<int> leftColors;
                    
                    for(int m = 0; m < 6; m++){
                        for(int n = 0; n < (4-cornerUsed[m]); n++) 
                            leftColors.push_back(m);
                    }

                    cout << endl;
                    cout << "colors left for corners:\t";
                    for(int i=0; i<leftColors.size(); i++)
                        cout << leftColors.at(i) << " ";
                    cout << endl;

                    {
                        int totalcol = 0;
                        for(int m = 0; m < 6; m++){
                            totalcol += cornerUsed[m];
                        }
                        totalcol += leftColors.size();
                        cout << "colorsum " << totalcol << endl;
                    }


                    vector<int> remCorCol;
                    for(int i = 0; i < 6; i++){
                        int used = 6;
                        for(int j = 0; j < leftColors.size(); j++){
                            if(used == i) 
                                break;
                            if(leftColors.at(j) == i){
                                remCorCol.push_back(i);
                                used = i; 
                            }
                        }  
                    }          

                    for(int i = 0; i < 3; i++){         
                        remCorCol.erase(remove(remCorCol.begin(), remCorCol.end(),  corner[k][i]), remCorCol.end());
                    }

                    cout << "oldcorner " << k << ": \t\t\t" ;   
                    for(int i = 0; i < 3; i++){

                        cout << corner[k][i] << " ";
                    }
                    cout << endl;
                    cout << "colors left for corner " << k <<":\t";
                    for(int i=0; i<remCorCol.size(); i++)
                        cout << remCorCol.at(i) << " ";
                    cout << endl;
                    random_shuffle(remCorCol.begin(), remCorCol.end());

                    cout << "newcorner " << k << ": \t\t\t" ;                             
                    for(int i = 0; i < 3; i++){
                        if(corner[k][i] == 6){
                            corner[k][i] = remCorCol.back();
                            remCorCol.pop_back();
                        }
                        cout << corner[k][i] << " ";
                    }
                    cout << endl << endl;
                    setCorners(corner, probcube);
                    
                    cout << "new cube:" << endl;                    
                    printCubeColor(probcube);                   

                    

                      
                }
            }
        }/*
        cout << "total used colors:" << endl;
        
        for(int i = 0; i < 6; i++)
            coluse[i] = 0;

        for(int i = 0; i < 6; i++){
            for(int j = 0; j < 3; j++){
                for(int k = 0; k < 3; k++){
                    int curcol = probcube[i][j][k];
                        if(curcol != 6){
                            coluse[curcol] +=1;                       
                        }
                }    
            }
        } 
        cout << endl << "colors used:" << endl;          
        printnumber(coluse); 
        */

        cout << endl << "________________________ CORNERS COMPLETE ________________________" << endl; 
    }

    //////////////////////////////// fill edges ////////////////////////////////     
    {
        int edgeUsed[6] = {0,0,0,0,0,0};

        int edge[12][2];
        getEdges(edge, probcube);

        for(int i = 0; i < 6; i++)
            edgeUsed[i] = 0;

        for(int i = 0; i < 12; i++){
            for(int j = 0; j < 2; j++){
                if(edge[i][j] != 6)
                    edgeUsed[edge[i][j]] += 1;
            }
            
        } 
        cout << endl << "number of colors in edges:" << endl;
        printnumber(edgeUsed); 
        
        vector<int> leftColors;
        
        for(int i = 0; i < 6; i++){
            for(int j = 0; j < (4-edgeUsed[i]); j++) 
                leftColors.push_back(i);
        }
        
        cout << endl;
        cout << "colors left for corners:\t";
        for(int i=0; i<leftColors.size(); i++)
            cout << leftColors.at(i) <<  " " ;
        cout << endl;
    
        //// find cubies with already filled faces
        int edgeFilled[12] = {0,0,0,0,0,0,0,0,0,0,0,0};
        cout << "number of filled faces: \t";
        for(int i = 0; i < 12; i++){
            for(int j = 0; j < 2; j++){
                if(edge[i][j] != 6)
                    edgeFilled[i] ++;
            }
            cout << edgeFilled[i] << " ";
        }
        cout << endl;

        //// fill up edges first using the ones already filled
        for(int i = 0; i < 2; i ++){
            for(int j = 0; j < 12; j++){
                if(edgeFilled[j] == (1-i)){
                    getEdges(edge, probcube);

                    for(int k = 0; k < 6; k++)
                        edgeUsed[k] = 0;

                    for(int k = 0; k < 12; k++){
                        for(int l = 0; l < 2; l++){
                            if(edge[k][l] != 6)
                                edgeUsed[edge[k][l]] += 1;
                        }
                        
                    } 
                    cout << endl << "edges used:" << endl;
                    printnumber(edgeUsed); 
                    
                    vector<int> leftColors;
                    
                    for(int k = 0; k < 6; k++){
                        for(int l = 0; l < (4-edgeUsed[k]); l++) 
                            leftColors.push_back(k);
                    }
                    cout << endl;
                    cout << "colors left for corners:\t";
                    for(int k=0; k<leftColors.size(); k++)
                        cout << leftColors.at(k) << " ";
                    cout << endl;

                    int edgeFilled[12] = {0,0,0,0,0,0,0,0,0,0,0,0};
                    cout << "filled faces: \t\t\t";
                    for(int k = 0; k < 12; k++){
                        for(int l = 0; l < 2; l++){
                            if(edge[k][l] != 6)
                                edgeFilled[k] ++;
                        }
                        cout << edgeFilled[k] << " ";
                    }
                    cout << endl;

                    vector<int> remCorCol;
                    for(int k = 0; k < 6; k++){
                        int used = 6;
                        for(int l = 0; l < leftColors.size(); l++){
                            if(used == k) 
                                break;
                            if(leftColors.at(l) == k){
                                remCorCol.push_back(k);
                                used = k; 
                            }
                        }  
                    }  

                    for(int k = 0; k < 3; k++){         
                        remCorCol.erase(remove(remCorCol.begin(), remCorCol.end(),  edge[j][k]), remCorCol.end());
                    }

                    cout << "oldedge " << i << ": \t\t\t" ;   
                    for(int k = 0; k < 2; k++){

                        cout << edge[j][k] << " ";
                    }
                    cout << endl;
                    cout << "colors left for edge " << j <<":\t";
                    for(int k=0; k<remCorCol.size(); k++)
                        cout << remCorCol.at(k) << " ";
                    cout << endl;
                    random_shuffle(remCorCol.begin(), remCorCol.end());

                    cout << "newedge " << j << ": \t\t\t" ;                             
                    for(int k = 0; k < 2; k++){
                        if(edge[j][k] == 6){
                            edge[j][k] = remCorCol.back();
                            remCorCol.pop_back();
                        }
                        cout << edge[j][k] << " ";
                    }
                    cout << endl;
                    setEdges(edge, probcube);

                    printCubeColor(probcube);                   

                    
                    cout << endl << "_________________________________________________________________" << endl;
                   
                }

            }

        }

    }

        cout << "colors used:" << endl;
        
        for(int i = 0; i < 6; i++)
            coluse[i] = 0;

        for(int i = 0; i < 6; i++){
            for(int j = 0; j < 3; j++){
                for(int k = 0; k < 3; k++){
                    int curcol = probcube[i][j][k];
                        if(curcol != 6){
                            coluse[curcol] +=1;                       
                        }
                }    
            }
        } 
        cout << endl << "total:" << endl;          
        printnumber(coluse); 

        for(int i = 0; i < 6; i++)
            coluse[i] = 0;

        int corner[8][3];
        getCorners(corner, probcube);

        for(int m = 0; m < 8; m++){
            for(int n = 0; n < 3; n++){
                if(corner[m][n] != 6)
                    coluse[corner[m][n]] += 1;
            }
            
        }         
        cout << endl << "corners:" << endl;          
        printnumber(coluse); 

        int edge[12][2];
        getEdges(edge, probcube);
        for(int i = 0; i < 6; i++)
            coluse[i] = 0;

        for(int i = 0; i < 12; i++){
            for(int j = 0; j < 2; j++){
                if(edge[i][j] != 6)
                    coluse[edge[i][j]] += 1;
            }
            
        } 
        cout << endl << "edges:" << endl;
        printnumber(coluse); 




}

void fillrandom(){

    //srand(time(nullptr));
    for(int i = 0; i < 6; i++){
        for(int j = 0; j <3; j++){
            for(int k = 0; k < 3; k++){
                
                cube[i][j][k] = rand() % 6;
            }    
        }
    }
}

int getCorners(int array[8][3], int cubetofind[6][3][3]){


    array[0][0] = cubetofind[0][0][0];
    array[0][1] = cubetofind[1][0][0];
    array[0][2] = cubetofind[4][0][2];

    array[1][0] = cubetofind[0][0][2];
    array[1][1] = cubetofind[4][0][0];
    array[1][2] = cubetofind[3][0][2];

    array[2][0] = cubetofind[0][2][2];
    array[2][1] = cubetofind[3][0][0];
    array[2][2] = cubetofind[2][0][2];

    array[3][0] = cubetofind[0][2][0];
    array[3][1] = cubetofind[2][0][0];
    array[3][2] = cubetofind[1][0][2];

    array[4][0] = cubetofind[5][2][0];
    array[4][1] = cubetofind[4][2][2];
    array[4][2] = cubetofind[1][2][0];

    array[5][0] = cubetofind[5][2][2];
    array[5][1] = cubetofind[3][2][2];
    array[5][2] = cubetofind[4][2][0];

    array[6][0] = cubetofind[5][0][2];
    array[6][1] = cubetofind[2][2][2];
    array[6][2] = cubetofind[3][2][0];

    array[7][0] = cubetofind[5][0][0];
    array[7][1] = cubetofind[1][2][2];
    array[7][2] = cubetofind[2][2][0];

}

int setCorners(int array[8][3], int cubetofind[6][3][3]){


    cubetofind[0][0][0] = array[0][0];
    cubetofind[1][0][0] = array[0][1];
    cubetofind[4][0][2] = array[0][2];

    cubetofind[0][0][2] = array[1][0];
    cubetofind[4][0][0] = array[1][1];
    cubetofind[3][0][2] = array[1][2];

    cubetofind[0][2][2] = array[2][0];
    cubetofind[3][0][0] = array[2][1];
    cubetofind[2][0][2] = array[2][2];

    cubetofind[0][2][0] = array[3][0];
    cubetofind[2][0][0] = array[3][1];
    cubetofind[1][0][2] = array[3][2];

    cubetofind[5][2][0] = array[4][0];
    cubetofind[4][2][2] = array[4][1];
    cubetofind[1][2][0] = array[4][2];

    cubetofind[5][2][2] = array[5][0];
    cubetofind[3][2][2] = array[5][1];
    cubetofind[4][2][0] = array[5][2];

    cubetofind[5][0][2] = array[6][0];
    cubetofind[2][2][2] = array[6][1];
    cubetofind[3][2][0] = array[6][2];

    cubetofind[5][0][0] = array[7][0];
    cubetofind[1][2][2] = array[7][1];
    cubetofind[2][2][0] = array[7][2];

}

void permutationparitytest(int permutationCube[6][3][3]){
	int cnt=0;
	int visitedCorner[8]={0,0,0,0,0,0,0,0};
	long cornerAdress[8];
	int corner[8][3];
	int i=0;
	int firstIndexSum=0;
	int indexSum=0;
	int whileCnt=0;
	
	corner[0][0] = permutationCube[0][0][0];
    corner[0][1] = permutationCube[1][0][0];
    corner[0][2] = permutationCube[4][0][2];

    corner[1][0] = permutationCube[0][0][2];
    corner[1][1] = permutationCube[4][0][0];
    corner[1][2] = permutationCube[3][0][2];

    corner[2][0] = permutationCube[0][2][2];
    corner[2][1] = permutationCube[3][0][0];
    corner[2][2] = permutationCube[2][0][2];

    corner[3][0] = permutationCube[0][2][0];
    corner[3][1] = permutationCube[2][0][0];
    corner[3][2] = permutationCube[1][0][2];

    corner[4][0] = permutationCube[5][2][0];
    corner[4][1] = permutationCube[4][2][2];
    corner[4][2] = permutationCube[1][2][0];

    corner[5][0] = permutationCube[5][2][2];
    corner[5][1] = permutationCube[3][2][2];
    corner[5][2] = permutationCube[4][2][0];

    corner[6][0] = permutationCube[5][0][2];
    corner[6][1] = permutationCube[2][2][2];
    corner[6][2] = permutationCube[3][2][0];

    corner[7][0] = permutationCube[5][0][0];
    corner[7][1] = permutationCube[1][2][2];
    corner[7][2] = permutationCube[2][2][0];

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

    corner[0][0] = cornercube[0][0][0];
    corner[0][1] = cornercube[1][0][0];
    corner[0][2] = cornercube[4][0][2];

    corner[1][0] = cornercube[0][0][2];
    corner[1][1] = cornercube[4][0][0];
    corner[1][2] = cornercube[3][0][2];

    corner[2][0] = cornercube[0][2][2];
    corner[2][1] = cornercube[3][0][0];
    corner[2][2] = cornercube[2][0][2];

    corner[3][0] = cornercube[0][2][0];
    corner[3][1] = cornercube[2][0][0];
    corner[3][2] = cornercube[1][0][2];

    corner[4][0] = cornercube[5][2][0];
    corner[4][1] = cornercube[4][2][2];
    corner[4][2] = cornercube[1][2][0];

    corner[5][0] = cornercube[5][2][2];
    corner[5][1] = cornercube[3][2][2];
    corner[5][2] = cornercube[4][2][0];

    corner[6][0] = cornercube[5][0][2];
    corner[6][1] = cornercube[2][2][2];
    corner[6][2] = cornercube[3][2][0];

    corner[7][0] = cornercube[5][0][0];
    corner[7][1] = cornercube[1][2][2];
    corner[7][2] = cornercube[2][2][0];

    /*
    for(int i = 0; i < 8; i++){
        cout << "conrner" << i << ":" << endl;
        cout << corner[i][0] << " - " << corner[i][1] << " - " << corner[i][2] << endl;
    
    }
    */

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

void setEdges(int edge[12][2], int cube[6][3][3]){
    cube[0][1][0] = edge[0][0];  
    cube[1][0][1] = edge[0][1];

    cube[0][0][1] = edge[1][0];
    cube[4][0][1] = edge[1][1];

    cube[0][1][2] = edge[2][0];
    cube[3][0][1] = edge[2][1];

    cube[0][2][1] = edge[3][0];
    cube[2][0][1] = edge[3][1]; 

////////////////////////////

    cube[1][1][0] = edge[4][0];
    cube[4][1][2] = edge[4][1];

    cube[3][1][2] = edge[5][0];
    cube[4][1][0] = edge[5][1];

    cube[2][1][2] = edge[6][0];
    cube[3][1][0] = edge[6][1];

    cube[1][1][2] = edge[7][0];
    cube[2][1][0] = edge[7][1];

////////////////////////////

    cube[1][2][1] = edge[8][0];
    cube[5][1][0] = edge[8][1];

    cube[4][2][1] = edge[9][0];
    cube[5][2][1] = edge[9][1];

    cube[3][2][1] = edge[10][0];
    cube[5][1][2] = edge[10][1];

    cube[2][2][1] = edge[11][0];
    cube[5][0][1] = edge[11][1];

}

void getEdges(int edge[12][2], int cube[6][3][3]){
 edge[0][0] = cube[0][1][0]; 
 edge[0][1] = cube[1][0][1];

 edge[1][0] = cube[0][0][1];
 edge[1][1] = cube[4][0][1];

 edge[2][0] = cube[0][1][2];
 edge[2][1] = cube[3][0][1];

 edge[3][0] = cube[0][2][1];
 edge[3][1] = cube[2][0][1];

////////////////////////////

 edge[4][0] = cube[1][1][0];
 edge[4][1] = cube[4][1][2];

 edge[5][0] = cube[3][1][2];
 edge[5][1] = cube[4][1][0];

 edge[6][0] = cube[2][1][2];
 edge[6][1] = cube[3][1][0];

 edge[7][0] = cube[1][1][2];
 edge[7][1] = cube[2][1][0];

////////////////////////////

 edge[8][0] = cube[1][2][1];
 edge[8][1] = cube[5][1][0];

 edge[9][0] = cube[4][2][1];
 edge[9][1] = cube[5][2][1];

 edge[10][0] = cube[3][2][1];
 edge[10][1] = cube[5][1][2];

 edge[11][0] = cube[2][2][1];
 edge[11][1] = cube[5][0][1];

}



int edgepartitytest(int edgecube[6][3][3]){

 int topcol = edgecube[0][1][1];
 int botcol = edgecube[5][1][1];
 int frocol = edgecube[2][1][1];
 int baccol = edgecube[4][1][1];

 int edge[12][2];
 
 edge[0][0] = edgecube[0][1][0]; 
 edge[0][1] = edgecube[1][0][1];

 edge[1][0] = edgecube[0][0][1];
 edge[1][1] = edgecube[4][0][1];

 edge[2][0] = edgecube[0][1][2];
 edge[2][1] = edgecube[3][0][1];

 edge[3][0] = edgecube[0][2][1];
 edge[3][1] = edgecube[2][0][1];

////////////////////////////

 edge[4][0] = edgecube[1][1][0];
 edge[4][1] = edgecube[4][1][2];

 edge[5][0] = edgecube[3][1][2];
 edge[5][1] = edgecube[4][1][0];

 edge[6][0] = edgecube[2][1][2];
 edge[6][1] = edgecube[3][1][0];

 edge[7][0] = edgecube[1][1][2];
 edge[7][1] = edgecube[2][1][0];

////////////////////////////

 edge[8][0] = edgecube[1][2][1];
 edge[8][1] = edgecube[5][1][0];

 edge[9][0] = edgecube[4][2][1];
 edge[9][1] = edgecube[5][2][1];

 edge[10][0] = edgecube[3][2][1];
 edge[10][1] = edgecube[5][1][2];

 edge[11][0] = edgecube[2][2][1];
 edge[11][1] = edgecube[5][0][1];
    

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





void printCubeStd(int data[6][3][3])
{
	for(int i=0;i<3;i++)
	{
		cout<<"    "<<data[0][i][0]<<data[0][i][1]<<data[0][i][2]<<endl;
	}
	for(int i=0;i<3;i++)
	{
		cout<<data[1][i][0]<<data[1][i][1]<<data[1][i][2]<<" ";
		cout<<data[2][i][0]<<data[2][i][1]<<data[2][i][2]<<" ";
		cout<<data[3][i][0]<<data[3][i][1]<<data[3][i][2]<<" ";
		cout<<data[4][i][0]<<data[4][i][1]<<data[4][i][2]<<" "<<endl;
	}
	for(int i=0;i<3;i++)
	{
		cout<<"    "<<data[5][i][0]<<data[5][i][1]<<data[5][i][2]<<endl;
	}	
	cout<<endl<<endl;
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
/*
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
*/
return 0;
}
