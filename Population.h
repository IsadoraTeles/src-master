#pragma once
#ifndef _POPULATION
#define _POPULATION
#include "Phenotype.h"

// A class to describe a population of 'creatures' 
class Population
{
public:
	// Variables
	float mutationRate;
	vector <Phenotype*> population;
	vector <Phenotype*> matingPool;
	int generations;
	int numPlantes;
	float step;

	// Constructors
	Population();

	// Metodes
	void setup(float _mutationRate, int _numPlantes);
	void draw();
	void calcFitness(float &_pluieValue, float &_ventValue, float &_soleilValue, float &_humiditeValue);
	void evolvePath();
	void selection();
	void reproduction();
	int getGenerations() { return generations; };
	float getMaxFitness();

	float pluieValue = 0;
	float ventValue = 0;
	float soleilValue = 0;
	float humiditeValue = 0;

	vector <ofVec2f> positions;

private:
};
#endif // !_POPULATION