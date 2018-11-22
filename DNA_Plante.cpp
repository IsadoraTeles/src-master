#include "DNA_Plante.h"

// Constructor (makes a DNA of random vectors)
DNA_Plante::DNA_Plante()
{
	genes.resize(numGenes);
	for (auto &g : genes)
	{
		float gene = ofRandom(1);
		g = gene;
	}
}

void DNA_Plante::getGenes(vector <float> newGenes)
{
	// makes copy of newGenes
	genes = newGenes;
}

// CROSSOVER
// creates new DNA sequence from two (this and the partner)
DNA_Plante DNA_Plante::crossover(DNA_Plante partner)
{
	vector <float> child;
	child.resize(numGenes);

	// Pick a midpoint
	// int crossover = int(ofRandom(genes.size()));

	//cout << "crossover = "<< crossover << endl;
	//cout << "geneSize = " << genes.size() << endl;
	// Take "half" from one and "half" from the other
	for (int i = 0; i < numGenes; i++)
	{
		int decide = int(ofRandom(0, 2));

		if (decide == 0)
		{
			child[i] = genes[i];
		}
		else if (decide == 1)
		{
			child[i] = partner.genes[i];
		}
		else
		{
			float moyenne = (genes[i] + partner.genes[i]) * 0.5;
			child[i] = moyenne;
		}
	}

	DNA_Plante newGenes;
	newGenes.getGenes(child);
	return newGenes;
}

// Based on a mutation probability, picks a new random vector
void DNA_Plante::mutate(float _mutationRate)
{
	for (int i = 0; i < genes.size(); i++)
	{
		if (ofRandom(1) < _mutationRate)
		{
			genes[i] = ofRandom(1);
		}
	}
}



