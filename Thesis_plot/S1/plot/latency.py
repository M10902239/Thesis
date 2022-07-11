import csv
#from tkinter import font
import numpy as np
import matplotlib.pyplot as plt; 
import string
import sys
#FILE = "test.txt"
delay_list = []
list_time_NC = []
list_time_PD = []
list_time_PD15 = []
list_time_Cotag = []
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
        zipped1 = list_of_rows1[0:]
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

def getDelayList(file):
    with open(file) as f:
        list_of_rows1 = list(csv.reader(f, delimiter=','))
        delayList = []
        for line in list_of_rows1:
            delay_sum = 0
            cnt = 0
            for i in range(0,25,1):
                delay_sum+= float(line[i])
                if (line[i] == 0):  
                    cnt+=1
            delayList.append(delay_sum/(25-cnt))
        # print(delayList)
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
        list_of_rows1[82].pop(0)
        while(len(list_of_rows1[82])):
            ThrList.append(float(list_of_rows1[82].pop(0))) 
        for min in range(0,1,1):
            unused.append((np.argsort(ThrList)[min])+1)
        # print(unused)
    return unused
    
if __name__ == "__main__":
    ThrFILE = "../NC_15ms/%s/2_latency.csv" %(people) #give the path
    NC_list.append(getDelayList(ThrFILE)) ## get all seed
    list_time_NC.append(getTimeList(ThrFILE)) ## get time list

    ThrFILE = "../PD/%s/2_latency.csv" %(people) #give the path
    PD_list.append(getDelayList(ThrFILE)) ## get all seed
    list_time_PD.append(getTimeList(ThrFILE)) ## get time list

    ThrFILE = "../PD_15ms/%s/2_latency.csv" %(people) #give the path
    PD15_list.append(getDelayList(ThrFILE)) ## get all seed
    list_time_PD15.append(getTimeList(ThrFILE)) ## get time list

    ThrFILE = "../Cotag/%s/2_latency.csv" %(people) #give the path
    Cotag_list.append(getDelayList(ThrFILE)) ## get all seed
    list_time_Cotag.append(getTimeList(ThrFILE)) ## get time list
    # print(delay_list)


##########################
fig,ax=plt.subplots()
plt.figure(dpi=500)
plt.rc('font',family = 'Times New Roman')
plt.axhline(y=20, color="gray", ls="--",linewidth=1)
plt.tick_params(labelsize=13) # x,y

plt.plot(list_time_PD15.pop(0),PD15_list.pop(0),"-p",color="steelblue",label='BeamTOP',markersize=5)
plt.plot(list_time_PD.pop(0),PD_list.pop(0),"-x",color="purple",label='PD',markersize=0.5)
plt.plot(list_time_NC.pop(0),NC_list.pop(0),"-^",color="peru",label='RLNC+BM',markersize=0.5)
plt.plot(list_time_Cotag.pop(0),Cotag_list.pop(0),"-p",color="slategray",label='COTAG-based NC',markersize=0.5)

plt.xlabel('Time (s)',color='black',fontsize = 15)
plt.ylabel('Latency (ms)',color='black',fontsize = 15)
plt.ylim([5, 40])
plt.legend(bbox_to_anchor=(0.5, 1.15),loc="upper center", ncol=4,frameon=False,fontsize = 12)

ThrFILE = "../NC_15ms/%s/2_latency.csv" %(people) #give the path
NC_list.append(getDelayList(ThrFILE)) ## get all seed
list_time_NC.append(getTimeList(ThrFILE)) ## get time list

ThrFILE = "../PD/%s/2_latency.csv" %(people) #give the path
PD_list.append(getDelayList(ThrFILE)) ## get all seed
list_time_PD.append(getTimeList(ThrFILE)) ## get time list

ThrFILE = "../PD_15ms/%s/2_latency.csv" %(people) #give the path
PD15_list.append(getDelayList(ThrFILE)) ## get all seed
list_time_PD15.append(getTimeList(ThrFILE)) ## get time list

ThrFILE = "../Cotag/%s/2_latency.csv" %(people) #give the path
Cotag_list.append(getDelayList(ThrFILE)) ## get all seed
list_time_Cotag.append(getTimeList(ThrFILE)) ## get time list

plt.axes([0.2, 0.6, 0.25, 0.25])  

plt.plot(list_time_PD15.pop(0),PD15_list.pop(0),"-p",color="steelblue",markersize=5)
plt.plot(list_time_PD.pop(0),PD_list.pop(0),"-x",color="purple",markersize=0.5)
plt.plot(list_time_NC.pop(0),NC_list.pop(0),"-^",color="peru",markersize=0.5)
plt.plot(list_time_Cotag.pop(0),Cotag_list.pop(0),"-p",color="slategray",markersize=0.5)

plt.xlim(4.0, 5.0)
plt.ylim(7, 10)




plt.savefig("S1-Latency.jpg")
