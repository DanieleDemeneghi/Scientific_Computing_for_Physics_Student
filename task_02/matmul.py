import numpy as np

def matrix_multiplication(N):

    x_val = 3
    y_val = 7.1
    expected_val = 21.3*N

    # Create matrices
    A = np.full((N, N), x_val, dtype=float)
    B = np.full((N, N), y_val, dtype=float)

    # Expected value of every element
    expected = np.full((N, N), expected_val, dtype=float)
   
    C = A @ B

    # Check that all elements are equal to 21,3*N above a certain tolerance
    tolerance = 1.0e-13
    bool_matrix = np.abs(C - expected) <= tolerance

    if False in bool_matrix:
        print(f"Incorrectly multiplied matrices of dimension ({N}, {N})")
    else:       
        print(f"Correctly multiplied matrices of dimension ({N}, {N})")

N = 10

matrix_multiplication(N)

