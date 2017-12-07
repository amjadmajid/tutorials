basicFontSize = 20

def userInput():
	filename = input('Please enter the file name:')
	return (filename)

def outputFileName():
	return = "Formatted_"+userInput()

def fontSizeSpecifier(line):
	num = 0
	while(line[num] == '-'):
		num+=1
	return ( basicFontSize- 2*(num) )

def textWriter():
	file = userInput()
	outFile = outputFileName()
	open(outFile, 'w')
	for line in open(file):
		lineFontSize = fontSizeSpecifier(line)
		outFile.write(line)




