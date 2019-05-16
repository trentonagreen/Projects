Trenton Green 
trenton.green@sbcglobal.net

prog2_1.hpp/.cpp
A C++ tokenizer class. This class has four public methods: constructor, destructor, Tokenize, and GetTokens.
The Tokenize function takes a string as input and will tokenize it. The valid tokens are:
    push, pop, add, sub, mul, div, mod, skip, save, get, and any integer
The GetTokens function retrives input tokens from Tokenize in a queue. 
There is also a private boolean function called isNumber which takes a string input and checks if it a number.

prog2_2.cpp
Driver program for prog2_1. Takes a single command line argument and Tokenize each line of file. Print error if there
was an error in Tokenization. If no error driver correctly prints strings in txt file.

prog2_3.hpp/.cpp
A Parser class. This has three public methods: constructor, destructor, and Parse. The Parse function takes a single
vector and validates the tokens.
    pop, add, sub, mul, div, mod, skip - should all be by themselves on a line 
    push, save, get - should be followed by an <int>
    
prog2_4
Driver program for prog2_1 and prog2_3. This reades through a text file and tokenizes and parses line by line.
If there is an error, it will print what the error is and the location. If there are no errors will print the contents
of the text file.

Running the programs:
    Compiling prog2_2
        g++ prog2_2.cpp prog2_1.cpp -o prog2_2
    Executing prog2_2
        ./prog2_2 test.txt
    Compiling prog2_2
        g++ prog2_4.cpp prog2_3.cpp prog2_1.cpp -o prog2_4
    Executing prog2_4
        ./prog2_2 test.txt        

    
