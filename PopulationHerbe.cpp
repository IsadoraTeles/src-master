#include "PopulationHerbe.h"

Population_Herbe::Population_Herbe()
{
	generations = 0;
}

void Population_Herbe::setup(float _mutationRate, int _numHerbes)
{
	float w = 512;
	float h = 512;

	mutationRate = _mutationRate;
	numHerbes = _numHerbes;
	populationHerbe.resize(numHerbes);

	positions.resize(numHerbes);
	positions[0] = ofVec2f(w * 0.5, h - 10);
	positions[1] = ofVec3f(w + w * 0.5, h - 10);
	positions[2] = ofVec3f(w * 0.5, h + h - 10);
	positions[3] = ofVec3f(w + w * 0.5, h + h - 10);

	int counter = 0;

	// make new set of plants
	for (auto &p : populationHerbe)
	{
		// CREER DES LOVES CONSTANTS POUR CHAQUE PLANTEEEE
		float x = positions[counter].x;
		float y = positions[counter].y;
		float z = 0.0;
		ofVec3f origin(x, y, z);
		DNA_Plante tempDNA;
		p = new Phenotype_Herbe();
		p->setup(tempDNA, x, y);
		p->calculate();
		counter++;
	}
}

void Population_Herbe::draw()
{
	// Run every plant
	for (auto &p : populationHerbe)
	{
		p->drawSysHerbe();
	}
}

// Calculate fitness for each plant
void Population_Herbe::calcFitness(float &_pluieValue, float &_ventValue, float &_soleilValue, float &_humiditeValue)
{
	pluieValue = _pluieValue;
	ventValue = _ventValue;
	soleilValue = _soleilValue;
	humiditeValue = _humiditeValue;

	for (auto &p : populationHerbe)
	{
		p->incrementFitness(pluieValue, ventValue, soleilValue, humiditeValue);
	}
}

// Generate a mating Pool
void Population_Herbe::selection()
{
	// clear the vector
	matingPool.clear();

	// Calculate total fitness of whole population
	float maxFitness = getMaxFitness();

	// Calculate fitness for each member of the population 
	// (scaled to value between 0 and 1)
	// based on fitness, each member will get added to the mating pool a certain number of times
	for (auto &p : populationHerbe)
	{
		float fit = p->getFitness();
		float fitnessNormal = ofMap(fit, 0, maxFitness, 0, 1);

		int n = fitnessNormal * 100;

		for (int i = 0; i < n; i++)
		{
			matingPool.push_back(p);
		}
	}
}

void Population_Herbe::reproduction()
{
	// Refill the population with children from the mating pool
	for (int i = 0; i < populationHerbe.size(); i++)
	{
		// sping the wheel of fortune to pick parents
		int m = ofRandom(matingPool.size());
		int d = ofRandom(matingPool.size());
		// pick two parents
		// get their genes
		DNA_Plante momGenes = matingPool[m]->getDNA();
		DNA_Plante dadGenes = matingPool[d]->getDNA();
		// mate their genes
		DNA_Plante child = momGenes.crossover(dadGenes);
		// mutate their genes
		child.mutate(mutationRate);
		// fill the new population with the new child
		float x = positions[i].x;
		float y = positions[i].y;
		float z = 0.0;
		ofVec3f origin(x, y, z);
		populationHerbe[i] = new Phenotype_Herbe();
		populationHerbe[i]->setup(child, x, y);
		populationHerbe[i]->calculate();
	}
	generations++;
}

float Population_Herbe::getMaxFitness()
{
	float record = 0;
	for (auto &p : populationHerbe)
	{
		if (p->getFitness() > record)
		{
			record = p->getFitness();
		}
	}
	return record;
}