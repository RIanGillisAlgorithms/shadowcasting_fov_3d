#ifndef RANDOM_WRAPPER_H
#define RANDOM_WRAPPER_H

#include "MersenneTwister.h"
#include <vector>	
#include <chrono>


namespace RND
{
	class RandomMersenneTwisterWrapper;
	extern RandomMersenneTwisterWrapper rnd;
	class RandomMersenneTwisterWrapper
	{
	public:
		RandomMersenneTwisterWrapper();
		RandomMersenneTwisterWrapper(uint32_t initialSeed);
		~RandomMersenneTwisterWrapper();

		MTRand* mainR;
		uint32_t mainSeed;
		std::vector<MTRand*> subR;
		std::vector<uint32_t> subSeeds;
		int numSubR;

		int intRand();
		//This returns a number, inclusive, between [startRange - endRange]
		int intRand(const int& startRange, const int& endRange);

		double doubleRand();
		double doubleRand(const double& startRange, const double& endRange);

		int newSubRand();
		int newSubRand(uint32_t initialSeed);

		uint32_t newSeed();
	};
}

#endif