#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <deque>
#include <omp.h>
#include <sys/time.h>
double cpu_time_used;
struct timeval start, end;
/*
	*** UNDER TESTING ***
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
void display(vector<Line> v)
{
	int i;
	for(i=0;i<v.size();i++)
	{
		cout<<v[i].line<<":"<<v[i].lineno<<" ";
	}
	cout<<"\n";
}
void getSameDiff(vector<string> filec1,long long int &dif1,vector<string> filec2,long long int &dif2,vector<Line> &difffile1,vector<Line> &difffile2,vector<Line> &same,long long int start,long long int end)
{
	if(end<=start)
	{
		long long int temp = start;
		start = end;
		end = temp;
	}
	if(end-start<=100000)
	{
		long long int diff1=0;
		long long int diff2=0;
		long long int i1=start;
		long long int i2=start;
		while((i1<end)&&(i2<end))
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
		dif1=diff1;
		dif2=diff2;
	}
	else
	{
		long long int mid = end + start;
		//cout<<"end:start:mid:"<<end<<":"<<start<<":"<<mid<<"\n";
		vector<Line> differfile11,differfile12,differfile13,differfile14;
		vector<Line> differfile21,differfile22,differfile23,differfile24;	
		vector<Line> same1,same2,same3,same4;
		long long int diff11,diff12,diff13,diff14;
		long long int diff21,diff22,diff23,diff24;
		#pragma omp parallel sections  
		{
			#pragma omp section  
			{			
				getSameDiff(filec1,diff11,filec2,diff21,differfile11,differfile21,same1,start,mid/2);
			}			
			#pragma omp section  
			{			
				getSameDiff(filec1,diff12,filec2,diff22,differfile12,differfile22,same2,mid/2,end);
			}				
		}
		dif1=diff11+diff12;
		dif2=diff21+diff22;
		long long int i,j;
		#pragma omp parallel sections
		{
			#pragma omp section
			{
				for(i=0;i<differfile11.size();i++)
				{	
					difffile1.push_back(differfile11[i]);
				}
			}
			#pragma omp section
			{
				for(i=0;i<differfile21.size();i++)
				{	
					difffile2.push_back(differfile21[i]);
				}
			}
			#pragma omp section
			{
				for(j=0;j<same1.size();j++)
				{
					same.push_back(same1[j]);
				}
			}
		}
		#pragma omp parallel sections
		{
			#pragma omp section
			{
				for(i=0;i<differfile12.size();i++)
				{
					difffile1.push_back(differfile12[i]);
				}
			}
			#pragma omp section
			{
				for(i=0;i<differfile22.size();i++)
				{
					difffile2.push_back(differfile22[i]);
				}
			}
			#pragma omp section
			{
				for(j=0;j<same2.size();j++)
				{
					same.push_back(same2[j]);
				}
			}
		}	
	}
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
	long long int min = filec1.size()<filec2.size()?filec1.size():filec2.size();
	long long int diff1;
	long long int diff2;
	gettimeofday(&start, NULL);
	{
		getSameDiff(filec1,diff1,filec2,diff2,differfile1,differfile2,same,0,min);
	}
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
		cout<<differfile1.size()+(filec1.size()>filec2.size()?filec1.size()-filec2.size():0)<<"c"<<differfile2.size()+(filec1.size()>filec2.size()?0:filec2.size()-filec1.size())<<"\n";
		for(i=0;i<differfile1.size();i++)
		{	
			cout<<"< "<<differfile1[i].line<<"  :"<<differfile1[i].lineno<<"\n";
		}
		if(filec1.size()>filec2.size())
		{
			for(i=filec2.size();i<filec1.size();i++)
			{
				cout<<"< "<<filec1[i]<<"  :"<<(i+1)<<"\n";			
			}
		}
		cout<<"-----------------------------------------------------------------------\n";
		for(i=0;i<differfile2.size();i++)
		{	
			cout<<"> "<<differfile2[i].line<<"  :"<<differfile2[i].lineno<<"\n";
		}
		if(filec2.size()>filec1.size())
		{
			for(i=filec1.size();i<filec2.size();i++)
			{
				cout<<"< "<<filec2[i]<<"  :"<<(i+1)<<"\n";			
			}
		}
	}
	if(same.size()>0)
	{
		cout<< "There are "<<same.size()<<" similar lines in both the files\n";
		cout<< "***********************************************************************\nThese lines are same\n";
		int i;		
		for(i=0;i<same.size();i++)
		{
			cout<<same[i].line<<"  :"<<same[i].lineno<<"\n";
		}
		cout<< "***********************************************************************\n" ;
	}
	printf("Time Taken: %lf\n",delta);		
	return 0;
}
