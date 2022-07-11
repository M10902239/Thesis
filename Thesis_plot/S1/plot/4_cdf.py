from cProfile import label
import csv
import sys
import numpy as np
import matplotlib.pyplot as plt 
from scipy import stats
import string
from mpl_toolkits.axes_grid1.inset_locator import mark_inset
from mpl_toolkits.axes_grid1.inset_locator import inset_axes
from pylab import *

list_all = []
list_all2 = []
list1 = []
waylist = ['PD_15ms','PD','NC_15ms','Cotag']
namelist = ['BeamTOP','PD','RLNC+BM','COTAG-based NC']
people = 8

def getDelayList(file):
    with open(file) as f:
        list_of_rows1 = list(csv.reader(f, delimiter=','))
        delayList = []
        for line in list_of_rows1:
            for time in range (0,25,1):
                delayList.append((float(line[time]))/1000)
    return delayList

def cdf(list):
    cdf = []
    x = []
    res_freq = stats.relfreq(list,numbins=10000)
    cdf = np.cumsum(res_freq.frequency)
    x = res_freq.lowerlimit+np.linspace(0,res_freq.binsize * res_freq.frequency.size,res_freq.frequency.size)
    return x,cdf

if __name__ == "__main__":

    fig,ax=plt.subplots()
    plt.figure(dpi=500)
    plt.rc('font',family = 'Times New Roman')
    plt.tick_params(labelsize=13) # x,y

for ti in range (0,4,1):    
    FILE = "../%s/%s/2_packet_latency.csv" %(waylist[ti],people-6)  #give the path
    list_all = getDelayList(FILE)
    # print(waylist[ti])
    x1,cdf1 = cdf(list_all)            
    plt.plot(x1,cdf1/cdf1[-1],"-x",label="%s-%s" %(namelist[ti],people-6),linewidth = 1.0,markersize=2.0)  
    x1 =[]
    cdf1=[]

    
for ti in range (0,4,1):    
    FILE = "../%s/%s/2_packet_latency.csv" %(waylist[ti],people-3)  #give the path
    list_all = getDelayList(FILE)
    x1,cdf1 = cdf(list_all)            
    plt.plot(x1,cdf1/cdf1[-1],"-.",label="%s-%s" %(namelist[ti],people-3),linewidth = 1.0,markersize=2.0)  
    x1 =[]
    cdf1=[]


for ti in range (0,4,1):    
    FILE = "../%s/%s/2_packet_latency.csv" %(waylist[ti],people)  #give the path
    list_all = getDelayList(FILE)
    x1,cdf1 = cdf(list_all)            
    plt.plot(x1,cdf1/cdf1[-1],"--",label="%s-%s" %(namelist[ti],people),linewidth = 1.0)  
    x1 =[]
    cdf1=[]


plt.xlim(4,20)
plt.ylim(0.0,1.1)
# plt.xlim(18, 20)
# plt.ylim(0.95, 1.0)
plt.xlabel('Packet Latency (ms)',color='black',fontsize = 15)
plt.ylabel('CDF',color='black',fontsize = 15)
plt.axhline(y=1, color="gray", ls="--",linewidth=0.5)
plt.legend(bbox_to_anchor=(0.5, 1.3),loc="upper center", ncol=3,frameon=False,fontsize = 10)

plt.axes([0.55, 0.25, 0.30, 0.30])  

for ti in range (0,4,1):    
    FILE = "../%s/%s/2_packet_latency.csv" %(waylist[ti],people-6)  #give the path
    list_all = getDelayList(FILE)
    # print(waylist[ti])
    x1,cdf1 = cdf(list_all)            
    plt.plot(x1,cdf1/cdf1[-1],"-x",label="%s-%s" %(waylist[ti],people-6),linewidth = 1.0,markersize=2.0)  
    x1 =[]
    cdf1=[]

    
for ti in range (0,4,1):    
    FILE = "../%s/%s/2_packet_latency.csv" %(waylist[ti],people-3)  #give the path
    list_all = getDelayList(FILE)
    x1,cdf1 = cdf(list_all)            
    plt.plot(x1,cdf1/cdf1[-1],"-.",label="%s-%s" %(waylist[ti],people-3),linewidth = 1.0,markersize=2.0)  
    x1 =[]
    cdf1=[]


for ti in range (0,4,1):    
    FILE = "../%s/%s/2_packet_latency.csv" %(waylist[ti],people)  #give the path
    list_all = getDelayList(FILE)
    x1,cdf1 = cdf(list_all)          
    if (ti==0):
        plt.plot(x1,cdf1/cdf1[-1],"--",label="%s-%s" %(waylist[ti],people),linewidth = 2.0)    
    else:
        plt.plot(x1,cdf1/cdf1[-1],"--",label="%s-%s" %(waylist[ti],people),linewidth = 1.0)  
    x1 =[]
    cdf1=[]

plt.xlim(16,20)
plt.ylim(0.975,1.02)

plt.savefig("S1-cdf.jpg",bbox_inches='tight')
    # plt.show()
