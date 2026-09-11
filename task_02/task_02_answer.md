# Task_02 answers

## Did you find any problems in running the codes for some N. If so, do you have an idea why?
The only calculation that was not left to run until the end, was the matrix multiplication of 10000x10000 matrices written in C.
Because of how the matrix multiplication algorithm was set up this requires $10000^3 = 10^12$ operations. On the contrary, python
uses an optimized multiplication algorithm from the numpy library.

## Where you able to test correctly the sum and product of points 1-3? If so, how? If not, what was the problem?
Yes, but because the resulting numbers could not be exactly represented a tolerance value had to be set. 
This was fixes at $tol=10^-15$ for the vecsum.py and vecsum.c script. Instead, for the matmul.py due to accumulation of errors, 
good tolerance values where found to be $tol=10^-13, 10^-11 for N=10^-8 for10, 100, 10^4$ respectively.