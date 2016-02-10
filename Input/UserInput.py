import winsound
morse_code = {
	"a" : [1,0],
	"b" : [1,0,0,0],
	"c" : [1,0,1,0],
	"d" : [0],
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
	"z" : [1,1,0,0]
}
morse_input = raw_input("Enter a word\n> ").lower()
morse_buffer = []
count = 0
while count < len(morse_input):
	morse_buffer.append(morse_code[morse_input[count]])
	count += 1
count = 0
innercount = 0
while count < len(morse_buffer):
	currentlength = len(morse_buffer[count])
	while innercount < currentlength:
		if morse_buffer[count][innercount] == 0:
			winsound.beep(750, 350)
		elif morse_buffer[count][innercount] == 1:
			winsound.beep(750,1000)
		innercount += 1
	innercount = 0
	count += 1




	
	

