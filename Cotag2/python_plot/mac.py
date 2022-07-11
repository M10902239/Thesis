import numpy as np;
import matplotlib.pyplot as plt; 
Data = np.genfromtxt('mac_re.txt',dtype='float');
plt.plot(Data[0:,0], Data[0:,1],"-", label="one link");
plt.title('NC-mac_retransmission');
plt.xlabel('mac_retransmission(times)');
plt.ylabel('throughput(Mbps)');
plt.legend()
plt.savefig("NC-mac_retransmission.jpg")

