# Task_05 answers

## a)Are the three results the same? If not, can you guess why?

The exact result is $0.5$, but the three summation algorithms yield $-0.5$. In The naive for loop implementation the loss is due to the 15-16 digit precision of double numbers that lead to the loss of the value $1$ in the $10^16 +1$ operation. Probably even the ```gsl_vector_sum()``` is not based on an algorithm that compensate this loss. Finally, the Kahan summation still yields the incorrect answer because the compensation $c=-1$ after the second cycle is lost in the summation -$-10^16 -1$ in the thir cycle.

## b)How can you test that d, the sum of x and y, is correct?
One possible test is to calculate the mean and standard deviation of the resulting *d* vector. Given a certain tolerance the two values should be:

$$
Mean =  0
Standar deviation = \sqrt{a^2 + 1}
$$

