from math import gcd
import matplotlib.pyplot as plt
from time import time
from tqdm import tqdm as prog


def gcd_(a, b):
    while a != 0 and b != 0:
        if a > b:
            a %= b
        else:
            b %= a
    return a + b


ax = plt.axes()
ax.set_xlabel('Length of input data')
ax.set_ylabel('Time, mc')

y0 = []
y1 = []
x = []

for i in prog(range(10 ** 8, 10 ** 10, 100)):
    x.append(i)

    time_start = time()
    gcd(1024, i)
    time_end = time() - time_start
    y0.append(time_end * 1000)

    time_start = time()
    gcd_(1024, i)
    time_end = time() - time_start
    y1.append(time_end * 1000)


ax.plot(x, y0, color='blue')
ax.plot(x, y1, color='green')

plt.show()
