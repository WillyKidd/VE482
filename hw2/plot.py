import numpy as np
import math
import matplotlib.pyplot as plt

n = np.linspace(0, 10, 1000)
x = 1 - 0.25**n
y = 1 - 0.6**n
z = 1-0.9**n

plt.plot(n, x*100, 'r', label="25% I/O wait")
plt.plot(n, y*100, 'g', label="60% I/O wait")
plt.plot(n, z*100, 'b', label="90% I/O wait")
plt.xlabel('number of processes n')
plt.ylabel('CPU utilization (in percent)')
plt.legend()
plt.show()