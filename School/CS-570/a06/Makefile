
CXX = g++  # C++ compiler
CXXFLAGS = -g -c  # C++ flags

# Replace test_suite.C with your code

disksim : BlockDevice.o main.o hexdump.o linkedlist.o
	$(CXX) -o disksim -g BlockDevice.o main.o hexdump.o linkedlist.o

BlockDevice.o : BlockDevice.C BlockDevice.h

hexdump.o : hexdump.C hexdump.h

linkedlist.0: linkedlist.C linkedlist.h

main.o : main.C BlockDevice.h

clean :
	rm *.o
