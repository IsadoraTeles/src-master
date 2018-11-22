#include "GOL.h"

GOL::GOL()
{
	w = 1;

	columns = 256 / MAX(1,w);
	rows = 256 / MAX(1, w);

	board.resize(columns, std::vector<Cell*>(rows));
	init();
}

void GOL::init()
{
	for (int i = 0; i < columns; i++) {
		for (int j = 0; j < rows; j++) {
			board[i][j] = new Cell(i*w, j*w, w);
		}
	}
}

void GOL::generate()
{
	for (int i = 0; i < columns; i++)
	{
		for (int j = 0; j < rows; j++)
		{
			board[i][j]->savePrevious();
		}
	}

	for (int x = 0; x < columns; x++)
	{
		for (int y = 0; y < rows; y++)
		{
			int neighborsHerbe = 0;
			int neighborsPlante = 0;
			int neighborsArbre = 0;

			for (int i = -1; i <= 1; i++)
			{
				for (int j = -1; j <= 1; j++)
				{
					if (i == 0 && j == 0)
					{
						continue;
					}


					if ((board[(x + i + columns) % columns][(y + j + rows) % rows]->previous) == 1)
					{
						neighborsHerbe += 1;
					}
					else if ((board[(x + i + columns) % columns][(y + j + rows) % rows]->previous) == 2)
					{
						neighborsPlante += 1;
					}
					else if ((board[(x + i + columns) % columns][(y + j + rows) % rows]->previous) == 3)
					{
						neighborsArbre += 1;
					}
				}
			}

			// HERBE
			if ((board[x][y]->state == 1) && (neighborsHerbe < 1))
			{
				board[x][y]->newState(0);	// LONELINESS
			}
			else if ((board[x][y]->state == 1) && (neighborsHerbe > 4))
			{
				board[x][y]->newState(0);	// SUPERPOPULATION
			}
			else if ((board[x][y]->state == 0) && (neighborsHerbe >= 2))
			{
				board[x][y]->newState(1);	// REPRODUCTION
			}
			// HERBE x ARBRE
			else if ((board[x][y]->state == 1) && (neighborsArbre > 3))
			{
				board[x][y]->newState(0);
			}
			// HERBE x PLANTE
			else if ((board[x][y]->state == 1) && (neighborsPlante > 3))
			{
				board[x][y]->newState(0);
			}


			// PLANTE
			else if ((board[x][y]->state == 2) && (neighborsPlante < 2))
			{
				board[x][y]->newState(0);	// LONELINESS
			}
			else if ((board[x][y]->state == 2) && (neighborsPlante > 4))
			{
				board[x][y]->newState(0);	// SUPERPOPULATION
			}
			else if ((board[x][y]->state == 0) && (neighborsPlante >= 2))
			{
				board[x][y]->newState(2);	// REPRODUCTION
			}
			// PLANTE x ARBRE
			else if ((board[x][y]->state == 2) && (neighborsArbre > 5))
			{
				board[x][y]->newState(0);
			}
			// PLANTE x HERBE
			else if ((board[x][y]->state == 2) && (neighborsHerbe > 5))
			{
				board[x][y]->newState(0);
			}

			// ARBRE
			else if ((board[x][y]->state == 3) && (neighborsArbre < 2))
			{
				board[x][y]->newState(0);	// LONELINESS
			}
			else if ((board[x][y]->state == 3) && (neighborsArbre > 5))
			{
				board[x][y]->newState(0);	// SUPERPOPULATION
			}
			else if ((board[x][y]->state == 0) && (neighborsArbre >= 2))
			{
				board[x][y]->newState(3);	// REPRODUCTION
			}
			// ARBRE x PLANTE
			else if ((board[x][y]->state == 3) && (neighborsPlante > 5))
			{
				board[x][y]->newState(0);
			}
			// ARBRE x HERBE
			else if ((board[x][y]->state == 3) && (neighborsHerbe > 5))
			{
				board[x][y]->newState(0);
			}
		}
	}
}

void GOL::display()
{
	for (int i = 0; i < columns; i++)
	{
		for (int j = 0; j < rows; j++)
		{
			board[i][j]->display();
		}
	}
}