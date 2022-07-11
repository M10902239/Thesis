import csv
import numpy as np
import matplotlib.pyplot as plt; 
import string
import sys
#FILE = "test.txt"
delay_list = []
list_time_NC = []
list_time_PD = []
list_time_PD15 = []
list_time_Coatg = []
NC_list = []
PD_list = []
PD15_list = []
Cotag_list = []

Delay_list_data = []
goodrate_list = []
sum=[]
people = 8
np.seterr(divide='ignore', invalid='ignore')


def getTimeList(file):
    with open(file) as f:
        list_of_rows1 = list(csv.reader(f, delimiter=','))
        zipped1 = list_of_rows1[0:-2]
        TimeList = []
        for line in zipped1:
            TimeList.append(float(line[0]))
    return TimeList

def getThrList(file):
    with open(file) as f:
        list_of_rows1 = list(csv.reader(f, delimiter=','))
        zipped1 = list_of_rows1[6:-1]
        ThrList = []
        sum = 0
        AvgList = []
        for line in zipped1:
            ThrList.append(float(line[people+1]))
            sum+= float(line[people+1])
        AvgList.append(sum/22)
    return ThrList

def getAvgList(file,unused_list):
    with open(file) as f:
        list_of_rows1 = list(csv.reader(f, delimiter=','))
        zipped1 = list_of_rows1[0:-2]
        sum = 0
        AvgList = []
        for line in zipped1:
            for i in range(1,31,1):
                if not (i in unused_list):
                    sum+= float(line[i])
            AvgList.append(sum/25)
            sum = 0
        # print(AvgList)
    return AvgList

def getDelayList(file,people):
    with open(file) as f:
        list_of_rows1 = list(csv.reader(f, delimiter=','))
        zipped1 = list_of_rows1[6:-1]
        delayList = []
        for line in zipped1:
            delay_sum = 0
            for pos in range(1,people+1,1):
                # print(float(line[3]))
                delay_sum  += float(line[pos])*float(line[3+people+pos])/1000
            if delay_sum > 0:
                delayList.append(float(delay_sum/float(line[people+1])))
            else:
                delayList.append(float(0.0))
        # print(delayList)
    return delayList

def getThresholdPercent(delayList, threshold):
    num = 0
    for d in delayList:
        if d <= threshold:
            num += 1
    return (num/len(delayList))

def getunusedList(file):
    with open(file) as f1:
        list_of_rows1 = list(csv.reader(f1, delimiter=','))
        ThrList = []
        unused=[]
        list_of_rows1[22].pop(0)
        while(len(list_of_rows1[22])):
            ThrList.append(float(list_of_rows1[22].pop(0))) 
        for min in range(0,5,1):
            unused.append((np.argsort(ThrList)[min])+1)
        # print(unused)
    return unused
    
if __name__ == "__main__":
    ThrFILE = "../NC_15ms/%s/1_thr.csv" %(people) #give the path
    unused_list = getunusedList(ThrFILE)
    NC_list.append(getAvgList(ThrFILE,unused_list)) ## get all seed
    list_time_NC.append(getTimeList(ThrFILE)) ## get time list

    ThrFILE = "../PD/%s/1_thr.csv" %(people) #give the path
    unused_list = getunusedList(ThrFILE)
    PD_list.append(getAvgList(ThrFILE,unused_list)) ## get all seed
    list_time_PD.append(getTimeList(ThrFILE)) ## get time list

    ThrFILE = "../PD_15ms/%s/1_thr.csv" %(people) #give the path
    unused_list = getunusedList(ThrFILE)
    PD15_list.append(getAvgList(ThrFILE,unused_list)) ## get all seed
    list_time_PD15.append(getTimeList(ThrFILE)) ## get time list

    ThrFILE = "../Cotag/%s/1_thr.csv" %(people) #give the path
    Cotag_list.append(getAvgList(ThrFILE,unused_list)) ## get all seed
    list_time_Coatg.append(getTimeList(ThrFILE)) ## get time list
    # print(delay_list)

##########################
fig,ax=plt.subplots()
plt.figure(dpi=500)
plt.rc('font',family = 'Times New Roman')

plt.plot(list_time_PD15.pop(0),PD15_list.pop(0),"-p",color="steelblue",label='BeamTOP',markersize=5)
plt.plot(list_time_PD.pop(0),PD_list.pop(0),"-x",color="purple",label='PD',markersize=0.5)
plt.plot(list_time_NC.pop(0),NC_list.pop(0),"-^",color="peru",label='RLNC+BM',markersize=0.5)
plt.plot(list_time_Coatg.pop(0),Cotag_list.pop(0),"-p",color="slategray",label='COTAG-based NC',markersize=0.5)

plt.xlabel('Time (s)',color='black',fontsize = 15)
plt.ylabel('Throughput (Mbps)',color='black',fontsize = 15)
ax.set_ylim([0, 2000])

plt.tick_params(labelsize=13) # x,y
plt.legend(bbox_to_anchor=(0.5, 1.15),loc="upper center", ncol=4,frameon=False,fontsize = 12)
plt.savefig("S2-Throughput.jpg")
