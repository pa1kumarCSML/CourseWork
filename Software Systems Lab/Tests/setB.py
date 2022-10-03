import pandas as pd
import numpy as np


file = open('d1.txt')
msgA= file.read().lower()
file=open('d2.txt')
msgB=file.read().lower()

#print(msgA)
#print(msgB)


def getList(msg):
        lis=[]
        string=''
        for i in msg:
            if i.isalpha():
                string+=i
            else:
                if(len(string)>0):                    
                     lis.append(string)
                     string=''
        return lis        


#prog-1

listA=[]
listB=[]

listA=getList(msgA)
listB=getList(msgB)

#print(listA,listB)

lendiff =len(listA)-len(listB)

if(lendiff<0):
    lendiff=-1*lendiff
    
if lendiff!=0:
    if(len(listA)>len(listB)):
        for i in range(lendiff):
            listA.pop(-1)
    else:
        for i in range(lendiff):
            listB.pop(-1)

print(listA,listB)


#prog-2
vocab_set=set()
lists=[listA,listB]
list_dicts=[]


for list in lists:
	for item in list:
		vocab_set.add(item)

#sorting the vocab set.		
vocab_set=sorted(vocab_set)

#vocab dict of each list.
for i in range(2):
	vocab_dict=dict()
	for token in vocab_set:
		vocab_dict[token]=lists[i].count(token)
	list_dicts.append(vocab_dict)

tableData=[]

for i in range(2):
	listData=[]
	for j in list_dicts[i].values():
		listData.append(j)
	tableData.append(listData)


#Building DataFrame

df=pd.DataFrame(tableData,columns=vocab_set)

print(df.to_string(index=False))

df.to_csv("BoW.csv",index=False)


#prog-3

HMCodes=[]

for i in range(len(listA)):
    maxLen=max(len(listA[i]),len(listB[i]))
    minLen=min(len(listA[i]),len(listB[i]))
    if(listA[i]==listB[i]):# if codes as same
        HMCodes.append(0)
    elif (listA[i][0]!=listB[i][0]):# if initial char doesn't match
        HMCodes.append(maxLen)        
    else:                             #check till char doesn't match
        for j in range(minLen):
            if(listA[i][j]==listB[i][j]):
                continue
            else:
                HMCodes.append(maxLen-j)
                break
                        
print(HMCodes)































































