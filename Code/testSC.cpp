#include "ServerCube.hpp"
#include <iostream>
#include <ctime>
#include <cstdlib>
#include <algorithm>

using namespace std;

int main()
{
	srand(time(NULL));
	ServerCube x(1),y,z,w;
	
	z.stringToCube("000000000111111111222222222333333333444444444555555555");
	
	z.print();
	
	
	
	
	x.print();
	
	y.stringToCube("006660000116661111222266622366633333444444466556665555");
	
	
	y.print();
	
	int a[3];
	
	x.compareToQuestion(y,a);
	for(int i=0;i<3;i++)
	{
		cout<<a[i]<<" ";
	}
	cout<<endl;
	
	if(!x.checkDone())
		cout<<"x: false"<<endl;
	else 
		cout<<"x: true"<<endl;
	
	if(!y.checkDone())
		cout<<"y: false"<<endl;
	else 
		cout<<"y: true"<<endl;
	
	if(!z.checkDone())
		cout<<"z: false"<<endl;
	else 
		cout<<"z: true"<<endl;
	
	if(!w.checkDone())
		cout<<"w: false"<<endl;
	else 
		cout<<"w: true"<<endl;
	
	return 0;
}

















