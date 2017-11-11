import lib as l
import pandas as pd
import numpy as np

y_train = []
y_test = []
trainNum = 0
testNum = 0

with open('../train.out') as file:
	for i in file.readlines():
		y_train.append(int(i))
		trainNum += 1
with open('../test.out') as file:
	for i in file.readlines():
		y_test.append(int(i))
		testNum += 1

bag = []
index = 0
with open('../train.in') as file:
	for line in file.readlines():
		words = l.text2array(line)
		for word in words:  
			if(not word in bag):
				bag.append(word)
		index += 1

assert(index==trainNum)

idx = 0
x_train = pd.DataFrame(0.0,index=range(trainNum),columns=bag)
with open('../train.in') as file:
	for line in file.readlines():
		words = l.text2array(line)
		for word in words:  
			x_train.iloc[idx][word] += 1.0/len(words)
		idx += 1

x_test = pd.DataFrame(0.0,index=range(testNum),columns=bag)
idx = 0
with open('../test.in') as file:
	for line in file.readlines():
		words = l.text2array(line)
		for word in words:
			if(word in bag):
				x_test.iloc[idx][word] += 1.0/len(words)
		idx += 1

def sim(a,b):
	return np.sum(np.multiply(a,b))/(np.sqrt(np.sum(np.square(a)))*np.sqrt(np.sum(np.square(a))))

y_p = []
correct = 0
for idx_test in x_test.index:
	max = 0.0
	for idx_train in x_train.index:
		similarity = sim(x_test.loc[idx_test].values,x_train.loc[idx_train].values)
		if(similarity > max):
			max = similarity
			yi = y_train[idx_train]
	y_p.append(yi)
	if(yi == y_test[idx_test]):
		correct += 1
	print('{}/{} : {} | {}'.format(idx_test,testNum,bool(yi==y_test[idx_test]),correct/(idx_test+1.0)))


idx = 0
correct = 0
with open('ACC','w') as fout:
	for yi in y_p:
		fout.write(str(yi)+'\n')
		if(yi == y_test[idx]):
			correct += 1
		idx += 1
	
acc = correct*1.0/testNum
print(acc)


