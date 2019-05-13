outputsuf = .out.txt

BRANCH = 2
LEVEL = 5
LIMIT = 10
ANS1 = 2147483647
ANS2 = -1

run: main checkdata
	./main data/$(BRANCH)-$(LEVEL)-$(LIMIT).txt 0 $(ANS1) $(ANS2)

main: main.o
	g++ -o main main.o -std=c++11 -O3

main.o: main.cpp
	g++ -c main.cpp -std=c++11 -O3

checkdata: gendata
ifeq (,$(wildcard data/$(BRANCH)-$(LEVEL)-$(LIMIT).txt ))
	./gendata $(BRANCH) $(LEVEL) $(LIMIT) > data/$(BRANCH)-$(LEVEL)-$(LIMIT).txt
endif

gendata: gendata.o
	g++ -o gendata gendata.o -std=c++11 -O3

gendata.o: gendata.cpp
	g++ -c gendata.cpp -std=c++11 -O3
