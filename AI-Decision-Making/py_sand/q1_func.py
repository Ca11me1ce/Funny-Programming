##########################
items = [1, 1, 0, 0]  
def q1(items):
	def perm(items, n=None):  
	    if n == None:  
		n = len(items)  
	    for i in xrange(len(items)):  
		v = items[i: i+1]  
		if len(items) == 1:  
		    yield v  
		else:  
		    rest = items[:i] + items[i+1:]  
		    for p in perm(rest, n-1):  
		        yield v + p  
		  
		  

	for a in perm(items):  
		print('--')
	    	print (a)
