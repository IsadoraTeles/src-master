#pragma once
#ifndef _LSYSTEM
#define _LSYSTEM
#include "Rule.h"

/*

Keeping track of fractal structures that require complex and multi-faceted production rules

have to be confortable with:
a) Recursion
b) Transformation matrices
c) Strings

Three main components:
1) Alphabet
Valid characters
2) Axiom
A sentence (made up with characters from the alphabet) that describes the initial state of the system
3) Rules
Rules applied to the axiom and then applied recursively, generating new sentences over and over again
An L-system rule includes two sentences:
Predecessor
Successor

*/

class LSystem
{
public:
	LSystem();

	// Methods
	void setup(string axiom, vector <Rule> r);
	void generate();
	string getSentence();
	int getGeneration();
	// Variables
	string sentence;
	int generation;

	// Objects
	vector <Rule> ruleset; // a vector of rule objects


private:

};
#endif // !_LSYSTEM