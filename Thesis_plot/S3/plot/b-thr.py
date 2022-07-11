from cProfile import label
import csv
#from re import A
from time import time
import numpy as np
import matplotlib.pyplot as plt; 
import sys
from scipy import stats



#FILE = "test.txt"
list_all = []
unused_list = []
thr_list=[]
timelist = [7,11,15,19,23]
NC_list = []
PD_list = []

NC_list_std = []
PD_list_std = []

people = 4
people2 = 8

# way = sys.argv[1] ## people
# input1 = sys.argv[2] ## people
# time = int(input1)


def getunusedList(file):
	with open(file) as f1:
		list_of_rows2 = list(csv.reader(f1, delimiter=','))
		ThrList = []
		unused=[]
		for line in list_of_rows2:
			ThrList.append(float(line[2]))
		for min in range(0,9,1):
			unused.append((np.argsort(ThrList)[min])+1)
	return unused

def getAvgList(file,unused_list):
	with open(file) as f:
		list_of_rows1 = list(csv.reader(f, delimiter=','))
		a=0
		AvgList = []	
        # alist =[]
	for line in list_of_rows1:
			a+=1
			if not (a in unused_list):
				AvgList.append(float(line[2]))
				# print(line[2])
	return np.mean(AvgList)

def getstdList(file,unused_list):
	with open(file) as f:
		list_of_rows1 = list(csv.reader(f, delimiter=','))
		a=0
		AvgList = []	
        # alist =[]
	for line in list_of_rows1:
			a+=1
			if not (a in unused_list):
				AvgList.append(float(line[2]))
				# sum1+= float(line[2])
	# print(AvgList)
	return np.std(AvgList)

    
if __name__ == "__main__":
	for i in range (0,5,1):
		ThrFILE = "../NC_15ms/%s/%s/1_thr_settle.csv" %(people,timelist[i]) #give the path
		unused_list = getunusedList(ThrFILE)
		# print(unused_list)
		NC_list.append(getAvgList(ThrFILE,unused_list)) ## get all seed
		NC_list_std.append(getstdList(ThrFILE,unused_list))
	
	for i in range (0,5,1):
		ThrFILE = "../PD_15ms/%s/%s/1_thr_settle.csv" %(people,timelist[i]) #give the path
		unused_list = getunusedList(ThrFILE)
		# print(unused_list)
		PD_list.append(getAvgList(ThrFILE,unused_list)) ## get all seed
		PD_list_std.append(getstdList(ThrFILE,unused_list))

	fig,ax=plt.subplots()
	plt.figure(dpi=500)
	plt.rc('font',family = 'Times New Roman')
	width = 0.1
	x=np.arange(len(timelist)) 
	plt.bar(x-1.5*width, (PD_list), width, color='steelblue',label = 'BeamTOP-%s'%people,yerr = PD_list_std, error_kw = {'ecolor' : '0.1', 'capsize' :3},hatch="o")
	plt.bar(x-0.5*width, (NC_list), width, color='peru',label = 'RLNC-%s'%people,yerr = NC_list_std, error_kw = {'ecolor' : '0.1', 'capsize' :3},hatch="o")
	
	NC_list = []
	PD_list = []
	NC_list_std = []
	PD_list_std = []

	for i in range (0,5,1):
		ThrFILE = "../NC_15ms/%s/%s/1_thr_settle.csv" %(people2,timelist[i]) #give the path
		unused_list = getunusedList(ThrFILE)
		# print(unused_list)
		NC_list.append(getAvgList(ThrFILE,unused_list)) ## get all seed
		NC_list_std.append(getstdList(ThrFILE,unused_list))
	
	for i in range (0,5,1):
		ThrFILE = "../PD_15ms/%s/%s/1_thr_settle.csv" %(people2,timelist[i]) #give the path
		unused_list = getunusedList(ThrFILE)
		# print(unused_list)
		PD_list.append(getAvgList(ThrFILE,unused_list)) ## get all seed
		PD_list_std.append(getstdList(ThrFILE,unused_list))

	plt.bar(x+0.5*width, (PD_list), width, color='steelblue',label = 'BeamTOP-%s'%(people2),yerr = PD_list_std, error_kw = {'ecolor' : '0.1', 'capsize' :3})
	plt.bar(x+1.5*width, (NC_list), width, color='peru',label = 'RLNC-%s'%(people2),yerr = NC_list_std, error_kw = {'ecolor' : '0.1', 'capsize' :3})
	

	plt.xlabel('$T_{BM}$ (ms)',color='black',fontsize = 15)
	plt.ylabel('Goodput (Mpbs)',color='black',fontsize = 15)

	plt.xticks(range(len(timelist)),timelist)
	# if(people == 8 ):
	plt.ylim(600,1900)
	# elif (people == 6):
	# 	plt.ylim(1500,1900)
	# elif (people == 4):
	# 	plt.ylim(1100,1300)

	# plt.grid(True)

	plt.tick_params(labelsize=13) # x,y
	plt.legend(bbox_to_anchor=(0.5, 1.15),loc="upper center", ncol=4,frameon=False,fontsize = 12)
	plt.tight_layout()
	plt.savefig("S3-bar-Tput-%s.jpg"%(people))
