CC = g++
CFLAGS = -c -Wall -std=c++11
LDFLAGS = 

SkipList: test.o FlipCoin.o SkipListNode.o SkipList.o
	$(CC) test.o FlipCoin.o SkipListNode.o SkipList.o -o SkipList

test.o: test.cpp
	$(CC) $(CFLAGS) test.cpp

FlipCoin.o: FlipCoin.cpp
	$(CC) $(CFLAGS) FlipCoin.cpp

SkipListNode.o: SkipListNode.cpp
	$(CC) $(CFLAGS) SkipListNode.cpp

SkipList.o: SkipList.cpp
	$(CC) $(CFLAGS) SkipList.cpp

clean:
	rm -rf *.o SkipList