Cube::Cube(int n=0)
{
	moves="";
	this->n=n;
	//int num[6] = {0, 1, 2, 3, 4, 5};
	int num[6] = {0, 1, 2, 3, 4, 5};
	
	//random_shuffle(num, num + 6);//Farben(Zahlen) zufällig am Cube erzeugen)
    
	if(n==0) //Erzeugung des 0-Cubes
	{
		for(int i=0;i<6;i++)
			for(int j=0;j<3;j++)
				for(int k=0;k<3;k++)
					data[i][j][k]=0;
	}else
	{ 
		for(int i=0;i<6;i++)
			for(int j=0;j<3;j++)
				for(int k=0;k<3;k++)
				{
					data[i][j][k]=num[i]; //Erzeugung eines Cubes mit zufälligen Farben (Zahlen)
					//data[i][j][k]=i; //Erzeugung Standardcube
				}
					
			
		if(n)
				randomize(); //Methode zum zufälligen verdrehen des Cubes		rotate(UP,1);//	
	}
}
string Cube::printColor(int field)
{
	
	//			1 white			2 red			3 green			4 blue			5 orange			6 yellow	
    // neuer farbenversuch		
    string RESET = "\033[0m";
	string WHITE = "\033[107m";      /* White */
	string RED = "\033[101m";      /* Red */
	string GREEN = "\033[102m";      /* Green */
	string BLUE = "\e[48;5;21m";      /* Blue */
	string ORANGE = "\e[48;5;208m";      /* Magenta */	 
	string YELLOW = "\033[103m";      /* Yellow */
				
	string printcolor;
	switch(field){
		case 1:
			printcolor = WHITE + "  " + RESET;		
			break;		
		case 2:
			printcolor = RED + "  " + RESET;					
			break;
		case 3: 
			printcolor = GREEN + "  " + RESET;					
			break;
		case 4:
			printcolor = BLUE + "  " + RESET;									
			break;
		case 5: 				
			printcolor = ORANGE + "  " + RESET;					
			break;			
		case 6: 
			printcolor = YELLOW + "  " + RESET;								
			break;				
	}
	return printcolor;
}
void Cube::printCubeColor()
{ 
	for(int i=0;i<3;i++)
	{
		cout<<"       "<<printColor(data[0][i][0])<<printColor(data[0][i][1])<<printColor(data[0][i][2])<<endl;
	}
	for(int i=0;i<3;i++)
	{
		cout<<printColor(data[1][i][0])<<printColor(data[1][i][1])<<printColor(data[1][i][2])<<" ";
		cout<<printColor(data[2][i][0])<<printColor(data[2][i][1])<<printColor(data[2][i][2])<<" ";
		cout<<printColor(data[3][i][0])<<printColor(data[3][i][1])<<printColor(data[3][i][2])<<" ";
		cout<<printColor(data[4][i][0])<<printColor(data[4][i][1])<<printColor(data[4][i][2])<<" "<<endl;
	}
	for(int i=0;i<3;i++)
	{
		cout<<"       "<<printColor(data[5][i][0])<<printColor(data[5][i][1])<<printColor(data[5][i][2])<<endl;
	}	
	cout<<endl<<endl;	
}
void Cube::printCubeStd()
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
void Cube::randomize()
{
	int x=(rand()%6)+1;
	int xOld=0;
	int y;
	
	for(int i=0;i<RANDOM;i++)
	{
		while(x==xOld)
			x=(rand()%6)+1;
		xOld=x;
		y=(rand()%3)+1;
		rotate(x,y);
	}
}
void Cube::rotate(int side,int howOften)
{
	howOften+=4;
	howOften=howOften%4;
	switch (side)
	{
		case FRONT:
			//cout<<"FRONT:"<<howOften<<endl;
			shift8by2n(data[2][0][0],data[2][0][1],data[2][0][2],data[2][1][2],data[2][2][2],data[2][2][1],data[2][2][0],data[2][1][0],howOften);
			shift12by3n(data[0][2][0],data[0][2][1],data[0][2][2],data[3][0][0],data[3][1][0],data[3][2][0],
						data[5][0][2],data[5][0][1],data[5][0][0],data[1][2][2],data[1][1][2],data[1][0][2],howOften);
			break;
		case BACK:
			//cout<<"BACK:"<<howOften<<endl;
			shift8by2n(data[4][0][0],data[4][0][1],data[4][0][2],data[4][1][2],data[4][2][2],data[4][2][1],data[4][2][0],data[4][1][0],howOften);
			shift12by3n(data[0][0][2],data[0][0][1],data[0][0][0],data[1][0][0],data[1][1][0],data[1][2][0],
						data[5][2][0],data[5][2][1],data[5][2][2],data[3][2][2],data[3][1][2],data[3][0][2],howOften);
			break;
		case LEFT:
			//cout<<"LEFT:"<<howOften<<endl;
			shift8by2n(data[1][0][0],data[1][0][1],data[1][0][2],data[1][1][2],data[1][2][2],data[1][2][1],data[1][2][0],data[1][1][0],howOften);
			shift12by3n(data[0][0][0],data[0][1][0],data[0][2][0],data[2][0][0],data[2][1][0],data[2][2][0],
						data[5][0][0],data[5][1][0],data[5][2][0],data[4][2][2],data[4][1][2],data[4][0][2],howOften);
			break;
		case RIGHT:
			//cout<<"RIGHT:"<<howOften<<endl;
			shift8by2n(data[3][0][0],data[3][0][1],data[3][0][2],data[3][1][2],data[3][2][2],data[3][2][1],data[3][2][0],data[3][1][0],howOften);
			shift12by3n(data[0][2][2],data[0][1][2],data[0][0][2],data[4][0][0],data[4][1][0],data[4][2][0],
						data[5][2][2],data[5][1][2],data[5][0][2],data[2][2][2],data[2][1][2],data[2][0][2],howOften);
			break;
		case UP:
			//cout<<"UP:"<<howOften<<endl;
			shift8by2n(data[0][0][0],data[0][0][1],data[0][0][2],data[0][1][2],data[0][2][2],data[0][2][1],data[0][2][0],data[0][1][0],howOften);
			shift12by3n(data[4][0][2],data[4][0][1],data[4][0][0],data[3][0][2],data[3][0][1],data[3][0][0],
						data[2][0][2],data[2][0][1],data[2][0][0],data[1][0][2],data[1][0][1],data[1][0][0],howOften);
			break;
		case DOWN:
			//cout<<"DOWN:"<<howOften<<endl;
			shift8by2n(data[5][0][0],data[5][0][1],data[5][0][2],data[5][1][2],data[5][2][2],data[5][2][1],data[5][2][0],data[5][1][0],howOften);
			shift12by3n(data[4][2][0],data[4][2][1],data[4][2][2],data[1][2][0],data[1][2][1],data[1][2][2],
						data[2][2][0],data[2][2][1],data[2][2][2],data[3][2][0],data[3][2][1],data[3][2][2],howOften);
			break;
		default:
			break;					
	}
	//printCubeStd();
}
void Cube::shift8by2n(int& a,int& b,int& c,int& d, int& e,int& f,int& g,int& h,int& n)
{				
	int temp;
	switch(n)
	{
		case 1:
			temp=g; g=e; e=c; c=a; a=temp;
			temp=h; h=f; f=d; d=b; b=temp;
			break;
		case 2:	
			temp=a;	a=e; e=temp;
			temp=b;	b=f; f=temp;
			temp=c;	c=g; g=temp;
			temp=d;	d=h; h=temp;					
			break;
		case 3:
			temp=a; a=c; c=e; e=g; g=temp;
			temp=b; b=d; d=f; f=h; h=temp;
			break;
		default:
			break;
	}
}
void Cube::shift12by3n(int& a,int& b,int& c,int& d, int& e,int& f,int& g,int& h,int& i,int& j,int& k,int& l,int& n)
{
	int temp;	
	switch(n)
	{
		case 1:
			temp=j; j=g; g=d; d=a; a=temp;
			temp=k; k=h; h=e; e=b; b=temp;
			temp=l; l=i; i=f; f=c; c=temp;
			break;
		case 2:
			temp=a; a=g; g=temp;
			temp=b; b=h; h=temp;
			temp=c; c=i; i=temp;
			temp=d; d=j; j=temp;
			temp=e; e=k; k=temp;
			temp=f; f=l; l=temp;
			break;
		case 3:
			temp=a; a=d; d=g; g=j; j=temp;
			temp=b; b=e; e=h; h=k; k=temp;
			temp=c; c=f; f=i; i=l; l=temp;
			break;
		default:
			break;
	}		
}
string makeCubeQuestion(Cube& sendCube)
{
	string CubeQuestion="1,";
	CubeQuestion+=cubeToString(sendCube);
	return CubeQuestion;
}
string cubeToString(Cube& cube)
{ 
	string returnString="";
	int* a=new int[54];
	cube.toArray(a);	
	for(int i=0;i<54;i++)
    	returnString+=a[i]+'0';
  	
  	delete a;
	return returnString;
	
}
void Cube::toArray(int* a)
{
	int x=0;
	for(int i=0;i<6;i++)
	{
		for(int j=0;j<3;j++)
		{
			for(int k=0;k<3;k++)
			{				
				a[x]=data[i][j][k];
				x++;
			}
		}	
	}
}
Cube stringToCube(string& s)
{
	Cube c(0);
	int a[54];
	int x=0;
	for(int i=0;i<54;i++)
    	a[i]=s[i]-'0';
	for(int i=0;i<6;i++)
	{
		for(int j=0;j<3;j++)
		{
			for(int k=0;k<3;k++)
			{				
				c.data[i][j][k]=a[x];
				x++;
			}
		}	
	}
	return c;
}
void compareCube(Cube& qc,Cube& c,int* a)
{
	for(int i=0;i<3;i++)
		a[i]=0;
	for(int i=0;i<6;i++)
	{
		for(int j=0;j<3;j++)
		{
			for(int k=0;k<3;k++)
			{
				if(qc.data[i][j][k]==0)
				{	
					if(qc.data[i][j][k]==c.data[i][1][1])
					{
						if(1);
					}else
					{
						a[0]++;
					}
				}
			}
		}	
	}
}
void Cube::getEdge(int& a,int& b,int& c,int& x)
{
	if(a==0&&b==0&&c==1) x=data[0][2][1];
	if(a==0&&b==1&&c==0) x=data[1][1][2];
	if(a==0&&b==1&&c==2) x=data[3][1][0];
	if(a==0&&b==2&&c==1) x=data[5][0][1];
	
	if(a==1&&b==0&&c==1) x=data[4][0][1];
	if(a==1&&b==1&&c==0) x=data[1][0][1];
	if(a==1&&b==1&&c==2) x=data[3][0][1];
	if(a==1&&b==2&&c==1) x=data[2][0][1];
	
	if(a==2&&b==0&&c==1) x=data[0][1][2];
	if(a==2&&b==1&&c==0) x=data[2][1][2];
	if(a==2&&b==1&&c==2) x=data[4][1][0];
	if(a==2&&b==2&&c==1) x=data[5][1][2];
		
	if(a==3&&b==0&&c==1) x=data[0][1][0];
	if(a==3&&b==1&&c==0) x=data[4][1][2];
	if(a==3&&b==1&&c==2) x=data[2][1][0];
	if(a==3&&b==2&&c==1) x=data[5][1][0];
	
	if(a==4&&b==0&&c==1) x=data[2][2][1];
	if(a==4&&b==1&&c==0) x=data[1][2][1];
	if(a==4&&b==1&&c==2) x=data[3][2][1];
	if(a==4&&b==2&&c==1) x=data[4][2][1];
	
	if(a==5&&b==0&&c==1) x=data[0][0][1];
	if(a==5&&b==1&&c==0) x=data[3][1][2];
	if(a==5&&b==1&&c==2) x=data[1][1][0];
	if(a==5&&b==2&&c==1) x=data[5][2][1];
}

