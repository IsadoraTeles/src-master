#include "Phenotype.h"

Phenotype::Phenotype()
{

}

void Phenotype::setup(DNA_Plante _dna, float _x, float _y)
{
	dna = _dna;
	location = ofVec2f(_x, _y);
	fitness = 1;
}

void Phenotype::calculate()
{
	// we are using the phenotype's DNA to pick properties for the drawing
	// such as: size, color, angle
	// now, since every gene is a flowting point between 0 and 1, we map the values
	float radius = ofMap(dna.genes[0], 0, 1, 1.0, 3.0);
	float len = ofMap(dna.genes[1], 0, 1, 20, 30);
	float angle = ofMap(dna.genes[2], 0, 1, 15, 35);
	float changeLen = ofMap(dna.genes[3], 0, 1, 0.8, 1.0);

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
	pathPoints.resize(path.points.size());
	for (int i = 0; i < path.points.size(); i++)
	{
		pathPoints.push_back(path.points[i]);
	}

	// SYSTEME

	int genIntervalAttractor = int(ofMap(dna.genes[0], 0, 1, 600, 1200));
	float genDecreaseRate = ofMap(dna.genes[3], 0, 1, 0.5, 1.0);
	float genAttract = dna.genes[0];
	float genTs = ofMap(dna.genes[3], 0, 1, 2.5, 5.0);
	float genMf = ofMap(dna.genes[0], 0, 1, 2.3, 3.5);
	float genMass = ofMap(dna.genes[1], 0, 1, 9, 18);
	float genRadius = ofMap(dna.genes[2], 0, 1, 1, 4);
	float genRed = ofMap(dna.genes[2], 0, 1, 0.5, 1.0);
	float genGreen = ofMap(dna.genes[1], 0, 1, 0.3, 0.8);
	float genBlue = ofMap(dna.genes[3], 0, 1, 0.1, 0.5);
	bool genFleur = false;
	float genWanderRadius = ofMap(dna.genes[1], 0, 1, 30, 90);
	float genWanderDistance = ofMap(dna.genes[2], 0, 1, 10, 20);
	float genChange = ofMap(dna.genes[3], 0, 1, 180, 360);
	genNumVehicles = int(ofMap(dna.genes[0], 0, 1, 7, 20));
	genIntervalDrawVehicles = int(ofMap(dna.genes[1], 0, 1, 30, 60));

	ofVec3f c(genRed, genGreen, genBlue);

	sys.setupWithPath(origin, pathPoints);
	sys.setGeneticData(genIntervalAttractor, genDecreaseRate, genAttract, genTs, genMf, genMass, genRadius, c, genFleur, genWanderRadius, genWanderDistance, genChange);

	cout << genAttract << endl;
}

void Phenotype::incrementFitness(float &_pluieValue, float &_ventValue, float &_soleilValue, float &_humiditeValue)
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

void Phenotype::newPath()
{
	path.generatePoints();
	path.addPoints();

	pathPoints.clear();
	pathPoints.resize(path.points.size());
	for (int i = 0; i < path.points.size(); i++)
	{
		pathPoints.push_back(path.points[i]);
	}
	sys.updatePath(pathPoints);
}

void Phenotype::evolvePath()
{
	if (counter < 3)
	{
		newPath();
		counter++;
	}
}

void Phenotype::drawPath()
{
	path.drawPoints();
}

void Phenotype::drawSys()
{
	// SYSTEME DE VEHICULES

	for (int i = 0; i < genNumVehicles; i++)
	{
		if (ofGetFrameNum() % genIntervalDrawVehicles == 0)
		{
			sys.addVehicle();
		}
	}
	sys.update();
	sys.draw();
}