all: 
	g++ -o simhash.server -O3 -DLOGGER_LEVEL=LL_INFO -Wall -g -I./submodules/husky/include -I./submodules/simhash/include -I./submodules/simhash/submodules/cppjieba/include/ -I./submodules/simhash/submodules/cppjieba/deps/limonp/include/ simhash_server.cpp -lpthread
osx:
	g++ -o simhash.server -O3 -DLOGGER_LEVEL=LL_INFO -Wall -g -std=c++11 -I./include -I./include/CppJieba/ simhash_server.cpp -lpthread
clean: 
	rm -f *.o *.a simhash.server
