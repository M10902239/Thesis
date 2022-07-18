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

def getDelayList(file,seq):
    with open(file) as f:
        list_of_rows1 = list(csv.reader(f, delimiter=' '))
        delayList = []
        for line in list_of_rows1:
            if((float(line[2])) == seq):
                delayList.append((float(line[1]))/1000)
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

    
def getThresholdPercent(delayList, threshold):
    num = 0
    for d in delayList:
        if d <= threshold:
            num += 1
    if (len(delayList) == 0):
        return 0.0
    else:
        return (1-num/float(len(delayList)))

if __name__ == "__main__":
    # for seed in range(5,15,5): #read which seed --------------------------(5,125,5)
        #for people in range(1,9,1): #read how many people
    fig,ax=plt.subplots()
    plt.figure(dpi=500)
    plt.rc('font',family = 'Times New Roman')

    FILE2 = "./0516rawdata/S1/seed10/S1/PD_15ms/8/0_packet_latency.txt"  #give the path
    for seq in range (1,9,1): 
        list_all = getDelayList(FILE2,seq)
        print("people = %s,BeamTOP"%(seq))
        # print("AvgLatency = %s"%(sum(list_all)/len(list_all)))
        # print("Std = %s"%(np.std(list_all)))
        print("expired = %s"%(getThresholdPercent(list_all,20)))
    print ("====================================")


    
