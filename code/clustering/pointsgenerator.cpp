#include<iostream>
#include<fstream>
#include<stdlib.h>


using namespace std;


unsigned int getRandomValue() // to get random value.. rand() gives the same random values for every execution 
{			      // hence to get completely random value am multiplying rand() with current time value which always
   usleep(1000);              // yields unique values for the every execution
   return (rand()*time(NULL));
}


int main()
{
	char name[50]={0};
	
	int n,mod;
	cout<<"Enter the filename to be created:";
	cin>>name;
	ofstream out(name,ios::binary);
	cout<<"Enter the numer of cluster points:";
	cin>>n;
	unsigned short arr[100000][2]={0};
	cout<<"Enter the limit of the points:";
	cin>>mod;
	out<<n<<endl;
	for(int i=0;i<n;i++)
	{
		unsigned int x,y;
		x=getRandomValue()%mod;
		y=getRandomValue()%mod;
		arr[i][0]=x;
		arr[i][1]=y;
		out<<x<<" "<<y<<endl;
	}
	
	int numCenters=0,numIternations;
	cout<<"Enter the number of cetners:";
	cin>>numCenters;
	cout<<"Enter the index of "<<numCenters<<" cluster centers:";
	out<<endl<<numCenters<<endl;
	for(int i=0;i<numCenters;i++)
	{
		int index;
		cin>>index;
		
		out<<arr[index][0]<<" "<<arr[index][1]<<endl;
	}
	
	cout<<"Enter the number of iternations:";
	cin>>numIternations;
	out<<endl<<numIternations;
	out.flush();
	
	out.close();
	return 0;
}




