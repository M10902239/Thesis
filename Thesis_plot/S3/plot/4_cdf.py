from cProfile import label
import csv
import sys
import numpy as np
import matplotlib.pyplot as plt 
from scipy import stats

list_all = []
list_all2 = []
list1 = []
timelist = [7,11,15,19,23]
people = 8

def getDelayList(file):
    with open(file) as f:
        list_of_rows1 = list(csv.reader(f, delimiter=','))
        delayList = []
        for line in list_of_rows1:
            for time in range (0,25,1):
                delayList.append((float(line[time]))/1000)
        # print(delayList)
        # print(len(list_of_rows1))
    return delayList

def cdf(list):
    cdf = []
    x = []
    res_freq = stats.relfreq(list,numbins=10000)
    cdf = np.cumsum(res_freq.frequency)
    x = res_freq.lowerlimit+np.linspace(0,res_freq.binsize * res_freq.frequency.size,res_freq.frequency.size)
    return x,cdf

if __name__ == "__main__":
    # for seed in range(5,15,5): #read which seed --------------------------(5,125,5)
        #for people in range(1,9,1): #read how many people
    fig,ax=plt.subplots()
    plt.figure(dpi=500)
    plt.rc('font',family = 'Times New Roman')

    for ti in range (0,5,1):   
        FILE2 = "../PD_15ms/%s/%s/2_packet_latency.csv" %(people,timelist[ti])  #give the path
        list_all = getDelayList(FILE2)
        x1,cdf1 = cdf(list_all)
        if timelist[ti] == 15:
            plt.plot(x1,cdf1/cdf1[-1],label="BeamTOP-%s" %timelist[ti])  
        else:
            plt.plot(x1,cdf1/cdf1[-1], label="BeamTOP-%s" %timelist[ti])
        x1 =[]
        cdf1=[]

    for ti in range (0,5,1):    
        FILE = "../NC_15ms/%s/%s/2_packet_latency.csv" %(people,timelist[ti])  #give the path
        list_all = getDelayList(FILE)
        x1,cdf1 = cdf(list_all)
        if timelist[ti] == 15:
            plt.plot(x1,cdf1/cdf1[-1],"-.",label="RLNC+BM-%s" %timelist[ti],linewidth = 1.0)  
        else:
            plt.plot(x1,cdf1/cdf1[-1],"-.", label="RLNC+BM-%s" %timelist[ti],linewidth = 1.0)
        x1 =[]
        cdf1=[]
    

    
    plt.xlim(4,20)
    plt.ylim(0.0,1.1)
    # plt.xlim(18,20)
    # plt.ylim(0.85,1.05)
plt.xlabel('Packet Latency (ms)',color='black',fontsize = 15)
plt.ylabel('CDF',color='black',fontsize = 15)
plt.axhline(y=1, color="gray", ls="--",linewidth=0.5)
plt.tick_params(labelsize=13) # x,y
plt.legend(bbox_to_anchor=(0.5, 1.15),loc="upper center", ncol=5,frameon=False,fontsize = 8)


plt.axes([0.5, 0.25, 0.35, 0.35])  

for ti in range (0,5,1):   
    FILE2 = "../PD_15ms/%s/%s/2_packet_latency.csv" %(people,timelist[ti])  #give the path
    list_all = getDelayList(FILE2)
    x1,cdf1 = cdf(list_all)
    if timelist[ti] == 15:
        plt.plot(x1,cdf1/cdf1[-1],linewidth = 3.0)  
    else:
        plt.plot(x1,cdf1/cdf1[-1],linewidth = 2.0)
    x1 =[]
    cdf1=[]

for ti in range (0,5,1):    
    FILE = "../NC_15ms/%s/%s/2_packet_latency.csv" %(people,timelist[ti])  #give the path
    list_all = getDelayList(FILE)
    x1,cdf1 = cdf(list_all)
    if timelist[ti] == 15:
        plt.plot(x1,cdf1/cdf1[-1],"-.",linewidth = 3.0)  
    else:
        plt.plot(x1,cdf1/cdf1[-1],"-.",linewidth = 2.0)
    x1 =[]
    cdf1=[]




plt.xlim(18,20)
plt.ylim(0.96,1.01)

#plt.tight_layout()
plt.savefig("S3-cdf.jpg",bbox_inches='tight')
    # plt.show()
