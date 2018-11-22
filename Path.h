#pragma once
#ifndef _PATH
#define _PATH
#include "Turtle.h"
#include "LSystem.h"

class Path
{
public:
	// PATH STUFF
	Path();

	// Methods
	void setup(ofVec3f _origin, float _radius, float _len, float _angle, float _changeLen);
	void generatePoints();
	void addPoints();
	void drawPoints();

	// Variables
	float radius;
	ofVec3f origin;

	// Objects
	vector <ofVec3f> points;
	vector <ofVec3f> fleurs;

	// LSYSTEM STUFF
	// Variables
	float width;
	float height;
	int counter = 0;
	int numRules;
	float changeLen = 0;

	// Objects
	LSystem lsys;
	Turtle turtle;
	vector <Rule> ruleset;
	Rule rule0;


private:

};
#endif // !_RULE