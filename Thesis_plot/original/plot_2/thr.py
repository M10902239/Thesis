import csv
import numpy as np
import matplotlib.pyplot as plt; 

font2 = {'family' : 'Times New Roman',  
         'weight' : 'normal',  
         'size'   : 15,  
        }
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
            ThrList.append((float(line[1])+float(line[2])+float(line[3]))/3)
    return ThrList

def getThrList2(file):
    with open(file) as f:
        list_of_rows1 = list(csv.reader(f, delimiter=','))
        zipped1 = list_of_rows1[6:-1]
        ThrList = []
        for line in zipped1:
            ThrList.append((float(line[4])+float(line[5])+float(line[6]))/3)
    return ThrList

def getDelayList(file):
    with open(file) as f:
        list_of_rows1 = list(csv.reader(f, delimiter=','))
        zipped1 = list_of_rows1[6:-1]
        delayList = []
        for line in zipped1:
            delayList.append(float(line[4]))
    return delayList

def getsnrList(file,pos):
    with open(file) as f:
        list_of_rows1 = list(csv.reader(f, delimiter=','))
        zipped1 = list_of_rows1[6:-1]
        snrList = []
        for line in zipped1:
            snrList.append(float(line[pos]))
    return snrList

thr_list1 = []
thr_list2 = []

snr_list1 = []
snr_list2 = []
time_list = []

plt.rcParams.update({'font.family':'Times New Roman'})
if __name__ == "__main__":

    path = "../data/1_thr.csv"
    time_list=(getTimeList(path))
    thr_list1=(getThrList(path))
    thr_list2=(getThrList2(path))
    snr_list1 = (getsnrList(path,7))
    snr_list2 = (getsnrList(path,8))

    fig,ax=plt.subplots(dpi=500)    
    plt.rc('font',family = 'Times New Roman')
    line4 = ax.plot(time_list, thr_list1,"-x",color='darkblue',label='Move-Throughput')
    line3 = ax.plot(time_list, thr_list2,"-x",color='yellowgreen',label='Not move-Throughput')
    ax.set_ylabel('Throughput (Mbps)',color='black',fontsize = 15)

    # ax.set_ylim([0, 1200])
    ax.tick_params(axis='y',labelcolor='black')

    ax2=ax.twinx()
    line1 = ax2.plot(time_list, snr_list1,"-",color="plum",label='Move-SNR')
    line2 = ax2.plot(time_list, snr_list2,"-",color="skyblue",label='Not move-SNR')
    ax.set_xlabel('Time (s)',color='black',fontsize=15)
    ax2.set_ylabel('SNR (dB)',color='black',fontsize = 15)
    ax2.set_ylim([-5, 25])
    ax2.tick_params(axis='y',labelcolor='black')

    
    total_line = line4 + line3 + line1 + line2
    labs = [l.get_label() for l in total_line]
    plt.legend(total_line,labs,bbox_to_anchor=(0.5, 1.2),loc="upper center", ncol=2,frameon=False,fontsize = 13)
    plt.savefig("SNR_Thr.jpg")

# blue darkblue skyblue blueviolet royalblue
# red  darkred indianred
# orange orangered

#Date: 2021.Sep.13 
#Editor: Xie Meng_Hua

