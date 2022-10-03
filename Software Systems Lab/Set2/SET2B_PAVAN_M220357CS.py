import pandas as pd
import numpy as np
from numpy.linalg import norm

lists=[]
vocab_set=set()
list_dicts=[]

def tokenizer(fileName):
	file=open(fileName, "r")
	doc_str=''
	doc_str = ''.join(letter for letter in file.read() if (letter.isalnum() or letter==" " or letter=="\n"))

	#otherway:
	# for char in file.read():
	# 	if char.isalnum() or char==" ":
	# 		doc_str+=char
	# 	if char=="\n":
	# 		doc_str+=" "

	file.close()
	return doc_str.lower().split()

#strings formating
for i in range(4):
	lists.append(tokenizer("doc"+str(i+1)+".txt"))

#vocab set
for list in lists:
	for item in list:
		vocab_set.add(item)

#sorting the vocab set.		
vocab_set=sorted(vocab_set)

#vocab dict of each list.
for i in range(4):
	vocab_dict=dict()
	for token in vocab_set:
		# if token in lists[i]:
		# 	if (vocab_dict[token])>0:
		# 		vocab_dict[token]+=1
		# 	else:
		# 		vocab_dict[token]=1
		vocab_dict[token]=lists[i].count(token)
	list_dicts.append(vocab_dict)

tableData=[]

for i in range(4):
	listData=[]
	for j in list_dicts[i].values():
		listData.append(j)
	tableData.append(listData)


#Building DataFrame

df=pd.DataFrame(tableData,columns=vocab_set)

print(df)

df.to_csv("BoW.csv",index=False)

#cosine Distance matrix

matrix = []
for i in df.index:
    for j in df.index:
        ADotB = np.dot(np.array(df.loc[i]),np.array(df.loc[j]))
        ACrossB = norm(np.array(df.loc[i]))*norm(np.array(df.loc[j]))
        matrix.append(ADotB/ACrossB)

print(np.array(matrix).reshape(4,4))
