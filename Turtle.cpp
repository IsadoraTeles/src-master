#include "Turtle.h"

Turtle::Turtle()
{

}

void Turtle::setup(string s, float l, float t)
{
	todo = s;
	len = l;
	theta = t;
	xoff = 0;
	yoff = 0;
}

void Turtle::render(ofVec3f _origin)
{
	points.clear();
	ofVec3f origine = _origin;
	ofVec3f current(origine);
	ofVec3f direction(0, -len, 0);
	vector <ofVec3f> tmpCurrent;
	vector <ofVec3f> tmpDirection;
	points.push_back(origine);
	int isOver = 0;

	//theta += ofMap(ofNoise(xoff), 0, 1, -0.1, 0.1);

	for (int i = 0; i < todo.size(); i++)
	{
		char c = todo[i];

		/*
		if (i % 2 == 0)
		{
			theta *= -1;
		}
		*/
		if (c == 'F' || c == 'X')
		{
			current += direction;
			if (current.x > (origine.x + 256) || current.x < (origine.x - 256) || current.y > (origine.y) || current.y < (origine.y - 512))
			{
				break;
			}
			else 
			{
				points.push_back(current);
				/*
				if (i % 4 == 0)
				{
					fleurs.push_back(current);
				}
				*/
			}
		}

		else if (c == '+')
		{
			direction.rotate(theta, ofVec3f(0, 0, 1));
		}

		else if (c == '-')
		{
			direction.rotate(theta, ofVec3f(0, 0, -1));
		}

		else if (c == '[')
		{
			//points.push_back(current);
			tmpCurrent.push_back(current);
			tmpDirection.push_back(direction);
			//fleurs.push_back(current);
		}

		else if (c == ']')
		{
			//points.push_back(current);
			//if (i % 2 == 0)
			//{
				//if (current.x < (origine.x + 256) & current.x > (origine.x - 256) & current.y < (origine.y) & current.y > (origine.y - 512))
				//{
					fleurs.push_back(current);
				//}
			//}

			//fleurs.push_back(current);


			current = tmpCurrent[tmpCurrent.size() - 1];
			tmpCurrent.erase(tmpCurrent.begin() + tmpCurrent.size() - 1);

			direction = tmpDirection[tmpDirection.size() - 1];
			tmpDirection.erase(tmpDirection.begin() + tmpDirection.size() - 1);

			//fleurs.push_back(current);
		}
	}
	//xoff += 0.001;
}

void Turtle::setLen(float l)
{
	len = l;
}
void Turtle::changeLen(float percent)
{
	len *= percent;
}

void Turtle::setToDo(string s)
{
	todo = s;
}