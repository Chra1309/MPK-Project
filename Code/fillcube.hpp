#ifndef FILLCUBE_HPP
#define FILLCUBE_HPP

#include "masterheader.hpp"
#include <iostream>
#include <list>
#include <iterator>
#include <unistd.h>
#include <array>
#include "rubikssolver_header.hpp"
#include <algorithm>    // std::sort
#include "solvability.hpp"


using namespace std;
/*
struct corner;
struct edge;
struct middle;
*/
#define useUI 0 

void fillMiddle(int cubeMiddle[6][3][3], int Middle[]);
void clearEdgeList(list<edge> EdgeCodes[]);
void fillCorners(list <corner> CornerCodes[]);




void fillEdges(list<edge> EdgeCodes[], int edge_cube[6][3][3], int edgeorder[])
{
    int edge2fill[12][2]; 

    // set all adges to black
    for(int i = 0; i < 12; i++)
        for(int j = 0; j < 2; j++)
            edge2fill[i][j]=6;
    
    list <edge> UsedEdges;
    
    for(int i = 0; i < 12; i++){  

        edge tmp;
        // UI begin
        if(useUI){
            cout << "________________________________________________" << endl;
            cout << "fill edge: " << edgeorder[i] << endl;
        }        
        // UI end

        list <edge>::iterator itPossible = EdgeCodes[edgeorder[i]].begin();        
        list <edge>::iterator itUsed = UsedEdges.begin(); 

        // UI begin
        if(useUI){
            cout << "used: \t\t"; 
            for(int j = 0; j < UsedEdges.size(); j++){
                cout << itUsed->field1 << itUsed->field2 << " | "; itUsed++;}
            cout << endl;
            itUsed= UsedEdges.begin();
        }       
        // UI end


    int caunt = 0; 
        //going through already used combinations and deleting them from possible combinations
        itUsed = UsedEdges.begin(); 
        while(itUsed != UsedEdges.end())
        //for(int k = 0; k < UsedEdges.size(); k++)
        {
         //   cout << "hier 1: " << UsedEdges.size()<< " i: " << i << endl;
            list <int> deletelist;
            int deleter = 0; 

            // finding matching with already used
            itPossible = EdgeCodes[edgeorder[i]].begin();
            while(itPossible != EdgeCodes[edgeorder[i]].end()){
                if(((itPossible->field1 == itUsed->field1) && (itPossible->field2 == itUsed->field2)) || 
                   ((itPossible->field1 == itUsed->field2) && (itPossible->field2 == itUsed->field1)))
                {
                    deletelist.push_back(deleter);
                }
                
                itPossible++;
                deleter ++;
            }

            // deleting already used
            while(deletelist.size()>0){
                itPossible = EdgeCodes[edgeorder[i]].begin();//deletelist.back(itdelete); 
                advance(itPossible,deletelist.back());
                deletelist.pop_back();   
                EdgeCodes[edgeorder[i]].erase(itPossible);
            }

            //UI begin
            if(useUI){
                {
                cout << "possible: \t";

                    list <edge>::iterator itrem = EdgeCodes[edgeorder[i]].begin();		                    
                    while(itrem != EdgeCodes[edgeorder[i]].end())
                    {
	                    cout << itrem->field1 << itrem->field2 << " | ";			                    
	                    itrem++;
                    }		                    
                    cout << endl;

                }
            //UI end 

            }
            itUsed++;
            caunt++;
     //cout << "hier 6: "<< caunt << endl;           
        }  

        // fill cube with random combinations from remaining possible ones
        list <edge>::iterator it = EdgeCodes[edgeorder[i]].begin();        
        int random = rand()%(EdgeCodes[edgeorder[i]].size());


        for(int j = 0; j < random; j++)
            it++;

        edge2fill[edgeorder[i]][0] = it->field1;
        edge2fill[edgeorder[i]][1] = it->field2;  

        // adding currently used combinations to used-list
        tmp.field1 = it->field1; 
        tmp.field2 = it->field2;
        UsedEdges.push_back(tmp);

        if(useUI){
            cout << "set to: " << it->field1 << "." << it->field2 << endl;
        }
    }

    setEdges(edge2fill, cube);

}


