#include "SkipListNode.hpp"
#include <limits>

SkipListNode::SkipListNode(): prev(NULL), next(NULL), up(NULL), down(NULL), key(std::numeric_limits<int>::min())
{

}

SkipListNode::SkipListNode(int k): prev(NULL), next(NULL), up(NULL), down(NULL), key(k)
{

}

SkipListNode::~SkipListNode()
{
	prev = NULL;
	next = NULL;
	up = NULL;
	down = NULL;
}

std::ostream& operator<<(std::ostream& os, const SkipListNode& node)
{
	if (node.key > 0)
	{
		os<<node.key;
		if (node.next !=NULL)
		{
			os<<"-->";
		}

	} else {
		os<<"head-->";
	}
	if (node.next != NULL)
	{
		os<<*(node.next);
	}

	return os;
}
