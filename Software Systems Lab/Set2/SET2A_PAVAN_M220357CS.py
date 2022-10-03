import pandas as pd
import numpy as np

#program-3

df=pd.read_csv("Student_marks.csv")


for i in df.columns:
	if i in ['math score','reading score','writing score']:
		df[i].replace([np.nan,""], df[i].mean(),inplace=True)


def student_stat(student_df):
	groups=student_df.groupby("group")
	tableData=[]
	for group,group_df in groups:
		group_len=len(group_df.index)
		i='math score'
		tableData.append([group[-1],
			group_df[i].mean(),
			group_df[i].std(),
			round(len(group_df[group_df[i]>50])/group_len,4)])
	return tableData

table=pd.DataFrame(student_stat(df),columns=["Group","Mean math score","Stan. Dev. math score","Prob_scoring above 50_maths"])
print(table.to_string(index=False))