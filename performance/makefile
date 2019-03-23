all:
	make clean
	make run

run:
	g++ -Wall mutex.cpp -o mutex.o -lpthread -std=c++11
	./mutex.o
	g++ -Wall busy_wait.cpp -o busy_wait.o -lpthread -std=c++11
	./busy_wait.o
	g++ -Wall condition_variable.cpp -o condition_variable.o -lpthread -std=c++11
	./condition_variable.o
	g++ -Wall barrier.cpp -o barrier.o -lpthread -std=c++11
	./barrier.o
clean:
	rm -f *.o

	