void SortEdgesList(list<edge> EdgeCodes[], int order[], int size){

    bool done = 0;   
    do{


        done = 1;
        int rightorder = 0;
        for(int i = 0; i < size-1; i++){ 

            if(EdgeCodes[order[i]].size()>EdgeCodes[order[i+1]].size())
            {

                int temporder; 
                temporder = order[i];
                order[i] = order[i+1];
                order[i+1] = temporder;
                done = 0;
            }
   
        }    

    }
    while(!done);

    // UI begin
    if(useUI){
        cout << "sorted lists:" << endl;
        for(int k = 0; k < size; k++){
            cout << "list " << order[k] << ": \t";
            for(int j = 0; j < EdgeCodes[order[k]].size(); j++)
                cout << "|";
            cout << endl;   
        }
    }
    // UI end


}

void fillCorners(list<corner> CornerCodes[]){ //einträge mit wenigsten zu erst, permutationen raus, nicht immer gleichen index löschen der 8 listen sondern extra suchen
	int arCorner[8][3];
	int cnt1=0;
	int cnt2=0;
	
	struct mySort
	{
		int index;
		int length;
	};
	struct mySort arSort[8];
	struct mySort tmp;
	int tmpCorner1=0;
	int tmpCorner2=0;
	int arAdress[3];
	
	//*******************************************Listen der größe nach in arSort eintragen index=0 => kürzeste Liste
	for(int i=0;i<8;i++)
	{
		list<corner>::iterator it= CornerCodes[i].begin();
		while(it!=CornerCodes[i].end())
		{
			cnt1++;
			it++;
		}
		
		arSort[i].length=cnt1;
		arSort[i].index=i;
		//cout<<arSort[i].length<<"  "<<arSort[i].index<<endl;
		cnt1=0;
	}
	
	for (int i = 1; i < 8 ; i++) 
    {
		for (int j = 0; j < (8 - i) ; j++) 
		{
			if (arSort[j].length > arSort[j+1].length) 
			{
              tmp = arSort[j];
              arSort[j]= arSort[j+1];
              arSort[j+1]= tmp;
              
              
			}
		}
	}
	//*************Testzweck
	/*for(int i=0;i<8;i++)
	{
		cout<<arSort[i].length<<"  "<<arSort[i].index<<endl;
		
	}*/
	
	//*******************************************getting corners to fill cube
	for(int i=0; i<8; i++)
	{
		while(1)
		{
			cnt1=0;
			cnt2=0;
			list<corner>::iterator itCo = CornerCodes[arSort[i].index].begin();
			while(itCo!=CornerCodes[arSort[i].index].end()) //sizeof list, starting with smallest list
			{
				itCo++;
				cnt1++;
			}
			cnt1=rand()%cnt1; // random value between 0 and sizeof list
			//cout<<i<<"Corner Adress index"<<cnt1<<endl; //Testzweck
			
			itCo=CornerCodes[arSort[i].index].begin();
			while(cnt2!=cnt1) //get iterator to random value
			{
				cnt2++;
				itCo++;
			}
			
			if(itCo->field1!=-1)
			{
				arCorner[i][0]=itCo->field1;
				arCorner[i][1]=itCo->field2;
				arCorner[i][2]=itCo->field3;
				
				//cout<<i<<" Corners "<< itCo->field1<<itCo->field2<<itCo->field3<<endl;//Testzweck
		//*******************************************setting visited coners and permutations to -1
				arAdress[0]=itCo->field1;
				arAdress[1]=itCo->field2;
				arAdress[2]=itCo->field3;
				sort(arAdress,arAdress+3);
				tmpCorner1=100*arAdress[0]+10*arAdress[1]+1*arAdress[2]; //sortierte adresse ist automatisch alle permutationen
				
				for(int j=0; j<8; j++)
				{
					list <corner>::iterator itCo= CornerCodes[j].begin();
					while(itCo!=CornerCodes[j].end())
					{
						arAdress[0]=itCo->field1;
						arAdress[1]=itCo->field2;
						arAdress[2]=itCo->field3;
				        sort(arAdress,arAdress+3);
				        tmpCorner2=100*arAdress[0]+10*arAdress[1]+1*arAdress[2];//sortierte adresse ist automatisch alle permutationen
				        
				        if(tmpCorner1==tmpCorner2)
				        {
							itCo->field1=-1;
						}
						itCo++;
					}
				}	
				break;
			}
		}
	
	}

    setCorners(arCorner, cube);
/*
	cube[0][2][0] = arCorner[0][0] ;
	cube[1][0][2] = arCorner[0][1] ;	
    cube[2][0][0] = arCorner[0][2] ;
    
    cube[0][2][2] = arCorner[1][0] ;
    cube[2][0][2] = arCorner[1][1] ;
    cube[3][0][0] = arCorner[1][2] ;
    
    cube[0][0][2] = arCorner[2][0] ;
    cube[3][0][2] = arCorner[2][1] ;
    cube[4][0][0] = arCorner[2][2] ;
    
    cube[0][0][0] = arCorner[3][0] ;
    cube[4][0][2] = arCorner[3][1] ;
    cube[1][0][0] = arCorner[3][2] ;
    
    cube[1][2][2] = arCorner[4][0] ;
    cube[2][2][0] = arCorner[4][1] ;
    cube[5][0][0] = arCorner[4][2] ;
    
    cube[1][2][0] = arCorner[5][0] ;
    cube[4][2][2] = arCorner[5][1] ;
    cube[5][2][0] = arCorner[5][2] ;
    
    cube[2][2][2] = arCorner[6][0] ;
    cube[5][0][2] = arCorner[6][1] ;
    cube[3][2][0] = arCorner[6][2] ;
    
    cube[3][2][2] = arCorner[7][0] ;
    cube[5][2][2] = arCorner[7][1] ;
    cube[4][2][0] = arCorner[7][2] ;
*/
}




