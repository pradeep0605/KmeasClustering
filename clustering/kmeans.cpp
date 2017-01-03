#include<iostream>
#include<fstream>
#include<stdlib.h>
#include<math.h>
#include "string.cpp"

using namespace std;


double mod(double x)
{
	if(x>=0)
		return x;
	else
	 return (x*-1);
}

class Point
{
	public:
	double x,y;
	unsigned int clusterNumber;
	Point()
	{
		x=y=clusterNumber=0;
	}	
	void display()
	{
		cout<<"("<<x<<","<<y<<")";
	}
};

int main()
{
	unsigned int numPoints,numCluster,numIterations;
	cout.precision(3);
	cin>>numPoints;
	
	Point inputPoints[numPoints];
	for(int i=0;i<numPoints;i++)
	{
		cin>>inputPoints[i].x;
		cin>>inputPoints[i].y;
	} 
	cin>>numCluster;
	Point clusterPoints[numCluster];
	for(int i=0;i<numCluster;i++)
	{
		cin>>clusterPoints[i].x;
		cin>>clusterPoints[i].y;
	}
	
	cin>>numIterations;
	for(int k=0;k<numIterations;k++)
	{
		String s,tp=String();
		s=k;
		ofstream iterout((s+(char*)".iterplt").str,ios::binary);
		s=(char*)"set term png\nset output \"" + s + (char*)".png\"\nplot ";
		
		
	 	cout<<"ITERATION "<<k+1<<endl<<"\t";
 	 	for(int p=0;p<numCluster;p++)
			{
				clusterPoints[p].display();
			
				cout<<"\t";
			}
			cout<<endl;
		for(int i=0;i<numPoints;i++)
		{
			double distances[numCluster],least=9999999;
			int index=0;
			
			for(int j=0;j<numCluster;j++)
			{
				distances[j]=mod(inputPoints[i].x-clusterPoints[j].x)+	mod(inputPoints[i].y-clusterPoints[j].y);
			}	
			inputPoints[i].display();
			
			for(int j=0;j<numCluster;j++)
			{
				if(distances[j]<least)
				{
					least=distances[j];
					index=j;
				}	
				inputPoints[i].clusterNumber=index;
				cout<<"\t"<<distances[j];
			}
			cout<<"\t|"<<inputPoints[i].clusterNumber+1<<endl;
		}
		
		for(int i=0;i<numCluster;i++)
		{	
			String temp,temp2;
			temp=k;
			temp2=i;
			
			ofstream out((temp+temp2+(char*)".plt").str,ios::binary);		
			s=s+ (char*) " \"" + (temp+temp2+(char*)".plt") + (char*)"\",";
			Point New=Point();
			int count=0;
			for(int j=0;j<numPoints;j++)
			{
				if(inputPoints[j].clusterNumber==i)
				{
				  New.x+=inputPoints[j].x;
				  New.y+=inputPoints[j].y;
				  out<<inputPoints[j].x<<" "<<inputPoints[j].y<<endl;
				  count++;
				}  
			}
			
			clusterPoints[i].x=New.x/count;
			clusterPoints[i].y=New.y/count;
		}
			s.str[s.getLength()-1]=0;
			iterout<<s.str;
			iterout.flush();
			iterout.close();
			s=k;
			system(((char*)"gnuplot < " + s + (char*)".iterplt").str);
		cout<<endl<<endl;
	}
	return 0;
}




