# Task_06 answers

## 2) Reconstruct matrix A by inverse_c2c Fourier transform, what is the mean and median absolute and relative error?  
$$
Mean absolute error: 0.00000000000000048422
Median absolute error: 0.00000000000000033307
Mean relative error: 0.00000000000013864391
Median relative error: 0.00000000000000032468
$$

## 4) Reconstruct matrix A by inverse_c2r Fourier transform, what is the mean and median absolute and relative error?
$$
Mean absolute error: 0.00000000000000060115
Median absolute error: 0.00000000000000044409
Mean relative error: 0.00000000000015331304
Median relative error: 0.00000000000000038976
$$
## Are you reaching machine precision in point 2 and 4? If not, try to comment on why
Yes the mean and median absolute error are on the order of $10^-16$ consistent with double precision


## 6) What is the value of C[0,0] or R[0,0]? Can you guess its meaning?
$$
C[0, 0] == 999246.03086579171940684 + 0.00000000000000000i
R[0, 0] == 973550.10376395168714225 + 953312.85272390744648874i
$$
The values of C[0,0] and R[0,0] represent value DC component therefore the sum of all the entries of the matrix that is approximately $1000*100 = 10^6$

