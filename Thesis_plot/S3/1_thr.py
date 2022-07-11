import csv
import string
import sys
#FILE = "test.txt"
list_all = []
list_time = []
list1 = []
way = sys.argv[1] ## way
input1 = sys.argv[2] ## people
time = int(input1)
people = 4

def getTimeList(file):
    with open(file) as f:
        list_of_rows1 = list(csv.reader(f, delimiter=','))
        zipped1 = list_of_rows1[6:-1]
        TimeList = []
        for line in zipped1:
            TimeList.append(float(line[0]))
    return TimeList

def getDelayList(file):
    with open(file) as f:
        list_of_rows1 = list(csv.reader(f, delimiter=','))
        zipped1 = list_of_rows1[6:-1]
        delayList = []
        for line in zipped1:
            delayList.append(float(line[1+people]))
    return delayList
    
if __name__ == "__main__":
    for seed in range(5,155,5): #read which seed --------------------------(5,125,5)
        #for people in range(1,9,1): #read how many people
        FILE = "./S3_rawdata/S3/%s/seed%s/S3/%s/%s/2_overall.csv" %(people,seed,way,time) #give the path
        list_all.append(getDelayList(FILE)) ## get all seed
    list_time.append(getTimeList(FILE)) ## get time list
    with open('./%s/%s/%s/1_thr.csv'%(way,people,time),'w',newline='')as f:
        w = csv.writer(f, quoting=csv.QUOTE_ALL,delimiter=',')
        while(len(list_time[0])):
            # w.writerow([list_time[0].pop(0),list_all[0].pop(0),list_all[1].pop(0),list_all[2].pop(0),list_all[3].pop(0),list_all[4].pop(0),list_all[5].pop(0),list_all[6].pop(0),list_all[7].pop(0),list_all[8].pop(0),list_all[9].pop(0),list_all[10].pop(0),list_all[11].pop(0)])
            w.writerow([list_time[0].pop(0),list_all[0].pop(0),list_all[1].pop(0),list_all[2].pop(0),list_all[3].pop(0),list_all[4].pop(0),list_all[5].pop(0),list_all[6].pop(0),list_all[7].pop(0),list_all[8].pop(0),list_all[9].pop(0),list_all[10].pop(0),list_all[11].pop(0),list_all[12].pop(0),list_all[13].pop(0),list_all[14].pop(0),list_all[15].pop(0),list_all[16].pop(0),list_all[17].pop(0),list_all[18].pop(0),list_all[19].pop(0),list_all[20].pop(0),list_all[21].pop(0),list_all[22].pop(0),list_all[23].pop(0),list_all[24].pop(0),list_all[25].pop(0),list_all[26].pop(0),list_all[27].pop(0),list_all[28].pop(0),list_all[29].pop(0)])
                
