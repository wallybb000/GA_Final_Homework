#include "stdafx.h"
#include "GA.h"

using namespace std;
int GA::Fitness()
{
	int Max = -110000;
	for (int i = 0; i < SUM_OF_CHROMOSOME; i++)
	{
		mChromosome[i].CalculateFitness();
		if (mChromosome[i].fitness>Max) Max = mChromosome[i].fitness; 
	}
	return Max;
}

void GA::Select()
{	
	pool.clear();

	for (int i = 0; i < SUM_OF_CHROMOSOME-1; i++)
	for (int j = i + 1; j < SUM_OF_CHROMOSOME; j++)
	{
		if (mChromosome[i].fitness < mChromosome[j].fitness)
			swap(mChromosome[i], mChromosome[j]);
	}

	for (int i = 0; i <5; i++){
		vector<int> temp;
		temp.push_back(i);
		temp.push_back(SUM_OF_CHROMOSOME-1-i);
		pool.push_back(temp);
	}

}void GA::Select2()
{
	pool.clear();

	for (int i = 0; i < SUM_OF_CHROMOSOME - 1; i++)
	for (int j = i + 1; j < SUM_OF_CHROMOSOME; j++)
	{
		if (mChromosome[i].fitness < mChromosome[j].fitness)
			swap(mChromosome[i], mChromosome[j]);
	}



}
void GA::Crossover()
{

	if (pool.size() != 0)
	{
		for (int i = 0; i < pool.size(); i++){
			Chromosome temp = mChromosome[pool[i][0]];
			temp.Crossover(mChromosome[pool[i][1]]);
			mChromosome[pool[i][1]] = temp;
		}
	}
}


void GA::Mutation()
{
	for (int i = 0; i < SUM_OF_CHROMOSOME;i++)
	if (rand() % 1000>5)
	{
		mChromosome[i].Mutation();
	}
}
