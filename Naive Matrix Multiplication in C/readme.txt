To read my blog please go here: https://chintamanibharath.wordpress.com/2017/04/18/matrix-multiplication-optimizations-and-speed-up/?preview_id=192&preview_nonce=2d9aa79cba
Contents: All codes are written in C
naive.c - A naive matrix multiplication algorithm
naivecacheoptimized.c - A cache Friendly Naive Matrix Multiplication Algorithm
naivenestedloop.c - Matrix Multiplication Algorithms made efficient using Nested Loop Optimizations
naiveparallelnestedloop.c - Nested Loop Optimized Matrix Multiplication Algorithm in parallel
naivecacheparallel.c - Cache Friendly Naive Matrix Multiplication made parallel
parallelnotefficient.c - A algorithm more faster than Naive Matrix Multiplication but less efficient than others.

This Folder Mainly Consists of 3 main methods
Initialize - To initialize the two matrices that needs to be multiplied
Multiply - A mutltiply method that uses Naive Matrix Multiplication algorithm
Transpose - A method to find transpose of a matrix

To change the input size, you need to change the value of variable n in each the program. 
The default value of matrices are set to A[i][j] = i+j
You can also set it to random by uncommenting the code

To run each of the code you need a gcc compiler.
All of these programs are tested in Ubuntu 16.04 and Windows 10

to run any program use 
gcc filename.c

The fastest programs in these folders are naivenestedloop.c and naiveparallelnestloop.c
