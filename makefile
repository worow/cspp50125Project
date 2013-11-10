CC=g++
FLAGS= -Wall -ansi

all: matchingEngine tradePub

matchingEngine: match.o SharedMemory.o BinarySems.o
	$(CC) $(FLAGS) -o matchingEngine match.o SharedMemory.o BinarySems.o
	

tradePub: tradepublisher.o SharedMemory.o BinarySems.o
	$(CC) $(FLAGS) -o tradePub tradepublisher.o SharedMemory.o BinarySems.o

match.o: match.cpp SharedMemory.h BinarySems.h
	$(CC) $(FLAGS) -c match.cpp -I.

tradepublisher.o: tradepublisher.cpp SharedMemory.h BinarySems.h
	$(CC) $(FLAGS) -c tradepublisher.cpp -I.
	
SharedMemory.o: SharedMemory.cpp SharedMemory.h
	$(CC) $(FLAGS) -c SharedMemory.cpp -I.
	
BinarySems.o: BinarySems.cpp BinarySems.h
	$(CC) $(FLAGS) -c BinarySems.cpp -I.


	

clean:
	\rm -f *.o matchingEngine tradePub *~