#pragma once

#include "ofMain.h"

class Weather
{
public:
	Weather();
	~Weather();
	
	string name;
	float temperature;
	float  humidity;
	float clouds;
	float precipitation;
	string lastupdate;	
	int citySunRiseHours;
	int citySunRiseMinutes;	
	int citySunSetHours;
	int citySunSetMinutes;
	float windSpeed;
	float windDirection;

	void update();
	void changeCity(string cityID);
	void correctUTC(int UTC);
	int getUTC();

	bool newTown = false;
	void setNewTown(bool state);

	string citySunSet;
	string citySunRise;
	int UTCValue;
	string mode;
	string APIkey;
	ofHttpResponse resp;
	ofXml weather;
	string city;
	string url;
private:
	
};