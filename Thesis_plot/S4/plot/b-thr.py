from cProfile import label
import csv
import numpy as np
import matplotlib.pyplot as plt; 
import sys

#FILE = "test.txt"
list_all = []
list_all_std =[]
unused_list = []
thr_list=[]
namelist = ['Low','Medium','High']

NC_list = []
PD15_list = []
Cotag_list = []
PD_list = []

NC_list_std = []
PD_list_std = []
PD15_list_std = []
Cotag_list_std = []

# way = sys.argv[1] ## people
# input1 = sys.argv[2] ## people
# time = int(input1)


def getunusedList(file):
    with open(file) as f1:
        list_of_rows2 = list(csv.reader(f1, delimiter=','))
        ThrList = []
        unused=[]
        for line in list_of_rows2:
            ThrList.append(float(line[5]))
        for min in range(0,5,1):
            unused.append((np.argsort(ThrList)[min])+1)
    return unused

def getthrList(file,user,unused_list):
	with open(file) as f1:
		list_of_rows2 = list(csv.reader(f1, delimiter=','))
		ThrList = []
		a=0
		for line in list_of_rows2:
			a+=1
			if not (a in unused_list):
				ThrList.append(float(line[user]))
	return ThrList


def getstdList(file,user,unused_list):
	with open(file) as f1:
		list_of_rows2 = list(csv.reader(f1, delimiter=','))
		ThrList = []
		a=0
		for line in list_of_rows2:
			a+=1
			if not (a in unused_list):
				ThrList.append(float(line[user]))
	return np.std(ThrList)

if __name__ == "__main__":
	ThrFILE = "../NC_15ms/6/1_thr.csv"  #give the path
	unused_list = getunusedList(ThrFILE)
	list_all.append(getthrList(ThrFILE,4,unused_list))
	list_all.append(getthrList(ThrFILE,5,unused_list))
	list_all.append(getthrList(ThrFILE,6,unused_list))
	for j in range(0,3,1):
		NC_list.append(sum(list_all[j])/25)
		NC_list_std.append(np.std(list_all[j]))
	list_all = []

	ThrFILE = "../PD/6/1_thr.csv"  #give the path
	unused_list = getunusedList(ThrFILE)
	list_all.append(getthrList(ThrFILE,4,unused_list))
	list_all.append(getthrList(ThrFILE,5,unused_list))
	list_all.append(getthrList(ThrFILE,6,unused_list))
	for j in range(0,3,1):
		PD_list.append(sum(list_all[j])/25)
		PD_list_std.append(np.std(list_all[j]))
	list_all = []

	ThrFILE = "../PD_15ms/6/1_thr.csv"  #give the path
	unused_list = getunusedList(ThrFILE)
	list_all.append(getthrList(ThrFILE,4,unused_list))
	list_all.append(getthrList(ThrFILE,5,unused_list))
	list_all.append(getthrList(ThrFILE,6,unused_list))
	for j in range(0,3,1):
		PD15_list.append(sum(list_all[j])/25)
		PD15_list_std.append(np.std(list_all[j]))
	list_all = []

	ThrFILE = "../Cotag/6/1_thr.csv"  #give the path
	unused_list = getunusedList(ThrFILE)
	list_all.append(getthrList(ThrFILE,4,unused_list))
	list_all.append(getthrList(ThrFILE,5,unused_list))
	list_all.append(getthrList(ThrFILE,6,unused_list))
	for j in range(0,3,1):
		Cotag_list.append(sum(list_all[j])/25)
		Cotag_list_std.append(np.std(list_all[j]))
	list_all = []

	fig,ax=plt.subplots()
	plt.figure(dpi=500)
	plt.rc('font',family = 'Times New Roman')


	width = 0.15
	x=np.arange(len(namelist)) 
	plt.bar(x-1.5*width, (PD15_list), width, color='steelblue',label = 'BeamTOP',yerr = PD15_list_std, error_kw = {'ecolor' : '0.1', 'capsize' :3})
	plt.bar(x-0.5*width, (PD_list), width, color='purple',label = 'PD',yerr = PD_list_std, error_kw = {'ecolor' : '0.1', 'capsize' :3})
	plt.bar(x+0.5*width, (NC_list), width, color='peru',label = 'RLNC+BM',yerr = NC_list_std, error_kw = {'ecolor' : '0.1', 'capsize' :3})
	plt.bar(x+1.5*width, (Cotag_list), width, color='slategray',label = 'COTAG-based NC',yerr = Cotag_list_std, error_kw = {'ecolor' : '0.1', 'capsize' :3})


	plt.xlabel('User Group',color='black',fontsize = 15)
	plt.ylabel('Goodput (Mbps)',color='black',fontsize = 15)
	plt.xticks(range(len(namelist)),namelist)

	plt.tick_params(labelsize=13) # x,y
	plt.legend(bbox_to_anchor=(0.5, 1.15),loc="upper center", ncol=4,frameon=False,fontsize = 12)
	plt.savefig("S4-bar-Tput.jpg")

