#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <sys/time.h>
double** multiply(double **A,double **B,int n);
double** copy(double **a,int n1,int n2,int m1,int m2 );
void initialize(double** A,int n);
double** add(double **a,double **b,int n);
double** combine(double **c11,double **c12,double **c21,double **c22,int m);
void destroy(double **A,int n);
void display(double** A,int n);
//clock_t start, end;
double cpu_time_used;
struct timeval start, end;
int main()
{

	int n;
	for(n=4;n<=4094;n*=2)
	{
//scanf("%d",&n);
		double **A = (double **)malloc(n * sizeof(double *));
		double **B = (double **)malloc(n * sizeof(double *));
		int i;
		for(i=0;i<n;i++)
		{	
			A[i]=(double *)malloc(n * sizeof(double));
			B[i]=(double *)malloc(n * sizeof(double));
		}
		initialize(A,n);
		initialize(B,n);
		gettimeofday(&start, NULL);
		double **C=multiply(A,B,n);
		gettimeofday(&end, NULL);
		double delta = ((end.tv_sec  - start.tv_sec) * 1000000u + 
         end.tv_usec - start.tv_usec) / 1.e6;
		printf("Time Taken for n=%d : %lf\n",n,delta);	
		//display(C,n);
		destroy(A,n);
		destroy(B,n);
		destroy(C,n);
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
void initialize(double **A,int n)
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
}
double** multiply(double **a,double **b,int n)
{
	if(n==1)
	{
		double **c= (double **)malloc(n * sizeof(double *));
		int i;
		for(i=0;i<n;i++)
		{	
			c[i]=(double *)malloc(n * sizeof(double));
		}
		c[n-1][n-1]=a[n-1][n-1]*b[n-1][n-1];
		return c;
	}
	else if(n<=64)
	{
		int m=n/2;
		double ** a11;
		double ** a12;
		double ** a21;
		double ** a22;
		double ** b11;
		double ** b12;
		double ** x1;
		double ** x2;
		double ** x3;
		double ** x4;
		double ** x5;
		double ** x6;
		double ** b21;
		double ** b22;
		double ** x7;
		double ** x8;
		double ** c1;
		double ** c2;
		double ** c3;
		double ** c4;
		a11=copy(a,0,m,0,m);
		a12=copy(a,0,m,m,n);
		a21=copy(a,m,n,0,m);
		a22=copy(a,m,n,m,n);
		b11=copy(b,0,m,0,m);
		b12=copy(b,0,m,m,n);
		b21=copy(b,m,n,0,m);
		b22=copy(b,m,n,m,n);
		x1=multiply(a11,b11,m);
		x2=multiply(a12,b21,m);
		x3=multiply(a11,b12,m);
		x4=multiply(a12,b22,m);
		x5=multiply(a21,b11,m);
		x6=multiply(a22,b21,m);
		x7=multiply(a21,b12,m);
		x8=multiply(a22,b22,m);
		c1 =add(x1,x2,m);
		c2 =add(x3,x4,m);
		c3 =add(x5,x6,m);
		c4 =add(x7,x8,m);
		double **c=combine(c1,c2,c3,c4,m);
		destroy(a11,m);
		destroy(a12,m);
		destroy(a21,m);
		destroy(a22,m);
		destroy(b11,m);
		destroy(b12,m);
		destroy(b21,m);
		destroy(b22,m);
		destroy(x1,m);
		destroy(x2,m);
		destroy(x3,m);
		destroy(x4,m);
		destroy(x5,m);
		destroy(x6,m);
		destroy(x7,m);
		destroy(x8,m);
		destroy(c1,m);
		destroy(c2,m);
		destroy(c3,m);
		destroy(c4,m);
		return c;
	}
	else
	{
		int m=n/2;
		double ** a11;
		double ** a12;
		double ** a21;
		double ** a22;
		double ** b11;
		double ** b12;
		double ** b21;
		double ** b22;
		double ** x1;
		double ** x2;
		double ** x3;
		double ** x4;
		double ** x5;
		double ** x6;
		double ** x7;
		double ** x8;
		double ** c1;
		double ** c2;
		double ** c3;
		double ** c4;
		a11=copy(a,0,m,0,m);
		a12=copy(a,0,m,m,n);
		a21=copy(a,m,n,0,m);
		a22=copy(a,m,n,m,n);
		b11=copy(b,0,m,0,m);
		b12=copy(b,0,m,m,n);
		b21=copy(b,m,n,0,m);
		b22=copy(b,m,n,m,n);
		#pragma omp parallel sections  
		{
			#pragma omp section  
			{	  
				x1=multiply(a11,b11,m);
			}
			#pragma omp section  
			{	  
				x2=multiply(a12,b21,m);
			}
			#pragma omp section  
			{	  
				x3=multiply(a11,b12,m);
			}
			#pragma omp section  
			{	  	
				x4=multiply(a12,b22,m);
			}
			#pragma omp section  
			{	  
				x5=multiply(a21,b11,m);
			}
			#pragma omp section  
			{	  
				x6=multiply(a22,b21,m);
			}
			#pragma omp section  
			{	  
				x7=multiply(a21,b12,m);
			}
			#pragma omp section  
			{	  
				x8=multiply(a22,b22,m);
			}
		}

		c1 =add(x1,x2,m);
		c2 =add(x3,x4,m);
		c3 =add(x5,x6,m);
		c4 =add(x7,x8,m);
		double **c=combine(c1,c2,c3,c4,m);
		destroy(a11,m);
		destroy(a12,m);
		destroy(a21,m);
		destroy(a22,m);
		destroy(b11,m);
		destroy(b12,m);
		destroy(b21,m);
		destroy(b22,m);
		destroy(x1,m);
		destroy(x2,m);
		destroy(x3,m);
		destroy(x4,m);
		destroy(x5,m);
		destroy(x6,m);
		destroy(x7,m);
		destroy(x8,m);
		destroy(c1,m);
		destroy(c2,m);
		destroy(c3,m);
		destroy(c4,m);
		return c;
	}
}
double** copy(double **a,int n1,int n2,int m1,int m2 )
{
	int i,j;
	double **c= (double **)malloc((n2-n1) * sizeof(double *));
	for(i=n1;i<n2;i++)
	{	
		c[i-n1]=(double *)malloc((m2-m1) * sizeof(double));
	}
	for(i=n1;i<n2;i++)
	{
		for(j=m1;j<m2;j++)
		{
			c[i-n1][j-m1]=a[i][j];
		}
	}
	return c;
}
double** add(double **a,double **b,int n)
{
	double **c= (double **)malloc(n * sizeof(double *));
	int i,j;
	for(i=0;i<n;i++)
	{	
		c[i]=(double *)malloc(n * sizeof(double));
	}
	for(i=0;i<n;i++)
	{
		for(j=0;j<n;j++)
		{
			c[i][j]=a[i][j]+b[i][j];
		}
	}
	return c;
}
double** combine(double **c11,double **c12,double **c21,double **c22,int m)
{
	double **c= (double **)malloc((2*m) * sizeof(double *));
	int i,j;
	for(i=0;i<2*m;i++)
	{	
		c[i]=(double *)malloc((2*m) * sizeof(double));
	}
	for(i=0;i<m;i++)
	{
		for(j=0;j<m;j++)
		{
			c[i][j]=c11[i][j];
		}
	}
	for(i=0;i<m;i++)
	{
		for(j=m;j<2*m;j++)
		{
			c[i][j]=c12[i][j-m];
		}
	}
	for(i=m;i<2*m;i++)
	{
		for(j=0;j<m;j++)
		{
			c[i][j]=c21[i-m][j];
		}
	}
	for(i=m;i<2*m;i++)
	{
		for(j=m;j<2*m;j++)
		{
			c[i][j]=c22[i-m][j-m];
		}
	}
	return c;
}
void destroy(double **A,int n)
{
	int i;
	for (i = 0; i < n; i++)
	{
		double* currentIntPtr1 = A[i];
		free(currentIntPtr1);
	}
	free(A);
}
