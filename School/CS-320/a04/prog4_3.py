import sys
import prog4_1 as tp
import prog4_2 as sm

def main():
    print('Assignment #4-3, Trenton Green, trenton.green@sbcglobal.net')
    count = 0
    data = []
    stack = sm.StackMachine()
    
    file = open(sys.argv[1], 'r')

    # data is a list of tokenized values for each line
    data = [tp.Tokenize(line) for line in file]
    
    # check for each token in data against the Parser
    for tok in data:
        tp.Parse(tok)

    count = len(data)

    # while the currentLine property of the stack is less than count
    # execute input from data list
    # if at any time there is any error it will print the error and its location
    # will print if program ran with no errors
    try:
        while(stack.currentLine < count):
            if(stack.currentLine < 0):
                print("Trying to execute invalid: " + str(stack.currentLine))
            else:
                stack.Executions(data[stack.currentLine])          
        print('Program terminated correctly')

    except IndexError:
        errorL = stack.currentLine
        errorT = data[stack.currentLine -1]
        print("Line " + str(errorL) + ": " + "'" + str(errorT) + "'" + " caused Invalid Memory Access")  

main()