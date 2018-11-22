#include "LSystem.h"

LSystem::LSystem()
{

}

void LSystem::setup(string axiom, vector <Rule> r)
{
	sentence = axiom;
	ruleset = r;
	generation = 0;
}

void LSystem::generate()
{
	// An empty string that we'll fill
	string nextGen;

	// for every character in the sentence
	for (int i = 0; i < sentence.size(); i++)
	{
		string b;
		// what is the character
		char curr = sentence[i];
		// we will replace it with itself unless it maches one of our rules
		//string replace = "" + curr;
		// Check every rule
		for (int j = 0; j < ruleset.size(); j++)
		{
			bool found = false;
			char a = ruleset[j].getA();
			// if we want the rule, get the replacement string out of the rule
			if (curr == a)
			{
				found = true;
				b = ruleset[j].getB();
				break;
			}
			if (!found)
			{
				b = curr;
			}
		}
		// append replacement string
		nextGen += b;
	}

	// replace the sentence
	sentence = nextGen;

	// increment the generation
	generation++;
}

string LSystem::getSentence()
{
	return sentence;
}

int LSystem::getGeneration()
{
	return generation;
}
