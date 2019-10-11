# Makefile for test program

CC = g++
CFLAGS = -Wall -c -g -fpermissive 

INC = -I.

test_class: test_class.cpp json_wrapper.o 
	$(CC) -Wall $(INC) -o test_class test_class.cpp json_wrapper.o 

json_wrapper.o: json_wrapper.cpp 
	$(CC) -Wall $(INC) -c json_wrapper.cpp 

clean:
	rm *.o
