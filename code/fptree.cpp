#include<iostream>
#include<stdlib.h>
#include "string.cpp"
#include<fstream>


unsigned short nodeCount=0;
ofstream out;
	
class node   // a primary class which represents a node in the tree
{
   public:
    char nodeName; // this indicates the character, to which the node is associated with
    unsigned short count,nodenumber;
    
    node *pointers[30];
    node()
    {
    	nodeName=0;
    	count=1;
    	nodenumber=0;
    	for(int i=0;i<30;i++)
		pointers[i]=NULL;
    }
};


class FPTree
{
	public:
	node *root;
	FPTree()
	{
		node *n=new node();
		n->nodeName='0';
		n->nodenumber=0;
		n->count=0;
		nodeCount++;
		root=n;
	}
	
	void addToTree(char *arr,int n)
	{
		
	     node *temp=root;
	     int k=0;
	     while(k<n)
	     {
		  if(temp->pointers[arr[k]-'a']==NULL)
		  {	
			   node *n=new node();
			   n->nodeName=arr[k];
			   n->nodenumber=nodeCount;
			   nodeCount++;
			   temp->pointers[arr[k]-'a']=n;
			   temp=n;	  	  	
		  }
		  else
		  {
			 temp=temp->pointers[arr[k]-'a'];
			 temp->count++;		  	
		  } 
		  k++;
	     }
	}		
	
	void preDisplay(node *root)
	{
		cout<<root->nodeName<<"  "<<root->count<<endl;	
		for(int i=0;i<30;i++)
		{
			if(root->pointers[i]!=NULL)
			{
				preDisplay(root->pointers[i]);
			}
		}
	}
	
	void createNodes(node *root)
	{
		String s,s2,nodecount;
		s=root->nodenumber;
		s2.str[0]=root->nodeName;
		s2.str[1]=0;
		nodecount=root->count;
		s=s + (char*) " [ style=bold label=\"'" + s2 + (char*) "'\\n" + nodecount + (char*)"\" ]\n";
		out.write((char*)s.str,s.getLength());
		out.flush();
		
		for(int i=0;i<30;i++)
		{
			if(root->pointers[i]!=NULL)
			{
				createNodes(root->pointers[i]);
			}
		}
	}
	void linkNodes(node *root)
	{
		String s,s2,temp;
		s=root->nodenumber;
		
		for(int i=0;i<30;i++)
		{
			if(root->pointers[i]!=NULL)
			{
				s2=root->pointers[i]->nodenumber;
				temp=s + (char*)"->" + s2 + (char*)"\n";
				out.write((char*)temp.str,temp.getLength());
				out.flush();
				linkNodes(root->pointers[i]);
			}
		}
	}
	void display()
	{
	     node * temp=root;
		preDisplay(temp);
		createNodes(temp);
		linkNodes(temp);
	}		
};


void sortInput(char *arr, unsigned short freqArr[])
{
	int k=strlen(arr);
	for(int i=0;i<k-1;i++)
	  for(int j=0;j<k-1;j++)
	   if(freqArr[arr[j]]<freqArr[arr[j+1]])
	   {
	   	char temp=arr[j];
	   	arr[j]=arr[j+1];
	   	arr[j+1]=temp;
	   }
	   
	for(int i=0;i<k;i++)
	  cout<< arr[i]<<", ";
	  cout<<endl;
}


int main()
{
	String s=String((char*)"digraph dg \n{\n");
	out.open("fptree.dot",ios::binary);
	out.write((char*)s.str,strlen(s.str));
	out.flush();
	FPTree fpt=FPTree();
	char arr[30][30]={0};
	int n, no_items=0;
	unsigned short freqArr[256]={0};
	cin>>n;
	
	for(int i=0;i<n;i++)
	{   int j=0;
	    cin>> no_items;
	    for(j=0;j<no_items;j++)
	    {
	    	cin>>arr[i][j];
	    	freqArr[arr[i][j]]++;
	    }	    	
	    arr[i][j]='\0';
	}
         
        for(int i=0;i<256;i++)
        {	
        	if(freqArr[i]!=0)
           cout<<char(i)<<"  : "<<freqArr[i]<<endl;
        }
        
	for(int i=0;i<n;i++)
	        sortInput(arr[i],freqArr);
	        
	for(int i=0;i<n;i++)
	    fpt.addToTree(arr[i],strlen(arr[i]));
	fpt.display();
	s=(char*)"\n}";
	out.write((char*)s.str,strlen(s.str));
	out.close();
	system("dotty fptree.dot");
	return 0;
}
