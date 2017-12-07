from datetime import datetime
from datetime import date
from datetime import time

"""
The code shows how to get date and time (basic)
"""

def main():
	 today = date.today() # only date
	 now = datetime.now() # date and time

	 weekday = date.weekday(now)
	 time = datetime.time(now)
	 print today
	 print today.day , today.month , today.year

	 print now
	 print weekday
	 print time
	 print time.hour , time.minute , time.second 

if __name__=="__main__":
	main()