all: 
	g++ -o simhash.server -O3 -DLOGGER_LEVEL=LL_INFO -Wall -g -I./include -I./include/CppJieba/ simhash_server.cpp -lpthread
osx:
	g++ -o simhash.server -O3 -DLOGGER_LEVEL=LL_INFO -Wall -g -std=c++11 -I./include -I./include/CppJieba/ simhash_server.cpp -lpthread
clean: 
	rm -f *.o *.a simhash.server
