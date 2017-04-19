#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <sys/time.h>
double cpu_time_used;
struct timeval start, end;
/*
	****Author:Bharath****
	****Utility:File Differtiator****
	****Abstract:Gives what lines in a file are same and what lines are different!****
	****Usuage: <executable> <file1> <file2>****
*/
using namespace std;
class Line
{
	public:
		string line;
		long long int lineno;
};
void display(vector<string> v)
{
	int i;
	for(i=0;i<v.size();i++)
	{
		cout<<v[i]<<"\n";
	}
}
void getSameDiff(vector<string> filec1,long long int &dif1,vector<string> filec2,long long int &dif2,vector<Line> &difffile1,vector<Line> &difffile2,vector<Line> &same,long long int start,long long int end)
{
	int diff1=0;
	int diff2=0;
	int i1=0;
	int i2=0;
	while(i1<filec1.size()&&i2<filec2.size())
	{
		if(filec1[i1].compare(filec2[i2])!=0)
		{
			Line l1;
			Line l2;
			l1.line=filec1[i1];
			l1.lineno=l2.lineno=(i1+1);
			l2.line=filec2[i2];			
			difffile1.push_back(l1);
			difffile2.push_back(l2);
			diff1++;
			diff2++;
		}
		else
		{
			Line l1;
			l1.line=filec1[i1];
			l1.lineno=(i1+1);
			same.push_back(l1);
		}
		i1++;
		i2++;
	}
	while(i1<filec1.size())
	{
		Line l1;
		l1.lineno=(i1+1);
		l1.line=filec1[i1++];
		difffile1.push_back(l1);
		diff1++;
	}
	while(i2<filec2.size())
	{
		Line l2;
		l2.lineno=(i2+1);
		l2.line=filec2[i2++];
		difffile2.push_back(l2);
		diff2++;
	}
	dif1=diff1;
	dif2=diff2;
}
int main(int argc,char *argv[])
{
	if(argc<2)
	{
		cout<<"Invalid usuage of the program!\n";
		cout<<"Correct Usuage: <executable> <filename> <filename>\n";
		return 1;
	}
	string line;
	vector<string> filec1;
	vector<string> filec2;
	bool isdiff = true;
	vector<Line> differfile1,differfile2;
	vector<Line> same;
	ifstream file1(argv[1]);
	ifstream file2(argv[2]);
	if(!file1)
	{
	        cout<<"Error opening "<<argv[1]<< endl;
	        return -1;
	}
	while (getline(file1, line))
	{	
   		filec1.push_back(line);	
	}
	if(!file2)
	{
        	cout<<"Error opening output "<<argv[2]<<endl;
       		return -1;
	}
	while (getline(file2, line))
	{
		filec2.push_back(line);
	}
	long long int diff1;
	long long int diff2;
	gettimeofday(&start, NULL);
	getSameDiff(filec1,diff1,filec2,diff2,differfile1,differfile2,same,0,filec1.size()>filec2.size()?filec1.size():filec2.size());
	gettimeofday(&end, NULL);
	double delta = ((end.tv_sec  - start.tv_sec) * 1000000u + 
         end.tv_usec - start.tv_usec) / 1.e6;	
	int i;	
	if(differfile1.size()==0)
		isdiff=false;
	if(isdiff)
	{
		cout<<"***********************************************************************\n";
		cout<<"These are different:\n";
		cout<<diff1<<"c"<<diff2<<"\n";
		for(i=0;i<differfile1.size();i++)
		{	
			cout<<"< "<<differfile1[i].line<<"  :"<<differfile1[i].lineno<<"\n";
		}
		cout<<"-----------------------------------------------------------------------\n";
		for(i=0;i<differfile2.size();i++)
		{	
			cout<<"> "<<differfile2[i].line<<"  :"<<differfile2[i].lineno<<"\n";
		}
	}
	if(same.size()>0)
		cout<< "***********************************************************************\nThese lines are same\n";
	for(i=0;i<same.size();i++)
	{	
		cout<<same[i].line<<"  :"<<same[i].lineno<<"\n";
	}
	if(same.size()>0)
		cout<< "***********************************************************************\n" ;
	printf("Time Taken: %lf\n",delta);
	return 0;
}
