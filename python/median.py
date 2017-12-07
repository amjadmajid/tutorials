def median(x):
	"""This function compute the median of a list of numbers.
	"""
	x.sort() # Sort the insert list
	y=None # so the y will be visible outside the if else suits
	if len(x) % 2 ==0:
		y= ( x[ int(len(x)/2 -1) ] + x[ int(len(x)/2) ] ) / 2.0 # length is index + 1
	else:
		y = x[ int( len(x) / 2 )]
	return y