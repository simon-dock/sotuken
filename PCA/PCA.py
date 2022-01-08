import math
import random
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

def circule():
    vector = [[0 for i in range(2)] for j in range(9)]

    PI = 3.14159265358979323846

    vector[8][0]= round(random.uniform(-2.0, 2.0), 3)
    vector[8][1]= round(random.uniform(-2.0, 2.0), 3)

    vector[0][0] = vector[8][0]+2.5
    vector[0][1] = vector[8][1]

    vector[1][0] = vector[8][0] + math.cos(PI/4)*2.5
    vector[1][1] = vector[8][1] + math.sin(PI/4)*2.5

    vector[2][0] = vector[8][0]
    vector[2][1] = vector[8][1]+2.5

    vector[3][0] = vector[8][0] - math.cos(PI/4)*2.5
    vector[3][1] = vector[8][1] + math.sin(PI/4)*2.5

    vector[4][0] = vector[8][0]-2.5
    vector[4][1] = vector[8][1]

    vector[5][0] = vector[8][0] - math.cos(PI/4)*2.5
    vector[5][1] = vector[8][1] - math.sin(PI/4)*2.5

    vector[6][0] = vector[8][0]
    vector[6][1] = vector[8][1]-2.5

    vector[7][0] = vector[8][0] + math.cos(PI/4)*2.5
    vector[7][1] = vector[8][1] - math.sin(PI/4)*2.5

    return vector


def heiix(n):
    vector = [[0 for i in range(3)] for j in range(n)]

    for i in range(n):
        vector[i][2] = (math.sqrt(2)/2)*i
        vector[i][0] = math.cos(vector[i][2])
        vector[i][1] = math.sin(vector[i][2])

    return vector

n = 9
dimensional = 9
i_d = 2
#x0 = straightline(dimensional, n)
x0 = circule() #n=9
#x0 = heiix(n)
y0 = initialize(i_d, n)
#y0 = [0.0, 0.0], [0.0, 0.0], [0.0, 0.0], [0.0, 0.0], [0.0, 0.0], [0.0, 0.0], [0.0, 0.0], [0.0, 0.0], [0.0, 0.0]
fig = plt.figure()
p = extreme(x0, y0)

print(p[0])

ans_x = initialize(1, n)
ans_y = initialize(1, n)

for i in range(len(p[1])):
    for j in range(len(p[1][0])):
        p[1][i][j] = round(p[1][i][j],4)
        if j == 0:
            ans_x[i] = p[1][i][j]
        else:
            ans_y[i] = p[1][i][j]
                
    
    print(p[1][i])

ani = animation.ArtistAnimation(fig, p[2], interval=1, repeat_delay=1000)
plt.show()
ani.save('stl_1e-6_001.gif',writer='imagemagick')