import numpy as np
import pandas as pd


file = f"Function_{10**7}.dat"

df = pd.read_csv(file, sep=r"\s+")

dx = (np.pi/2)/10**7

f = df["f(x)"].astype(float).values

exact_integral = (np.exp(np.pi/2) - 1) / 2
result_integral = np.trapezoid(f, dx = dx)
epsrel = (result_integral/exact_integral) - 1

print(f"Result integral is: {result_integral}")
print(f"Exact integral is: {exact_integral}")
print(f"Relative error is {epsrel}")



