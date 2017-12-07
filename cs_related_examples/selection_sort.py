def selSort(L):
	"""
	Find the smallest element in the list and put it (swap it) in the first location, 
	Find the second element and put it (swap it) in the second locaiton, and so on. 
	
	"""
	for i in range(len(L) - 1):
		minIndx = i
		minVal= L[i]
		j = i + 1
		while j < len(L):
			if minVal > L[j]:
			minIndx = j
			minVal= L[j]
			j += 1
		temp = L[i]
		L[i] = L[minIndx]
		L[minIndx] = temp 