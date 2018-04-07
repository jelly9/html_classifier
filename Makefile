ROOTPATH=$(shell pwd)
INCLUDE=$(ROOTPATH)/lib/include
LIB=$(ROOTPATH)/lib/lib
FLAGS=#-D_DEBUG_
CC=g++

#export LD_LIBRARY_PATH=/home/jelly/Code/bd/lib_gumbo/lib

main: main.o html_classifier.o common.o
	g++ -o $@ $^ -L$(LIB) -lgumbo

%.o:%.cpp
	g++ -c $< -I$(INCLUDE)
	
.PHONY:clean
clean:
	rm -f main *.o
