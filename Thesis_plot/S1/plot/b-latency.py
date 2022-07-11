import csv
import numpy as np
import matplotlib.pyplot as plt; 
import string
import sys
#FILE = "test.txt"
NC_list = []
PD_list = []
PD15_list = []
Cotag_list = []
peoplelist = ['1','2','3','4','5','6','7','8']

NC_list_std = []
PD_list_std = []
PD15_list_std = []
Cotag_list_std = []


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
        for line in zipped1:
            ThrList.append(float(line[people+1]))
            sum+= float(line[people+1])
    return ThrList

def getAvgList(file,unused_list):
    with open(file) as f:
        list_of_rows1 = list(csv.reader(f, delimiter=','))
        zipped1 = list_of_rows1[0:-2]
        sum1 = 0
        AvgList = []	
        # alist =[]
        for line in zipped1:
            for i in range(1,7,1):
                if not (i in unused_list):
                    sum1+= float(line[i])
            AvgList.append(sum1/5)
            sum1 = 0
        # alist.append(np.mean(AvgList))
    return np.mean(AvgList)

def getDelayList(file):
    with open(file) as f:
        list_of_rows1 = list(csv.reader(f, delimiter=','))
        zipped1 = list_of_rows1[0:]
        delayList = []
        for line in zipped1:
            delay_sum = 0
            cnt = 0
            for i in range(0,25,1):
                delay_sum+= float(line[i])
                if (line[i] == 0):  
                    cnt+=1
            delayList.append(delay_sum/(25-cnt))
        # print(delayList)
        # print(delayList)
    return np.mean(delayList)

def getstdList(file):
    with open(file) as f:
        list_of_rows1 = list(csv.reader(f, delimiter=','))
        zipped1 = list_of_rows1[0:]
        delayList = []
        for line in zipped1:
            delay_sum = 0
            cnt = 0
            for i in range(0,25,1):
                delay_sum+= float(line[i])
                if (line[i] == 0):  
                    cnt+=1
            delayList.append(delay_sum/(25-cnt))
        # print(delayList)
        # print(delayList)
    return np.std(delayList)

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
        for min in range(0,5,1):
            unused.append((np.argsort(ThrList)[min])+1)
        # print(unused)
    return unused
    
if __name__ == "__main__":
    for people in range (1,9,1):
        ThrFILE = "../NC_15ms/%s/2_latency.csv" %(people) #give the path
        NC_list.append(getDelayList(ThrFILE)) ## get all seed
        NC_list_std.append(getstdList(ThrFILE))

for people in range (1,9,1):
    ThrFILE = "../PD/%s/2_latency.csv" %(people) #give the path
    PD_list.append(getDelayList(ThrFILE)) ## get all seed
    PD_list_std.append(getstdList(ThrFILE))


for people in range (1,9,1):
    ThrFILE = "../PD_15ms/%s/2_latency.csv" %(people) #give the path
    PD15_list.append(getDelayList(ThrFILE)) ## get all seed
    PD15_list_std.append(getstdList(ThrFILE))

for people in range (1,9,1):
    ThrFILE = "../Cotag/%s/2_latency.csv" %(people) #give the path
    Cotag_list.append(getDelayList(ThrFILE)) ## get all seed
    Cotag_list_std.append(getstdList(ThrFILE))



fig,ax=plt.subplots()
plt.figure(dpi=500)
plt.rc('font',family = 'Times New Roman')


width = 0.15
x=np.arange(len(peoplelist)) 
# plt.bar(x-1.5*width, (NC_list), width, color='steelblue',label = 'NC',yerr = NC_list_std, error_kw = {'ecolor' : '0.1', 'capsize' :3})
# plt.bar(x-0.5*width, (PD_list), width, color='purple',label = 'PD',yerr = PD_list_std, error_kw = {'ecolor' : '0.1', 'capsize' :3})
# plt.bar(x+0.5*width, (PD15_list), width, color='peru',label = 'PD_15',yerr = PD15_list_std, error_kw = {'ecolor' : '0.1', 'capsize' :3})
# plt.bar(x+1.5*width, (Cotag_list), width, color='slategray',label = 'Cotag-based NC',yerr = Cotag_list_std, error_kw = {'ecolor' : '0.1', 'capsize' :3})
plt.bar(x-1.5*width, (PD15_list), width, color='steelblue',label = 'BeamTOP')
plt.bar(x-0.5*width, (PD_list), width, color='purple',label = 'PD')
plt.bar(x+0.5*width, (NC_list), width, color='peru',label = 'RLNC+BM')
plt.bar(x+1.5*width, (Cotag_list), width, color='slategray',label = 'COTAG-based NC')



plt.xlabel('People',color='black',fontsize = 15)
plt.ylabel('Latency (ms)',color='black',fontsize = 15)
plt.xticks(range(len(peoplelist)),peoplelist)

plt.tick_params(labelsize=13) # x,y
plt.legend(bbox_to_anchor=(0.5, 1.15),loc="upper center", ncol=4,frameon=False,fontsize = 12)
plt.savefig("S1-bar-Latency.jpg")

