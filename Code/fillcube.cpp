int myrandom (int i) { return std::rand()%i;}

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

