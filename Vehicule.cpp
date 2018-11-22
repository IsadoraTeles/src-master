#include "Vehicule.h"

Vehicule::Vehicule()
{

}

void Vehicule::setup(ofVec3f _origin, float ts, float mf, float _mass)
{
	c = ofFloatColor(ofRandom(0.1, 1), ofRandom(0.1, 1), ofRandom(0.1, 1));
	acceleration.set(0, 0, 0);
	velocity.set(0.5, -1, 0);
	origin = _origin;
	location = origin;

	mass = _mass;
	r = mass * 0.5;

	maxForce = mf;
	maxSpeed = ts;

	lifeSpan = 255;
	lifeSpanDecrease = 1;
}

void Vehicule::setupHerbe(ofVec3f _loc, ofVec3f _origin, float ts, float mf, float _mass)
{
	c = ofFloatColor(ofRandom(0.1, 1), ofRandom(0.1, 1), ofRandom(0.1, 1));
	acceleration.set(0, 0, 0);
	velocity.set(0.5, -1, 0);
	origin = _origin;
	location = _loc;

	mass = _mass;
	r = mass * 0.5;

	maxForce = mf;
	maxSpeed = ts;

	lifeSpan = 255;
	lifeSpanDecrease = 1;
}

void Vehicule::update(float _decrease)
{
	float decrease = _decrease;
	decrease = ofRandom(decrease, decrease + 2.0);
	velocity += acceleration;
	location += velocity;
	velocity.limit(maxSpeed);
	acceleration *= 0;

	angle = ofRadToDeg(atan2(velocity.y, velocity.x)) + 90;

	lifeSpan -= decrease;
}

void Vehicule::drawPlant(float _red, float _green, float _blue)
{
	red = _red;
	green = _green;
	blue = _blue;
	float life = lifeSpan;
	float inverseTime = abs(life - 250);
	// ofSetColor(c.r + red*inverseTime*0.9, c.g - green*inverseTime*0.9, c.b + blue*inverseTime*0.1, 255);
	ofSetColor(red*inverseTime, green*(inverseTime + 15), blue*inverseTime*0.9, 255);

	ofPushMatrix();
	ofTranslate(location);
	ofRotate(angle);
	ofDrawRectangle(ofVec3f(0, 0, 0), r*0.5, r);
	ofPopMatrix();
}

void Vehicule::drawHerbe(float _red, float _green, float _blue)
{
	red = _red;
	green = _green;
	blue = _blue;
	float life = lifeSpan;
	float inverseTime = abs(life - 250);
	// ofSetColor(c.r + red*inverseTime*0.9, c.g - green*inverseTime*0.9, c.b + blue*inverseTime*0.1, 255);
	ofSetColor(red*inverseTime, green*inverseTime, blue * 60, 255);

	ofPushMatrix();
	ofTranslate(location);
	ofRotate(angle);
	ofDrawRectangle(ofVec3f(0, 0, 0), r*0.5, r);
	ofPopMatrix();
}

void Vehicule::drawArbre(float _red, float _green, float _blue)
{
	red = _red;
	green = _green;
	blue = _blue;
	float life = lifeSpan;
	float inverseTime = abs(life - 250);
	// ofSetColor(c.r + red*inverseTime*0.9, c.g - green*inverseTime*0.9, c.b + blue*inverseTime*0.1, 255);
	ofSetColor(red*inverseTime, green*inverseTime*0.8, blue * 150, 255);

	ofPushMatrix();
	ofTranslate(location);
	ofRotate(angle);
	ofDrawRectangle(ofVec3f(0, 0, 0), r*0.5, r);
	ofPopMatrix();
}

void Vehicule::applyForce(const ofVec3f &_force)
{
	// Newton's second law with accumulation of mass
	ofVec3f force = _force;
	force /= MAX(mass,0.001f);
	acceleration += force;
}

bool Vehicule::isDead()
{
	if (lifeSpan <= 0.0)
	{
		return true;
	}
	else
	{
		return false;
	}
}

void Vehicule::followPath(vector <ofVec3f> _points, float _radius)
{
	points.resize(_points.size());
	points = _points;
	radius = _radius;

	// Step 1: Predict the vehicle's future location
	ofVec3f predict = velocity;
	predict.normalize();
	predict *= 30;	// arbitrary value for distance of target on path
	ofVec3f predictLoc = location + predict;

	// Step 2: Find the normal point along the path
	worldRecord = 100000000;
	// Loop through all points of the path
	for (int i = 0; i < points.size() - 1; i++)
	{
		// look at a line segment
		ofVec3f a(points[i]);
		ofVec3f b(points[i + 1]);

		// get the normal point to that line
		ofVec3f normalPoint = getNormalPointAtPath(predictLoc, a, b);

		if (normalPoint.x <= a.x || normalPoint.x >= b.x)
		{
			normalPoint.set(b.x, b.y);
		}

		// how far are we from the path?
		// Step 4: if we are off the path, seek the target in order to stay on the path
		float distance = normalPoint.distance(predictLoc);
		if (distance < worldRecord)
		{
			worldRecord = distance;
			normal = normalPoint;
			ofVec3f dir = b - a;
			dir.normalize();
			dir *= 20; // magnitude of the force direction
			target.set(normalPoint);
			target += dir;
		}
	}

	// Step 4: if we are off the path, seek the target in order to stay on the path
	if (worldRecord > radius)
	{
		seekTarget(target);
	}
}

