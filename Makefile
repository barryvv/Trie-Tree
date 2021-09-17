triedriver: node.cpp header.h trietest.cpp
	g++ -std=c++11 node.cpp trietest.cpp -o triedriver

run:
	./triedriver <test01.in> file01.out
	./triedriver <test02.in> file02.out
	./triedriver <test03.in> file03.out
	./triedriver <test04.in> file04.out
clean:
	rm triedriver
	rm file01.out
	rm file02.out
	rm file03.out
	rm file04.out