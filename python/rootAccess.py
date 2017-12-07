#!/usr/bin/python3

""" 
restricting the writing privileges to a file through this script to only root users
"""

import sys, os

if not so.geteuid()==0: # check if the user if not root
	sys.exit("\nOnly root can write to /etc/hosts\n") # exit script execution
print(sys.argv[1]) # for debugging 

hosts=open("/etc/hosts", "a") # open a file
hosts.write(sys.argv[1] + os.linesep) # append to the file
hosts.close() # close the file
print("\nWritten "+ sys.argv[1] +" to /etc/hosts\n") # output a message to the user 