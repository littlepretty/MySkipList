#include <iostream>

struct SkipListNode
{
	SkipListNode();
	explicit SkipListNode(int k);
	~SkipListNode();

	friend std::ostream& operator<<(std::ostream& os, const SkipListNode& node);

	SkipListNode* prev;
	SkipListNode* next;
	SkipListNode* up;
	SkipListNode* down;

	const int key;

};

