
#include "SkipList.hpp"
#include <iostream>

void testFlipCoin()
{
	FlipCoin coin(0.5);
	int count = 100;
	for (int i = 0; i < count; ++i)
	{
		std::cout<<coin.flipCoinOnce()<<'\t';
	}
}

void testSkipListNode()
{
	SkipListNode head_bottom;
	SkipListNode head_mid;
	SkipListNode head_roof;

	head_roof.down = &head_mid; head_mid.down = &head_bottom;
	head_bottom.up = &head_mid; head_mid.up = &head_roof;

	SkipListNode b1(1), b2(2), b3(3), b4(4);
	SkipListNode m1(1), m2(2), m4(4);
	SkipListNode r1(1), r4(4);

	r1.down = &m1; m1.down = &b1;
	b1.up = &m1; m1.up = &r1;

	r4.down = &m4; m4.down = &b4;
	b4.up = &m4; m4.up = &r4;

	m2.down = &b2;
	b2.up = &m2;

	head_bottom.next = &b1; b1.next = &b2; b2.next = &b3; b3.next = &b4;
	b4.prev = &b3; b3.prev = &b2; b2.prev = &b1; b1.prev = &head_bottom;

	head_mid.next = &m1; m1.next = &m2; m2.next = &m4;
	m4.prev = &m2; m2.prev = &m1; m1.prev = &head_mid;

	head_roof.next = &r1; r1.next = &r4;
	r4.prev = &r1; r1.prev = &head_roof;

	std::cout<<head_roof;
	std::cout<<head_mid;
	std::cout<<head_bottom;

}

void testBasicSkipList()
{
	SkipList sl(0.55);
	sl.insert(8);
	std::cout<<sl<<std::endl;
	sl.insert(6);
	std::cout<<sl<<std::endl;
	
	sl.search(3);
	sl.insert(3);
	std::cout<<sl<<std::endl;
	sl.search(3);
	
	sl.insert(5);
	std::cout<<sl<<std::endl;
	sl.insert(1);
	std::cout<<sl<<std::endl;
	sl.insert(2);
	std::cout<<sl<<std::endl;
	sl.insert(4);
	std::cout<<sl<<std::endl;
	sl.insert(7);
	std::cout<<sl<<std::endl;

	sl.search(2);
	std::cout<<sl<<std::endl;

	sl.search(8);
	sl.search(1);
	sl.search(10);

	std::cout<<sl<<std::endl;
	sl.remove(5);
	std::cout<<sl<<std::endl;
	sl.remove(8);
	std::cout<<sl<<std::endl;
	sl.remove(1);
	std::cout<<sl<<std::endl;

}

int main(int argc, char const *argv[])
{	
	// std::cout<<"--------Test Flip Coin----------"<<std::endl;
	// testFlipCoin();
	// std::cout<<std::endl;

	// std::cout<<"--------Test Skip List Node-----"<<std::endl;
	// testSkipListNode();
	// std::cout<<std::endl;

	std::cout<<"--------------------------Test Skip List Basic--------------------------------------"<<std::endl;
	testBasicSkipList();
	std::cout<<std::endl;
	
	return 0;
}