#include "Path.h"

Path::Path()
{

}

void Path::setup(ofVec3f _origin, float _radius, float _len, float _angle, float _changeLen)
{
	// PATH STUF
	radius = _radius;
	origin = _origin;

	// LSYSTEM STUFF
	width = ofGetWidth();
	height = ofGetHeight();

	float len = _len;
	float angle = _angle;
	changeLen = _changeLen;

	counter = 0;
	numRules = 1;
	ruleset.resize(numRules);
	ruleset[0] = rule0;

	/*
	Formules et angles pour les lsystemes

	n=4, δ=22.5◦
	F
	F → FF-[-F+F+F]+[+F-F-F]

	n=5, δ=20◦
	F
	F → F[+F]F[-F][F]

	n=5, δ=22.5◦
	X
	X → F-[[X]+X]+F[+FX]-X
	F → FF

	n=7, δ=25.7◦
	X
	X → F[+X][-X]FX
	F → FF

	// arbre en trois dimentions 
	n=7, δ=22.5◦
	ω : A
	p1 : A → [&FL!A]/////’[&FL!A]///////’[&FL!A]
	p2 : F → S ///// F
	p3 : S → F L
	p4 : L → [’’’∧∧{-f+f+f-|-f+f+f}]

	// stochastic lsystems
	ω : F
	p1 : F .33 → F[+F]F[−F]F
	p2 : F .33 → F[+F]F
	p3 : F .34 → F[−F]F

	*/

	float random = ofRandom(0, 1);
	if (random < 0.3)
	{
		ruleset[0].setup('F', "F[+F]F[-F][F]");
	}
	else if (random < 0.6)
	{
		ruleset[0].setup('F', "F[+F]F[-F]F");
	}
	else
	{
		ruleset[0].setup('F', "FF-[-F+F+F]+[+F-F-F]");
	}


	lsys.setup("F-F+F+", ruleset);
	turtle.setup(lsys.getSentence(), len, angle);
}

void Path::addPoints()
{
	if (counter < 4)
	{
		lsys.generate();
		turtle.setToDo(lsys.getSentence());
		turtle.changeLen(changeLen);
		counter++;
	}
}

void Path::generatePoints()
{
	turtle.render(origin);
	points = turtle.points;
	fleurs = turtle.fleurs;
}

void Path::drawPoints()
{
	for (int i = 1; i < points.size() - 1; i++)
	{
		/*
		if ((points[i].y < (origin.y - 512)) || (points[i].x >(origin.x + 256)) || (points[i].x < (origin.x - 256)) ||
			(points[i + 1].y < (origin.y - 512)) || (points[i + 1].x >(origin.x + 256)) || (points[i + 1].x < (origin.x - 256)))
		{
			break;
		}
		else
		{
		*/
			ofEnableSmoothing();
			ofSetColor(ofColor::chocolate.r - (i/2), ofColor::chocolate.g, ofColor::chocolate.b + ofRandom(0, 100));
			ofDrawEllipse(points[i - 1], 7.0, 7.0);
			ofSetLineWidth(1.0 + (15.0 / MAX(0.31, (i))));
			ofDrawLine(points[i- 1], points[i]);
		//}
		
	}
}