#pragma once
#ifndef _VEHICULE
#define _VEHICULE
#include "ofMain.h"

class Vehicule
{
public:

	Vehicule();

	// FONCTIONALITES
	void setup(ofVec3f _origin, float ts, float mf, float _mass);
	void setupHerbe(ofVec3f _loc, ofVec3f _origin, float ts, float mf, float _mass);
	void applyForce(const ofVec3f &_force);
	void seekTarget(ofVec3f &_target);
	void flee(ofVec3f &_target);
	void wander(float _wanderRadius, float _wanderDistance, float _change);
	void followPath(vector <ofVec3f> _points, float _radius);
	ofVec3f getNormalPointAtPath(ofVec3f &_p, ofVec3f &_a, ofVec3f &_b);
	void separate(vector <Vehicule*> vehicles);
	void update(float _decrease);
	void drawHerbe(float _red, float _green, float _blue);
	void drawPlant(float _red, float _green, float _blue);
	void drawArbre(float _red, float _green, float _blue);
	bool isDead();
	void borders();


	// ELEMENTS
	float maxSpeed = 0.0;
	float maxForce = 0.0;
	float angle = 0.0;
	float wanderTheta = 0.0;
	float r = 0.0;
	float mass = 0.0;
	float worldRecord = 0.0;
	float radius = 0;
	float lifeSpan = 0.0;
	float lifeSpanDecrease = 0.0;
	float red = 0.0;
	float green = 0.0;
	float blue = 0.0;

	// VECTEURS
	ofVec3f origin;
	ofVec3f location;
	ofVec3f velocity;
	ofVec3f acceleration;

	ofVec3f normal;
	ofVec3f target;
	vector <ofVec3f> points;

	// AUTRES AMIS
	ofColor c;

private:


};
#endif // !_VEHICULE
