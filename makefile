link: compile
	g++ -std=c++14 *.o -o test
compile: 
	g++ -std=c++14 -c test.cpp
	g++ -std=c++14 -c include/myvector
	