#pragma once
#include "ofMain.h"
#include "ofxSpout2Receiver.h"
#include "ofxSpout2Sender.h"

class SpoutInOut
{
public:
	SpoutInOut();
	~SpoutInOut();

	void setup();
	void update();
	void showSenders();
	void sendTexture(ofTexture texture, string spoutName);
	void exit();
	void draw();

	//placement
	void setPosition(ofVec3f pos);
	void setScale(ofVec3f scale);
	void setSize(float x, float y);

	//Spout In/Out
	ofxSpout2::Receiver unityReceiver;
	ofxSpout2::Sender spoutSender;

	ofPlanePrimitive farmerPlane;

private:

};