void Cube::getCorner(int& a,int& b,int& c,int& x,int& y)
{
	if(a==0&&b==0&&c==0) {x=data[0][2][0]; y=data[1][0][2];}
	if(a==0&&b==0&&c==2) {x=data[0][2][2]; y=data[3][0][0];}
	if(a==0&&b==2&&c==0) {x=data[5][0][0]; y=data[1][2][2];}
	if(a==0&&b==2&&c==2) {x=data[5][0][2]; y=data[3][2][0];}
	
	if(a==1&&b==0&&c==0) {x=data[4][0][2]; y=data[1][0][0];}
	if(a==1&&b==0&&c==2) {x=data[4][0][0]; y=data[3][0][2];}
	if(a==1&&b==2&&c==0) {x=data[2][0][0]; y=data[1][0][2];}
	if(a==1&&b==2&&c==2) {x=data[2][0][2]; y=data[3][0][0];}
	
	if(a==2&&b==0&&c==0) {x=data[0][2][2]; y=data[2][0][2];}
	if(a==2&&b==0&&c==2) {x=data[4][0][0]; y=data[0][0][2];}
	if(a==2&&b==2&&c==0) {x=data[5][0][2]; y=data[2][2][2];}
	if(a==2&&b==2&&c==2) {x=data[4][2][0]; y=data[5][2][2];}
	
	if(a==3&&b==0&&c==0) {x=data[0][0][0]; y=data[4][0][2];}
	if(a==3&&b==0&&c==2) {x=data[2][0][0]; y=data[0][2][0];}
	if(a==3&&b==2&&c==0) {x=data[5][2][0]; y=data[4][2][2];}
	if(a==3&&b==2&&c==2) {x=data[2][2][0]; y=data[5][0][0];}
	
	if(a==4&&b==0&&c==0) {x=data[2][2][0]; y=data[1][2][2];}
	if(a==4&&b==0&&c==2) {x=data[2][2][2]; y=data[3][2][0];}
	if(a==4&&b==2&&c==0) {x=data[4][2][2]; y=data[1][2][0];}
	if(a==4&&b==2&&c==2) {x=data[4][2][0]; y=data[3][2][2];}
	
	if(a==5&&b==0&&c==0) {x=data[0][0][2]; y=data[3][0][2];}
	if(a==5&&b==0&&c==2) {x=data[0][0][0]; y=data[1][0][0];}
	if(a==5&&b==2&&c==0) {x=data[5][2][2]; y=data[3][2][2];}
	if(a==5&&b==2&&c==2) {x=data[5][2][0]; y=data[1][2][0];}
	

}

