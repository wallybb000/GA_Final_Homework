#include "stdafx.h"
#include "Chromosome.h"
using namespace std;
class GA
{
public:
	Chromosome mChromosome[SUM_OF_CHROMOSOME];

	vector<vector<int>> pool;

	int Fitness();
	void Select();
	void Select2();
	void Crossover();
	void Mutation();


};