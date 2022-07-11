import csv
import string
import sys
#FILE = "test.txt"
list_all = []
list_time = []
list1 = []
Delay_list_data = []
goodrate_list = []
sum=[]
way = sys.argv[1] ## way
input1 = sys.argv[2] ## people
people = int(input1)


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
        AvgList = []
        if people ==1:
            pos = 0
        else:
            pos = people
        for line in zipped1:
            ThrList.append(float(line[pos+1]))
            sum+= float(line[pos+1])
        AvgList.append(sum/82)
    return ThrList

def getAvgList(file,people):
    with open(file) as f:
        list_of_rows1 = list(csv.reader(f, delimiter=','))
        zipped1 = list_of_rows1[6:-1]
        sum = 0
        AvgList = []
        if people ==1:
            pos = 0
        else:
            pos = people
        for line in zipped1:
            sum+= float(line[pos+1])
        AvgList.append(sum/82)
    return AvgList

def getDelayList(file):
    with open(file) as f:
        list_of_rows1 = list(csv.reader(f, delimiter=' '))
        zipped1 = list_of_rows1[6:-1]
        delayList = []
        for line in zipped1:
            delayList.append(float(line[1]))
    return delayList

def getThresholdPercent(delayList, threshold):
    num = 0
    for d in delayList:
        if d <= threshold:
            num += 1
    return (num/len(delayList))
    
if __name__ == "__main__":
    for seed in range(5,155,5): #read which seed --------------------------(5,125,5)
        #for people in range(1,9,1): #read how many people
        FILE = "../Cotag/seed%s/S1/%s/%s/2_overall.csv" %(seed,way,people) #give the path
        list_all.append(getThrList(FILE,people)) ## get all seed
        sum.append(getAvgList(FILE,people)) ## get all seed
        GoodRateFILE = "../Cotag/seed%s/S1/%s/%s/0_packet_latency.txt" %(seed,way,people) #give the path
        Delay_list_data.append(getDelayList(GoodRateFILE)) ## get all seed avg delay
    for th in range(0,30,1):  
            goodrate_list.append(getThresholdPercent(Delay_list_data[th],20000))
    list_time.append(getTimeList(FILE)) ## get time list
    with open('./%s/%s/1_thr.csv'%(way,people),'w',newline='')as f:
        w = csv.writer(f, quoting=csv.QUOTE_ALL,delimiter=',')
        while(len(list_time[0])):
        #     w.writerow([list_time[0].pop(0),list_all[0].pop(0),list_all[1].pop(0),list_all[2].pop(0),list_all[3].pop(0),list_all[4].pop(0),list_all[5].pop(0)])
        # w.writerow([" ",sum[0].pop(0),sum[1].pop(0),sum[2].pop(0),sum[3].pop(0),sum[4].pop(0),sum[5].pop(0)])
        # w.writerow([" ",goodrate_list.pop(0),goodrate_list.pop(0),goodrate_list.pop(0),goodrate_list.pop(0),goodrate_list.pop(0),goodrate_list.pop(0)])
            w.writerow([list_time[0].pop(0),list_all[0].pop(0),list_all[1].pop(0),list_all[2].pop(0),list_all[3].pop(0),list_all[4].pop(0),list_all[5].pop(0),list_all[6].pop(0),list_all[7].pop(0),list_all[8].pop(0),list_all[9].pop(0),list_all[10].pop(0),list_all[11].pop(0),list_all[12].pop(0),list_all[13].pop(0),list_all[14].pop(0),list_all[15].pop(0),list_all[16].pop(0),list_all[17].pop(0),list_all[18].pop(0),list_all[19].pop(0),list_all[20].pop(0),list_all[21].pop(0),list_all[22].pop(0),list_all[23].pop(0),list_all[24].pop(0),list_all[25].pop(0),list_all[26].pop(0),list_all[27].pop(0),list_all[28].pop(0),list_all[29].pop(0)])
        w.writerow([" ",sum[0].pop(0),sum[1].pop(0),sum[2].pop(0),sum[3].pop(0),sum[4].pop(0),sum[5].pop(0),sum[6].pop(0),sum[7].pop(0),sum[8].pop(0),sum[9].pop(0),sum[10].pop(0),sum[11].pop(0),sum[12].pop(0),sum[13].pop(0),sum[14].pop(0),sum[15].pop(0),sum[16].pop(0),sum[17].pop(0),sum[18].pop(0),sum[19].pop(0),sum[20].pop(0),sum[21].pop(0),sum[22].pop(0),sum[23].pop(0),sum[24].pop(0),sum[25].pop(0),sum[26].pop(0),sum[27].pop(0),sum[28].pop(0),sum[29].pop(0)])
        w.writerow([" ",goodrate_list.pop(0),goodrate_list.pop(0),goodrate_list.pop(0),goodrate_list.pop(0),goodrate_list.pop(0),goodrate_list.pop(0),goodrate_list.pop(0),goodrate_list.pop(0),goodrate_list.pop(0),goodrate_list.pop(0),goodrate_list.pop(0),goodrate_list.pop(0),goodrate_list.pop(0),goodrate_list.pop(0),goodrate_list.pop(0),goodrate_list.pop(0),goodrate_list.pop(0),goodrate_list.pop(0),goodrate_list.pop(0),goodrate_list.pop(0),goodrate_list.pop(0),goodrate_list.pop(0),goodrate_list.pop(0),goodrate_list.pop(0),goodrate_list.pop(0),goodrate_list.pop(0),goodrate_list.pop(0),goodrate_list.pop(0),goodrate_list.pop(0),goodrate_list.pop(0)])     
