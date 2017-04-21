#File Differentiator and Similarity Finder
This progamam has been written in C++ to find line by line differences and similarities between two files.
Contents-
finderusingdeque.cpp - A C++ implementation implemented using Deque - fastest in this folder
finderusinglist.cpp - A C++ implementation implemented using List - Second fastest in this folder
finderusingvector.cpp - A C++ implementation implemented using Vector - Slowest among the sequential algorithms
parallelusingdivideandconquerfinderusingvector.cpp - A C++ divide and conquer implementation implemented using Vector - changes will be made to this file to near future
parallelattempttwo.cpp - Tried to parallelize even more!

Difference between parallelusingdivideandconquerfinderusingvector.cpp and other serial code:
I tried to parallelize this algorithm by dividing the file into parts, comparing each parts parallely as they are independent and then combining them to form a single datastructure. 



Difference between parallelattempttwo.cpp and other serial code:
I tried to parallelize this algorithm by dividing the file into parts, comparing each parts parallely as they are independent and then combining them to form a single datastructure. But as datastructures for two files are different and can be inserted parallely without causing any race condition and attempt was made to do so! 


To run:
Compile the program using:
g++ filename.cpp -o filename
To run:
<executable> <file1> <file2>

To read more about this tool: 
Visit https://chintamanibharath.wordpress.com/2017/04/19/creating-your-own-file-differentiator-and-similarity-finder/
