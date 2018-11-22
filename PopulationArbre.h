#pragma once
#ifndef _POPULATIONARBRE
#define _POPULATIONARBRE
#include "PhenotypeArbre.h"

// A class to describe a population of 'creatures' 
class Population_Arbre
{
public:
	// Variables
	float mutationRate;
	vector <Phenotype_Arbre*> populationArbre;
	vector <Phenotype_Arbre*> matingPool;
	int generations;
	int numArbres;
	float step;

	// Constructors
	Population_Arbre();

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
#endif // !_POPULATIONARBRE