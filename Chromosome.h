#pragma once
#include "stdafx.h"
#define WEAK_LENGTH 5
#define SUM_OF_LESSON 24
#define SUM_OF_ROOM 3
#define SUM_OF_TIME 10
#define SUM_OF_CHROMOSOME 10
struct Lesson
{
	int no;
	int teacher;
	int lesson;
	int grade;
};
struct Location
{
	int room;
	int time;
};

class Chromosome
{
public:
	Lesson lessonlist[SUM_OF_ROOM][SUM_OF_TIME];
	Location location[SUM_OF_LESSON];
	int fitness;
	int goodOfEveryTime[SUM_OF_TIME];
	int badOfEveryTime[SUM_OF_TIME];
	Chromosome();

	void Initialisation();
	void CopyTo(Chromosome& in);

	void CalculateFitness();
	void Crossover(Chromosome& in);
	void Crossover2(Chromosome& in);
	void Mutation();


};
