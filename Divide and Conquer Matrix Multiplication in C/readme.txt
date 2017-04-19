To read my blog please go here: https://chintamanibharath.wordpress.com/2017/04/18/matrix-multiplication-optimizations-and-speed-up/?preview_id=192&preview_nonce=2d9aa79cba
Contents: All codes are written in C
divideandconquer.c - Classic divide and conquer Algorithm written using C
parallelnoteff.c - a Parallelized Matrix Multiplication written in C using OpenMP - but is not as efficent as others
parrallelwithcacheopt.c -  a Parallelized Matrix Multiplication written in C using OpenMP, is cache friendly and serialized after certain depth.
parallelwithoutcacheopt.c -  a Parallelized Matrix Multiplication written in C using OpenMP, not so cache friendly and serialized after certain height
parallelwithloopopt.c -  a Parallelized Matrix Multiplication written in C using OpenMP, using nested loop optimizations but contains a bug

This Folder Mainly Consists of 3 main methods
Initialize - To initialize the two matrices that needs to be multiplied
Multiply - A mutltiply method that uses Divide and Conquer Matrix Multiplication algorithm
Transpose - A method to find transpose of a matrix
Add - A method to add two matrices
Combine - a method to combine 4 matrices into a single matrix
Copy - A method to copy part of a matrix into anothe matrix
Destroy - A method to free all matrices

To change the input size, you need to change the value of variable n in each the program. 
The default value of matrices are set to A[i][j] = i+j
You can also set it to random by uncommenting the code

To run each of the code you need a gcc compiler.
All of these programs are tested in Ubuntu 16.04 and Windows 10

to run any program use 
gcc filename.c

The fastest programs in this folder is parallelwithcacheopt.c

Note: parallelwithloopopt.c has a bug which I will be fixing in the near future!
