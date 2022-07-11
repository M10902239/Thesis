import csv
import numpy as np
import matplotlib.pyplot as plt; 
snr1list=[]
snr2list=[]
time1list=[]
time2list=[]


def getSNRList(file,pos):
    with open(file) as f:
        list_of_rows1 = list(csv.reader(f, delimiter=','))
        zipped1 = list_of_rows1[6:-1]
        snrList = []
        for line in zipped1:
            snrList.append(float(line[pos]))
    return snrList

def getTimeList(file):
    with open(file) as f:
        list_of_rows1 = list(csv.reader(f, delimiter=','))
        zipped1 = list_of_rows1[6:-1]
        TimeList = []
        for line in zipped1:
            TimeList.append(float(line[0]))
    return TimeList

if __name__ == "__main__":
    SNRFILE = '../0516rawdata/S1/seed55/S1/NC_15ms/8/2_overall.csv' #give the path
    snr1list.append(getSNRList(SNRFILE,10))
    snr2list.append(getSNRList(SNRFILE,11))
    time1list.append(getTimeList(SNRFILE))
    time2list.append(getTimeList(SNRFILE))

    fig,ax=plt.subplots()
    plt.figure(dpi=500)
    plt.rc('font',family = 'Times New Roman')

    plt.plot(time1list.pop(0),snr1list.pop(0),"-^",color="red",label='AP1',markersize=0.5)
    plt.plot(time2list.pop(0),snr2list.pop(0),"-x",color="dodgerblue",label='AP2',markersize=0.5)

    plt.xlabel('Time (s)',color='black',fontsize = 15)
    plt.ylabel('SNR (dB)',color='black',fontsize = 15)


    plt.tick_params(labelsize=13) # x,y
    plt.legend(bbox_to_anchor=(0.5, 1.15),loc="upper center", ncol=3,frameon=False,fontsize = 13)
    plt.savefig("SNR.jpg")
