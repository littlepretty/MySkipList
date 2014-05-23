#include "FlipCoin.hpp"

FlipCoin::FlipCoin(double p): possibility(p)
{
	generator = new std::default_random_engine();
	distribution = new std::bernoulli_distribution(possibility);
}

FlipCoin::~FlipCoin()
{
	delete generator;
	delete distribution;
}

int FlipCoin::flipCoinOnce()
{
	return (*distribution)(*generator);
}

