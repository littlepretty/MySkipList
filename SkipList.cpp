#include "SkipList.hpp"

SkipList::SkipList(): numLevels(1), numDistinctElems(0), numNodes(0), coin(new FlipCoin(0.5))
{
	headers.push_back(new SkipListNode());
}

SkipList::SkipList(double p): numLevels(1), numDistinctElems(0), numNodes(0), coin(new FlipCoin(p))
{
	headers.push_back(new SkipListNode());
}

SkipList::~SkipList()
{
	std::cout<<"SkipList Statistics: "<<numNodes<<" Nodes Left and "<<numLevels<<" Levels Left"<<std::endl;
	// delete SkipListNode in the chain
	for (std::vector<SkipListNode* >::iterator iter = headers.begin(); iter != headers.end(); ++iter)
	{
		SkipListNode* header = *iter;
		if (header->next != NULL)
		{
			//	could not delete header NOW while iterater through vector
			SkipListNode* current = header->next;
			while(current != NULL) {
				SkipListNode* toDelete = current;
				current = current->next;
				deleteSkipNode(toDelete);
				--numNodes;
			}
		}
		--numLevels;
	}

	delete coin;
	std::cout<<"SkipList Disposed: "<<numNodes<<" Nodes Left and "<<numLevels<<" Levels Left"<<std::endl;
}

void SkipList::deleteSkipNode(SkipListNode*& node)
{
	if (node->up != NULL)
	{
		node->up->down = NULL;
	}
	if (node->down != NULL)
	{
		node->down->up = NULL;
	}
	if (node->prev != NULL)
	{
		node->prev->next = NULL;
	}
	if (node->next != NULL)
	{
		node->next->prev = NULL;
	}
	delete node;
}

int SkipList::insert(int key)
{
	std::cout<<"---------------Insertion "<<key<<"-------------------------"<<std::endl;
	SkipListNode* pos = searchSuitablePosition(key);
	if (pos->key == key)
	{
		std::cout<<"Node With Key"<<key<<" Already Exists"<<std::endl;
		return 0;
	} else {
		std::cout<<"Insert After "<<pos->key<<std::endl;
		insertNewNode(key, pos);
		return 1;
	}
	std::cout<<"------------------------------------------------------------"<<std::endl;
}

void SkipList::insertNewNode(int key, SkipListNode* pos)
{
	SkipListNode* addUp = new SkipListNode(key);
	
	//	1. insert at bottom level
	if (pos->next != NULL)
	{
		pos->next->prev = addUp;
		addUp->next = pos->next;

		pos->next = addUp;
		addUp->prev = pos;
	} else {
		pos->next = addUp;
		addUp->prev = pos;
	}
	++numDistinctElems;
	++numNodes;
	std::cout<<"Inserted At Bottom Level After "<<pos->key<<std::endl;

	
	//	2. flipping coin and lift node
	int numLifts = 0;
	while(coin->flipCoinOnce()) {
		++numLifts;
	}
	std::cout<<"Need "<<numLifts<<" Lifts When Insert "<<key<<std::endl;

	// int numInnerLifts = numLifts < (numLevels - 1) ? numLifts : (numLevels - 1);
	int numExtrLifts = numLifts > (numLevels - 1) ? numLifts - (numLevels - 1) : 0;

	std::cout<<"Need Extra "<<numExtrLifts<<" Level When Insert "<<key<<std::endl;

	while(numExtrLifts > 0) {
		SkipListNode* highest_head = headers.back();
		SkipListNode* extra_head = new SkipListNode();
		highest_head->up = extra_head;
		extra_head->down = highest_head;
		headers.push_back(extra_head);
		--numExtrLifts;
		++numLevels;
	}

	SkipListNode* liftedNodeAtLowerLevel = addUp;

	for (std::vector< SkipListNode* >::iterator iter = headers.begin() + 1; iter - headers.begin() <= numLifts; ++iter)
	{
		SkipListNode* head = *iter;
		SkipListNode *liftedNode = new SkipListNode(key);

		if (head->next != NULL)
		{
			SkipListNode* posInThisLevel = head->next;
			while(posInThisLevel->next != NULL && posInThisLevel->key < key) {
				posInThisLevel = posInThisLevel->next;
			}
			if (posInThisLevel->key > key)
			{
				posInThisLevel = posInThisLevel->prev;

				posInThisLevel->next->prev = liftedNode;
				liftedNode->next = posInThisLevel->next;

			} 
			posInThisLevel->next = liftedNode;
			liftedNode->prev = posInThisLevel;
			
			std::cout<<"Inserted At Level "<<iter-headers.begin()+1<<" After "<<posInThisLevel->key<<std::endl;


		} else {
			//	add first element in this level
			head->next = liftedNode;
			liftedNode->prev = head;
			std::cout<<"Inserted At Level "<<iter-headers.begin()+1<<" After Header"<<std::endl;

		}

		liftedNodeAtLowerLevel->up = liftedNode;
		liftedNode->down = liftedNodeAtLowerLevel;
		liftedNodeAtLowerLevel = liftedNode;

		++numNodes;
	}

}

SkipListNode* SkipList::search(int key)
{
	std::cout<<"---------------Search "<<key<<"-----------------------------"<<std::endl;
	SkipListNode *result = searchSuitablePosition(key);
	if (result->key == key)
	{
		return result;
	} else if (result != NULL) {
		std::cout<<"Not Found. Suitable Insert Position After "<<result->key<<std::endl;
	}
	std::cout<<"------------------------------------------------------------"<<std::endl;

	return NULL;
}

SkipListNode* SkipList::searchSuitablePosition(int key)
{
	SkipListNode* highest_level = headers.back();

	if (highest_level->next == NULL)
	{
		std::cout<<"List Empty"<<std::endl;
		return highest_level;
	}

	SkipListNode* current = highest_level->next;

	int level = headers.size();
	while(current != NULL && level >= 1)
	{
		// std::cout<<"In Level "<<level<<std::endl;
		//	go next until go so far
		while(current->key < key && current->next != NULL) 
		{
			current = current->next;
		}
		if (current->key == key)
		{
			//	return successfully or return a 
			std::cout<<"Found At Level "<<level<<std::endl;
			return current;

		} else if(level == 1) {
			break;
		} else {
			do {
				current = current->prev;
			} while (current->down ==NULL);

			current = current->down;
			// std::cout<<"Enter Lower Level At "<<current->key<<std::endl;
			--level;
		}
	}
	std::cout<<"Break At "<<current->key<<" Level "<<level<<std::endl;

	return current->key > key ? current->prev : current;
}

std::ostream& operator<<(std::ostream& os, const SkipList& sl)
{
	os<<"---------------SkipList Info-----------------------------"<<std::endl;

	int k = 1;
	for (std::vector< SkipListNode* >::const_iterator iter = sl.headers.begin(); iter != sl.headers.end(); ++iter)
	{
		SkipListNode* head = *iter;
		os<<"Level "<<k<<": "<<(*head)<<std::endl;
		++k;
	}
	os<<"---------------------------------------------------------"<<std::endl;

	return os;
}