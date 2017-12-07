 def bSearch(L, e, low, high):
 	""" 
 	L: is a sorted list
	e: is the targeted number 
	low: is the lowest value of the list
	hight: is the highest value of list
 	"""
 	if len(L) == 0:					# empty list
	 	return False 
	 	
	 if high == low:					# if the list is one element 
	 	return L[low] == e

	 mid = low + int((high - low)/2)

	 if L[mid] == e:					# If the midpoint is the targeted number 
	 	return True
	 if L[mid] > e:						# check if the number is in the lower half of the list
	 	return bSearch(L, e, low, mid - 1)
	 else:								# otherwire it is in the higher of the list
	 	return bSearch(L, e, mid + 1, high)


