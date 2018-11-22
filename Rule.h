#pragma once
#ifndef _RULE
#define _RULE
#include "ofMain.h"

// LSystem Ruel class

class Rule
{
public:
	Rule();

	// Methods
	void setup(char _a, string _b);
	char getA();
	string getB();

	// Variables
	char a;
	string b;

	// Objects


private:

};
#endif // !_RULE