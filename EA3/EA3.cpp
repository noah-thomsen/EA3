#include <iostream>
#include <time.h>
#include <math.h>
#include <algorithm>
#include <vector>

// Scenario Configuration

#define CITIES 20
#define MAX_POSITION 1000

// Algorithm Settings
#define POPULATION 100
#define GENERATIONS 200
#define ELITE_CHROMOSOMES 10
#define CROSSOVER_CHANCE 950
#define CROSSOVER_CHANCE_DENOMINATOR 1000
#define MUTATION_CHANCE 10
#define MUTATION_CHANCE_DENOMINATOR 100

// Misc
#define RANDOM_SEED 101

struct City
{
	int x;
	int y;
};

struct FitnessBlock
{
	double fitness;
	int chromosome;
};

void GenerateCities(City*);
void GenerateLehmerCode(int*);
double CalculateFitness(int*,City*);
bool SortingRule(FitnessBlock, FitnessBlock);
void ConvertLehmerToPermutation(int*, int*);
void CloneChromosome(int*, int*);
void Crossover(int*,int*);


int main()
{
	// Set up the problem
	srand(RANDOM_SEED);
	City Cities[CITIES];
	GenerateCities(Cities);
	srand(time(NULL));

	// Generate the initial chromosomes
	int Chromosomes[POPULATION][CITIES];
	for (int i = 0; i < POPULATION; i++)
		GenerateLehmerCode(Chromosomes[i]);

	// Evolutionary loop
	for (int i = 0; true; i++)//i < GENERATIONS; i++)
	{
		// Calculate fitness
		std::vector <FitnessBlock> fitness;
		for (int j = 0; j < POPULATION; j++)
		{
			FitnessBlock ToBeSorted;
			ToBeSorted.fitness = CalculateFitness(Chromosomes[j], Cities); // n time complexity
			ToBeSorted.chromosome = j;
			fitness.push_back(ToBeSorted);
		}
		std::sort(fitness.begin(), fitness.end(),SortingRule); // Default sort will work (n*logn time complexity)

		std::cout << fitness.at(0).fitness << std::endl;

		// Crossover
		int clonedelites[ELITE_CHROMOSOMES][CITIES];
		for (int j = 0; j < ELITE_CHROMOSOMES; j++)
			CloneChromosome(Chromosomes[fitness.at(j).chromosome], clonedelites[j]);
			
		for (int j = 0; j < POPULATION; j++)
			if (Chromosomes[j] != Chromosomes[fitness.at(0).chromosome]) // Making sure we aren't overwriting the best one
				if (CROSSOVER_CHANCE > rand() % CROSSOVER_CHANCE_DENOMINATOR) // Do we crossover this chromosome?
					Crossover(Chromosomes[j],clonedelites[rand() % ELITE_CHROMOSOMES]); // Perform the crossover

		// Mutate
		for (int j = 0; j < POPULATION; j++)
			if (Chromosomes[j] != Chromosomes[fitness.at(0).chromosome])
				for (int k = 0; k < CITIES; k++)
					if (MUTATION_CHANCE > rand() % MUTATION_CHANCE_DENOMINATOR)
						Chromosomes[j][k] = rand() % (CITIES - k);
	}
}

void GenerateCities(City* output)
{
	for (int i = 0; i < CITIES; i++)
	{
		output[i].x = rand() % MAX_POSITION;
		output[i].y = rand() % MAX_POSITION;
	}
}

void GenerateLehmerCode(int* output)
{
	for (int i = CITIES; i > 0; i--)
		output[CITIES - i] = rand() % i;
}

double CalculateFitness(int* lehmer,City* cities)
{
	int permutation[CITIES];
	ConvertLehmerToPermutation(lehmer, permutation); // n time complexity
	double fitness = 0;
	for (int i = 0; i < CITIES; i++)
	{
		if (i == CITIES - 1)
		{
			fitness += sqrt(pow(cities[permutation[i]].x - cities[permutation[0]].x, 2) + pow(cities[permutation[i]].y - cities[permutation[0]].y, 2));
		}
		else
		{
			fitness += sqrt(pow(cities[permutation[i]].x - cities[permutation[i+1]].x, 2) + pow(cities[permutation[i]].y - cities[permutation[i+1]].y, 2));
		}
	}
	return fitness;
}

void ConvertLehmerToPermutation(int* lehmer, int* permutation_output)
{
	std::vector <int> base;
	for (int i = 0; i < CITIES; i++)
		base.push_back(i);

	for (int i = 0; i < CITIES; i++)
	{
		permutation_output[i] = base.at(lehmer[i]); // Retrieval is in constant time.
		base.erase(base.begin() + lehmer[i]); // Erase is also in constant time.
	}
}

bool SortingRule(FitnessBlock i, FitnessBlock j)
{
	return i.fitness < j.fitness;
}

void CloneChromosome(int* input, int* output)
{
	for (int i = 0; i < CITIES; i++)
		output[i] = input[i];
}

void Crossover(int* subject, int* elite)
{
	int crossoverPoint = rand() % CITIES;
	bool before = rand() % 2;
	for (int i = 0; i < CITIES; i++)
	{
		if (before)
		{
			if (i < crossoverPoint)
			{
				subject[i] = elite[i];
			}
		}
		else
		{
			if (i > crossoverPoint)
			{
				subject[i] = elite[i];
			}
		}
	}
}