void Cube::testSolve()
{
	solveTopCross();
	cout << "cross: " << moves << endl;
	clearMoves();
    printCubeStd();
	solveTopCorners();
	cout << "corners: " << moves << endl;
	clearMoves();
    printCubeStd();
	solveMiddleLayer();
	cout << "middle layer: " << moves << endl;
	clearMoves();
    printCubeStd();
	solveBottomLayer();
	cout << "Bottom: " << moves << endl;
	clearMoves();
    printCubeStd();
}

void Cube::solveTopCross()
{
    cout << "checkpoint1" << endl;
	moveTopEdges();
    cout << "checkpoint2" << endl;
	//look for the 4 yellow edges
	for (int i = 1; i < 5; i++)
	{
		int side = 0; //side that the yellow sticker is on
		int pos = 0; //position (1-4) of the yellow sticker
		findNextTopEdge(side, pos);
		int numTurns = 0; //keeps track of how many times we turn the cube to put pieces on the bottom layer so we can undo the turns
		if (side == 1)
		{
			while (data[5][1][0] == 0)
			{
				rotate(DOWN,1);
			}
			while (data[0][1][0] == 0)
			{
				rotate(UP,1);
				numTurns++;
			}
			if (pos == 1)
			{
				rotate(LEFT,2);
			}
			else if (pos == 2)
			{
				rotate(LEFT,1);
			}
			else if (pos == 4)
			{
				rotate(LEFT,3);
			}
		}
		else if (side == 2)
		{
			while (data[5][0][1] == 0)
			{
				rotate(DOWN,1);
			}
			while (data[0][2][1] == 0)
			{
				rotate(UP,1);
				numTurns++;
			}
			if (pos == 1)
			{
				rotate(FRONT,2);
			}
			else if (pos == 2)
			{
				rotate(FRONT,1);
			}
			else if (pos == 4)
			{
				rotate(FRONT,3);
			}
			rotate(DOWN,3);
		}
		else if (side == 3)
		{
			while (data[5][1][2] == 0)
			{
				rotate(DOWN,1);
			}
			while (data[0][1][2] == 0)
			{
				rotate(UP,1);
				numTurns++;
			}
			if (pos == 1)
			{
				rotate(RIGHT,2);
			}
			else if (pos == 2)
			{
				rotate(RIGHT,1);
			}
			else if (pos == 4)
			{
				rotate(RIGHT,3);
			}
			rotate(DOWN,2);
		}
		else if (side == 4)
		{
			while (data[5][2][1] == 0)
			{
				rotate(DOWN,1);
			}
			while (data[0][0][1] == 0)
			{
				rotate(UP,1);
				numTurns++;
			}
			if (pos == 1)
			{
				rotate(BACK,1);
				rotate(BACK,1);
			}
			else if (pos == 2)
			{
				rotate(BACK,1);
			}
			else if (pos == 4)
			{
				rotate(BACK,3);
			}
			rotate(DOWN,1);
		}
		else if (side == 5)
		{
			for (int j = 0; j < 4 - pos; j++)
			{
				rotate(DOWN,1);
			}
		}
		for (int j = 0; j < numTurns; j++)
		{
			rotate(UP,3);
		}
		if (side == 5) //algorithm for when the sticker is on the bottom
		{
			int color = data[1][2][1];
			for (int a = 1; a < color; a++) //set-up so that the edge goes into the right spot
			{
				rotate(UP,1);
			}
			rotate(LEFT,2);
			for (int a = 1; a < color; a++) //undo set-up
			{
				rotate(UP,3);
			}
		}
		else //algorithm for when th esticker is not on the bottom
		{
			int color = data[5][1][0];
			if (color < 4) //set-up so that the sticker goes into the right spot
			{
				for (int a = 1; a < color + 1; a++)
				{
					rotate(UP,1);
				}
			}
			rotate(LEFT,1);
			rotate(BACK,3);
			rotate(LEFT,3);
			if (color < 4) //undo set-up
			{
				for (int a = 1; a < color + 1; a++)
				{
					rotate(UP,3);
				}
			}
		}
	}
}

void Cube::moveTopEdges() //move all yellow edge stickers on top to the bottom
{
	for (int i = 0; i < 4; i++)
	{
		if (data[0][2][1] == 0)
		{
			while (data[5][0][1] == 0)
			{
				rotate(DOWN,1);
			}
			rotate(FRONT,2);
		}
		rotate(UP,1);
	}
}

void Cube::findNextTopEdge(int & s, int & p)
{
	for (s = 1; s < 6; s++)
	{
		if (data[s][0][1] == 0)
		{
			p = 1;
			break;
		}
		else if (data[s][1][2] == 0)
		{
			p = 2;
			break;
		}
		else if (data[s][2][1] == 0)
		{
			p = 3;
			break;
		}
		else if (data[s][1][0] == 0)
		{
			p = 4;
			break;
		}
	}
}

