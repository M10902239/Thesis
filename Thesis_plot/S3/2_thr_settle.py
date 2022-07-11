import csv
import string
import sys
#FILE = "test.txt"
list_all = []
Delay_list_data = []
goodrate_list = []
way = sys.argv[1] ## way
input1 = sys.argv[2] ## people
time = int(input1)
people = 4



def getTimeList(file):
    with open(file) as f:
        list_of_rows1 = list(csv.reader(f, delimiter=','))
        TimeList = []
        for line in list_of_rows1:
            TimeList.append(float(line[0]))
    return TimeList

def getAvgThrList(file):
    with open(file) as f:
        sum = 0.0
        list_of_rows1 = list(csv.reader(f, delimiter=','))
        delayList = []
        # print(len(list_of_rows1))
        for time in range(1,31,1):
            for line in list_of_rows1:
                sum += (float(line[time]))
            delayList.append(sum/len(list_of_rows1))
            sum = 0.0
    return delayList

def getDelayList(file):
    with open(file) as f:
        list_of_rows1 = list(csv.reader(f, delimiter=' '))
        delayList = []
        for line in list_of_rows1:
            delayList.append(int(line[1]))
    return delayList

def getThresholdPercent(delayList, threshold = 20000):
    num = 0
    for d in delayList:
        if d <= threshold:
            num += 1
    return (num/len(delayList))

    
if __name__ == "__main__":
    # for seed in range(5,155,5): #read which seed --------------------------(5,125,5)
        #for people in range(1,9,1): #read how many people
    FILE = "./%s/%s/%s/1_thr.csv" %(way,people,time) #give the path
    list_all.append(getAvgThrList(FILE)) ## get all seed avg thr

    for seed in range(5,155,5):
        GoodRateFILE = "./S3_rawdata/S3/%s/seed%s/S3/%s/%s/0_packet_latency.txt" %(people,seed,way,time) #give the path
        Delay_list_data.append(getDelayList(GoodRateFILE)) ## get all seed avg delay
    for th in range(0,30,1):  
            goodrate_list.append(getThresholdPercent(Delay_list_data[th],20000))

    with open('./%s/%s/%s/1_thr_settle.csv'%(way,people,time),'w',newline='')as f:
        w = csv.writer(f, quoting=csv.QUOTE_ALL,delimiter=',')
        # w.writerow(["Each seed Avg Thr(Mbps)","Good Rate(%)"])
        while(len(list_all[0])):
            A = list_all[0].pop(0)
            B = goodrate_list.pop()
            w.writerow([A,B,A*B])
                
