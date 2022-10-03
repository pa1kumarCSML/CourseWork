import pandas as pd
import numpy as np


df=pd.read_csv("USUnemployment.csv")
dictyr=dict()

years=df["Year"]
cols=df.columns
newdf=df[cols[1:]]
npd=np.array(newdf)
#npd1=np.array(newdf)
npd=npd.T
newdf=pd.DataFrame(npd)

for i in newdf.columns:
        newdf[i].replace([np.nan], newdf[i].mean(),inplace=True)
   
npd=np.array(newdf)
npd=npd.T
df=pd.DataFrame(npd,columns=cols[1:])    
        
def custom_sum(axs):
    return axs.mean()

df["mean"]=df.apply(custom_sum, axis=1)
df["Year"]=years
print(df)


dictemp=dict()

for i in df.index:
    dictemp[df.loc[i][-1]]=df.loc[i][-2]

temp=dictemp.values()
sum=0
for i in temp:
    sum+=i
master_mean=sum/len(temp)
print(sum)
print(master_mean)

for i in dictemp.keys():
    dictemp[i]=master_mean

print(dictemp)
    
#covariance    
#print(df["Year"][])
#print(npd1[0],npd1[1])

print("covariance")

print(np.cov(npd1[1991-1948],npd1[2000-1948]))

index=0
val=[]
for i in range(len(npd1)):
    val.append(1000)
    for j in npd1[i]:
        if val[i]>j:
            val[i]=j

valu=1000
for i in range(len(val)):
    if valu>val[i]:
        index=i
        valu=val[i]



print("min year:" +str(df.loc[index]["Year"]))

index1=0
val=[]
for i in range(len(npd1)):
    val.append(0)
    for j in npd1[i]:
        if val[i]<j:
            val[i]=j

valu=0
for i in range(len(val)):
    if valu<val[i]:
        index1=i
        valu=val[i]




print("max year :" +str(df.loc[index1]["Year"]))