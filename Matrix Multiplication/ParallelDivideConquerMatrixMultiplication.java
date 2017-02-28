import java.util.*;
import java.text.DecimalFormat;
import java.util.concurrent.*;
class ParallelDivideConquerMatrixMultiplication
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
		ParallelMatrixMultiplication t1=new ParallelMatrixMultiplication(a,b,n);
		double start=System.nanoTime();
		t1.multiply();
		double end=System.nanoTime();
		double c[][]=t1.getResult();
		DecimalFormat formatter = new DecimalFormat("#.######");
		double time=(end-start)/1000000000;
		System.out.println(formatter.format(time)+" sec");
	}
}
class ParallelMatrixMultiplication 
{
    private double[][] a;
    private double[][] b;
    private double[][] c;
    private static final int POOL_SIZE = Runtime.getRuntime().availableProcessors();
    private final ExecutorService exec = Executors.newFixedThreadPool(POOL_SIZE);
    ParallelMatrixMultiplication(double[][] a, double[][] b,int n) 
    {
        this.a = a;
        this.b = b;
        this.c = new double[n][n];
    }
    public void multiply() 
    {
	Future f = exec.submit(new Multiplier(a, b, c, 0, 0, 0, 0, 0, 0, a.length));
        try 
	{
            f.get();
            exec.shutdown();
        }
	catch (Exception e) 
	{
		System.out.println(e);
	}
    }
    public double[][] getResult() 
    {
        return c;
    }
    class Multiplier implements Runnable
    {
        private double[][] a;
        private double[][] b;
        private double[][] c;
        private int a_i, a_j, b_i, b_j, c_i, c_j, size;

        Multiplier(double[][] a, double[][] b, double[][] c, int a_i, int a_j, int b_i, int b_j, int c_i, int c_j, int size)
	{
            this.a = a;
            this.b = b;
            this.c = c;
            this.a_i = a_i;
            this.a_j = a_j;
            this.b_i = b_i;
            this.b_j = b_j;
            this.c_i = c_i;
            this.c_j = c_j;
            this.size = size;
        }
	public void multiply(double[][] a, double[][] b, double[][] c, int a_i, int a_j, int b_i, int b_j, int c_i, int c_j, int size)
	{
		if(size==1)
		{
			c[c_i][c_j]+=a[a_i][a_j]*b[b_i][b_j];
		}
		else	
		{
			int m=size/2;
			double a11[][]=copy(a,a_i,a_i+m,a_j,a_j+m);
			double a12[][]=copy(a,a_i,a_i+m,a_j+m,a_j+size);
			double a21[][]=copy(a,a_i+m,a_i+size,a_j,a_j+m);
			double a22[][]=copy(a,a_i+m,a_i+size,a_j+m,a_j+size);
			double b11[][]=copy(b,b_i,b_i+m,b_j,b_j+m);
			double b12[][]=copy(b,b_i,b_i+m,b_j+m,b_j+size);
			double b21[][]=copy(b,b_i+m,b_i+size,b_j+0,b_j+m);
			double b22[][]=copy(b,b_i+m,b_i+size,b_j+m,b_j+size);
			double x1[][]=new double[m][m];
			double x2[][]=new double[m][m];
			double x3[][]=new double[m][m];
			double x4[][]=new double[m][m];
			double x5[][]=new double[m][m];
			double x6[][]=new double[m][m];
			double x7[][]=new double[m][m];
			double x8[][]=new double[m][m];
			multiply(a11,b11,x1,0,0,0,0,0,0,m);
			multiply(a12,b21,x2,0,0,0,0,0,0,m);
			multiply(a11,b12,x3,0,0,0,0,0,0,m);
			multiply(a12,b22,x4,0,0,0,0,0,0,m);
			multiply(a21,b11,x5,0,0,0,0,0,0,m);
			multiply(a22,b21,x6,0,0,0,0,0,0,m);
			multiply(a21,b12,x7,0,0,0,0,0,0,m);
			multiply(a22,b22,x8,0,0,0,0,0,0,m);
			combine(c,add(x1,x2,m),add(x3,x4,m),add(x5,x6,m),add(x7,x8,m),c_i,c_j,size);
		}
	}
	public void combine(double c[][],double c11[][],double c12[][],double c21[][],double c22[][],int c_i,int c_j,int n)
	{
		int m=n/2;
		for(int i=0;i<m;i++)
		{
			for(int j=0;j<m;j++)
			{
				c[c_i+i][c_j+j]+=c11[i][j];
			}
		}
		for(int i=0;i<m;i++)
		{
			for(int j=m;j<2*m;j++)
			{
				c[c_i+i][c_j+j]+=c12[i][j-m];
			}
		}
		for(int i=m;i<2*m;i++)
		{
			for(int j=0;j<m;j++)
			{
				c[c_i+i][c_j+j]+=c21[i-m][j];
			}
		}
		for(int i=m;i<2*m;i++)
		{
			for(int j=m;j<2*m;j++)
			{
				c[c_i+i][c_j+j]+=c22[i-m][j-m];
			}
		}
	}	
	public double[][] add(double a[][],double b[][],int n)
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
	public double[][] copy(double [][]a,int n1,int n2,int m1,int m2 )
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
        public void run() 
	{
            int h = size/2;
            if (size <= 64) 
	    {
                multiply(a,b,c,a_i,a_j,b_i,b_j,c_i,c_j,size);
            } 
	    else 
	    {
                Multiplier[] tasks = {
                    new Multiplier(a, b, c, a_i, a_j, b_i, b_j, c_i, c_j, h),
                    new Multiplier(a, b, c, a_i, a_j+h, b_i+h, b_j, c_i, c_j, h),
                    new Multiplier(a, b, c, a_i, a_j, b_i, b_j+h, c_i, c_j+h, h),
                    new Multiplier(a, b, c, a_i, a_j+h, b_i+h, b_j+h, c_i, c_j+h, h),
                    new Multiplier(a, b, c, a_i+h, a_j, b_i, b_j, c_i+h, c_j, h),
                    new Multiplier(a, b, c, a_i+h, a_j+h, b_i+h, b_j, c_i+h, c_j, h),
                    new Multiplier(a, b, c, a_i+h, a_j, b_i, b_j+h, c_i+h, c_j+h, h),
                    new Multiplier(a, b, c, a_i+h, a_j+h, b_i+h, b_j+h, c_i+h, c_j+h, h)
                };
                FutureTask[] fs = new FutureTask[tasks.length/2];
                for (int i = 0; i < tasks.length; i+=2) 
		{
                    fs[i/2] = new FutureTask(new Sequentializer(tasks[i], tasks[i+1]), null);
                    exec.execute(fs[i/2]);
                }
                for (int i = 0; i < fs.length; ++i) 
		{
                    fs[i].run();
                }
                try 
		{
                    for (int i = 0; i < fs.length; ++i) 
		    {
                        fs[i].get();
                    }
                } 
		catch (Exception e) 
		{
			System.out.println(e);
                }
            }
        }
    }
    class Sequentializer implements Runnable
    {
        private Multiplier first, second;
        Sequentializer(Multiplier first, Multiplier second) 
	{
            this.first = first;
            this.second = second;
        }
        public void run() 
	{
            first.run();
            second.run();
        }
    }
}
