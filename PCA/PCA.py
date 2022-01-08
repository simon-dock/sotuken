import math
import random
import numpy as np
import matplotlib.pyplot as plt
import matplotlib.animation as animation
from matplotlib.animation import PillowWriter
from matplotlib._version import get_versions as mplv

def initialize(dimensional, n):
    
    vector = [[0 for i in range(dimensional)] for j in range(n)]
    
    for i in range(n):
        for j in range(dimensional):
            vector[i][j] = round(random.uniform(-5.0, 5.0), 3)
            
    return vector

def straightline(dimensional, n):
    
    vector = [[0 for i in range(dimensional)] for j in range(n)]
    direction = [0 for i in range(dimensional)]
    a = [1, -1]
    
    for i in range(dimensional):
        vector[0][i] = round(random.uniform(-2.0, 2.0), 3)
        direction[i] = random.choice(a)
    
    for i in range(1, n):
        for j in range(dimensional):
            vector[i][j] = round(vector[i-1][j] + direction[j], 3)
        
    return vector



def multi_mat_vec(covariance_matrix, vector_eigen):
    dimensional = len(vector_eigen)
    Ax = [0 for i in range(dimensional)]
    
    for i in range(dimensional):
        Ax[i] = 0.0
        for j in range(dimensional):
            Ax[i] += covariance_matrix[i][j] * vector_eigen[j]
    
    return Ax

def inner_prod(vector_eigen, Ax):
    prod = 0.0
    dimensional = len(vector_eigen)
    for i in range(dimensional):
        prod += vector_eigen[i] * Ax[i]

    return prod

def normalize_vec(vector_eigen, Ax):
    length = math.sqrt(inner_prod(Ax, Ax))
    dimensional = len(vector_eigen)
    for i in range(dimensional):
        vector_eigen[i] = Ax[i] / length
    
    return vector_eigen

def poweigen(covariance_matrix, vector_eigen):

    EPS = 1e-5
    l = 0.0
    old_l = 1.0

    while abs(l-old_l) > EPS*abs(l):
        old_l = l
        Ax = multi_mat_vec(covariance_matrix, vector_eigen)
        l = inner_prod(vector_eigen, Ax)
        vector_eigen = normalize_vec(vector_eigen, Ax)

    return l

n = 10
dimensional = 5
i_d = 2


origin_data = straightline(dimensional, n)
vector_eigen = [0 for i in range(dimensional)]
vector_eigen[0] = 1

np_data = np.array(origin_data)
covariance_matrix = np.cov(np_data, rowvar=0, bias=1)
poweigen(covariance_matrix, vector_eigen)
print(origin_data)
print(vector_eigen)


