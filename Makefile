mine.out : decoder.o encoder.o encoderRunner.o BinaryHeap.o  
	g++ -ansi -Wall -g -o mine.out decoder.o encoder.o encoderRunner.o BinaryHeap.o

decoder.o : decoder.cpp decoder.h 
	g++ -ansi -Wall -g -c decoder.cpp

encoder.o : encoder.cpp encoder.h 
	g++ -ansi -Wall -g -c encoder.cpp

BinaryHeap.o : BinaryHeap.cpp BinaryHeap.h
	g++ -ansi -Wall -g -c BinaryHeap.cpp

encoderRunner.o : encoderRunner.cpp CPUTimer.h encoder.h decoder.h 
	g++ -ansi -Wall -g -c encoderRunner.cpp

clean : 
	rm -f mine.out decoder.o  encoder.o  encoderRunner.o  BinaryHeap.o  
