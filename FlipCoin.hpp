#include <random>

class FlipCoin
{
public:
	FlipCoin(double p);
	~FlipCoin();

	int flipCoinOnce();

private:
	double possibility;
	std::default_random_engine* generator;
	std::bernoulli_distribution* distribution;

};