void Cube::solveTopCorners()
{
	moveTopCorners();
	for (int i = 1; i < 5; i++)
	{
		bool bottom = false; //holds whether the yellow sticker is on the bottom face
		bool rig = false; //holds whether the yellow sticker is on the right face
		int side = 0; //what face the yellow sticker is on
		int pos = 0; //which corner the piece is in
		findNextTopCorner(side, pos);
		if (side < 5) //puts the corner in the back bottom right corner
		{
			if (pos == 2)
			{
				rig = true;
			}
			for (int t = 0; t < side + pos - 1; t++)
			{
				rotate(DOWN,3);
			}
		}
		else //puts the corner in the back bottom right corner
		{
			bottom = true;
			for (int t = 0; t < pos; t++)
			{
				rotate(DOWN,3);
			}
		}
		if (rig) //algorithm for when yellow is on the right
		{
			int color = data[4][2][0];
			if (color < 4) //move the top so that the corner goes into the correct position
			{
				for (int t = 0; t < color; t++)
				{
					rotate(UP,1);
				}
			}
			rotate(RIGHT,1);
			rotate(DOWN,1);
			rotate(RIGHT,3);
			if (color < 4) //undo the setup moves to put the corner in the right position
			{
				for (int t = 0; t < color; t++)
				{
					rotate(UP,3);
				}
			}
		}
		else if (bottom) //algorithm for when yellow is on bottom
		{
			int color = data[3][2][2];
			if (color < 4) //move the top so that the corner goes into the correct position
			{
				for (int t = 0; t < color; t++)
				{
					rotate(UP,1);
				}
			}
			rotate(RIGHT,1);
			rotate(DOWN,2);
			rotate(RIGHT,3);
			rotate(DOWN,3);
			rotate(RIGHT,1);
			rotate(DOWN,1);
			rotate(RIGHT,3);
			if (color < 4) //undo the setup moves to put the corner in the right position
			{
				for (int t = 0; t < color; t++)
				{
					rotate(UP,3);
				}
			}
		}
		else //algorithm for when yellow is on back
		{
			int color = data[5][2][2];
			if (color < 4) //move the top so that the corner goes into the correct position
			{
				for (int t = 0; t < color; t++)
				{
					rotate(UP,1);
				}
			}
			rotate(BACK,3);
			rotate(DOWN,3);
			rotate(BACK,1);
			if (color < 4) //undo the setup moves to put the corner in the right position
			{
				for (int t = 0; t < color; t++)
				{
					rotate(UP,3);
				}
			}
		}
	}
}

void Cube::moveTopCorners() //moves all yellow corners on the top to the bottom face
{
	for (int i = 0; i < 4; i++)
	{
		if (data[0][2][2] == 0 || data[2][0][2] == 0 || data[3][0][0] == 0)
		{
			while (data[1][2][2] == 0 || data[2][2][0] == 0 || data[5][0][0] == 0) //make sure not to push a different yellow corner back to the top
			{
				rotate(DOWN,1);
			}
			rotate(RIGHT,3);
			rotate(DOWN,1);
			rotate(RIGHT,1);
		}
		rotate(UP,1);
	}
}

void Cube::findNextTopCorner(int & s, int & p) //locates the next corner that is not in its correct spot (guaranteed to be one of the bottom four corners)
//updates pos and side in solveTopCorners() to hold the side and position of the yellow sticker
{
	for (s = 1; s < 5; s++)
	{
		if (data[s][2][0] == 0)
		{
			p = 1;
			return;
		}
		else if (data[s][2][2] == 0)
		{
			p = 2;
			return;
		}
	}
	if (data[5][0][0] == 0)
	{
		p = 2;
	}
	else if (data[5][0][2] == 0)
	{
		p = 3;
	}
	else if (data[5][2][2] == 0)
	{
		p = 0;
	}
	else
	{
		p = 1;
	}
}

void Cube::solveMiddleLayer()
{
	int side = -1;
	int color = -1;
	int count = 0;
    
beginning:
	if (side != -1)
	{
		placeMiddleEdge(color, side);
		//print();
		count++;
		side = -1;
		color = -1;
	}
    
	for (int i = 1; i <= 4; i++)
	{
    cout << "checkpoint3" << endl;
		side = findBottomMatch(i);
        
		if (side != -1)
		{
			color = i;
			goto beginning;
		}
	}
    
	for (int i = 1; i <= 4; i++)
	{
		if (data[i][1][0] != (i))
		{
			middleAlgorithm(i, 1);
			if(count >= 15)
			{
				solveTopCross();
				solveTopCorners();
			}
            
			goto beginning;
		}
		else if (data[i][1][2] != i)
		{
			middleAlgorithm(i, 2);
            
			if(count >= 10)
			{
				solveTopCross();
				solveTopCorners();
			}
            
			goto beginning;
		}
	}
    
	int done = 0;
}

int Cube::findBottomMatch(int color)
{
	for (int i = 1; i <= 4; i++)
	{
		if (data[i][2][1] == color)
		{
			if (i % 2 == 0)
			{
				if (data[5][abs(2 - i)][1] != 5)
				{
					return i;
				}
			}
			else
			{
				if (data[5][abs(2 - i)][i - 1] != 5)
				{
					return i;
				}
			}
		}
	}
    
	return -1;
}

void Cube::placeMiddleEdge(int color, int edgeSide)
{
	if (edgeSide - color == 0)
	{
		middleAlgorithm(color, -1);
	}
	else if (edgeSide - color == 1)
	{
		rotate(DOWN,3);
		middleAlgorithm(color, -1);
	}
	else if (edgeSide - color == 2)
	{
		rotate(DOWN,2);
		middleAlgorithm(color, -1);
	}
	else if (edgeSide - color == 3)
	{
		rotate(DOWN,1);
		middleAlgorithm(color, -1);
	}
	else if (edgeSide - color == -1)
	{
		rotate(DOWN,1);
		middleAlgorithm(color, -1);
	}
	else if (edgeSide - color == -2)
	{
		rotate(DOWN,2);
		middleAlgorithm(color, -1);
	}
	else if (edgeSide - color == -3)
	{
		rotate(DOWN,3);
		//print();
		middleAlgorithm(color, -1);
	}
}

