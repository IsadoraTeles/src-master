#pragma once
#ifndef _POPULATIONARBRE2
#define _POPULATIONARBRE2
#include "PhenotypeArbre2.h"

// A class to describe a population of 'creatures' 
class Population_Arbre2
{
public:
	// Variables
	float mutationRate;
	vector <Phenotype_Arbre2*> populationArbre2;
	vector <Phenotype_Arbre2*> matingPool2;
	int generations;
	int numArbres;
	float step;

	// Constructors
	Population_Arbre2();

	// Metodes
	void setup(float _mutationRate, int _numArbres);
	void draw();
	void drawPath();
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
#endif // !_POPULATIONARBRE2