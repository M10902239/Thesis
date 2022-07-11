import csv
import string
import sys
import numpy as np
#FILE = "test.txt"
delay_list = []
list_time = []
list1 = []
Delay_list_data = []
goodrate_list = []
sum=[]
way = sys.argv[1] ## way
input1 = sys.argv[2] ## people
people = int(input1)
np.seterr(divide='ignore', invalid='ignore')


def getTimeList(file):
    with open(file) as f:
        list_of_rows1 = list(csv.reader(f, delimiter=','))
        zipped1 = list_of_rows1[6:-1]
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

def getAvgList(file):
    with open(file) as f:
        list_of_rows1 = list(csv.reader(f, delimiter=','))
        zipped1 = list_of_rows1[6:-1]
        sum = 0
        AvgList = []
        for line in zipped1:
            sum+= float(line[people+1])
        AvgList.append(sum/22)
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
                if people == 1:
                    delay_sum  += float(line[4])/1000
                    # print(delay_sum)
                else:
                    delay_sum  += float(line[pos])*float(line[3+people+pos])/1000
            if people != 1 and delay_sum > 0:
                delayList.append(float(delay_sum/float(line[people+1])))
            elif people==1:
                delayList.append(float(delay_sum/1))
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
        print(unused)
    return unused
    
if __name__ == "__main__":
	ThrFILE = "./%s/%s/1_thr.csv" %(way,people) #give the path
	unused_list = getunusedList(ThrFILE)
for seed in range (5,155,5):
    FILE = "../Cotag/seed%s/S1/%s/%s/2_overall.csv" %(seed,way,people) #give the path
    if not (seed/5 in unused_list):
        delay_list.append(getDelayList(FILE,people)) ## get all seed
    list_time.append(getTimeList(FILE)) ## get time list
    # print(delay_list)

with open('./%s/%s/2_latency.csv'%(way,people),'w',newline='')as f:
    w = csv.writer(f, quoting=csv.QUOTE_ALL,delimiter=',')
    while(len(list_time[0])):
        #  w.writerow([list_time[0].pop(0),delay_list[0].pop(0),delay_list[1].pop(0),delay_list[2].pop(0),delay_list[3].pop(0),delay_list[4].pop(0),delay_list[5].pop(0)])
        w.writerow([list_time[0].pop(0),delay_list[0].pop(0),delay_list[1].pop(0),delay_list[2].pop(0),delay_list[3].pop(0),delay_list[4].pop(0),delay_list[5].pop(0),delay_list[6].pop(0),delay_list[7].pop(0),delay_list[8].pop(0),delay_list[9].pop(0),delay_list[10].pop(0),delay_list[11].pop(0),delay_list[12].pop(0),delay_list[13].pop(0),delay_list[14].pop(0),delay_list[15].pop(0),delay_list[16].pop(0),delay_list[17].pop(0),delay_list[18].pop(0),delay_list[19].pop(0),delay_list[20].pop(0),delay_list[21].pop(0),delay_list[22].pop(0),delay_list[23].pop(0),delay_list[24].pop(0)])