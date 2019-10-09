// EA3.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>

#define COMPLEXITY 10
#define RANDOM_SEED 101
#define MAX_POSITION 100

void printPoints(int*, int*, int*);

int main()
{
	int xpos[COMPLEXITY];
	int ypos[COMPLEXITY];
	int zpos[COMPLEXITY];

	srand(RANDOM_SEED);
	
	for (int i = 0; i < COMPLEXITY; i++)
	{
		xpos[i] = rand() % MAX_POSITION;
		ypos[i] = rand() % MAX_POSITION;
		zpos[i] = rand() % MAX_POSITION;
	}

	//tsp(xpos,ypos,zpos,COMPLEXITY);

	printPoints(xpos, ypos, zpos);
}

void printPoints(int* xp, int* yp, int* zp)
{
	for (int i = 0; i < COMPLEXITY; i++)
	{
		std::cout << "X:" << xp[i] << " Y:" << yp[i] << " Z:" << zp[i] << std::endl;
	}
}
