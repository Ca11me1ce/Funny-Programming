#Question 1
import random
def q1(history):
	n=1000000
	#find test stat of history
	test_stat=0

	for i in range(0, len(history)):
		if i-1<0:
			continue
		if history[i]==history[i-1]:
			test_stat+=1

	#assign random list	
	perm_num=0
	for i_perm in range(n):
		random.shuffle(history)
		clustering=0
		for i_array in range(len(history)):
			if i_array-1<0:
				continue
			if history[i_array]==history[i_array-1]:
				clustering+=1
		if clustering>=test_stat:
			perm_num+=1

	p_value=float(perm_num)/n
	return (p_value)
    
#Question 2
def q2(p):
	q=1.0-p
	alpha=((2*p+5*q)-q)/p
	return (alpha)
    
#Question 3
def q3(N):
	temp=[]
	wins_list=[]
	for i in range(int(N/2)): 		#initialize temp to a list with same # of 1 and 0, that used to shuffle
		temp.append(0)
		temp.append(1)

	num_perm=1000000			#number of permutation, that can change to large number such 10000000
	for k_perm in range(num_perm):
		wins=[]
		for i_intl in range(N):
			wins.append(0)		#initial a wins array to store result in one season
		for j_season in range(16):
			random.shuffle(temp)
			for i_wins in range(N):
				if temp[i_wins]==1:
					wins[i_wins]+=1
		wins_list.append(wins)

	#find total # of wins of chompian team
	total_wins=0
	for i_array in range(num_perm):		 #each array in list
		max_wins=max(wins_list[i_array]) #find max number in each array in this list
		total_wins+=max_wins		 #add all max number together

	average_wins=float(total_wins)/float(num_perm)
	return(average_wins)