void Cube::middleAlgorithm(int color, int direction) //1 - L 2 - R -1 for nothing
{
	if (color == 1)
	{
		if (data[5][1][0] == 4 || direction == 1)
		{
			rotate(DOWN,1);
			rotate(BACK,1);
			rotate(DOWN,3);
			rotate(BACK,3);
			rotate(DOWN,3);
			rotate(LEFT,3);
			rotate(DOWN,1);
			rotate(LEFT,1);
		}
		else if (data[5][1][0] == 2 || direction == 2)
		{
			rotate(DOWN,3);
			rotate(FRONT,3);
			rotate(DOWN,1);
			rotate(FRONT,1);
			rotate(DOWN,1);
			rotate(LEFT,1);
			rotate(DOWN,3);
			rotate(LEFT,3);
		}
	}
	else if (color == 2)
	{
		if (data[5][0][1] == 1 || direction == 1)
		{
			rotate(DOWN,1);
			rotate(LEFT,1);
			rotate(DOWN,3);
			rotate(LEFT,3);
			rotate(DOWN,3);
			rotate(FRONT,3);
			rotate(DOWN,1);
			rotate(FRONT,1);
		}
		else if (data[5][0][1] == 3 || direction == 2)
		{
			rotate(DOWN,3);
			rotate(RIGHT,3);
			rotate(DOWN,1);
			rotate(RIGHT,1);
			rotate(DOWN,1);
			rotate(FRONT,1);
			rotate(DOWN,3);
			rotate(FRONT,3);
		}
	}
	else if (color == 3)
	{
		if (data[5][1][2] == 2 || direction == 1)
		{
			rotate(DOWN,1);
			rotate(FRONT,1);
			rotate(DOWN,3);
			rotate(FRONT,3);
			rotate(DOWN,3);
			rotate(RIGHT,3);
			rotate(DOWN,1);
			rotate(RIGHT,1);
		}
		else if (data[5][1][2] == 4 || direction == 2)
		{
			rotate(DOWN,3);
			rotate(BACK,3);
			rotate(DOWN,1);
			rotate(BACK,1);
			rotate(DOWN,1);
			rotate(RIGHT,1);
			rotate(DOWN,3);
			rotate(RIGHT,3);
		}
	}
	else if (color == 4)
	{
		if (data[5][2][1] == 3 || direction == 1)
		{
			rotate(DOWN,1);
			rotate(RIGHT,1);
			rotate(DOWN,3);
			rotate(RIGHT,3);
			rotate(DOWN,3);
			rotate(BACK,3);
			rotate(DOWN,1);
			rotate(BACK,1);
		}
		else if (data[5][2][1] == 1 || direction == 2)
		{
			rotate(DOWN,3);
			rotate(LEFT,3);
			rotate(DOWN,1);
			rotate(LEFT,1);
			rotate(DOWN,1);
			rotate(BACK,1);
			rotate(DOWN,3);
			rotate(BACK,3);
		}
	}
}

void Cube::solveBottomLayer()
{
	positionBottomCorners();
	//print();
	positionBottomEdges();
	//print();
	correctBottomCorners();
	//print();
	correctBottomEdges();
    //	print();
}

void Cube::positionBottomCorners()
{
	int dTurns[4];
    
	int bestNumDTurns = 0;
	int pos1 = -1;
	int pos2 = -1;
    
	for (int i = 0; i < 4; i++)
	{
		dTurns[i] = numCorrectCorners();
        
		if (dTurns[i] == 4)
		{
			pos1 = 4;
			bestNumDTurns = i;
			break;
		}
		else if (dTurns[i] < 4 && dTurns[i] > -1)
		{
			if (pos2 == -1)
			{
				pos1 = dTurns[i];
				bestNumDTurns = i;
			}
		}
		else if (dTurns[i] > 4)
		{
			int side1 = dTurns[i] % 10 + 1;
			int side2 = (int)(dTurns[i] / 10) + 1;
            
			//Corners are next to each other
			if (side2 == (side1 + 1) || side1 == (side2 + 1) || (side2 == 4 && side1 == 1) || (side2 == 1 && side1 == 4))
			{
				pos1 = side1;
				pos2 = side2;
				bestNumDTurns = i;
			}
			else if (pos2 == -1)
			{
				pos1 = side1;
				pos2 = side2;
				bestNumDTurns = i;
			}
		}
        
		rotate(DOWN,1);
		//print();
	}
    
	for (int i = 0; i < bestNumDTurns && pos1 != 4; i++)
	{
		rotate(DOWN,1);
	}
    

	//Finally Ready to start positioning corners with algorithm!!!!! OMG WHO KNEW A BRAIN COULD DO SO MUCH SO EASILY!!!!!
    
	if (pos1 == 4)
	{
		//One CRAZY lucky scenario, and is the only way to exit this nightmare :D
		return;
	}
	else if (pos2 != -1 && (pos2 == (pos1 + 1) || pos1 == (pos2 + 1) || (pos2 == 4 && pos1 == 1) || (pos2 == 1 && pos1 == 4)))
	{
		int oppFace = pos2 + 3;
		//int face = oppFace + 2;
        
		if (oppFace > 4)
		{
			oppFace = oppFace - 4;
		}
        
		swapCorners(oppFace);
		positionBottomCorners();
		return;
	}
	else if (pos2 != -1)
	{
		//Corners opp. corners correct
		int face = pos1 + 4;
        
		if (face > 4)
		{
			face = face - 4;
		}
        
		int face2 = face + 1;
		if (face2 > 4)
		{
			face2 = face2 - 4;
		}
        
		swapCorners(face);
		swapCorners(face2);
		swapCorners(face);
		positionBottomCorners();
		return;
	}
	else
	{
		//Only 1 correct, 3 corners wrong... If thats even posible (I'm 99% positive it isnt the way I set the cube up)?????
		//But just in case
		int face = pos1 + 2;
        
		if (face > 4)
		{
			face = face - 4;
		}
        
		swapCorners(face); //Eventually One of the previous situations above will occur :D
		positionBottomCorners();
		return;
	}
    
}

void Cube::swapCorners(int face)
{
	if (face == 1)
	{
		rotate(DOWN,3);
		rotate(FRONT,3);
		rotate(DOWN,1);
		rotate(BACK,1);
		rotate(DOWN,3);
		rotate(FRONT,1);
		rotate(DOWN,1);
		rotate(BACK,3);
		rotate(DOWN,3);
	}
	else if (face == 2)
	{
		rotate(DOWN,3);
		rotate(RIGHT,3);
		rotate(DOWN,1);
		rotate(LEFT,1);
		rotate(DOWN,3);
		rotate(RIGHT,1);
		rotate(DOWN,1);
		rotate(LEFT,3);
		rotate(DOWN,3);
	}
	else if (face == 3)
	{
		rotate(DOWN,3);
		rotate(BACK,3);
		rotate(DOWN,1);
		rotate(FRONT,1);
		rotate(DOWN,3);
		rotate(BACK,1);
		rotate(DOWN,1);
		rotate(FRONT,3);
		rotate(DOWN,3);
	}
	else if (face == 4)
	{
		rotate(DOWN,3);
		rotate(LEFT,3);
		rotate(DOWN,1);
		rotate(RIGHT,1);
		rotate(DOWN,3);
		rotate(LEFT,1);
		rotate(DOWN,1);
		rotate(RIGHT,3);
		rotate(DOWN,3);
	}
}

