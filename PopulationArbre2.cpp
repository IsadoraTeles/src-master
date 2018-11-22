#include "PopulationArbre2.h"

Population_Arbre2::Population_Arbre2()
{
	generations = 0;
}

void Population_Arbre2::setup(float _mutationRate, int _numArbres)
{
	float w = 512;
	float h = 512;

	mutationRate = _mutationRate;
	numArbres = _numArbres;
	populationArbre2.resize(numArbres);

	positions.resize(numArbres);
	positions[0] = ofVec2f(w * 0.5, h - 10);
	positions[1] = ofVec3f(w + w * 0.5, h - 10);
	positions[2] = ofVec3f(w * 0.5, h + h - 10);
	positions[3] = ofVec3f(w + w * 0.5, h + h - 10);

	int counter = 0;

	// make new set of plants
	for (auto &p : populationArbre2)
	{
		// CREER DES LOVES CONSTANTS POUR CHAQUE PLANTEEEE
		float x = positions[counter].x;
		float y = positions[counter].y;
		float z = 0.0;
		ofVec3f origin(x, y, z);
		DNA_Plante tempDNA;
		p = new Phenotype_Arbre2();
		p->setup(tempDNA, x, y);
		p->calculate();
		counter++;
	}
}

void Population_Arbre2::draw()
{

	// Run every plant
	for (auto &p : populationArbre2)
	{
		p->drawSysArbre2();
	}
}

void Population_Arbre2::drawPath()
{

	// Run every plant
	for (auto &p : populationArbre2)
	{
		p->drawPath();
	}
}


void  Population_Arbre2::evolvePath()
{
	// Run every plant
	for (auto &p : populationArbre2)
	{
		p->evolvePath();
	}
}

// Calculate fitness for each plant
void Population_Arbre2::calcFitness(float &_pluieValue, float &_ventValue, float &_soleilValue, float &_humiditeValue)
{
	pluieValue = _pluieValue;
	ventValue = _ventValue;
	soleilValue = _soleilValue;
	humiditeValue = _humiditeValue;

	for (auto &p : populationArbre2)
	{
		p->incrementFitness(pluieValue, ventValue, soleilValue, humiditeValue);
	}
}

// Generate a mating Pool
void Population_Arbre2::selection()
{
	// clear the vector
	matingPool2.clear();

	// Calculate total fitness of whole population
	float maxFitness = getMaxFitness();

	// Calculate fitness for each member of the population 
	// (scaled to value between 0 and 1)
	// based on fitness, each member will get added to the mating pool a certain number of times
	for (auto &p : populationArbre2)
	{
		float fit = p->getFitness();
		float fitnessNormal = ofMap(fit, 0, maxFitness, 0, 1);

		int n = fitnessNormal * 100;

		for (int i = 0; i < n; i++)
		{
			matingPool2.push_back(p);
		}
	}
}

void Population_Arbre2::reproduction()
{
	// Refill the population with children from the mating pool
	for (int i = 0; i < populationArbre2.size(); i++)
	{
		// sping the wheel of fortune to pick parents
		int m = ofRandom(matingPool2.size());
		int d = ofRandom(matingPool2.size());
		// pick two parents
		// get their genes
		DNA_Plante momGenes = matingPool2[m]->getDNA();
		DNA_Plante dadGenes = matingPool2[d]->getDNA();
		// mate their genes
		DNA_Plante child = momGenes.crossover(dadGenes);
		// mutate their genes
		child.mutate(mutationRate);
		// fill the new population with the new child
		float x = positions[i].x;
		float y = positions[i].y;
		float z = 0.0;
		ofVec3f origin(x, y, z);
		populationArbre2[i] = new Phenotype_Arbre2();
		populationArbre2[i]->setup(child, x, y);
		populationArbre2[i]->calculate();
	}
	generations++;
}

float Population_Arbre2::getMaxFitness()
{
	float record = 0;
	for (auto &p : populationArbre2)
	{
		if (p->getFitness() > record)
		{
			record = p->getFitness();
		}
	}
	return record;
}