void clearEdgeList(list<edge> EdgeCodes[]){
//just for deleting random entries from list - will be done by master mind
	for (int j=0; j<12; j++)
	{
		
		list <edge>::iterator it = EdgeCodes[j].begin();

        int randnum2 = rand()%(EdgeCodes[j].size()-2);
        
        int more = 0;
        for(int k = 0; k < randnum2; k++)
        {
            int randnum = rand()%EdgeCodes[j].size();

            it = EdgeCodes[j].begin();
            //cout << "iterator" << it << endl;
            for(int i = 0; i < randnum; i++)
                it++;                
            EdgeCodes[j].erase(it);

            more++; 
        }

	}  
    if(useUI){
	    for (int j=0; j<12; j++)
	    {
		    cout << "List number " << j << " " << endl;
		    
		    list <edge>::iterator it = EdgeCodes[j].begin();
		    
		    while(it != EdgeCodes[j].end())
		    {
			    cout << it->field1 << it->field2 << " | ";
			    
			    it++;
		    }
		    
		    cout << endl;
	    }
    }

}

void fillCenter(int center[6], int color[6]){

    for(int i = 0; i < 6; i++)
        cube[center[i]][1][1] = color[center[i]];

}

void CopyListEdges(list<edge> original[], list<edge> copy[]){

	edge temp;

	for(int i=0;i<12;i++)
	{
		list<edge>::iterator it= original[i].begin();
		while(it != original[i].end())
		{
			temp.field1=it->field1;
			temp.field2=it->field2;
			copy[i].push_back(temp);
			it++;
		}
    }



}

void CopyListCorners(list<corner> original[], list<corner> copy[]){

	corner temp;

	for(int i=0;i<8;i++)
	{
		list<corner>::iterator it= original[i].begin();
		while(it != original[i].end())
		{
			temp.field1=it->field1;
			temp.field2=it->field2;
			temp.field3=it->field3;
			copy[i].push_back(temp);
			it++;
		}
    }
}






void fillrandomcube(int MiddleCode[6], int MiddleColor[6], list <edge> EdgeCodes[12], list <corner> CornerCodes[8]){

    srand(clock());
    bool solvable = 0; 
    int solved = 0; 
    int tries = 0; 
    int edgeorder[12] ={0,1,2,3,4,5,6,7,8,9,10,11};

    while(!solvable){


        list <edge> EdgeCodesCopy[12];
	    list <corner> CornerCodesCopy[8];

        CopyListCorners(CornerCodes, CornerCodesCopy);
        CopyListEdges(EdgeCodes, EdgeCodesCopy);
        //clearEdgeList(EdgeCodes); 
        system("clear");
        fillCenter(MiddleCode, MiddleColor);

        // befuelle cube mit random edges aus den listen  
        SortEdgesList(EdgeCodesCopy, edgeorder, 12);
        fillEdges(EdgeCodesCopy, cube, edgeorder); 


        fillCorners(CornerCodesCopy);
        //printCubeColor(cube);

        solvable = checksolvability(cube);
        //solved += checksolvability(cube);
        //if(solvable)
        //    solved ++;

        //cout << "check: " << solved << endl;
        tries++;
        //cout << "tries: " << tries << endl;
        //float verh = (float)solved/(float)tries;
        //cout << "soll:\t1/12 = 0,0833  ist:\t" << verh << endl;
        //usleep(1000000*0.01);  
        //cin.get();
    }
    cout << "tries:\t" << tries << endl; 

}


#endif
