# CS530Assignment1

This assignment is broken up between 3 parts.

prog1_1.c
    This program takes a SINGLE command line argument file. This file is read in 
as binary. Then the program will calculate a CRC32 checksum of the file and
print out the value as an 8 digit hex.
    
    Example Compilation:
        gcc prog1_1.c -o prog1_1
    
    Example Output:
        ./prog1_1 hello
        > Assignment #1-1, Trenton Green, trenton.green@sbcglobal.net
        > 4652481b

prog1_2.h
    This header file contains two structs. One for the Elf Header and one for 
the Section Header. This also contains the definitions of the two functions in
computing the CRC32 checksum. crc32_Compute and crc32ComputeBuff. Structs and
variable names were based off:
    https://en.wikipedia.org/wiki/Executable_and_Linkable_Format

prog1_2.c
    This program takes a SINGLE command line arguement FILE. This program will
then calcualte the CRC32 checksum of ONLY the program header.

prog1_3.c
    This program takes TWO command line arguments, a FILE and SECTION_NAME.
Then the program will calculate a CRC32 checksum of the section row of the 
SECTION_NAME. If given only ONE command line argument it will call prog1_2.
    
    Example Compilation:
        gcc prog1_3.c prog1_2.c -o prog1_3
    
    Example Output:
        ./prog1_3 hello
        > Assignment #1-2, Trenton Green, trenton.green@sbcglobal.net
        > fb93e9b0
        ./prog1_3 hello .shstrtab
        > Assignment #1-3, Trenton Green, trenton.green@sbcglobal.net
        > 6ecaabeb

Pictures of example compilation are also attatched. As well as the 'hello' file
used in example outputs.
