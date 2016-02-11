import winsound #Import winsound library for winsound.Beep() function
import time #Import time library for time.sleep() function
morse_code = { #Dictionary containing each letter and their respective morse code
	"a" : [0,1],
	"b" : [1,0,0,0],
	"c" : [1,0,1,0],
	"d" : [1,0,0],
	"e" : [0],
	"f" : [0,0,1,0],
	"g" : [1,1,0],
	"h" : [0,0,0,0],
	"i" : [0,0],
	"j" : [0,1,1,1],
	"k" : [1,0,1],
	"l" : [0,1,0,0],
	"m" : [1,1],
	"n" : [1,0],
	"o" : [1,1,1],
	"p" : [0,1,1,0],
	"q" : [1,1,0,1],
	"r" : [0,1,0],
	"s" : [0,0,0],
	"t" : [1],
	"u" : [0,0,1],
	"v" : [0,0,0,1],
	"w" : [0,1,1],
	"x" : [1,0,0,1],
	"y" : [1,0,1,1],
	"z" : [1,1,0,0],
	" " : [2]
}
while True: #Loops program
	morse_input = input("Enter a word\n> ").lower() #Asks user for input
	morse_buffer = [] #Buffer for input
	count = 0
	while count < len(morse_input):
		morse_buffer.append(morse_code[morse_input[count]]) #Adds input to buffer and converts to morse code
		count += 1
	count = 0
	innercount = 0
	while count < len(morse_buffer):
		currentlength = len(morse_buffer[count])
		while innercount < currentlength:
			if morse_buffer[count][innercount] == 0:
				winsound.Beep(1000, 500) #Plays a dot
				time.sleep(0.2)
			elif morse_buffer[count][innercount] == 1:
				winsound.Beep(1000, 980) #Plays a dash
				time.sleep(0.1)
			elif morse_buffer[count][innercount] == 2:
				time.sleep(2.1) #Space
			innercount += 1
		innercount = 0
		count += 1
		time.sleep(1)



	
	

