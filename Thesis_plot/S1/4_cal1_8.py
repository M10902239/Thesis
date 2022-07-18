import csv
import string
import sys
#FILE = "test.txt"
list_all = []
list_time = []
list1 = []
Delay_list_data = []
goodrate_list = []
# sum1=[]
way = 'PD_15ms'
people = 8


def getTimeList(file):
    with open(file) as f:
        list_of_rows1 = list(csv.reader(f, delimiter=','))
        zipped1 = list_of_rows1[6:-1]
        TimeList = []
        for line in zipped1:
            TimeList.append(float(line[0]))
    return TimeList

def getThrList(file,people):
    with open(file) as f:
        list_of_rows1 = list(csv.reader(f, delimiter=','))
        zipped1 = list_of_rows1[6:-1]
        ThrList = []
        sum = 0
        for line in zipped1:
            ThrList.append(float(line[people]))
    return ThrList

def getAvgList(file,people):
    with open(file) as f:
        list_of_rows1 = list(csv.reader(f, delimiter=','))
        zipped1 = list_of_rows1[6:-1]
        sum1 = 0
        for line in zipped1:
            sum1+= float(line[people])
    return sum1/82

def getDelayList(file,people):
    with open(file) as f:
        list_of_rows1 = list(csv.reader(f, delimiter=','))
        zipped1 = list_of_rows1[6:-1]
        sum1 = 0
        for line in zipped1:
            sum1+= float(line[people+11])
    return sum1/82

def getThresholdPercent(delayList, threshold):
    num = 0
    for d in delayList:
        if d <= threshold:
            num += 1
    return (num/len(delayList))
    
if __name__ == "__main__":
    #for people in range(1,9,1): #read how many people
    for seq in range (1,9,1):
        for seed in range (5,155,5):
            FILE = "./0516rawdata/S1/seed%s/S1/%s/%s/2_overall.csv" %(seed,way,people) #give the path
            list_all.append(getAvgList(FILE,seq))
            list_time.append(getDelayList(FILE,seq))
        print("User%s"%seq)
        print(sum(list_all)/len(list_all))
        print(sum(list_time)/len(list_time))
        list_all=[]
        list_time=[]
   