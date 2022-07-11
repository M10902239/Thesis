import csv
import string
import sys
#FILE = "test.txt"
list_all = []
list_time = []
list1 = []
Delay_list_data1 = []
Delay_list_data2 = []
goodrate_list = []
snr1=[]
snr2=[]
sum=[]


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
        for line in zipped1:
            ThrList.append(float(line[1]))
    return ThrList

def getAvgList(file):
    with open(file) as f:
        list_of_rows1 = list(csv.reader(f, delimiter=','))
        zipped1 = list_of_rows1[6:-1]
        AvgList = []
        for line in zipped1:
            AvgList.append(float(line[9])-float(line[1]))
    return AvgList

def getDelayList(file):
    with open(file) as f:
        list_of_rows1 = list(csv.reader(f, delimiter=','))
        zipped1 = list_of_rows1[6:-1]
        delayList = []
        for line in zipped1:
            delayList.append(float(line[14]))
    return delayList

def getDelayList2(file):
    with open(file) as f:
        list_of_rows1 = list(csv.reader(f, delimiter=','))
        zipped1 = list_of_rows1[6:-1]
        delayList = []
        for line in zipped1:
            delayList.append((float(line[15])+float(line[16])+float(line[17])+float(line[18])+float(line[19])+float(line[20])+float(line[21]))/7)
    return delayList

def getsnrList(file,pos):
    with open(file) as f:
        list_of_rows1 = list(csv.reader(f, delimiter=','))
        zipped1 = list_of_rows1[6:-1]
        delayList = []
        for line in zipped1:
            delayList.append(float(line[pos]))
    return delayList
    
if __name__ == "__main__":
    for seed in range(10,25,5): #read which seed --------------------------(5,125,5)
        FILE = "./ori/seed%s/S1/PD/8/2_overall.csv" %(seed) #give the path
        list_all.append(getThrList(FILE)) ## get all seed
        sum.append(getAvgList(FILE)) ## get all seed
        snr1.append(getsnrList(FILE,11))
        snr2.append(getsnrList(FILE,13))
        Delay_list_data1.append(getDelayList(FILE)) ## get all seed avg delay
        Delay_list_data2.append(getDelayList2(FILE)) ## get all seed avg delay
        list_time.append(getTimeList(FILE)) ## get time list

    with open('./data/1_thr.csv','w',newline='')as f:
        w = csv.writer(f, quoting=csv.QUOTE_ALL,delimiter=',')
        while(len(list_time[0])):
            w.writerow([list_time[0].pop(0),list_all[0].pop(0),list_all[1].pop(0),list_all[2].pop(0),sum[0].pop(0),sum[1].pop(0),sum[2].pop(0),snr1[0].pop(0),snr2[0].pop(0),Delay_list_data1[0].pop(0),Delay_list_data1[1].pop(0),Delay_list_data1[2].pop(0),Delay_list_data2[0].pop(0),Delay_list_data2[1].pop(0),Delay_list_data2[2].pop(0)])
        # w.writerow([" ",sum[0].pop(0),sum[1].pop(0),sum[2].pop(0),sum[3].pop(0),sum[4].pop(0),sum[5].pop(0),sum[6].pop(0),sum[7].pop(0),sum[8].pop(0),sum[9].pop(0),sum[10].pop(0),sum[11].pop(0),sum[12].pop(0),sum[13].pop(0),sum[14].pop(0),sum[15].pop(0),sum[16].pop(0),sum[17].pop(0),sum[18].pop(0),sum[19].pop(0),sum[20].pop(0),sum[21].pop(0),sum[22].pop(0),sum[23].pop(0),sum[24].pop(0),sum[25].pop(0),sum[26].pop(0),sum[27].pop(0),sum[28].pop(0),sum[29].pop(0)])
        # w.writerow([" ",goodrate_list.pop(0),goodrate_list.pop(0),goodrate_list.pop(0),goodrate_list.pop(0),goodrate_list.pop(0),goodrate_list.pop(0),goodrate_list.pop(0),goodrate_list.pop(0),goodrate_list.pop(0),goodrate_list.pop(0),goodrate_list.pop(0),goodrate_list.pop(0),goodrate_list.pop(0),goodrate_list.pop(0),goodrate_list.pop(0),goodrate_list.pop(0),goodrate_list.pop(0),goodrate_list.pop(0),goodrate_list.pop(0),goodrate_list.pop(0),goodrate_list.pop(0),goodrate_list.pop(0),goodrate_list.pop(0),goodrate_list.pop(0),goodrate_list.pop(0),goodrate_list.pop(0),goodrate_list.pop(0),goodrate_list.pop(0),goodrate_list.pop(0),goodrate_list.pop(0)])     
