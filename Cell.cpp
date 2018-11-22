#include "Cell.h"

Cell::Cell(float x_, float y_, float w_)
{
	x = x_;
	y = y_;
	w = w_;

	state = int(ofRandom(4));
	previous = state;
}

void Cell::savePrevious()
{
	previous = state;
}

void Cell::newState(int s)
{
	state = s;
}

void Cell::display()
{
	ofFill();

	if (state == 1)
	{
		ofSetColor(ofColor::green);
	}
	else if (state == 2)
	{
		ofSetColor(ofColor::red);
	}
	else if (state == 3)
	{
		ofSetColor(ofColor::blue);
	}
	else if (state == 0)
	{
		ofSetColor(0);
	}

	ofDrawRectangle(x, y, w, w);
}