int Cube::numCorrectCorners()
{
	//If numCorrect ==  4 it will return 4
	//If numCorrect == 2 it will return 2nd Corner * 10 + 1st corner (i.e. 20)
	//Else if numCorrect == 1 it will return pos of corner
	//Else if 0 are correct return -1
	int cornerColors[3];
	int side1 = 0;
	int side2 = 0;
    
	int count = 0;
    
	int colorsMatch = 0; //if this equals 2 then there is a match per corner
	int position[4] = { -1, -1, -1, -1 }; //-1 means there is no match, 1 means match
    
	for (int i = 0; i < 4; i++)
	{
		getCorner(i, cornerColors);
        
		side1 = i + 1;
		side2 = i + 2;
        
		if (side2 == 5)
		{
			side2 = 1;
		}
        
		for (int j = 0; j < 3; j++)
		{
			if (cornerColors[j] == side1 || cornerColors[j] == side2)
			{
				colorsMatch++;
			}
		}
        
		if (colorsMatch == 2)
		{
			position[i] = 1;
			count++;
		}
        
		colorsMatch = 0;
	}
    
	int pos = 0;
	int multiplier = 1;
    
	if (count == 4)
	{
		return 4;
	}
	else if (count == 2 || count == 1)
	{
		for (int i = 0; i < 4; i++)
		{
			if (position[i] == 1)
			{
				pos += i * multiplier;
				multiplier *= 10;
			}
		}
	}
	else
	{
		pos = -1;
	}
    
	return pos;
}

void Cube::getCorner(int num, int corners[])
{
	if (num == 0)
	{
		corners[0] = data[1][2][2];
		corners[1] = data[2][2][0];
		corners[2] = data[5][0][0];
	}
	else if (num == 1)
	{
		corners[0] = data[2][2][2];
		corners[1] = data[3][2][0];
		corners[2] = data[5][0][2];
	}
	else if (num == 2)
	{
		corners[0] = data[3][2][2];
		corners[1] = data[4][2][0];
		corners[2] = data[5][2][2];
	}
	else if (num == 3)
	{
		corners[0] = data[4][2][2];
		corners[1] = data[1][2][0];
		corners[2] = data[5][2][0];
	}
}

void Cube::positionBottomEdges()
{
	int pos = numEdgesInCorrectPos();
    
	if (pos == 0)
	{
		rotateEdges(2, true);
		positionBottomEdges();
		return;
	}
	else if (pos == 5)
	{
		return;
	}
	else
	{
		bool clockwise = pos > 0;
        
		int face = abs(pos) + 1;
        
		if (face > 4)
		{
			face = face - 4;
		}
        
		rotateEdges(face, clockwise);
		return;
	}
}

int Cube::numEdgesInCorrectPos()
{
	//Note this will either be 1, 0 or 4...
	//It will return 0 if none are in correct position
	//If there is one in correct position it will return the corresponding position pos or neg determining rotation
	//Note positions are determined by what side they match with, 1 - 4
	//Return 5 if all are in position
    
	int edges[4][2] = { { data[5][1][0], data[1][2][1] }, { data[5][0][1], data[2][2][1] }, { data[5][1][2], data[3][2][1] }, { data[5][2][1], data[4][2][1] } };
    
	int correctPos = -1;
	int numCorrect = 0;
	bool isOneCorrect = false;
	int positions[4];
    
	for (int i = 1; i <= 4; i++)
	{
		for (int j = 0; j < 2; j++)
		{
			if (edges[i - 1][j] == i)
			{
				isOneCorrect = true;
				correctPos = i - 1;
				numCorrect++;
			}
            
			if (edges[i - 1][j] != 5)
			{
				positions[i - 1] = edges[i - 1][j];
			}
		}
	}
    
	if (numCorrect == 4)
	{
		return 5;
	}
    
	if (isOneCorrect == false)
	{
		return 0;
	}
	else
	{
		bool clockwise = false;
		bool firstTime = true;
		int numTimesThrough = 0;
		numCorrect = 0;
		int temp;
		int temp2;
        
		while (numCorrect != 4)
		{
			firstTime = true;
			numCorrect = 0;
			for (int i = 0; i < 4; i++)
			{
				if (i != correctPos)
				{
					if (firstTime)
					{
						firstTime = false;
						temp = positions[i];
                        
						int j = i - 1;
                        
						if (j < 0)
						{
							j = 4 + j;
						}
                        
						if (j == correctPos)
						{
							j--;
							if (j < 0)
							{
								j = 4 + j;
							}
						}
                        
						positions[i] = positions[j];
					}
					else
					{
						temp2 = positions[i];
						positions[i] = temp;
						temp = temp2;
					}
				}
                
				if (positions[i] == i + 1)
				{
					numCorrect++;
				}
			}
            
			numTimesThrough++;
		}
        
		clockwise = numTimesThrough == 1;
		correctPos++;
        
		if (clockwise == false)
		{
			correctPos = -1 * (correctPos);
		}
	}
    
	return correctPos;
}

void Cube::rotateEdges(int face, bool rotClockwise)
{
	if (face == 1)
	{
		if (rotClockwise == true)
		{
			rotate(FRONT,2);
			rotate(DOWN,1);
			rotate(LEFT,3);
			rotate(RIGHT,1);
			rotate(FRONT,2);
			rotate(LEFT,1);
			rotate(RIGHT,3);
			rotate(DOWN,1);
			rotate(FRONT,2);
		}
		else
		{
			rotate(FRONT,2);
			rotate(DOWN,3);
			rotate(LEFT,3);
			rotate(RIGHT,1);
			rotate(FRONT,2);
			rotate(LEFT,1);
			rotate(RIGHT,3);
			rotate(DOWN,3);
			rotate(FRONT,2);
		}
	}
	else if (face == 2)
	{
		if (rotClockwise == true)
		{
			rotate(RIGHT,2);
			rotate(DOWN,1);
			rotate(FRONT,3);
			rotate(BACK,1);
			rotate(RIGHT,2);
			rotate(FRONT,1);
			rotate(BACK,3);
			rotate(DOWN,1);
			rotate(RIGHT,2);
		}
		else
		{
			rotate(RIGHT,2);
			rotate(DOWN,3);
			rotate(FRONT,3);
			rotate(BACK,1);
			rotate(RIGHT,2);
			rotate(FRONT,1);
			rotate(BACK,3);
			rotate(DOWN,3);
			rotate(RIGHT,2);
		}
	}
	else if (face == 3)
	{
		if (rotClockwise == true)
		{
			rotate(BACK,2);
			rotate(DOWN,1);
			rotate(RIGHT,3);
			rotate(LEFT,1);
			rotate(BACK,2);
			rotate(RIGHT,1);
			rotate(LEFT,3);
			rotate(DOWN,1);
			rotate(BACK,2);
		}
		else
		{
			rotate(BACK,2);
			rotate(DOWN,3);
			rotate(RIGHT,3);
			rotate(LEFT,1);
			rotate(BACK,2);
			rotate(RIGHT,1);
			rotate(LEFT,3);
			rotate(DOWN,3);
			rotate(BACK,2);
		}
	}
	else if (face == 4)
	{
		if (rotClockwise == true)
		{
			rotate(LEFT,2);
			rotate(DOWN,1);
			rotate(BACK,3);
			rotate(FRONT,1);
			rotate(LEFT,2);
			rotate(BACK,1);
			rotate(FRONT,3);
			rotate(DOWN,1);
			rotate(LEFT,2);
		}
		else
		{
			rotate(LEFT,2);
			rotate(DOWN,3);
			rotate(BACK,3);
			rotate(FRONT,1);
			rotate(LEFT,2);
			rotate(BACK,1);
			rotate(FRONT,3);
			rotate(DOWN,3);
			rotate(LEFT,2);
		}
	}
}

