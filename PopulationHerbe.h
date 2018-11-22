#pragma once
#ifndef _POPULATIONHERBE
#define _POPULATIONHERBE
#include "PhenotypeHerbe.h"

// A class to describe a population of 'creatures' 
class Population_Herbe
{
public:
	// Variables
	float mutationRate;
	vector <Phenotype_Herbe*> populationHerbe;
	vector <Phenotype_Herbe*> matingPool;
	int generations;
	int numHerbes;
	float step;

	// Constructors
	Population_Herbe();

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