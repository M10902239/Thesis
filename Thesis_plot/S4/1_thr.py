import csv
import string
import sys
#from tkinter import E
#FILE = "test.txt"
slow_list = []
medium_list = []
fast_list = []

l_slow_list = []
l_medium_list = []
l_fast_list = []

s_Delay_list_data = []
m_Delay_list_data = []
f_Delay_list_data = []
s_goodrate_list = []
m_goodrate_list = []
f_goodrate_list = []
way = sys.argv[1] ## way
input1 = sys.argv[2] ## people
time = int(input1)


def getTimeList(file):
    with open(file) as f:
        list_of_rows1 = list(csv.reader(f, delimiter=','))
        zipped1 = list_of_rows1[6:-1]
        TimeList = []
        for line in zipped1:
            TimeList.append(float(line[0]))
    return TimeList

def getThrList(file,user):
    with open(file) as f:
        list_of_rows1 = list(csv.reader(f, delimiter=','))
        zipped1 = list_of_rows1[6:-1]
        userList = []
        all_list = []
        for line in zipped1:
            userList.append((float(line[2*user-1])+float(line[2*user]))/2)
        all_list=(sum(userList)/len(userList))
    return all_list

def getlatencyList(file,user):
    with open(file) as f:
        list_of_rows1 = list(csv.reader(f, delimiter=','))
        zipped1 = list_of_rows1[6:-1]
        latency_list = []
        all_list = []
        for line in zipped1:
            latency_list.append((float(line[2*user])+float(line[2*user+1]))/2)
        all_list=(sum(latency_list)/len(latency_list))
    return all_list

def getThresholdPercent(delayList, threshold):
    num = 0
    for d in delayList:
        if d <= threshold:
            num += 1
    return (num/len(delayList))

def getDelayList(file,group):
    with open(file) as f:
        list_of_rows1 = list(csv.reader(f, delimiter=' '))
        delayList = []
        for line in list_of_rows1:
            if int(line[2]) == group or int(line[2]) == group-1:
                delayList.append(int(line[1]))
    return delayList

def getDelayList2(file):
    with open(file) as f:
        list_of_rows1 = list(csv.reader(f, delimiter=' '))
        delayList = []
        for line in list_of_rows1:
            delayList.append(int(line[1]))
    return delayList
    
if __name__ == "__main__":
    for seed in range(5,155,5): #read which seed --------------------------(5,125,5)
        FILE = "./0516rawdata/S4/seed%s/S4/%s/%s/2_overall.csv" %(seed,way,time) #give the path
        slow_list.append(getThrList(FILE,1)) ## get all seed
        medium_list.append(getThrList(FILE,2)) ## get all seed
        fast_list.append(getThrList(FILE,3)) ## get all seed
    for seed in range(5,155,5): #read which seed --------------------------(5,125,5)
        FILE = "./0516rawdata/S4/seed%s/S4/%s/%s/2_overall.csv" %(seed,way,time) #give the path
        l_slow_list.append(getlatencyList(FILE,5)) ## get all seed
        l_medium_list.append(getlatencyList(FILE,6)) ## get all seed
        l_fast_list.append(getlatencyList(FILE,7)) ## get all seed

    if (way == 'PD'):
        print(way)
        for seed in range(5,155,5):
            GoodRateFILE = "./0516rawdata/S4/seed%s/S4/%s/%s/0_packet_latency.txt" %(seed,way,time) #give the path
            s_Delay_list_data.append(getDelayList(GoodRateFILE,2)) ## get all seed avg delay
            m_Delay_list_data.append(getDelayList(GoodRateFILE,4)) ## get all seed avg delay
            f_Delay_list_data.append(getDelayList(GoodRateFILE,6)) ## get all seed avg delay

        for th in range(0,30,1):  
                print(th)
                s_goodrate_list.append(getThresholdPercent(s_Delay_list_data[th],20000))
                m_goodrate_list.append(getThresholdPercent(m_Delay_list_data[th],20000))
                f_goodrate_list.append(getThresholdPercent(f_Delay_list_data[th],20000))
    else:
        for seed in range(5,155,5):
            GoodRateFILE = "./0516rawdata/S4/seed%s/S4/%s/%s/0_packet_latency.txt" %(seed,way,time) #give the path
            s_Delay_list_data.append(getDelayList2(GoodRateFILE)) ## get all seed avg delay
            m_Delay_list_data.append(getDelayList2(GoodRateFILE)) ## get all seed avg delay
            f_Delay_list_data.append(getDelayList2(GoodRateFILE)) ## get all seed avg delay
        for th in range(0,30,1):  
            s_goodrate_list.append(getThresholdPercent(s_Delay_list_data[th],20000))
            m_goodrate_list.append(getThresholdPercent(m_Delay_list_data[th],20000))
            f_goodrate_list.append(getThresholdPercent(f_Delay_list_data[th],20000))

    with open('./%s/%s/1_thr.csv'%(way,time),'w',newline='')as f:
        w = csv.writer(f, quoting=csv.QUOTE_ALL,delimiter=',')
        while(len(slow_list)):
            A = slow_list.pop()
            B = medium_list.pop()
            C = fast_list.pop()
            D1 = s_goodrate_list.pop()
            D2 = m_goodrate_list.pop()
            D3 = f_goodrate_list.pop()
            E = l_slow_list.pop()
            F = l_medium_list.pop()
            G = l_fast_list.pop()
            print(D1,D2,D3)
            w.writerow([A,B,C,(D1+D2+D3)/3,A*D1,B*D2,C*D3,(A*D1+B*D2+C*D3),E,F,G])
            