void Cube::correctBottomCorners()
{
	int result = cornerOrientation();
    
	while (result != 5)
	{
		twoCornerRotate(abs(findBestFace(result)), findBestFace(result) > 0);
        
		result = cornerOrientation();
	}
}

int Cube::cornerOrientation()
{
	int numCorrect = 0;
	int wrongPosition = 0;
    
	int corners[4] = { data[5][0][0], data[5][0][2], data[5][2][2], data[5][2][0] };
    
	for (int i = 0; i < 4; i++)
	{
		if (corners[i] == 5)
		{
			numCorrect++;
		}
		else
		{
			wrongPosition = i;
		}
	}
    
	if (numCorrect == 4)
	{
		return 5;
	}
    
	return wrongPosition;
}

int Cube::findBestFace(int cornerNum)
{
	int corners[4] = { data[5][0][0], data[5][0][2], data[5][2][2], data[5][2][0] };
    
	int corner1 = cornerNum + 1;
	int corner2 = cornerNum - 1;
    
	if (corner1 > 3)
	{
		corner1 = 4 - corner1;
	}
    
	if (corner2 < 0)
	{
		corner2 = 4 + corner2;
	}
    
	//First Determine which corner to go with
	int finalCorner = -1;
	int face = -1;
    
	if (corners[cornerNum] == corners[corner1])
	{
		finalCorner = corner1;
        
		face = corners[finalCorner] + 1;
        
		if (face > 4)
		{
			face = face - 4;
		}
        
		return face;
	}
	else if (corners[cornerNum] == corners[corner2])
	{
		finalCorner = corner2;
        
		face = corners[finalCorner] + 1;
        
		if (face > 4)
		{
			face = face - 4;
		}
        
		return face;
	}
	else if (abs(corners[cornerNum] - corners[corner1]) == 2 && corners[corner1] != 5)
	{
		finalCorner = corner1;
		face = corners[finalCorner];
		return -face;
	}
	else if (abs(corners[cornerNum] - corners[corner2]) == 2 && corners[corner2] != 5)
	{
		finalCorner = corner2;
		face = corners[cornerNum];
		return -face;
	}
	else
	{
		face = corners[cornerNum];
		return face;
	}
}

void Cube::twoCornerRotate(int face, bool goForward)
{
	if (face == 1)
	{
		if (goForward == true)
		{
			rotate(BACK,3);
			rotate(UP,1);
			rotate(BACK,1);
			rotate(LEFT,1);
			rotate(UP,1);
			rotate(LEFT,3);
			rotate(DOWN,1);
			rotate(LEFT,1);
			rotate(UP,3);
			rotate(LEFT,3);
			rotate(BACK,3);
			rotate(UP,3);
			rotate(BACK,1);
			rotate(DOWN,3);
		}
		else
		{
			rotate(DOWN,1);
			rotate(BACK,3);
			rotate(UP,1);
			rotate(BACK,1);
			rotate(LEFT,1);
			rotate(UP,1);
			rotate(LEFT,3);
			rotate(DOWN,3);
			rotate(LEFT,1);
			rotate(UP,3);
			rotate(LEFT,3);
			rotate(BACK,3);
			rotate(UP,3);
			rotate(BACK,1);
		}
	}
	else if (face == 2)
	{
		if (goForward == true)
		{
			rotate(LEFT,3);
			rotate(UP,1);
			rotate(LEFT,1);
			rotate(FRONT,1);
			rotate(UP,1);
			rotate(FRONT,3);
			rotate(DOWN,1);
			rotate(FRONT,1);
			rotate(UP,3);
			rotate(FRONT,3);
			rotate(LEFT,3);
			rotate(UP,3);
			rotate(LEFT,1);
			rotate(DOWN,3);
		}
		else
		{
			rotate(DOWN,1);
			rotate(LEFT,3);
			rotate(UP,1);
			rotate(LEFT,1);
			rotate(FRONT,1);
			rotate(UP,1);
			rotate(FRONT,3);
			rotate(DOWN,3);
			rotate(FRONT,1);
			rotate(UP,3);
			rotate(FRONT,3);
			rotate(LEFT,3);
			rotate(UP,3);
			rotate(LEFT,1);
		}
	}
	else if (face == 3)
	{
		if (goForward == true)
		{
			rotate(FRONT,3);
			rotate(UP,1);
			rotate(FRONT,1);
			rotate(RIGHT,1);
			rotate(UP,1);
			rotate(RIGHT,3);
			rotate(DOWN,1);
			rotate(RIGHT,1);
			rotate(UP,3);
			rotate(RIGHT,3);
			rotate(FRONT,3);
			rotate(UP,3);
			rotate(FRONT,1);
			rotate(DOWN,3);
		}
		else
		{
			rotate(DOWN,1);
			rotate(FRONT,3);
			rotate(UP,1);
			rotate(FRONT,1);
			rotate(RIGHT,1);
			rotate(UP,1);
			rotate(RIGHT,3);
			rotate(DOWN,3);
			rotate(RIGHT,1);
			rotate(UP,3);
			rotate(RIGHT,3);
			rotate(FRONT,3);
			rotate(UP,3);
			rotate(FRONT,1);
		}
	}
	else if (face == 4)
	{
		if (goForward == true)
		{
			rotate(RIGHT,3);
			rotate(UP,1);
			rotate(RIGHT,1);
			rotate(BACK,1);
			rotate(UP,1);
			rotate(BACK,3);
			rotate(DOWN,1);
			rotate(BACK,1);
			rotate(UP,3);
			rotate(BACK,3);
			rotate(RIGHT,3);
			rotate(UP,3);
			rotate(RIGHT,1);
			rotate(DOWN,3);
		}
		else
		{
			rotate(DOWN,1);
			rotate(RIGHT,3);
			rotate(UP,1);
			rotate(RIGHT,1);
			rotate(BACK,1);
			rotate(UP,1);
			rotate(BACK,3);
			rotate(DOWN,3);
			rotate(BACK,1);
			rotate(UP,3);
			rotate(BACK,3);
			rotate(RIGHT,3);
			rotate(UP,3);
			rotate(RIGHT,1);
		}
	}
}

