import random
def q3(N):
	temp=[]
	#wins=[]
	wins_list=[]
	for i in range(int(N/2)):
		temp.append(0)
		temp.append(1)
		#wins.append(0)
		#wins.append(0)
	#print(temp)
	#print(wins)

	num_perm=10 #number of permutation, that can change to large number such 10000000
	
	for k_perm in range(num_perm):
		wins=[]
		for i_intl in range(N):
			wins.append(0)	#initial a wins array to store result in one season

		for j_season in range(16):
			random.shuffle(temp)
			#print(temp,'result', j_season)


			#print(wins, i_intl)


			for i_wins in range(N):
				#print(i_wins)
				if temp[i_wins]==1:
					wins[i_wins]+=1
		#print(wins)
		wins_list.append(wins)

	#print(wins_list)

	#find total # of wins of chompian team
	total_wins=0
	for i_array in range(num_perm): #each array in list
		max_wins=max(wins_list[i_array]) #find max number in each array in this list
		print(max_wins)
		total_wins+=max_wins #add all max number together

	print(total_wins)

	average_wins=float(total_wins)/float(num_perm)
	print(average_wins)
	return(average_wins)


q3(8)
