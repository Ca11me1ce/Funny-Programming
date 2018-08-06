#Question 1
#import numpy as np
import random
def q1(history):
	n=10
	#find test stat of history
	test_stat=0
	#perm_list=[]
	for i in range(0, len(history)):
		if i-1<0:
			continue
			#break
		if history[i]==history[i-1]:
			test_stat+=1
	#print('test stat:',test_stat)
	#assign random list	
	perm_num=0
	for i_perm in range(n):
		random.shuffle(history)
		#print(history)
		clustering=0
		for i_array in range(len(history)):
			if i_array-1<0:
				continue
			if history[i_array]==history[i_array-1]:
				clustering+=1
		if clustering>=test_stat:
			#print('clustering:', clustering)
			perm_num+=1

	p_value=float(perm_num)/n
	print(p_value)
	return (p_value)


q1([1,0,0])
