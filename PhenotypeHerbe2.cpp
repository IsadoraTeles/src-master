#include "PhenotypeHerbe2.h"

Phenotype_Herbe2::Phenotype_Herbe2()
{

}

void Phenotype_Herbe2::setup(DNA_Plante _dna, float _x, float _y)
{
	dna = _dna;
	location = ofVec2f(_x, _y);
	fitness = 1;
}

void Phenotype_Herbe2::calculate()
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
	float genDecreaseRate = ofMap(dna.genes[1], 0, 1, 0.5, 3.0);
	float genAttract = dna.genes[3];
	float genTs = ofMap(dna.genes[3], 0, 1, 1.2, 2.0);
	float genMf = ofMap(dna.genes[0], 0, 1, 0.5, 1.5);
	float genMass = ofMap(dna.genes[1], 0, 1, 3, 12);
	float genRadius = ofMap(dna.genes[2], 0, 1, 3, 8);
	float genRed = ofMap(dna.genes[2], 0, 1, 0.2, 0.8);
	float genGreen = ofMap(dna.genes[3], 0, 1, 0.1, 0.8);
	float genBlue = ofMap(dna.genes[0], 0, 1, 0.2, 0.1);
	bool genFleur = true;
	float genWanderRadius = ofMap(dna.genes[1], 0, 1, 10, 50);
	float genWanderDistance = ofMap(dna.genes[2], 0, 1, 5, 15);
	float genChange = ofMap(dna.genes[3], 0, 1, 60, 180);
	genNumVehicles = int(ofMap(dna.genes[0], 0, 1, 14, 18));
	genIntervalDrawVehicles = int(ofMap(dna.genes[1], 0, 1, 30, 90));

	// SYSTEME
	ofVec3f c(genRed, genGreen, genBlue);

	sysHerbe2.setupWithoutPath(origin);
	sysHerbe2.setGeneticData(genIntervalAttractor, genDecreaseRate, genAttract, genTs, genMf, genMass, genRadius, c, genFleur, genWanderRadius, genWanderDistance, genChange);
}

void Phenotype_Herbe2::incrementFitness(float &_pluieValue, float &_ventValue, float &_soleilValue, float &_humiditeValue)
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

void Phenotype_Herbe2::drawSysHerbe2()
{
	// SYSTEME DE VEHICULES

	for (int i = 0; i < genNumVehicles; i++)
	{
		if (ofGetFrameNum() % genIntervalDrawVehicles == 0)
		{
			sysHerbe2.addVehicleHerbe();
		}
	}
	sysHerbe2.update();
	sysHerbe2.draw();
}