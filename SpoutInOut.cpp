#include "SpoutInOut.h"

SpoutInOut::SpoutInOut()
{

}

void SpoutInOut::setup() {
	unityReceiver.setup();
	farmerPlane.set(16, 9);
	farmerPlane.setResolution(2, 2);
	farmerPlane.setPosition(0, 0, -70);
	unityReceiver.updateTexture();
	farmerPlane.mapTexCoordsFromTexture(unityReceiver.getTexture());
	//farmerPlane.roll(180);
	farmerPlane.setScale(2.0, -2.0, 2.0);
}

void SpoutInOut::update()
{
	unityReceiver.updateTexture();
}

void SpoutInOut::setSize(float x, float y)
{
	farmerPlane.set(x, y);
}

void SpoutInOut::setPosition(ofVec3f pos) {
	farmerPlane.setPosition(pos);
}

void SpoutInOut::setScale(ofVec3f scale) {
	farmerPlane.setScale(scale);
}

void SpoutInOut::draw()
{
	unityReceiver.getTexture().bind();
	farmerPlane.draw();
	unityReceiver.getTexture().unbind();
}

void SpoutInOut::sendTexture(ofTexture texture, string spoutName)
{
	spoutSender.sendTexture(texture, spoutName);
}

void SpoutInOut::showSenders()
{
	unityReceiver.showSenders();
}

void SpoutInOut::exit()
{
	unityReceiver.exit();
}

SpoutInOut::~SpoutInOut()
{
}