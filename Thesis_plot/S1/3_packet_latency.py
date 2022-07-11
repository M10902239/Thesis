import csv
import sys
import numpy as np
#FILE = "test.txt"
list_all = []
unused_list = []
thr_list=[]
delay_list=[]
way = sys.argv[1] ## people
input1 = sys.argv[2] ## people
people = int(input1)

def getDelayList(file):
    with open(file) as f:
        list_of_rows1 = list(csv.reader(f, delimiter=' '))
        delayList = []
        for line in list_of_rows1:
            delayList.append(int(line[1]))
    return delayList

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
	ThrFILE = "./%s/%s/1_thr.csv" %(way,people) #give the path
	unused_list = getunusedList(ThrFILE)
for seed in range (5,155,5):
    FILE = "./0516rawdata/S1/seed%s/S1/%s/%s/0_packet_latency.txt" %(seed,way,people) #give the path
    if not (seed/5 in unused_list):
        list_all.append(getDelayList(FILE)) ## get all seed


with open('./%s/%s/2_packet_latency.csv' %(way,people),'w',newline='')as f:
    w = csv.writer(f, quoting=csv.QUOTE_ALL,delimiter=',')
    while(len(list_all[0])):
        # w.writerow([list_all[0].pop(),list_all[1].pop(),list_all[2].pop(),list_all[3].pop(),list_all[4].pop(),list_all[5].pop()])
        w.writerow([list_all[0].pop(),list_all[1].pop(),list_all[2].pop(),list_all[3].pop(),list_all[4].pop(),list_all[5].pop(),list_all[6].pop(),list_all[7].pop(),list_all[8].pop(),list_all[9].pop(),list_all[10].pop(),list_all[11].pop(),list_all[12].pop(),list_all[13].pop(),list_all[14].pop(),list_all[15].pop(),list_all[16].pop(),list_all[17].pop(),list_all[18].pop(),list_all[19].pop(),list_all[20].pop(),list_all[21].pop(),list_all[22].pop(),list_all[23].pop(),list_all[24].pop()])
    