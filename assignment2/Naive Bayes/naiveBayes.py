import lib as l


trainOut = []
trainNum = [0,0]

with open('../train.out') as file:
	for i in file.readlines():
		trainOut.append(int(i))
		if(int(i)):
			trainNum[1] += 1
		else:
			trainNum[0] += 1
#print('number of train samples: {}'.format(trainNum))


dic = {}
index = 0
with open('../train.in') as file:
	for line in file.readlines():
		c = trainOut[index]
		words = l.text2array(line)
		for word in words:  
			if(dic.has_key(word)):
				dic[word][c] += 1
			else:
				dic[word] = {0:0,1:0}
		index += 1

assert(index==trainNum[0]+trainNum[1])

totalNum = len(dic)
 
def P(word, author):
	if(not dic.has_key(word)):
		return 1.0/(trainNum[author]+2)
	else:
		return (dic[word][author]+1.0)/(trainNum[author]+2)

testOut = []
with open('../test.in') as fin, open('ACC','w') as fout1, open('CE','w') as fout2:
	for line in fin.readlines():
		words = l.text2array(line)
		a = trainNum[0]*1.0/(trainNum[0]+trainNum[1])
		b = 1-a
		for word in words:
			a *= P(word,0)
			b *= P(word,1)
		prob = b/(a+b)
		testOut.append(int(prob>0.5))
		fout2.write(str(prob)+'\n')
		fout1.write(str(int(prob>0.5))+'\n')

acc = 0
idx = 0
with open('../test.out') as file:
	for line in file.readlines():
		target = int(line)
		if(testOut[idx]==target):
			acc += 1
		idx += 1
	print(acc*1.0/idx)
