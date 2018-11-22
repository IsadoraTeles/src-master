#include "PhenotypeArbre2.h"

Phenotype_Arbre2::Phenotype_Arbre2()
{

}

void Phenotype_Arbre2::setup(DNA_Plante _dna, float _x, float _y)
{
	dna = _dna;
	location = ofVec2f(_x, _y);
	fitness = 1;
}

void Phenotype_Arbre2::calculate()
{
	// we are using the phenotype's DNA to pick properties for the drawing
	// such as: size, color, angle
	// now, since every gene is a flowting point between 0 and 1, we map the values
	float radius = ofMap(dna.genes[0], 0, 1, 1.0, 3.0);
	float len = ofMap(dna.genes[1], 0, 1, 5, 80);
	float angle = ofMap(dna.genes[2], 0, 1, -80, 80);
	float changeLen = ofMap(dna.genes[3], 0, 1, 0.3, 1.0);

	pluieLove = int(ofMap(dna.genes[0], 0, 1, 0, 10));
	ventLove = int(ofMap(dna.genes[1], 0, 1, 0, 10));
	soleilLove = int(ofMap(dna.genes[2], 0, 1, 0, 10));
	humiditeLove = int(ofMap(dna.genes[3], 0, 1, 0, 10));

	// once we calculate the above properties, we use those variables to draw the plant
	// appel des objects dessinateurs avec les parametres des genes
	ofVec3f origin = location;

	// PATH
	path.setup(origin, radius, len, angle, changeLen);
	path.generatePoints();
	pathPoints.resize(path.fleurs.size());

	for (int i = 0; i < path.fleurs.size(); i++)
	{
		pathPoints.push_back(path.fleurs[i]);
	}

	// SYSTEME

	int genIntervalAttractor = int(ofMap(dna.genes[0], 0, 1, 600, 900));
	float genDecreaseRate = ofMap(dna.genes[1], 0, 1, 1.0, 4.0);
	float genAttract = false;
	float genTs = ofMap(dna.genes[3], 0, 1, 0.8, 2.0);
	float genMf = ofMap(dna.genes[0], 0, 1, 0.8, 2.2);
	float genMass = ofMap(dna.genes[1], 0, 1, 10, 19);
	float genRadius = ofMap(dna.genes[2], 0, 1, 1, 2);
	float genRed = ofMap(dna.genes[2], 0, 1, 0.2, 0.6);
	float genGreen = ofMap(dna.genes[3], 0, 1, 0.1, 0.5);
	float genBlue = ofMap(dna.genes[0], 0, 1, 0.02, 0.3);
	bool genFleur = true;
	float genWanderRadius = ofMap(dna.genes[1], 0, 1, 2, 10);
	float genWanderDistance = ofMap(dna.genes[2], 0, 1, 1, 5);
	float genChange = ofMap(dna.genes[0], 0, 1, 60, 360);
	genNumVehicles = int(ofMap(dna.genes[0], 0, 1, 1, 2));
	genIntervalDrawVehicles = int(ofMap(dna.genes[1], 0, 1, 1, 80));

	ofVec3f c(genRed, genGreen, genBlue);

	sysArbre2.setupWithPath(origin, pathPoints);
	sysArbre2.setGeneticData(genIntervalAttractor, genDecreaseRate, genAttract, genTs, genMf, genMass, genRadius, c, genFleur, genWanderRadius, genWanderDistance, genChange);

	//cout << genAttract << endl;
}

void Phenotype_Arbre2::incrementFitness(float &_pluieValue, float &_ventValue, float &_soleilValue, float &_humiditeValue)
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

void Phenotype_Arbre2::newPath()
{
	path.generatePoints();
	path.addPoints();

	pathPoints.clear();
	pathPoints.resize(path.fleurs.size());
	for (int i = 0; i < path.fleurs.size(); i++)
	{
		pathPoints.push_back(path.fleurs[i]);
	}
	sysArbre2.updatePath(pathPoints);
}

void Phenotype_Arbre2::evolvePath()
{
	if (counter < 3)
	{
		newPath();
		counter++;
	}
}

void Phenotype_Arbre2::drawPath()
{
	path.drawPoints();
}

void Phenotype_Arbre2::drawSysArbre2()
{
	// SYSTEME DE VEHICULES

	if (ofGetFrameNum() % genIntervalDrawVehicles == 0)
	{
		for (auto &p : pathPoints)
		{
			
				for (int i = 0; i < genNumVehicles; i++)
				{
					sysArbre2.addVehicleArbre(p);
				}
			
		}
	}
	sysArbre2.updateArbre();
	sysArbre2.drawArbre();
}