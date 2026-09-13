# Task\_06 answers

## 2\) Reconstruct matrix A by inverse\_c2c Fourier transform, what is the mean and median absolute and relative error?


$Mean absolute error: 4.8422×10^{-16}$



$Median absolute error: 3.3307×10^{-16}$



$Mean relative error: 1.3864391×10^{-14}$



$Median relative error: 3.2468^{-16}$


## 4\) Reconstruct matrix A by inverse\_c2r Fourier transform, what is the mean and median absolute and relative error?


$Mean absolute error: 6.0115×10^{-16}$



$Median absolute error: 4.4409×10^{-16}$



$Mean relative error: 1.5331304×10^{-13}$



$Median relative error: 3.8976×10^{-16}$


## Are you reaching machine precision in point 2 and 4? If not, try to comment on why

Yes the mean and median absolute error are on the order of $10^-{16}$ consistent with double precision



## 6\) What is the value of C\[0,0] or R\[0,0]? Can you guess its meaning?


$C\[0, 0] == 999246.03086579171940684 + 0.00000000000000000i$


$R\[0, 0] == 973550.10376395168714225 + 953312.85272390744648874i$

The values of C\[0,0] and R\[0,0] represent value DC component therefore the sum of all the entries of the matrix that is approximately $1000\*100 = 10^6$

