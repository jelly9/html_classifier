ROOTPATH=$(shell pwd)
ALL_INCLUDE=$(ROOTPATH)/lib/include
ALL_LIB=$(ROOTPATH)/lib/lib
FLAGS=#-D_DEBUG_
CC=g++

#export LD_LIBRARY_PATH=/home/jelly/Code/bd/lib_gumbo/lib

main: main.o html_classifier.o
	g++ -o $@ $^ -L$(ALL_LIB) -lgumbo

%.o:%.cpp
	g++ -c $< -I$(ALL_INCLUDE)
	
.PHONY:clean
clean:
	rm -f main *.o
