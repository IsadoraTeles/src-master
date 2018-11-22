#include "PhenotypeHerbe.h"

Phenotype_Herbe::Phenotype_Herbe()
{

}

void Phenotype_Herbe::setup(DNA_Plante _dna, float _x, float _y)
{
	dna = _dna;
	location = ofVec2f(_x, _y);
	fitness = 1;
}

void Phenotype_Herbe::calculate()
{
	// we are using the phenotype's DNA to pick properties for the drawing
	// such as: size, color, angle
	// now, since every gene is a flowting point between 0 and 1, we map the values

	pluieLove = int(ofMap(dna.genes[0], 0, 1, 0, 10));
	ventLove = int(ofMap(dna.genes[1], 0, 1, 0, 10));
	soleilLove = int(ofMap(dna.genes[2], 0, 1, 0, 10));
	humiditeLove = int(ofMap(dna.genes[3], 0, 1, 0, 10));

	// once we calculate the above properties, we use those variables to draw the plant
	// appel des objects dessinateurs avec les parametres des genes
	ofVec3f origin = location;

	int genIntervalAttractor = int(ofMap(dna.genes[0], 0, 1, 360, 600));
	float genDecreaseRate = ofMap(dna.genes[1], 0, 1, 3.0, 6.0);
	float genAttract = dna.genes[3];
	float genTs = ofMap(dna.genes[3], 0, 1, 0.7, 2.0);
	float genMf = ofMap(dna.genes[0], 0, 1, 1.0, 2.2);
	float genMass = ofMap(dna.genes[1], 0, 1, 5, 8);
	float genRadius = ofMap(dna.genes[2], 0, 1, 2, 7);
	float genRed = ofMap(dna.genes[2], 0, 1, 0.5, 0.8);
	float genGreen = ofMap(dna.genes[3], 0, 1, 0.6, 0.9);
	float genBlue = ofMap(dna.genes[0], 0, 1, 0.05, 0.1);
	bool genFleur = true;
	float genWanderRadius = ofMap(dna.genes[1], 0, 1, 10, 30);
	float genWanderDistance = ofMap(dna.genes[2], 0, 1, 10, 70);
	float genChange = ofMap(dna.genes[3], 0, 1, 10, 30);
	genNumVehicles = int(ofMap(dna.genes[0], 0, 1, 10, 19));
	genIntervalDrawVehicles = int(ofMap(dna.genes[1], 0, 1, 10, 30));

	// SYSTEME
	ofVec3f c(genRed, genGreen, genBlue);

	sysHerbe.setupWithoutPath(origin);
	sysHerbe.setGeneticData(genIntervalAttractor, genDecreaseRate, genAttract, genTs, genMf, genMass, genRadius, c, genFleur, genWanderRadius, genWanderDistance, genChange);
}

void Phenotype_Herbe::incrementFitness(float &_pluieValue, float &_ventValue, float &_soleilValue, float &_humiditeValue)
{
	pluieValue = _pluieValue;
	ventValue = _ventValue;
	soleilValue = _soleilValue;
	humiditeValue = _humiditeValue;

	fitness += pluieLove * pluieValue;
	fitness += ventLove * ventValue;
	fitness += soleilLove * soleilValue;
	fitness += humiditeLove * humiditeValue;
}

void Phenotype_Herbe::drawSysHerbe()
{
	// SYSTEME DE VEHICULES

	for (int i = 0; i < genNumVehicles; i++)
	{
		if (ofGetFrameNum() % genIntervalDrawVehicles == 0)
		{
			sysHerbe.addVehicleHerbe();
		}
	}
	sysHerbe.update();
	sysHerbe.draw();
}