#pragma once
#ifndef _SYSTEME
#define _SYSTEME
#include "Vehicule.h"

class Systeme
{
public:

	Systeme();

	// FONCTIONALITES
	void setupWithPath(ofVec3f _origin, vector <ofVec3f> &_path);
	void setupWithoutPath(ofVec3f _origin);
	void update();
	void updateArbre();
	void draw();
	void drawArbre();
	void applyForce(ofVec3f _force);
	void addVehicle();
	void addVehicleHerbe();
	void addVehicleArbre(ofVec3f &_loc);
	//bool checkDead(Vehicle &v);
	void updatePath(vector <ofVec3f> &_path);
	void setGeneticData(int _intervalAttractor, float _decreaseRate, float _attract, float _ts, float _mf, float _mass, float _radius, ofVec3f _color, bool _fleur, float _wanderRadius, float _wanderDistance, float _change);

	// ELEMENTS
	float radius = 0.0;
	float xoff = 0.0;
	float yoff = 0.0;
	int indexPlante = 0;
	int intervalAttractor = 0;
	float decrease = 0.0;
	float attract = 0.0;
	float ts = 0.0;
	float mf = 0.0;
	float mass = 0.0;
	float red = 0.0;
	float green = 0.0;
	float blue = 0.0;
	bool fleur = false;
	float wanderRadius = 0.0;
	float wanderDistance = 0.0;
	float change = 0.0;

	// VECTEURS
	ofVec3f origin;
	ofVec3f attractor;

	// AMIS
	vector <Vehicule*> vehicles;
	vector <ofVec3f> path;

private:

};
#endif // !_SYSTEME