void Cube::correctBottomEdges()
{
	int edges[4] = { data[5][1][0], data[5][0][1], data[5][1][2], data[5][2][1] };
    
	bool isTogether = false;
	bool isStart = false;
	int numWrong = 0;
	int pos1 = -1;
	int pos2 = -1;
	int j = 0;
    
	for (int i = 0; i < 5; i++)
	{
		j = i;
        
		if (i == 4)
		{
			j = 0;
		}
        
		if (edges[j] != 5)
		{
			numWrong++;
			if (isStart == false)
			{
				pos1 = j;
				isStart = true;
			}
			else
			{
				pos2 = j;
				isTogether = true;
			}
		}
		else
		{
			isStart = false;
		}
	}
    
	if (numWrong >= 4)
	{
		twoEdgeRotate(1, false);
		twoEdgeRotate(2, false);
		return;
	}
	else
	{
		if(pos2 != -1)
		{
			twoEdgeRotate(pos2 + 1, isTogether);
		}
		else
		{
			twoEdgeRotate(pos1 + 1, isTogether);
		}
		return;
	}
}

void Cube::twoEdgeRotate(int face, bool isNextTo)
{
	if (face == 1)
	{
		if (isNextTo == true)
		{
			rotate(LEFT,1);
			rotate(UP,3);
			rotate(DOWN,1);
			rotate(FRONT,2);
			rotate(DOWN,2);
			rotate(UP,2);
			rotate(BACK,1);
			rotate(DOWN,1);
			rotate(BACK,3);
			rotate(UP,2);
			rotate(DOWN,2);
			rotate(FRONT,2);
			rotate(DOWN,3);
			rotate(UP,1);
			rotate(LEFT,3);
			rotate(DOWN,3);
		}
		else
		{
			rotate(LEFT,1);
			rotate(UP,3);
			rotate(DOWN,1);
			rotate(FRONT,2);
			rotate(DOWN,2);
			rotate(UP,2);
			rotate(BACK,1);
			rotate(DOWN,2);
			rotate(BACK,3);
			rotate(UP,2);
			rotate(DOWN,2);
			rotate(FRONT,2);
			rotate(DOWN,3);
			rotate(UP,1);
			rotate(LEFT,3);
			rotate(DOWN,2);
		}
	}
	else if (face == 2)
	{
		if (isNextTo == true)
		{
			rotate(FRONT,1);
			rotate(UP,3);
			rotate(DOWN,1);
			rotate(RIGHT,2);
			rotate(DOWN,2);
			rotate(UP,2);
			rotate(LEFT,1);
			rotate(DOWN,1);
			rotate(LEFT,3);
			rotate(UP,2);
			rotate(DOWN,2);
			rotate(RIGHT,2);
			rotate(DOWN,3);
			rotate(UP,1);
			rotate(FRONT,3);
			rotate(DOWN,3);
		}
		else
		{
			rotate(FRONT,1);
			rotate(UP,3);
			rotate(DOWN,1);
			rotate(RIGHT,2);
			rotate(DOWN,2);
			rotate(UP,2);
			rotate(LEFT,1);
			rotate(DOWN,2);
			rotate(LEFT,3);
			rotate(UP,2);
			rotate(DOWN,2);
			rotate(RIGHT,2);
			rotate(DOWN,3);
			rotate(UP,1);
			rotate(FRONT,3);
			rotate(DOWN,2);
		}
	}
	else if (face == 3)
	{
		if (isNextTo == true)
		{
			rotate(RIGHT,1);
			rotate(UP,3);
			rotate(DOWN,1);
			rotate(BACK,2);
			rotate(DOWN,2);
			rotate(UP,2);
			rotate(FRONT,1);
			rotate(DOWN,1);
			rotate(FRONT,3);
			rotate(UP,2);
			rotate(DOWN,2);
			rotate(BACK,2);
			rotate(DOWN,3);
			rotate(UP,1);
			rotate(RIGHT,3);
			rotate(DOWN,3);
		}
		else
		{
			rotate(RIGHT,1);
			rotate(UP,3);
			rotate(DOWN,1);
			rotate(BACK,2);
			rotate(DOWN,2);
			rotate(UP,2);
			rotate(FRONT,1);
			rotate(DOWN,2);
			rotate(FRONT,3);
			rotate(UP,2);
			rotate(DOWN,2);
			rotate(BACK,2);
			rotate(DOWN,3);
			rotate(UP,1);
			rotate(RIGHT,3);
			rotate(DOWN,2);
		}
	}
	else if (face == 4)
	{
		if (isNextTo == true)
		{
			rotate(BACK,1);
			rotate(UP,3);
			rotate(DOWN,1);
			rotate(LEFT,2);
			rotate(DOWN,2);
			rotate(UP,2);
			rotate(RIGHT,1);
			rotate(DOWN,1);
			rotate(RIGHT,3);
			rotate(UP,2);
			rotate(DOWN,2);
			rotate(LEFT,2);
			rotate(DOWN,3);
			rotate(UP,1);
			rotate(BACK,3);
			rotate(DOWN,3);
		}
		else
		{
			rotate(BACK,1);
			rotate(UP,3);
			rotate(DOWN,1);
			rotate(LEFT,2);
			rotate(DOWN,2);
			rotate(UP,2);
			rotate(RIGHT,1);
			rotate(DOWN,2);
			rotate(RIGHT,3);
			rotate(UP,2);
			rotate(DOWN,2);
			rotate(LEFT,2);
			rotate(DOWN,3);
			rotate(UP,1);
			rotate(BACK,3);
			rotate(DOWN,2);
		}
	}
}

string Cube::last()
{
	if (moves.size() < 3)
	{
		return "";
	}
	int s = moves.size();
	return moves.substr(s - 3, 3);
}

void Cube::removeLast()
{
	if (moves.size() < 3)
	{
		return;
	}
	int s = moves.size();
	moves = moves.substr(0, s - 3);
}

void Cube::clearMoves()
{
	moves = "";
}



