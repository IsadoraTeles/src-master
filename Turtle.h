#pragma once
#ifndef _TURTLE
#define _TURTLE
#include "ofMain.h"

class Turtle
{
public:
	Turtle();

	// Methods
	void setup(string s, float l, float t);
	void render(ofVec3f _origin);
	void setLen(float l);
	void changeLen(float percent);
	void setToDo(string s);

	// Variables
	string todo;
	float len;
	float theta;
	float xoff, yoff;

	// Objects
	vector <ofVec3f> fleurs;
	vector <ofVec3f> points;

private:

};
#endif // !_TURTLE