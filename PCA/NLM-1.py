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

def function(x,y):# N次元　ｄ次元のデータのＥを求める
    
    n = len(x)
    p = [0 for i in range(2)]
    q = [0 for i in range(2)]
    sum_a = 0.0
    sum_b = 0.0
    
    for i in range(n):
        for j in range(i+1, n):
            p[0] = x[i]
            p[1] = x[j]
            dist_d = distance(p)
            q[0] = y[i]
            q[1] = y[j]
            dist_l = distance(q)
            
            sum_a += dist_d
            
            sum_b += ((dist_d - dist_l) ** 2) / dist_d
    
    return sum_b / sum_a


def distance(p):# p = [x....N],[x....N]の２個の点、N次元のデータの距離を求める
    
    dimensional = len(p[0])
    ans = [0]*dimensional
    sum = 0.0
    
    for i in range(dimensional):
        for j in range(2):
            if j == 0:
                ans[i] = p[j][i]
            else:
                ans[i] -= p[j][i]
        sum += ans[i]**2
        
    return math.sqrt(sum)


def autodifferen(func, x, y):#自動偏微分
    
    h = 0.00001
    
    n = len(y)
    dimensional = len(y[0])
    tmp = [[0 for i in range(dimensional)] for j in range(n)]
    ans = [0] * (n*dimensional)
    count = 0
    
    for i in range(n):
        for j in range(dimensional):
            tmp[i][j] = y[i][j]
    
    for i in range(n):
        for j in range(dimensional):
             tmp[i][j] = y[i][j] + h
             ans[count] = differential(func, x, y, tmp, h)
             tmp[i][j] = y[i][j]
             count += 1
    
    return ans


def differential(func, x, y, tmp, h):#微分
    
    fx = (func(x, tmp) - func(x, y)) / h
     
    return fx


def extreme(x, y):#最急降下法
    
    a = 0.5
    esp = 1.e-4#helix 4 #circle 8 stl 5
    ess = 1.e-10#helix 7 #circle 10
    err = 0.0
    tmp = 0.0
    
    nn = 0
    m = 100000

    
    #plt.xlim(-10,10)
    #plt.ylim(-10,10)
    
    n = len(y)
    dimensional = len(y[0])
    
    ims = []
    ytmps = []
    xtmps = []
    while True:
        nn += 1
        dy = autodifferen(function, x, y)
        count = 0
        for i in range(n):
            for j in range(dimensional):
                y[i][j] -= a * dy[count]

                if count % 2 == 0:
                    xtmp = y[i][j]
                    xtmps.append(xtmp)
                else:
                    ytmp = y[i][j]
                    ytmps.append(ytmp)
                count += 1
        
        if nn % 30 == 0:#helix 30 circle 10 stl 100
            im = plt.scatter(xtmps, ytmps, c="blue")
            ims.append([im])
        ytmps = []
        xtmps = []

        tmp = err
        err = abs(function(x,y))
        print(nn,err)
        if nn>m:
            break
        if err < esp:
            break
        if nn != 0 and abs(tmp - err) < ess:
            break
    
    
    
    return x, y, ims


n = 15
dimensional = 3
i_d = 2
#x0 = straightline(dimensional, n)
#x0 = circule() #n=9
x0 = heiix(n)
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
            pass
            #ans_x[i] = p[1][i][j]
        else:
            pass
            #ans_y[i] = p[1][i][j]
                
    
    print(p[1][i])

ani = animation.ArtistAnimation(fig, p[2], interval=1, repeat_delay=1000)
plt.show()
ani.save('helix_1e-6_001.gif',writer='imagemagick')




