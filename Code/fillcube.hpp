#ifndef FILLCUBE_HPP
#define FILLCUBE_HPP

#include "masterheader.hpp"
#include <iostream>
#include <list>
#include <iterator>
#include <unistd.h>
#include <array>

#include <algorithm>    // std::sort
#include "solvability.hpp"


using namespace std;
/*
struct corner;
struct edge;
struct middle;
*/
#define useUIfillcube 0

void fillMiddle(int cubeMiddle[6][3][3], int Middle[]);
void clearEdgeList(list<edge> EdgeCodes[]);
void fillCorners(list <corner> CornerCodes[]);




void fillEdges(list<edge> EdgeCodes[], int edge_cube[6][3][3], int edgeorder[], int orientationCube[6][3][3], int indexCube[6][3][3])
{
    //cout << "in fillEdges" << endl;
    int edge2fill[12][2]; 

    // set all adges to black
    for(int i = 0; i < 12; i++)
        for(int j = 0; j < 2; j++)
            edge2fill[i][j]=6;
    
    list <edge> UsedEdges;
    
    for(int i = 0; i < 12; i++){  

        edge tmp;
        // UI begin
        if(useUIfillcube){
            cout << "________________________________________________" << endl;
            cout << "fill edge: " << edgeorder[i] << endl;
        }        
        // UI end

        list <edge>::iterator itPossible = EdgeCodes[edgeorder[i]].begin();        
        list <edge>::iterator itUsed = UsedEdges.begin(); 

        // UI begin
        if(useUIfillcube){
            cout << "used: \t\t"; 
            for(int j = 0; j < UsedEdges.size(); j++){
                cout << itUsed->field[0] << itUsed->field[1] << " | "; itUsed++;}
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
                if(((itPossible->field[0] == itUsed->field[0]) && (itPossible->field[1] == itUsed->field[1])) || 
                   ((itPossible->field[0] == itUsed->field[1]) && (itPossible->field[1] == itUsed->field[0])))
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
            if(useUIfillcube){
                {
                cout << "possible: \t";

                    list <edge>::iterator itrem = EdgeCodes[edgeorder[i]].begin();		                    
                    while(itrem != EdgeCodes[edgeorder[i]].end())
                    {
	                    cout << itrem->field[0] << itrem->field[1] << " | ";			                    
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
        //cout << "out of while" << endl;
        // fill cube with random combinations from remaining possible ones
        //cout << "EdgeCodes[edgeorder[i]].begin " << EdgeCodes[edgeorder[i]].begin() << endl;
        //cout << "edgeorder[i] " << edgeorder[i] << endl;
        list <edge>::iterator it = EdgeCodes[edgeorder[i]].begin();
        //cout << "durch Null? " << EdgeCodes[edgeorder[i]].size();        
        int random = rand()%(EdgeCodes[edgeorder[i]].size());


        for(int j = 0; j < random; j++)
            it++;

        edge2fill[edgeorder[i]][0] = it->field[0];
        edge2fill[edgeorder[i]][1] = it->field[1];  

        // adding currently used combinations to used-list
        tmp.field[0] = it->field[0]; 
        tmp.field[1] = it->field[1];
        UsedEdges.push_back(tmp);

        if(useUIfillcube){
            cout << "set to: " << it->field[0] << "." << it->field[1] << endl;
        }
    }

    setEdges(edge2fill, cube, orientationCube, indexCube);
   // cout << "out fillEdges" << endl;
}


void SortCornerList(list<corner> CornerCodes[], int order[], int size){

    bool done = 0;   
    do{


        done = 1;
        int rightorder = 0;
        for(int i = 0; i < size-1; i++){ 

            if(CornerCodes[order[i]].size()>CornerCodes[order[i+1]].size())
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
    if(useUIfillcube){
        cout << "sorted lists:" << endl;
        for(int k = 0; k < size; k++){
            cout << "list " << order[k] << ": \t";
            for(int j = 0; j < CornerCodes[order[k]].size(); j++)
                cout << "|";
            cout << endl;   
        }
    }
    // UI end

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
    if(useUIfillcube){
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


void fillCorners(list<corner> CornerCodes[], int corner_cube[6][3][3], int cornerorder[], int orientationCube[6][3][3], int indexCube[6][3][3])
{

    int corner2fill[8][3]; 

    // set all adges to black
    for(int i = 0; i < 8; i++)
        for(int j = 0; j < 3; j++)
            corner2fill[i][j]=6;
    
    list <corner> UsedCorners;
    
    for(int i = 0; i < 8; i++){  

        corner tmp;
        // UI begin
        if(useUIfillcube){
            cout << "________________________________________________" << endl;
            cout << "fill corners: " << cornerorder[i] << endl;
        }        
        // UI end

        list <corner>::iterator itPossible = CornerCodes[cornerorder[i]].begin();        
        list <corner>::iterator itUsed = UsedCorners.begin(); 

        // UI begin
        if(useUIfillcube){
            cout << "used: \t\t"; 
            for(int j = 0; j < UsedCorners.size(); j++){
                cout << itUsed->field[0] << itUsed->field[1] << itUsed->field[2] << " | "; itUsed++;}
            cout << endl;
            itUsed= UsedCorners.begin();
        }       
        // UI end


    int caunt = 0; 
        //going through already used combinations and deleting them from possible combinations
        itUsed = UsedCorners.begin(); 
        while(itUsed != UsedCorners.end())
        //for(int k = 0; k < UsedEdges.size(); k++)
        {
         //   cout << "hier 1: " << UsedEdges.size()<< " i: " << i << endl;
            list <int> deletelist;
            int deleter = 0; 

            // finding matching with already used
            itPossible = CornerCodes[cornerorder[i]].begin();
            while(itPossible != CornerCodes[cornerorder[i]].end()){
                if(
((itPossible->field[0] == itUsed->field[0]) && (itPossible->field[1] == itUsed->field[1]) && (itPossible->field[2] == itUsed->field[2])) || 
((itPossible->field[0] == itUsed->field[1]) && (itPossible->field[1] == itUsed->field[2]) && (itPossible->field[2] == itUsed->field[0])) || 
((itPossible->field[0] == itUsed->field[2]) && (itPossible->field[1] == itUsed->field[0]) && (itPossible->field[2] == itUsed->field[1])) 

                    )
                {
                    deletelist.push_back(deleter);
                }
                
                itPossible++;
                deleter ++;
            }

            // deleting already used
            while(deletelist.size()>0){
                itPossible = CornerCodes[cornerorder[i]].begin();//deletelist.back(itdelete); 
                advance(itPossible,deletelist.back());
                deletelist.pop_back();   
                CornerCodes[cornerorder[i]].erase(itPossible);
            }

            //UI begin
            if(useUIfillcube){
                {
                cout << "possible: \t";

                    list <corner>::iterator itrem = CornerCodes[cornerorder[i]].begin();		                    
                    while(itrem != CornerCodes[cornerorder[i]].end())
                    {
	                    cout << itrem->field[0] << itrem->field[1] << itrem->field[2] << " | ";			                    
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

            //UI begin
            if(useUIfillcube && cornerorder[i] == 0){
                {
                cout << "possible: \t";

                    list <corner>::iterator itrem = CornerCodes[cornerorder[i]].begin();		                    
                    while(itrem != CornerCodes[cornerorder[i]].end())
                    {
	                    cout << itrem->field[0] << itrem->field[1] << itrem->field[2] << " | ";			                    
	                    itrem++;
                    }		                    
                    cout << endl;

                }
            }
            //UI end 


        // fill cube with random combinations from remaining possible ones
        list <corner>::iterator it = CornerCodes[cornerorder[i]].begin();        
        int random = rand()%(CornerCodes[cornerorder[i]].size());


        for(int j = 0; j < random; j++)
            it++;

        corner2fill[cornerorder[i]][0] = it->field[0];
        corner2fill[cornerorder[i]][1] = it->field[1];  
        corner2fill[cornerorder[i]][2] = it->field[2];  

        // adding currently used combinations to used-list
        tmp.field[0] = it->field[0]; 
        tmp.field[1] = it->field[1];
        tmp.field[2] = it->field[2];
        UsedCorners.push_back(tmp);

        if(useUIfillcube){
            cout << "set to: " << it->field[0] << "|" << it->field[1] << "|" << it->field[2] << endl;
        }
    }

    setCorners(corner2fill, cube, orientationCube, indexCube);

}



/*
void fillCorners(list<corner> CornerCodes[], int orientationCube[6][3][3], int indexCube[6][3][3]){ //einträge mit wenigsten zu erst, permutationen raus, nicht immer gleichen index löschen der 8 listen sondern extra suchen
cout << "here" << endl;
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
	//Testzweck
    //cout << "___reihenfolge___" << endl;
	//for(int i=0;i<8;i++)
	//{
	//	cout<<arSort[i].length<<"  "<<arSort[i].index<<endl;
		
	//}
	
	//getting corners to fill cube
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
		 //   cout<<i<<"Corner Adress index"<<cnt1<<endl; //Testzweck
			
			itCo=CornerCodes[arSort[i].index].begin();
			while(cnt2!=cnt1) //get iterator to random value
			{
				cnt2++;
				itCo++;
			}
			
			if(itCo->field[0]!=-1)
			{
				arCorner[i][0]=itCo->field[0];
				arCorner[i][1]=itCo->field[1];
				arCorner[i][2]=itCo->field[2];
				
			//	cout<<i<<" Corners "<< itCo->field[0]<<itCo->field[1]<<itCo->field[2]<<endl;//Testzweck
		//*******************************************setting visited coners and permutations to -1
				arAdress[0]=itCo->field[0];
				arAdress[1]=itCo->field[1];
				arAdress[2]=itCo->field[2];
				sort(arAdress,arAdress+3);
				tmpCorner1=100*arAdress[0]+10*arAdress[1]+1*arAdress[2]; //sortierte adresse ist automatisch alle permutationen
				
				for(int j=0; j<8; j++)
				{
					list <corner>::iterator itCo= CornerCodes[j].begin();
					while(itCo!=CornerCodes[j].end())
					{
						arAdress[0]=itCo->field[0];
						arAdress[1]=itCo->field[1];
						arAdress[2]=itCo->field[2];
				        sort(arAdress,arAdress+3);
				        tmpCorner2=100*arAdress[0]+10*arAdress[1]+1*arAdress[2];//sortierte adresse ist automatisch alle permutationen
                        cout << "" << tmpCorner2 << endl;
				        if(tmpCorner1==tmpCorner2)
				        {
 
							itCo->field[0]=-1;
						}
                        if(i==7){
                            cout << "poss: " << 
                            itCo->field[0] << " " << 
                            itCo->field[1] << " " << 
                            itCo->field[2] << endl;
                        }
				   
						itCo++;
					}
				}	
				break;
			}
		}
	
	}

    setCorners(arCorner, cube, orientationCube, indexCube);

}
*/



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
    if(useUIfillcube){
	    for (int j=0; j<12; j++)
	    {
		    cout << "List number " << j << " " << endl;
		    
		    list <edge>::iterator it = EdgeCodes[j].begin();
		    
		    while(it != EdgeCodes[j].end())
		    {
			    cout << it->field[0] << it->field[1] << " | ";
			    
			    it++;
		    }
		    
		    cout << endl;
	    }
    }

}

void fillCenter(int center[6], int color[6]){

    for(int i = 0; i < 6; i++)
        cube[i][1][1] = color[i];
    //printCubeColor(cube);
}

/*
void fillCenter(int center[6], int color[6]){

    for(int i = 0; i < 6; i++)
        cube[center[i]][1][1] = color[center[i]];
    //printCubeColor(cube);
}
*/

void CopyListEdges(list<edge> original[], list<edge> copy[]){

	edge temp;

	for(int i=0;i<12;i++)
	{
		list<edge>::iterator it= original[i].begin();
		while(it != original[i].end())
		{
			temp.field[0]=it->field[0];
			temp.field[1]=it->field[1];
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
			temp.field[0]=it->field[0];
			temp.field[1]=it->field[1];
			temp.field[2]=it->field[2];
			copy[i].push_back(temp);
			it++;
		}
    }
}






int fillrandomcube(int MiddleCode[6], int MiddleColor[6], list <edge> EdgeCodes[12], list <corner> CornerCodes[8], int oCube[6][3][3], int iCube[6][3][3]){

    srand(clock());
    bool solvable = 0; 
    int solved = 0; 
    int tries = 0; 
    int edgeorder[12] ={0,1,2,3,4,5,6,7,8,9,10,11};
    int cornerorder[8] ={0,1,2,3,4,5,6,7};

    while(!solvable)
    {

        list <edge> EdgeCodesCopy[12];
	    list <corner> CornerCodesCopy[8];

        CopyListCorners(CornerCodes, CornerCodesCopy);
        CopyListEdges(EdgeCodes, EdgeCodesCopy);
        //clearEdgeList(EdgeCodes); 

        fillCenter(MiddleCode, MiddleColor);

        // befuelle cube mit random edges aus den listen  
        SortEdgesList(EdgeCodesCopy, edgeorder, 12);
        fillEdges(EdgeCodesCopy, cube, edgeorder, oCube, iCube); 

        SortCornerList(CornerCodesCopy, cornerorder, 8);
        fillCorners(CornerCodesCopy, cube, cornerorder, oCube, iCube);


        solvable = checksolvability(cube);
        //cout << ".";
        tries++;
        if(tries > 12*8)
            return 1;
        // ausgabe statistik ueber loesbare cubes
        /*
        if(solvable)
            solved ++;

        system("clear");    
        cout << "check: " << solved << endl;
        tries++;
        cout << "tries: " << tries << endl;
        float verh = (float)solved/(float)tries;
        cout << "soll:\t1/12 = 0,0833  ist:\t" << verh << endl;
        usleep(1000000*0.01);  
        //cin.get();
        */
    }
    return 0;

}


#endif
