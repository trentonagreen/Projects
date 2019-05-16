Trenton Green
Trenton.green@sbcglobal.net

prog4_1.py
	This program has two main functions, Tokenize(string) and Parse(list). 
	Tokenize takes an input string and checks if it is valid. The valid strings are :
	push, pop, add, sub, mul, div, mod, save, get, and any integer. Parse takes a list input and checks
	if the tokens in the list are one part or two part commands. The one part commands are:
	pop, add, sub, mug, div, mod, skip. The two part commands are: push, save, get.

prog4_2.py
	This program is a StackMachine class. It’s only function is Execute(list). Execute takes a list 
	of tokens as input and depending on the token executes what is should do.
	    
	push # - pushes the # onto a stack
	pop - pops the top of the stack
	add - pops two values, adds them together and pushes answer
	sub - pops two values, subtracts them together and pushes answer
	mul - pops two values, multiplies them together and pushes answer
	div - pops two values, divides  them together and pushes answer
	mod - pops two values, mods them together and pushes answer
	skip - pops two values, if the first is 0 adjust currentLine property
	save # - pops and saves the popped value at # in memory
	get # - gets the save value at # in memory and pushes it 

prog4_3.py
	This is a driver program that utilizes both prog4_1 and prog4_2. 
	This takes the first command line argument and tokenizes and parses the file.
	If they raise no errors, while the currentLine of stack is less than the number of lines in file,
	it will execute the commands in the file. If there are any errors this program will print
	the location of the error and the token that caused it

HOW TO RUN
	Open terminal in directory:
		python3 prog4_3.py example.txt
		