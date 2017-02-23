import java.util.*;
import java.text.DecimalFormat;
class StrassensMatrixMultiplication
{
	public static void main(String[] args)
	{
		Scanner sc=new Scanner(System.in);
		int n=sc.nextInt(); //no of rows and columns
		double a[][]=new double[n][n];
		double b[][]=new double[n][n];
		for(int j=0;j<n;j++)
		{
			for(int k=0;k<n;k++)
			{
				a[j][k]=sc.nextDouble();
			}
		}
		for(int j=0;j<n;j++)
		{
			for(int k=0;k<n;k++)
			{
				b[j][k]=sc.nextDouble();
			}
		}
		double start=System.nanoTime();
		double c[][]=strassen(a,b,n); //strassen algorithm for multiplication of the two matrices
		double end=System.nanoTime();
		DecimalFormat formatter = new DecimalFormat("#.######");
		double time=(end-start)/1000000000;
		System.out.println(formatter.format(time)+" sec");
	}
	public static double[][] strassen(double [][]a,double [][]b,int n)
	{
		if(n==1)
		{
			double c[][]=new double[n][n];
			c[n-1][n-1]=a[n-1][n-1]*b[n-1][n-1];
			return c;
		}
		else
		{
			int m=n/2;
			double a11[][]=copy(a,0,m,0,m);
			double a12[][]=copy(a,0,m,m,n);
			double a21[][]=copy(a,m,n,0,m);
			double a22[][]=copy(a,m,n,m,n);
			double b11[][]=copy(b,0,m,0,m);
			double b12[][]=copy(b,0,m,m,n);
			double b21[][]=copy(b,m,n,0,m);
			double b22[][]=copy(b,m,n,m,n);
			double p1[][]=strassen(a11,sub(b12,b22,m),m);
			double p2[][]=strassen(add(a11,a12,m),b22,m);
			double p3[][]=strassen(add(a21,a22,m),b11,m);
			double p4[][]=strassen(a22,sub(b21,b11,m),m);
			double p5[][]=strassen(add(a11,a22,m),add(b11,b22,m),m);
			double p6[][]=strassen(sub(a12,a22,m),add(b21,b22,m),m);
			double p7[][]=strassen(sub(a21,a11,m),add(b11,b12,m),m);
			double c[][]=combine(sub(add(add(p5,p4,m),p6,m),p2,m),add(p1,p2,m),add(p3,p4,m),sub(add(p1,p5,m),sub(p3,p7,m),m),m);
			return c;
		}
	}
	public static double[][] add(double a[][],double b[][],int n)
	{
		double c[][]=new double[n][n];
		for(int i=0;i<n;i++)
		{
			for(int j=0;j<n;j++)
			{
				c[i][j]=a[i][j]+b[i][j];
			}
		}
		return c;
	}
	public static double[][] sub(double a[][],double b[][],int n)
	{
		double c[][]=new double[n][n];
		for(int i=0;i<n;i++)
		{
			for(int j=0;j<n;j++)
			{
				c[i][j]=a[i][j]-b[i][j];
			}
		}
		return c;
	}
	public static double[][] copy(double [][]a,int n1,int n2,int m1,int m2 )
	{
		double c[][]=new double[n2-n1][m2-m1];
		for(int i=n1;i<n2;i++)
		{
			for(int j=m1;j<m2;j++)
			{
				c[i-n1][j-m1]=a[i][j];
			}
		}
		return c;
	}
	public static double[][] combine(double c11[][],double c12[][],double c21[][],double c22[][],int m)
	{
		double c[][]=new double[2*m][2*m];
		for(int i=0;i<m;i++)
		{
			for(int j=0;j<m;j++)
			{
				c[i][j]=c11[i][j];
			}
		}
		for(int i=0;i<m;i++)
		{
			for(int j=m;j<2*m;j++)
			{
				c[i][j]=c12[i][j-m];
			}
		}
		for(int i=m;i<2*m;i++)
		{
			for(int j=0;j<m;j++)
			{
				c[i][j]=c21[i-m][j];
			}
		}
		for(int i=m;i<2*m;i++)
		{
			for(int j=m;j<2*m;j++)
			{
				c[i][j]=c22[i-m][j-m];
			}
		}
		return c;
	}
}