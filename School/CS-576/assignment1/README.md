# CS576Assignment1

This assignment is broken up between 2 parts.

server.c
    TCP server that recieves string input from a user client. Upon recieving
the input, the server will find the next ASCII character for each character
in the string. After finding the new ASCII string, sends it back to client.

    Example Compilation:
        gcc server.c -o server

client.c
    TCP client that takes in user input and sends it to the server. After
recieving data back from the server, it will print the new ASCII string.

    Example Compilation:
        gcc client.c -o client -lreadline

    Example Output:
        ./client
        > Type something: Trenton Green
        > recieved: Usfoupo!Hsffo

Pictures of example compilation are also attatched.

References for this project other than slides/book include:
  https://gist.github.com/suyash/2488ff6996c98a8ee3a84fe3198a6f85
