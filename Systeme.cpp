#include "Systeme.h"

Systeme::Systeme()
{

}

void Systeme::setupWithPath(ofVec3f _origin, vector <ofVec3f> &_path)
{
	path = _path;
	xoff = 2000;
	yoff = 0;
	origin = _origin;
	attractor = ofVec3f(origin.x, origin.y - 300, 0.0);
}

void Systeme::setupWithoutPath(ofVec3f _origin)
{
	xoff = 2000;
	yoff = 0;
	origin = _origin;
	attractor = origin;
}

void Systeme::setGeneticData(int _intervalAttractor, float _decreaseRate, float _attract, float _ts, float _mf, float _mass, float _radius, ofVec3f _color, bool _fleur, float _wanderRadius, float _wanderDistance, float _change)
{
	intervalAttractor = _intervalAttractor;
	decrease = _decreaseRate;
	attract = _attract;
	ts = _ts;
	mf = _mf;
	mass = _mass;
	radius = _radius;
	red = _color.x;
	green = _color.y;
	blue = _color.z;
	fleur = _fleur;
	wanderRadius = _wanderRadius;		// radius for wander circle
	wanderDistance = _wanderDistance;	// Distance for our wander circle
	change = _change;
}

void Systeme::update()
{
	ofVec3f wind = ofVec3f(ofMap(ofNoise(xoff), 0, 1, -2, 2), ofMap(ofNoise(yoff), 0, 1, -1, 1), 0.0);

	if (!fleur)
	{
		for (int i = 0; i < vehicles.size(); i++)
		{

			if (ofGetFrameNum() % MAX(1, intervalAttractor) == 0)
			{
				attractor = ofVec3f(ofRandom(origin.x - 150, origin.x + 150), ofRandom(origin.y - 50, origin.y - 250), 0);
			}

			vehicles[i]->wander(wanderRadius, wanderDistance, change);
			vehicles[i]->followPath(path, radius);
			vehicles[i]->separate(vehicles);

			if (attract > 0.7)
			{
				vehicles[i]->seekTarget(attractor);
				vehicles[i]->applyForce(wind);
			}

			vehicles[i]->update(decrease);
			vehicles[i]->borders();

			if (vehicles[i]->isDead())
			{
				vehicles.erase(vehicles.begin() + i);
			}
		}
	}

	else if (fleur)
	{
		for (int i = 0; i < vehicles.size(); i++)
		{
			vehicles[i]->wander(wanderRadius, wanderDistance, change);
			vehicles[i]->separate(vehicles);
			vehicles[i]->applyForce(wind);
			vehicles[i]->update(decrease);
			vehicles[i]->borders();

			if (vehicles[i]->isDead())
			{
				vehicles.erase(vehicles.begin() + i);
			}
		}
	}


	xoff += 0.001;
	yoff += 0.01;
}

void Systeme::updateArbre()
{
	ofVec3f wind = ofVec3f(ofMap(ofNoise(xoff), 0, 1, -1, 1), ofMap(ofNoise(yoff), 0, 1, -1, 1), 0.0);

	for (int i = 0; i < vehicles.size(); i++)
	{
		vehicles[i]->wander(wanderRadius, wanderDistance, change);
		vehicles[i]->separate(vehicles);
		vehicles[i]->update(decrease);
		vehicles[i]->borders();

		if (vehicles[i]->isDead())
		{
			vehicles.erase(vehicles.begin() + i);
		}
	}

	xoff += 0.001;
	yoff += 0.1;
}

void Systeme::draw()
{
	if (fleur)
	{
		for (auto &v : vehicles)
		{
			v->drawHerbe(red, green, blue);
		}
	}
	else if (!fleur)
	{
		for (auto &v : vehicles)
		{
			v->drawPlant(red, green, blue);
		}
	}
}

void Systeme::drawArbre()
{
	for (auto &v : vehicles)
	{
		v->drawArbre(red, green, blue);
	}
}

void Systeme::addVehicle()
{
	Vehicule* tempVehicle;
	tempVehicle = new Vehicule;
	tempVehicle->setup(origin, ts, mf, mass);
	vehicles.push_back(tempVehicle);
}

void Systeme::addVehicleHerbe()
{
	ofVec3f loc = ofVec3f(ofRandom(origin.x - 400 * 0.5, origin.x + 400 * 0.5), origin.y, origin.z);
	float tts = ts + ofRandom(0.2, 0.8);
	Vehicule* tempVehicle;
	tempVehicle = new Vehicule;
	tempVehicle->setupHerbe(loc, origin, tts, mf, mass);
	vehicles.push_back(tempVehicle);
}

void Systeme::addVehicleArbre(ofVec3f &_loc)
{
	ofVec3f loc = _loc;
	Vehicule* tempVehicle;
	tempVehicle = new Vehicule;
	tempVehicle->setupHerbe(loc, origin, ts, mf, mass);
	vehicles.push_back(tempVehicle);
}

void Systeme::applyForce(ofVec3f _force)
{
	for (auto &v : vehicles)
	{
		v->applyForce(_force);
	}
}

void Systeme::updatePath(vector <ofVec3f> &_path)
{
	path = _path;
}