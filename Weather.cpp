#include "Weather.h"

Weather::Weather()
{
	mode = "xml";
	APIkey = "b24517c8085c888291aef507c04b96a6";
	city = "7873240"; //now it is Linz, Austria//by default, Paris France ->6455259
	url = "http://api.openweathermap.org/data/2.5/weather?id=" + city + "&APPID=" + APIkey + "&mode=" + mode + "&units=metric";
	resp = ofLoadURL(url);
	weather.loadFromBuffer(resp.data.getData());	
}

void Weather::changeCity(string cityID)
{
	this->newTown = true;
	city = cityID;
	url = "http://api.openweathermap.org/data/2.5/weather?id=" + city + "&APPID=" + APIkey + "&mode=" + mode + "&units=metric";
	this->update();
}

void Weather::setNewTown(bool state)
{
	this->newTown = state;
}

void Weather::correctUTC(int UTC)
{
	this->UTCValue = UTC;
}

int Weather::getUTC()
{
	return this->UTCValue;
}

void Weather::update()
{
	resp = ofLoadURL(url);
	weather.loadFromBuffer(resp.data.getData());
	weather.setTo("current");
	name = weather.getAttribute("city[@name]");
	if (name != "") 
	{
	temperature = atof(weather.getAttribute("temperature[@value]").c_str());
	humidity = atof(weather.getAttribute("humidity[@value]").c_str())*0.01;
	clouds = (atof(weather.getAttribute("clouds[@value]").c_str())*0.01);
	precipitation = atof(weather.getAttribute("precipitation[@value]").c_str())*0.03;
	lastupdate = weather.getAttribute("lastupdate[@value]");
	weather.setTo("city");
	citySunRise = weather.getAttribute("sun[@rise]");
	citySunRiseHours = atof(citySunRise.substr(11, 2).c_str());
	citySunRiseMinutes = atof(citySunRise.substr(14, 2).c_str());
	citySunSet = weather.getAttribute("sun[@set]");
	citySunSetHours = atof(citySunSet.substr(11, 2).c_str());
	citySunSetMinutes = atof(citySunSet.substr(14, 2).c_str());
	weather.setToParent();
	weather.setTo("wind");
	windSpeed = atof(weather.getAttribute("speed[@value]").c_str())*0.1+0.05;
	windDirection = atof(weather.getAttribute("direction[@value]").c_str());
	citySunRiseHours += UTCValue;
	citySunSetHours += UTCValue;
	//remap between 0 et 23
	if (citySunRiseHours < 0) { citySunRiseHours += 24; }
	if (citySunSetHours < 0) { citySunSetHours += 24; }
	citySunRiseHours = citySunRiseHours % 24;
	citySunSetHours = citySunSetHours % 24;
	//show data, can be removed
	cout << "Data received from API" << endl;
	//cout << resp.data << endl;
	
	}
	else {
		name = "Cacahuete Land";
		temperature = 15;
		humidity = 20 * 0.01;
		clouds = 80*0.01;
		precipitation = 0*0.01;
		citySunRiseHours = 7;
		citySunRiseMinutes =32;
		citySunSetHours = 16;
		citySunSetMinutes = 20;
		windSpeed = 15*0.01;
		windDirection = 90;
		citySunRiseHours += UTCValue;
		citySunSetHours += UTCValue;
		//remap between 0 et 23
		if (citySunRiseHours < 0) { citySunRiseHours += 24; }
		if (citySunSetHours < 0) { citySunSetHours += 24; }
		citySunRiseHours = citySunRiseHours % 24;
		citySunSetHours = citySunSetHours % 24;
		cout << "Failed to load API, we choose random values, next checking in 2 minutes" << endl;
	}
}

Weather::~Weather()
{

}