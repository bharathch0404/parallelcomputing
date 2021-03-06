#include <stdio.h>
#include <stdlib.h>
#include <time.h>
void multiply(double **A,double **B,double **C,int n);
double ** initialize(double** A,int n);
void display(double** A,int n);
double ** transpose(double **a,int n);
clock_t start, end;
double cpu_time_used;
int main()
{

	int n;
	for(n=4;n<=4096;n*=2)
	{
//scanf("%d",&n);
		double **A = (double **)malloc(n * sizeof(double *));
		double **B = (double **)malloc(n * sizeof(double *));
		double **C= (double **)malloc(n * sizeof(double *));
		int i;
		for(i=0;i<n;i++)
		{	
			A[i]=(double *)malloc(n * sizeof(double));
			B[i]=(double *)malloc(n * sizeof(double));
			C[i]=(double *)malloc(n * sizeof(double));
		}
		initialize(A,n);
		initialize(B,n);
		start = clock();
		multiply(A,B,C,n);
		end = clock();
		cpu_time_used = ((double) (end - start)) / CLOCKS_PER_SEC;
		printf("Time Taken for n=%d : %lf\n",n,cpu_time_used);
		//display(C,n);	
		for (i = 0; i < n; i++)
		{
			double* currentIntPtr1 = A[i];
			free(currentIntPtr1);
			double* currentIntPtr2 = B[i];
			free(currentIntPtr2);
			double* currentIntPtr3 = C[i];
			free(currentIntPtr3);
		}
		free(A);
		free(B);
		free(C);
	}
	return 0;
}
void display(double **A,int n)
{
	int i,j;
	for(i=0;i<n;i++)
	{
		for(j=0;j<n;j++)
		{
			printf("%lf ",A[i][j]);
		}
		printf("\n");
	}
}
double ** initialize(double **A,int n)
{
	int i,j;
	double range = (1000 - 0);
	for(i=0;i<n;i++)
	{
		for(j=0;j<n;j++)
		{ 
			//double div = RAND_MAX / range;
			//return min + (rand() / div);
			//A[i][j]=(rand() / div);
			A[i][j]=i+j;
		}
	}
	return A;
}
void multiply(double **a,double **b,double **c,int n)
{
	int i,j,k,chunk=8;
	double **d = transpose(b,n);
	#pragma omp for schedule (static, chunk)
	for(i=0;i<n;i++)
	{
		for(j=0;j<n;j++)
		{
			for(k=0;k<n;k++)
			{
				c[i][j]+=a[i][k]*b[j][k];
			}
		}
	}
	for (i = 0; i < n; i++)
	{
		double* currentIntPtr4 = d[i];
		free(currentIntPtr4);
	}
	free(d);
}
double** transpose(double **a,int n)
{
	int i,j;
	double **b= (double **)malloc(n * sizeof(double *));
	for(i=0;i<n;i++)
	{	
		b[i]=(double *)malloc(n * sizeof(double));
	}
	for(i=0;i<n;i++)
	{
		for(j=0;j<n;j++)
		{
			b[i][j]=a[j][i];
		}
	}
	//display(b,n);
	return b;
}
