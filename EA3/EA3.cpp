// EA3.cpp : This file contains the 'main' function. Program execution begins and ends there.

#include <iostream>
#include <time.h>

// Scenario Configuration
#define NEIGHBORHOODS 10
#define HOUSES 5
#define MAX_NEIGHBORHOOD_POSITION 10000
#define MAX_HOUSE_OFFSET 100

// Algorithm Settings
#define CHROMOSOMES 10
#define GENERATIONS 200
#define MUTATION_CHANCE 0.05

// Misc
#define RANDOM_SEED 101

struct House
{
	int x;
	int y;
};

struct Neighborhood
{
	int x;
	int y;
	House Houses[HOUSES];
};

struct Chromosome
{
	int Neighboorhoods[NEIGHBORHOODS];
	int Houses[NEIGHBORHOODS];
};

void printPoints(Neighborhood*, int, int);

int main()
{
	Neighborhood Neighborhoods[NEIGHBORHOODS];

	srand(RANDOM_SEED);
	
	for (int i = 0; i < NEIGHBORHOODS; i++)
	{
		Neighborhoods[i].x = rand() % MAX_NEIGHBORHOOD_POSITION;
		Neighborhoods[i].y = rand() % MAX_NEIGHBORHOOD_POSITION;

		for (int j = 0; j < HOUSES; j++)
		{
			Neighborhoods[i].Houses[j].x = rand() % MAX_HOUSE_OFFSET + Neighborhoods[i].x;
			Neighborhoods[i].Houses[j].y = rand() % MAX_HOUSE_OFFSET + Neighborhoods[i].y;
		}
	}

	printPoints(Neighborhoods,HOUSES,NEIGHBORHOODS);
}

void printPoints(Neighborhood* nbrhds, int num_of_houses, int num_of_neighborhoods)
{
	for (int i = 0; i < num_of_neighborhoods; i++)
	{
		std::cout << "Neighborhood: " << i + 1 << std::endl;
		for (int j= 0; j < num_of_houses; j++)
		{
			std::cout << "House " << j + 1 << ": " << nbrhds[i].Houses[j].x << "," << nbrhds[i].Houses[j].y << std::endl;
		}
	}
}



