import csv
import sys
import numpy as np
#FILE = "test.txt"
list_all = []
unused_list = []
thr_list=[]
way = sys.argv[1] ## people
input1 = sys.argv[2] ## people
time = int(input1)
people = 8
def getDelayList(file):
    with open(file) as f:
        list_of_rows1 = list(csv.reader(f, delimiter=' '))
        delayList = []
        for line in list_of_rows1:
            delayList.append(int(line[1]))
    return delayList

def getunusedList(file):
    with open(file) as f1:
        list_of_rows2 = list(csv.reader(f1, delimiter=','))
        ThrList = []
        unused=[]
        for line in list_of_rows2:
            ThrList.append(float(line[2]))
        for min in range(0,5,1):
            unused.append((np.argsort(ThrList)[min])+1)
        # print(unused)
    return unused

    
if __name__ == "__main__":
    ThrFILE = "./%s/%s/%s/1_thr_settle.csv" %(way,people,time) #give the path
    unused_list = getunusedList(ThrFILE)
    for seed in range(5,155,5): #read which seed --------------------------(5,125,5)
        FILE = "./S3_rawdata/S3/%s/seed%s/S3/%s/%s/0_packet_latency.txt" %(people,seed,way,time) #give the path
        if not (seed/5 in unused_list):
            list_all.append(getDelayList(FILE))

    with open('./%s/%s/%s/2_packet_latency.csv' %(way,people,time),'w',newline='')as f:
        w = csv.writer(f, quoting=csv.QUOTE_ALL,delimiter=',')
        while(len(list_all[0])):
            # w.writerow([list_all[0].pop(),list_all[1].pop(),list_all[2].pop(),list_all[3].pop(),list_all[4].pop(),list_all[5].pop(),list_all[6].pop(),list_all[7].pop(),list_all[8].pop(),list_all[9].pop()])
            w.writerow([list_all[0].pop(),list_all[1].pop(),list_all[2].pop(),list_all[3].pop(),list_all[4].pop(),list_all[5].pop(),list_all[6].pop(),list_all[7].pop(),list_all[8].pop(),list_all[9].pop(),list_all[10].pop(),list_all[11].pop(),list_all[12].pop(),list_all[13].pop(),list_all[14].pop(),list_all[15].pop(),list_all[16].pop(),list_all[17].pop(),list_all[18].pop(),list_all[19].pop(),list_all[20].pop(),list_all[21].pop(),list_all[22].pop(),list_all[23].pop(),list_all[24].pop()])
    