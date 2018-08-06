COUNT=0  
count2=0
#history=[1,1,0,0]
def q1(history):
	def perm(n,begin,end): 
		global COUNT  
		global count2
		if begin>=end: 
		    for i in range(0, end):
		        if n[i]==n[i-1]:
                            count2+=1
                           # print(n)
                            break#manage test statistic
		    #print (n)
		    COUNT +=1  
		else:  
		    i=begin  
		    for num in range(begin,end):  
		        n[num],n[i]=n[i],n[num]  
		        perm(n,begin+1,end)  
		        n[num],n[i]=n[i],n[num]  
	perm(history, 0, len(history))
	p_value=float(count2)/float(COUNT)
	print('the p value is: ')
	print(p_value)
	return p_value

history=[1,0,0,1]  
q1(history)
#perm(n,0,len(n))  
#print (COUNT)  
#print(count2)
