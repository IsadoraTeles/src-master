#pragma once
#ifndef _GOL
#define _GOL
#include "Cell.h"

class GOL
{
public:
	GOL();
	void init();
	void generate();
	void display();

	int w;
	int columns;
	int rows;
	vector< vector<Cell*> > board;

private:

};
#endif // !_GOL
