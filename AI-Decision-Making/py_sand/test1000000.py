
#Question 1
#import numpy as np
import random
def q1(history):
	n=10

	#find test stat of history
	test_stat=0
	perm_list=[]
	for i in range(0, len(history)):
		if i-1<0:
			continue
			#break
		if history[i]==history[i-1]:
			test_stat+=1
	print('test stat:',test_stat)

	#assign random list
	#perm_list=np.random.randint(0,2,(n, len(history)))
	##########################################

	for j in range(n-1):
		random.shuffle(history)
		print('--',history)
		perm_list.append(history)
	
########################################################
	print(perm_list)

	#test stat permutation

	perm_num=0
	for i_perm in range(n):
		perm_test_stat=0
		for i_array in range(len(history)):
			if i_array-1<0:
				continue
			if perm_list[i_perm][i_array]==perm_list[i_perm][i_array-1]:
				perm_test_stat+=1
		if perm_test_stat>=test_stat:
			print(i_perm, ':',perm_test_stat)
			perm_num+=1
	#test p value
	print('perm_num:',perm_num)
	print('n=',n)
	p_value=float(perm_num)/n
	print(p_value)
	return(p_value)
		
	
	

###################################

history=[1,2,3,4]
q1(history)

	
