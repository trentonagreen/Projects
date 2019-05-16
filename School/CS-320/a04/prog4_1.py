# create 3 lists, one for valid tokens, one for tokens with only 1 command, one for tokens with 2 commands
_validTokens = ['push', 'pop', 'add', 'sub' ,'mul', 'div', 'mod', 'skip', 'save', 'get']
oneCmds = ['pop', 'add', 'sub', 'mul', 'div', 'mod', 'skip']
twoCmds = ['push', 'save' , 'get']

def Tokenize(s):
    data = []
    sp = s.split()      
    invalid = [x for x in sp if not isValid(x)]

    # if input string is not a valid token, raise a ValueError
    if len(invalid) != 0:
        raise ValueError("Unexpected Token: " + invalid[0])
    
    # if token is valid appened it to a list and return
    i = 0
    while(i < len(sp)):
        data.append(sp[i])
        i = i + 1
    return data

# function to check if input string is a valid token
def isValid(s):
    return s in _validTokens or isNumber(s)

# function to check if input string is a number
def isNumber(s):
    try:
        int(s)
        return True
    except ValueError:
        return False

def Parse(tokens):
    # if the len of the tokens list is 2 goto twoPartCommands 
    # else goto onepart
    if len(tokens) == 2:
        twoPartCmds(tokens)
    else:
        onePartCmds(tokens)
    
def onePartCmds(tokens):
    s = ''.join(tokens[0])
    
    # if the string is in onecommands list return 
    # else raise error
    if s in oneCmds:
        return tokens
    else:
        raise ValueError("Parsing Error: " + s)

def twoPartCmds(tokens):
    s1 = ''.join(tokens[0])
    s2 = ''.join(tokens[1])

    # if the first string is in twocommands list and the second string is a number return
    # else raise error
    if s1 in twoCmds and isNumber(s2):
        return tokens
    else:
        raise ValueError("Parsing Error: " + s1 + " " + s2)
