
import numpy as np
import matplotlib.pyplot as plt
import matplotlib.animation as animation
from matplotlib.animation import PillowWriter
from matplotlib._version import get_versions as mplv

fig = plt.figure()
N=10
ims = []
plt.xlim(-1,1)
plt.ylim(-1,1)
count = 0
while(True):
    rx =np.random.uniform(-1,1,N)
    ry=np.random.uniform(-1,1,N)

    im=plt.scatter(rx, ry,c="red")
    im=plt.scatter(np.mean(rx), np.mean(ry),c="blue")
    ims.append([im])
    count += 1
    if count == 10:
        break

# アニメーション作成
ani = animation.ArtistAnimation(fig, ims, interval=100, repeat_delay=1000)

# 表示
plt.show()

ani.save('test1.gif',writer='imagemagick')
