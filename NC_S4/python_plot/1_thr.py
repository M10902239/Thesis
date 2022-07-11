import numpy as np;
import matplotlib.pyplot as plt; 
Data = np.genfromtxt('1_thr_pureTCP.txt',dtype='float');
plt.plot(Data[0:,0], Data[0:,1],"-", label="one link");
plt.title('User 1(1G/0.001ms/1e6)');
plt.xlabel('time');
plt.ylabel('throughput');
plt.legend()
plt.savefig("User1_pureTCP.jpg")

