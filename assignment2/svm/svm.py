import lib as l
from sklearn import svm
import pandas as pd

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

#train
print('training....')
clf = svm.SVC(C=0.8, kernel='rbf', gamma=15, decision_function_shape='ovr')
clf.fit(x_train, y_train)


print('predicting...')
print('accuracy in train set: {}'.format(clf.score(x_train, y_train)))

y_p = clf.predict(x_test)

idx = 0
correct = 0
with open('ACC','w') as fout:
	for yi in y_p:
		fout.write(str(yi)+'\n')
		if(yi == y_test[idx]):
			correct += 1
		idx += 1
	
acc = correct*1.0/testNum
print(acc) # 0.775
