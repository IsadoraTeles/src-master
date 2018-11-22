#pragma once
#ifndef _CELL
#define _CELL
#include "ofMain.h"

class Cell
{
public:
	Cell(float, float, float);
	void display();
	void newState(int);
	void savePrevious();


	float x;
	float y;
	float w;

	int state;
	int previous;

private:

};
#endif // !_CELL