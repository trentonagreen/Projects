import sys
class StackMachine:
    def __init__(self):
        self.tokens = []
        self.memory = [None] * 5
        self.currentLine = 0

    def Executions(self, tokens):                    
        self.currentLine = self.currentLine + 1
        leng = len(self.tokens)

        # if the first token is push append the number to tokens list
        if(tokens[0] == 'push'):
            self.tokens.append(tokens[1])
            return None

        # if there is something in list print the last value, pop, then return
        # else the list is empty, raise error
        if(tokens[0] == 'pop'):
            if(leng != 0):
                last = self.tokens[-1]
                print(last)
                return self.tokens.pop()
            else:
                raise IndexError('Invalid Memory Access')
        
        # if the list does not contain at least 2 elements raise error
        # pop twice and set tmp values for each
        # add tmp values and push on stack
        if(tokens[0] == 'add'):
            if(leng < 2):
                raise IndexError('Invalid Memory Access')
            tmp1 = int(self.tokens.pop())
            tmp2 = int(self.tokens.pop())
            ans = tmp1 + tmp2
            self.tokens.append(ans)
            return None

        # if the list does not contain at least 2 elements raise error
        # pop twice and set tmp values for each
        # subtract tmp values and push on stack
        if(tokens[0] == 'sub'):
            if(leng < 2):
                raise IndexError('Invalid Memory Access')
            tmp1 = int(self.tokens.pop())
            tmp2 = int(self.tokens.pop())
            ans = tmp1 - tmp2
            self.tokens.append(ans)
            return None

        # if the list does not contain at least 2 elements raise error
        # pop twice and set tmp values for each
        # multiply tmp values and push on stack
        if(tokens[0] == 'mul'):
            if(leng < 2):
                raise IndexError('Invalid Memory Access')
            tmp1 = int(self.tokens.pop())
            tmp2 = int(self.tokens.pop())
            ans = tmp1 * tmp2
            self.tokens.append(ans)
            return None

        # if the list does not contain at least 2 elements raise error
        # pop twice and set tmp values for each
        # divide tmp values and push on stack
        if(tokens[0] == 'div'):
            if(leng < 2):
                raise IndexError('Invalid Memory Access')
            tmp1 = int(self.tokens.pop())
            tmp2 = int(self.tokens.pop())
            ans = tmp1 / tmp2
            # convert ans to int not float
            self.tokens.append(int(ans))
            return None

        # if the list does not contain at least 2 elements raise error
        # pop twice and set tmp values for each
        # mod tmp values and push on stack
        if(tokens[0] == 'mod'):
            if(leng < 2):
                raise IndexError('Invalid Memory Access')
            tmp1 = int(self.tokens.pop())
            tmp2 = int(self.tokens.pop())
            ans = tmp1 % tmp2
            self.tokens.append(ans)
            return None
    
        # # if the list does not contain at least 2 elements raise error
        # pop twice and set tmp values for each
        # if the first tmp value is zero
        # add the second tmp value to currentLine property
        # else return None
        if(tokens[0] == 'skip'):
            if(leng < 2):
                raise IndexError('Invalid Memory Access')
            tmp1 = int(self.tokens.pop())
            tmp2 = int(self.tokens.pop())

            if(tmp1 == 0):
                self.currentLine = self.currentLine + tmp2
                return None
            else:
                return None

        # saves a value into a memory list
        # if the list isnt empty save the value and pop off the stack
        # else raise error
        if(tokens[0] == 'save'):
            location = tokens[1]
            if(leng != 0):
                save = self.tokens.pop()
                self.memory[int(location)] = save
                return None
            else:
                raise IndexError('Invalid Memory Access')

        # get a saved value a push it on the stack
        if(tokens[0] == 'get'):
            location = tokens[1]
            if(location != None):
                get = self.memory[int(location)]
                self.tokens.append(get)
                return None
            else:
                raise IndexError('Invalid Memory Access')
