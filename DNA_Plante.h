#pragma once
#ifndef _DNA_PLANTE
#define _DNA_PLANTE
#include "ofMain.h"


// DNA is an vector of floats for interactive selection

class DNA_Plante
{
public:
	// The genetic sequence
	vector <float> genes;

	// The maximum strength of the forces
	int numGenes = 4;

	// Constructors
	DNA_Plante();
	void getGenes(vector <float> newGenes);

	DNA_Plante crossover(DNA_Plante partner);
	void mutate(float _mutationRate);

private:
};
#endif // !_DNA