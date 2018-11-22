#pragma once
#ifndef _PHENOTYPE
#define _PHENOTYPE
#include "DNA_Plante.h"
#include "Path.h"
#include "Systeme.h"

// DNA sequence, fitness value, position on scren
// Fitness function f(t) = t * resistance (where t is the weather parameter and resistance is the reception of the weather )

class Phenotype
{
public:
	Phenotype();

	void setup(DNA_Plante _dna, float _x, float _y);
	void calculate();
	void incrementFitness(float &_pluieValue, float &_ventValue, float &_soleilValue, float &_humiditeValue);
	float getFitness() { return fitness; };
	DNA_Plante getDNA() { return dna; };

	ofVec2f location;	// position on screen
	DNA_Plante dna;			// PHENOTYPE DNA (GENOTYPE)

	float pluieValue = 0;
	float ventValue = 0;
	float soleilValue = 0;
	float humiditeValue = 0;

	float fitness;		// how good is this phenotype ?

						// loves
	float pluieLove = 0;
	float ventLove = 0;
	float soleilLove = 0;
	float humiditeLove = 0;

	// PATH
	Path path;
	vector <ofVec3f> pathPoints;
	void newPath();
	void evolvePath();
	void drawPath();
	int counter = 0;

	// SYSTEME
	Systeme sys;
	void drawSys();
	int genNumVehicles;
	int genIntervalDrawVehicles;

private:
};
#endif // !_PHENOTYPE