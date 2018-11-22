#pragma once
#ifndef _POPULATIONHERBE2
#define _POPULATIONHERBE2
#include "PhenotypeHerbe2.h"

// A class to describe a population of 'creatures' 
class Population_Herbe2
{
public:
	// Variables
	float mutationRate;
	vector <Phenotype_Herbe2*> populationHerbe2;
	vector <Phenotype_Herbe2*> matingPool;
	int generations;
	int numHerbes;
	float step;

	// Constructors
	Population_Herbe2();

	// Metodes
	void setup(float _mutationRate, int _numHerbes);
	void draw();
	void calcFitness(float &_pluieValue, float &_ventValue, float &_soleilValue, float &_humiditeValue);
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
#endif // !_POPULATIONHERBE