def inclusive_range(*args):
	"""This function returns a range of numbers, like the range(num) 
	in python, but it is inclusive (it includes the num and not stops at num-1)
	"""

	args_len = len(args)

	if args_len <1: raise TypeError("args are required")
	elif args_len == 1:
		start = 0
		step = 1
		stop = args[0]
	elif args_len ==2:
		step = 1
		(start , stop) = args
	elif args_len == 3:
		(start , stop , step) = args
	else:
		raise TypeError("incluseive_range expected at most 3 args")
	i =  start
	while i <= stop:
		yield i 
		i += step