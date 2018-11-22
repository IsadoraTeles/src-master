#include "Rule.h"

Rule::Rule()
{

}

void Rule::setup(char _a, string _b)
{
	a = _a;
	b = _b;
}

char Rule::getA()
{
	return a;
}

string Rule::getB()
{
	return b;
}