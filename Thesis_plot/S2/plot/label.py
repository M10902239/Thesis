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
AP1_list =[]
AP2_list =[]
Delay_list_data = []
goodrate_list = []
sum=[]
people = 8
np.seterr(divide='ignore', invalid='ignore')


def getTimeList(file):
    with open(file) as f:
        list_of_rows1 = list(csv.reader(f, delimiter=' '))
        TimeList = []
        for line in list_of_rows1:
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

def getAvgList(file,seq):
    with open(file) as f:
        list_of_rows1 = list(csv.reader(f, delimiter=' '))
        AvgList = []
        for line in list_of_rows1:
            if seq ==1:
                AvgList.append(float(line[1])+10000)
            else:
                AvgList.append(float(line[1]))
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
    # ThrFILE = "2_AP1_queue.txt" #give the path
    ThrFILE = "2_AP1_queue_m.txt" #give the path
    AP1_list=(getAvgList(ThrFILE,1)) ## get all seed
    list_time_NC=(getTimeList(ThrFILE)) ## get time list

    # TThrFILE ="2_AP2_queue.txt" #give the path
    TThrFILE ="2_AP2_queue_m.txt" #give the path
    AP2_list=(getAvgList(TThrFILE,2)) ## get all seed
    list_time_PD=(getTimeList(TThrFILE)) ## get time list


##########################
fig,ax=plt.subplots()
plt.figure(dpi=500)
plt.rc('font',family = 'Times New Roman')

# plt.scatter(list_time_PD.pop(0),AP1_list.pop(0),".",color="purple",label='AP1',markersize=1.0)
# plt.scatter(list_time_NC.pop(0),AP2_list.pop(0),".",color="peru",label='AP2',markersize=1.0)
plt.plot(list_time_NC,AP1_list,".",color="peru",label='AP1',markersize=0.1)
plt.plot(list_time_PD,AP2_list,".",color="purple",label='AP2',markersize=0.1)

plt.xlabel('Time (s)',color='black',fontsize = 15)
plt.ylabel('BeamTOP NC Label',color='black',fontsize = 15)
plt.axvline(x=2.4, color="gray", ls="--",linewidth=1)
plt.axvline(x=2.5, color="gray", ls="-",linewidth=1)
plt.axvline(x=2.6, color="gray", ls="--",linewidth=1)
plt.axvline(x=2.7, color="gray", ls="-",linewidth=1)
plt.axvline(x=2.8, color="gray", ls="--",linewidth=1)
plt.axvline(x=2.9, color="gray", ls="-",linewidth=1)
plt.axvline(x=3.0, color="gray", ls="--",linewidth=1)
plt.axvline(x=3.1, color="gray", ls="-",linewidth=1)
# plt.ylim([60000, 80000])
# plt.xlim([3.5, 4.0])

plt.tick_params(labelsize=13) # x,y
plt.legend(bbox_to_anchor=(0.5, 1.15),loc="upper center", ncol=4,frameon=False,fontsize = 12)
# plt.savefig("S2-label-cotag.jpg")
# plt.savefig("S2-label-my.jpg")
plt.savefig("S2-label-BeamTOP.jpg")
