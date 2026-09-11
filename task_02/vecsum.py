import numpy as np

def vector_addition(N):

    N = int(N)

    a = 3.0
    x_val = 0.1
    y_val = 7.1
    expected_val = 7.4

    # Create vectors
    x = np.full((N, 1), x_val, dtype = float)
    y = np.full((N, 1), y_val, dtype = float)

    d = a * x + y

    # Check that all elements are equal to 7.4 above a certain tolerance
    expected = np.full((N, 1), expected_val, dtype = float)

    tolerance = 1.0e-15
    bool_vector = np.abs(d - expected) <= tolerance
  
    if False in bool_vector:
        print(f"Incorrectly added vectors of dimension ({N}, 1)")      
    else:
        print(f"Correctly added vectors of dimension ({N}, 1)")
        

N = 10**6

vector_addition(N)


