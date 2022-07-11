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
peoplelist = ['2','3','4','5','6','7','8']

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
        sum1 = 0
        AvgList = []	
        # alist =[]
        for line in zipped1:
            for i in range(1,31,1):
                if not (i in unused_list):
                    sum1+= float(line[i])
            AvgList.append(sum1/25)
            sum1 = 0
        # alist.append(np.mean(AvgList))
    return np.mean(AvgList)

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
        list_of_rows1[82].pop(0)
        while(len(list_of_rows1[82])):
            ThrList.append(float(list_of_rows1[82].pop(0))) 
        for min in range(0,5,1):
            unused.append((np.argsort(ThrList)[min])+1)
        # print(unused)
    return unused
    
if __name__ == "__main__":
	for people in range (8,9,1):
		ThrFILE = "./NC_15ms/%s/1_thr.csv" %(people) #give the path
		unused_list = getunusedList(ThrFILE)
		NC_list.append(getAvgList(ThrFILE,unused_list)) ## get all seed


	for people in range (8,9,1):
		ThrFILE = "./PD/%s/1_thr.csv" %(people) #give the path
		unused_list = getunusedList(ThrFILE)
		PD_list.append(getAvgList(ThrFILE,unused_list)) ## get all seed

	for people in range (8,9,1):
		ThrFILE = "./PD_15ms/%s/1_thr.csv" %(people) #give the path
		unused_list = getunusedList(ThrFILE)
		PD15_list.append(getAvgList(ThrFILE,unused_list)) ## get all seed

for people in range (8,9,1):
    ThrFILE = "./Cotag/%s/1_thr.csv" %(people) #give the path
    unused_list = getunusedList(ThrFILE)
    Cotag_list.append(getAvgList(ThrFILE,unused_list)) ## get all seed

print("NC = %s"%NC_list)
print("PD = %s"%PD_list)
print("PD_15ms = %s"%PD15_list)
print("Cotag = %s"%Cotag_list)









