#include "SkipListNode.hpp"
#include "FlipCoin.hpp"
#include <vector>
#include <iostream>

class SkipList
{
public:
	SkipList();
	SkipList(double p);
	~SkipList();

	int insert(int key);
	SkipListNode* search(int key);

	friend std::ostream& operator<<(std::ostream& os, const SkipList& sl); 

private:

	void insertNewNode(int key, SkipListNode* pos);
	SkipListNode* searchSuitablePosition(int key); // return the least element that greater than key
	int numLevels;
	int numDistinctElems;
	int numNodes;

	std::vector< SkipListNode* > headers;
	FlipCoin* coin;
};