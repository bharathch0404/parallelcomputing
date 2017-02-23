import java.util.*;
import java.text.DecimalFormat;
class BruteForceMatrixMultiplication
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
		double c[][]=brutemul(a,b,n); //brute force multiplication of the two matrices
		double end=System.nanoTime();
		DecimalFormat formatter = new DecimalFormat("#.######");
		double time=(end-start)/1000000000;
		System.out.println(formatter.format(time)+" sec");
	}
	public static double[][] brutemul(double [][]a,double [][]b,int n)
	{
		double c[][]=new double[n][n];
		for(int i=0;i<n;i++)
		{
			for(int j=0;j<n;j++)
			{
				for(int k=0;k<n;k++)
				{
					c[i][j]+=a[i][k]*b[k][j];
				}
			}
		}
		return c;
	}
}