# Matrix-Multiplication
Matrix multiplication of NxN Matrices where n is power of 2 using Naive Algorithm, Recursive Divide and Conquer Algorithm and Strassen Divid and Conquer algorithm.
------------------------------------------------------------------------------------------------------------------------------------------
Open Terminal

Compilation:

	gcc matmul.c –o matmul.exe
	
Execution:

	./matmul.exe –a 1/2/3 –i/f –s<size> 
------------------------------------------------------------------------------------------------------------------------------------------
-a: represents the algorithm to be chosen the options are 1 2 3 where
-a1: Dot Product Matrix Multiplication
-a2: Recursive Matrix Multiplication
-a3: Strassen Matrix Multiplication
  
-i: integer data
-f: floating point data

-s: represents the size of the matrix 

ex: ./matmul.exe –a 1 –f –s 16
If you want to run another algorithm for the same program choose the options accordingly. 

These outputs can then be compared using the diff command in the terminal with the output file names naïve, recur, stras for the algo 1, 2, and 3 respectively for integer datatype and naivefloat, recurfloat, strasfloat for the algo 1, 2, and 3 respectively for floating point datatype.