ofVec3f Vehicule::getNormalPointAtPath(ofVec3f &_p, ofVec3f &_a, ofVec3f &_b)
{
	ofVec3f ap = _p - _a;	// vector that points from a to p
	ofVec3f ab = _b - _a;	// vector that points from a to b

							// Using the dot product for scalar projection
	ab.normalize();
	ab *= (ap.dot(ab));

	ofVec3f normalPoint = _a + ab;	// finding the normal point along the line segment

	return normalPoint;
}

void Vehicule::seekTarget(ofVec3f &_target)
{
	ofVec3f desired = _target - location;

	float d = desired.length();				// The distance is the magnitude of the vector pointing from location to target
	desired.normalize();
	if (d < 100)							// if we're closer than 100 pixels
	{
		float m = ofMap(d, 0, 100, 0, maxSpeed);	// set the magnitude according to how close we are
		desired *= m;
	}
	else
	{
		desired *= maxSpeed;				// otherwise, proceed at maximum speed
	}

	ofVec3f steer = desired - velocity;		// Reynolds formula for steering force
	steer.limit(maxForce);					// limit the magnitude of the steering force
	applyForce(steer);						// using our physics model and applying the force to the object's acceleration
}

void Vehicule::flee(ofVec3f &_target)		// A TESTER
{
	ofVec3f desired = _target - location;
	float d = desired.length();				// The distance is the magnitude of the vector pointing from location to target
	desired.normalize();
	desired *= -1;							// inverse of seek

	if (d < 60)							// if we're closer than 100 pixels
	{
		float m = ofMap(d, 0, 60, 0, maxSpeed);	// set the magnitude according to how close we are
		desired *= m;
	}
	else
	{
		desired *= maxSpeed;				// otherwise, proceed at maximum speed
	}

	ofVec3f steer = desired - velocity;		// Reynolds formula for steering force
	steer.limit(maxForce);					// limit the magnitude of the steering force
	applyForce(steer);						// using our physics model and applying the force to the object's acceleration
}

void Vehicule::wander(float _wanderRadius, float _wanderDistance, float _change)
{
	/*
	float wanderRadius = 360;	// radius for wander circle
	float wanderDistance = 100;	// Distance for our wander circle
	float change = 100;
	*/

	float wanderRadius = _wanderRadius;	// radius for wander circle
	float wanderDistance = _wanderDistance;	// Distance for our wander circle
	float change = _change;

	wanderTheta += ofRandom(-change, change);	// randomly change wander theta

												// Now we have to calculate the new location to steer towards on the wander circle
	ofVec3f circleLoc = velocity;	// start with velocity
	circleLoc.normalize();			// normalize to get heading (direction)
	circleLoc *= wanderDistance;	// multiply by distance
	circleLoc += location;			// make relative to wanderer location

	float h = ofRadToDeg(atan2f(velocity.y, velocity.x)); // heading

	ofVec3f circleOffset = ofVec3f(wanderRadius * (cos(wanderTheta + h)), wanderRadius * (sin(wanderTheta + h)));
	ofVec3f target = circleLoc + circleOffset;
	seekTarget(target);
}

void Vehicule::separate(vector <Vehicule*> vehicles)
{
	float desiredSeparation = r * 3;
	ofVec3f sum;
	int count = 0;

	for (auto &v : vehicles)
	{
		float d = (location - v->location).length();
		if ((d > 0) && (d < desiredSeparation))
		{
			ofVec3f diff = location - v->location;
			diff.normalize();
			diff /= MAX(d,0.001f);
			sum += diff;
			count++;
		}
	}
	if (count > 0)
	{
		sum /= MAX(count,0.001f);
		sum.normalize();
		sum *= maxSpeed;

		sum -= velocity;
		sum.limit(maxForce);
	}
	applyForce(sum);
}

/*
void Vehicule::borders()
{
if (location.x < origin.x - 480*0.5)
{
location = ofVec3f(origin.x, origin.y, 0.0);
}
if (location.y < origin.y - 480)
{
location = ofVec3f(origin.x, origin.y, 0.0);
}
if (location.x > origin.x + 480*0.5)
{
location = ofVec3f(origin.x, origin.y, 0.0);
}
if (location.y > origin.y + 10)
{
lifeSpan = 0;
}
}
*/

void Vehicule::borders()
{
	//cout << location.x << endl;

	float ran = ofRandom(1, 20);

	if (location.x < origin.x - (470 + ran) * 0.5)
	{
		lifeSpan = 0;
	}
	if (location.y < origin.y - (470 + ran))
	{
		lifeSpan = 0;
	}
	if (location.x > origin.x + (470 + ran) * 0.5)
	{
		lifeSpan = 0;
	}
	if (location.y > (origin.y-5) + ran)
	{
		lifeSpan = 0;
	}
}
