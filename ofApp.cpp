#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
	myFont.loadFont("calibri.ttf", 16);
	//Global setup
	ofEnableAlphaBlending();
	ofEnableDepthTest();
	ofSetFrameRate(30);
	//glEnable(GL_BLEND);
	//glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	ofBackground(ofColor::bisque);
	sunValueMap = 0.5;
	//Setup Spout
	//spout.setup();	
	ofFbo::Settings settings;
	settings.width = 1280;
	settings.height = 720;
	settings.internalformat = GL_RGBA;
	settings.useDepth = true;
	settings.depthStencilAsTexture = true;
	fboPremierPlan.allocate(settings);
	fboSecondPlan.allocate(settings);
	fboTroisiemePlan.allocate(settings);
	fboQuatriemePlan.allocate(settings);
	fboPluie.allocate(settings);
	//Setup Osc
	sender.setup(HOST, PORT);
	//Setup weather
	weatherInfo.correctUTC(1);
	weatherInfo.changeCity("6454286"); //Laval, France
	//weatherInfo.changeCity("2774369"); //Linz, Austria by default
	computeCurrentTime();
	//Placement Map
	fboPlacementMap.allocate(256, 256, GL_RGB);
	//Genetic Algorithm and Plants setup-------------------------------------
	//ofSetBackgroundAuto(false); //no need for it, fbo doesn't auto clear
	pop.setup(mutationRatePlante1, popMax);
	herbe.setup(mutationRateHerbe1, popMax);
	arbre.setup(mutationRateArbre1, popMax);
	herbe2.setup(mutationRateHerbe2, popMax);
	arbre2.setup(mutationRateArbre2, popMax);
	for (int i = 0; i < 4; i++) 
	{
		pop.evolvePath();
		arbre.evolvePath();
		arbre2.evolvePath();
	}
	// tmpImage.getTextureReference().setTextureMinMagFilter(GL_NEAREST,GL_NEAREST);
	ofFbo::Settings settingsVegi;
	settingsVegi.width = 1024;
	settingsVegi.height = 1024;
	settingsVegi.internalformat = GL_RGBA;
	settingsVegi.useDepth = true;
	settingsVegi.depthStencilAsTexture = true;
	//settingsVegi.numSamples = 2;
	fboPlante.allocate(settingsVegi);
	//fboPlante.getTextureReference().setTextureMinMagFilter(GL_NEAREST, GL_NEAREST);
	fboHerbe.allocate(settingsVegi);
	//fboHerbe.getTextureReference().setTextureMinMagFilter(GL_NEAREST, GL_NEAREST);
	fboArbre.allocate(settingsVegi);
	//fboArbre.getTextureReference().setTextureMinMagFilter(GL_NEAREST, GL_NEAREST);
	fboHerbe2.allocate(settingsVegi);
	//fboHerbe2.getTextureReference().setTextureMinMagFilter(GL_NEAREST, GL_NEAREST);
	fboArbre2.allocate(settingsVegi);
	//fboArbre2.getTextureReference().setTextureMinMagFilter(GL_NEAREST, GL_NEAREST);
	previz.allocate(settingsVegi);
	//previz.getTextureReference().setTextureMinMagFilter(GL_NEAREST, GL_NEAREST);
	presentation.allocate(1920, 1080, GL_RGBA);
	//presentation.getTextureReference().setTextureMinMagFilter(GL_NEAREST, GL_NEAREST);	

	//First fbo cleaning
	clearFbo();

	//Vegetation Placement
	xoff = 0.0f;
	zoff = 0.0f;
	placementSize = 600.0f;
	placementNoiseSpaceFrequency = 1.0f;
	stalkHeight = 10.0f;
	swayingMaxAngle = 10.f;
	swayingTimeScale = weatherInfo.windSpeed+0.1f;
	swayingNoiseSpaceFrequency = 4.0f; 
	swayingTimeMaxDifference = 5.0f;
	vegetationShader.setGeometryInputType(GL_POINTS);
	vegetationShader.setGeometryOutputType(GL_TRIANGLE_STRIP);
	vegetationShader.setGeometryOutputCount(14);
	vegetationShader.load("Shaders/Grass/GL2/Grass.vert", "Shaders/Grass/GL2/Grass.frag", "Shaders/Grass/GL2/Grass.geom");
	//
	genNum = 0;	
	//------------------------------------------------------------
	//Setup Camera
	cameraPremier.setNearClip(0.3f);
	cameraPremier.setFarClip(130.0);
	cameraPremier.setFov(25);
	cameraSecond.setNearClip(30.f);
	cameraSecond.setFarClip(130.f);
	cameraSecond.setFov(25);
	cameraTroisieme.setNearClip(100.f);
	cameraTroisieme.setFarClip(340.f);
	cameraTroisieme.setFov(25);
	cameraQuatrieme.setNearClip(300.f);
	cameraQuatrieme.setFarClip(1000.0f);
	cameraQuatrieme.setFov(25);
	cameraPluie.setNearClip(0.01f);
	cameraPluie.setFarClip(1000.f);
	cameraPluie.setFov(25);

	//-----------------------------------------------------------
	// *** LIGHT *** //
	// turn on smooth lighting //
	ofSetSmoothLighting(true);
	// set the diffuse color, color reflected from the light source //
	// SUN
	light.setDirectional();
	light.setDiffuseColor(ofColor(255, 255, 255));
	light.setSpecularColor(ofColor(255.f, 255.f, 255.f));
	// *** MATERIAL *** //
	// shininess is a value between 0 - 128, 128 being the most shiny //
	material.setDiffuseColor(ofFloatColor(0.5, 0.4, 0.3));
	material.setShininess(64);
	material.setAmbientColor(ofFloatColor(0.2, 0.2, 0.2)); //need an ambiant light
	// *** MESH *** //
	terrain.loadModel("Geometry/terrain06_uvs.obj", 0);
	terrain.setRotation(0, 180, 0, 1, 0);
	terrain.setRotation(0, 180, 0, 0, 1);
	terrain.setScale(1, 1, 1);
	//terrain.setPosition(ofGetWidth() / 2, ofGetHeight() / 2, 0);
	terrain.setPosition(-10, 20, -330);
	// *** ROTATION *** //
	// we define the light's start and end orientation here:  
	startQuat.makeRotate(0, 0, 0, 0);			// zero rotation.  
	targetQuat.makeRotate(45, 1, 1, 0);			// rotation 90 degrees around y-axis.   
	texture.loadImage("Images/tex01.jpg");
	terrainShader.load("Shaders/Ground/ground.vert", "Shaders/Ground/ground.frag");
	// MESH
	int meshIndex = 0;
	ofMatrix4x4 modelMatrix = terrain.getModelMatrix();
	ofMatrix4x4 meshMatrix = terrain.getMeshHelper(meshIndex).matrix;
	ofMatrix4x4 concatMatrix;
	concatMatrix.preMult(modelMatrix);
	concatMatrix.preMult(meshMatrix);

	mesh = terrain.getMesh(meshIndex);
	
	for (int i = 0; i<mesh.getNumVertices(); i++) {
		ofVec3f & vert = mesh.getVertices()[i];
		vert.set(concatMatrix.preMult(vert));
	}
	computeMesh();
	//initShader
	// We need to set a few extra params for the geometry shader, in this order.
	rainShader.setGeometryInputType(GL_POINTS); //cf in ofMesh doc for the different types
	rainShader.setGeometryOutputType(GL_TRIANGLE_FAN);
	rainShader.setGeometryOutputCount(4); //number of vertex output by the geometry shader
	rainShader.load("Shaders/Rain/GL2/Rain.vert", "Shaders/Rain/GL2/Rain.frag", "Shaders/Rain/GL2/Rain.geom");

	//init rain mesh
	boundingBoxHalf = 200.f;
	dropNb = 2000* weatherInfo.precipitation;
	computeRain(dropNb, boundingBoxHalf);
}
//--------------------------------------------------------------
void ofApp::update(){
	//------------------------
	computeCurrentTime();
	sendMessageOSC();
	//SpoutFbo----------------
	fboPremierPlan.begin();
	ofClear(255, 255, 127, 0);
	fboPremierPlan.end();
	fboSecondPlan.begin();
	ofClear(255, 255, 127, 0);
	fboSecondPlan.end();
	fboTroisiemePlan.begin();
	ofClear(255, 255, 127, 0);
	fboTroisiemePlan.end();
	fboQuatriemePlan.begin();
	ofClear(255, 255, 127, 0);
	fboQuatriemePlan.end();
	fboPluie.begin();
	ofClear(255, 255, 127, 0);
	fboPluie.end();
	
	//Terrain-----------------
	// *** ROTATION *** //
	btweenValue = sunValueMap;
	// calculate the interpolated orientation  
	tweenedLightQuaternion.slerp(btweenValue, startQuat, targetQuat);
	// now update the light with the calculated orientation and position. 
	light.setOrientation(tweenedLightQuaternion);

	//PlacementMap
	fboPlacementMap.begin();
	ofClear(255, 255, 127);
	placementMap.display();
	fboPlacementMap.end();
	
	//Vegetation and previz drawing on frameBufferObject
	ofDisableDepthTest();
	//Vegetation
	fboPlante.begin();
	pop.draw();
	fboPlante.end();

	fboHerbe.begin();
	herbe.draw();
	fboHerbe.end();

	fboArbre.begin();
	arbre.draw();
	fboArbre.end();

	fboHerbe2.begin();
	herbe2.draw();
	fboHerbe2.end();

	fboArbre2.begin();
	arbre2.draw();
	fboArbre2.end();	

	previz.begin();
	arbre.draw();
	pop.draw();
	herbe.draw();
	arbre2.draw();
	herbe2.draw();
	//fboArbre.draw(0, 0);
	//fboHerbe.draw(0, 0);
	previz.end();

	presentation.begin();
	// 1
	fboArbre.getTexture().drawSubsection(0, 0, 360, 360, 0, 0, 512, 512);
	fboHerbe.getTexture().drawSubsection(0, 0, 360, 360, 0, 0, 512, 512);
	// 2
	fboArbre.getTexture().drawSubsection(360, 0, 360, 360, 512, 0, 512, 512);
	fboHerbe.getTexture().drawSubsection(360, 0, 360, 360, 512, 0, 512, 512);
	// 3
	fboArbre.getTexture().drawSubsection(720, 0, 360, 360, 0, 512, 512, 512);
	fboHerbe.getTexture().drawSubsection(720, 0, 360, 360, 0, 512, 512, 512);
	// 4
	// void ofTexture::drawSubsection(float x, float y, float w, float h, float sx, float sy, float sw, float sh)
	fboArbre.getTexture().drawSubsection(1080, 0, 360, 360, 512, 512, 512, 512);
	fboHerbe.getTexture().drawSubsection(1080, 0, 360, 360, 512, 512, 512, 512);
	// 5
	fboPlacementMap.draw(1552, 52);
	// 6
	fboArbre2.getTexture().drawSubsection(0, 360, 360, 360, 0, 0, 512, 512);
	fboHerbe2.getTexture().drawSubsection(0, 360, 360, 360, 0, 0, 512, 512);
	// 7 
	fboArbre2.getTexture().drawSubsection(360, 360, 360, 360, 512, 0, 512, 512);
	fboHerbe2.getTexture().drawSubsection(360, 360, 360, 360, 512, 0, 512, 512);
	// 8
	fboArbre2.getTexture().drawSubsection(720, 360, 360, 360, 0, 512, 512, 512);
	fboHerbe2.getTexture().drawSubsection(720, 360, 360, 360, 0, 512, 512, 512);
	// 9
	fboArbre2.getTexture().drawSubsection(1080, 360, 360, 360, 512, 512, 512, 512);
	fboHerbe2.getTexture().drawSubsection(1080, 360, 360, 360, 512, 512, 512, 512);
	// 10
	// 11
	fboPlante.getTexture().drawSubsection(0, 700, 360, 360, 0, 0, 512, 512);
	// 12
	fboPlante.getTexture().drawSubsection(360, 700, 360, 360, 512, 0, 512, 512);
	// 13
	fboPlante.getTexture().drawSubsection(720, 700, 360, 360, 0, 512, 512, 512);
	// 14
	fboPlante.getTexture().drawSubsection(1080, 700, 360, 360, 512, 512, 512, 512);
	// 15
	ofSetColor(ofColor::blueSteel);
	myFont.drawString("GENERATION ACTUELLE : " + ofToString(genNum), 1500, 700);
	myFont.drawString("VILLE : " + ofToString(weatherInfo.name), 1500, 760);
	myFont.drawString("SOLEIL : " + ofToString(abs(weatherInfo.clouds - 1)), 1500, 820);
	myFont.drawString("HUMIDITE : " + ofToString(weatherInfo.humidity), 1500, 880);
	myFont.drawString("VENT : " + ofToString(weatherInfo.windSpeed), 1500, 940);
	myFont.drawString("PLUIE : " + ofToString(weatherInfo.precipitation), 1500, 1000);
	ofSetColor(ofColor::darkGrey);
	// 	fboArbre.getTexture().drawSubsection(0, 0, 360, 360, 0, 0, 512, 512);
	myFont.drawString("POPULATION D'ARBRE ET D'HERBE DU PREMIER PLAN ", 20, 40);
	// 	fboArbre2.getTexture().drawSubsection(0, 360, 360, 360, 0, 0, 512, 512);
	myFont.drawString("POPULATION D'ARBRE ET D'HERBE DU DEUXIEME PLAN ", 20, 380);
	// fboPlante.getTexture().drawSubsection(0, 700, 360, 360, 0, 0, 512, 512);
	myFont.drawString("POPULATION DE PLANTE", 20, 750);
	// 	fboPlacementMap.draw(1552, 52);
	ofSetColor(ofColor::blueSteel);
	myFont.loadFont("calibri.ttf", 15);
	myFont.drawString("DISTRIBUTION DE LA VEGETATION ", 1500, 350);
	myFont.drawString("Interaction entre les elements du paysage ", 1500, 380);
	myFont.drawString("basee sur un algorithme d'automate cellulaire ", 1500, 410);
	myFont.loadFont("calibri.ttf", 16);
	ofSetColor(ofColor::red);
	ofDrawRectangle(1500, 445, 30, 30);
	myFont.drawString("PLANTES ", 1560, 467);
	ofSetColor(ofColor::green);
	ofDrawRectangle(1500, 505, 30, 30);
	myFont.drawString("HERBE ", 1560, 527);
	ofSetColor(ofColor::blue);
	ofDrawRectangle(1500, 565, 30, 30);
	myFont.drawString("ARBRES ", 1560, 587);
	presentation.end();

	ofEnableDepthTest();
}
//--------------------------------------------------------------
void ofApp::draw() {
	fboPremierPlan.begin();
	// *** LIGHT *** //
	// enable lighting //
	ofEnableLighting();
	cameraPremier.begin();
	//Terrain
	light.enable();
	material.begin();
	mesh.draw();
	material.end();
	drawVegetation(&cameraPremier, cameraPremier.getNearClip(), cameraPremier.getFarClip());
	cameraPremier.end();
	ofDisableLighting();
	fboPremierPlan.end();

	fboSecondPlan.begin();
	// *** LIGHT *** //
	// enable lighting //
	ofEnableLighting();
	cameraSecond.begin();
	//Terrain
	light.enable();
	material.begin();
	mesh.draw();
	material.end();
	drawVegetation(&cameraSecond, cameraSecond.getNearClip(), cameraSecond.getFarClip());
	cameraSecond.end();
	ofDisableLighting();
	fboSecondPlan.end();

	fboTroisiemePlan.begin();
	// *** LIGHT *** //
	// enable lighting //
	ofEnableLighting();
	cameraTroisieme.begin();
	//Terrain
	light.enable();
	material.begin();
	mesh.draw();
	material.end();
	drawVegetation(&cameraTroisieme, cameraTroisieme.getNearClip(), cameraTroisieme.getFarClip());
	cameraTroisieme.end();
	ofDisableLighting();
	fboTroisiemePlan.end();

	fboQuatriemePlan.begin();
	// *** LIGHT *** //
	// enable lighting //
	ofEnableLighting();
	cameraQuatrieme.begin();
	//Terrain
	light.enable();
	material.begin();
	mesh.draw();
	material.end();
	drawVegetation(&cameraQuatrieme, cameraQuatrieme.getNearClip(), cameraQuatrieme.getFarClip());
	cameraQuatrieme.end();
	ofDisableLighting();
	fboQuatriemePlan.end();

	fboPluie.begin();
	cameraPluie.begin();
	drawRain(cameraPluie.getNearClip(),cameraPluie.getFarClip());
	cameraPluie.end();
	fboPluie.end();

	//previz. draw(0, 0);
	//fboArbre.draw(0,0);
	presentation.draw(0, 0);

	spout.sendTexture(fboPremierPlan.getTexture(), "premierPlan");
	spout.sendTexture(fboSecondPlan.getTexture(), "secondPlan");
	spout.sendTexture(fboTroisiemePlan.getTexture(), "troisiemePlan");
	spout.sendTexture(fboQuatriemePlan.getTexture(), "quatriemePlan");
	spout.sendTexture(fboPluie.getTexture(), "pluie");
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){
	//need to correct GMT/UTC values
	//if (key == '1') {
	//	weatherInfo.correctUTC(1);
	//	weatherInfo.changeCity("6455259");//Paris, France	
	//}
	//if (key == '2') {
	//	weatherInfo.correctUTC(-2);
	//	weatherInfo.changeCity("3470127"); //Belo Horizonte, Brazil, Minas Gerais		
	//}
	//if (key == '3') {
	//	weatherInfo.correctUTC(9);
	//	weatherInfo.changeCity("1850147"); //Tokyo, Japan		
	//}
	//if (key == '4') {
	//	weatherInfo.correctUTC(2);
	//	weatherInfo.changeCity("993800"); //Johannesbourg, South Africa		
	//}
	//if (key == '5') {
	//	weatherInfo.correctUTC(-8);
	//	weatherInfo.changeCity("6173331"); //Vancouver, Canada	
	//}
	if (key == 'g')
	{
		evolve = true;
	}
}
//--------------------------------------------------------------
void ofApp::sendMessageOSC() {
	string buf;
	buf = "sending osc messages to" + string(HOST) + ofToString(PORT);
	ofDrawBitmapString(buf, 10, 20);
	ofxOscMessage m;
	m.setAddress("/weatherValue");
	//variables to send
	m.addFloatArg(sunValueMap);
	m.addFloatArg(weatherInfo.temperature);
	m.addFloatArg(currentHour);
	m.addFloatArg(currentMinute);
	m.addFloatArg(weatherInfo.clouds);
	m.addFloatArg(weatherInfo.precipitation);
	m.addFloatArg(weatherInfo.humidity);
	sender.sendMessage(m, false);
}
//--------------------------------------------------------------
void ofApp::computeCurrentTime() {
	applicationTimeSecs = int(ofGetFrameNum()) % 1800;
	if (applicationTimeSecs == 1 || weatherInfo.newTown == true) {
		weatherInfo.update();			
		applicationTimeSecs += 1;
		weatherInfo.setNewTown(false);
		dropNb = 2000*weatherInfo.precipitation;
		computeRain(dropNb, boundingBoxHalf);
	}

	currentHour = ofGetHours() - 1 + weatherInfo.getUTC();//minus 1 to be in UTC time
	if (currentHour < 0) { currentHour += 24; }
	currentMinute = ofGetMinutes();
	currentHour = currentHour % 24;
	
	float hourValue = ofMap(weatherInfo.citySunRiseHours+1, weatherInfo.citySunRiseHours, weatherInfo.citySunSetHours, 0.0f, 1.0f);
	float sunMinute = ofMap(currentMinute, 0, 60, 0, hourValue);
	float sunHour = ofMap(currentHour, weatherInfo.citySunRiseHours,weatherInfo.citySunSetHours, 0.0f, 1.0f);
	sunValueMap = sunMinute + sunHour;
	sunValueMap = ofClamp(sunValueMap, 0, 1);
	/*
	float evolutionTime = int(ofGetFrameNum()) % 600;
	if (evolutionTime == 0) {
		nextGeneration();
	}
	*/
	if (evolve == true)
	{
		nextGeneration();
		evolve = false;
	}
	pluieValue += weatherInfo.precipitation;
	ventValue += weatherInfo.windSpeed;
	soleilValue += abs(weatherInfo.clouds-1);
	humiditeValue += weatherInfo.humidity;
}
//--------------------------------------------------------------
void ofApp::computeRain(int rainDrops, int boundingBox) {
	//rain init
	rainMesh.clear();
	rainMesh.setMode(OF_PRIMITIVE_POINTS);
	for (int i = 0; i < rainDrops; i++) {
		ofVec3f tmpPos(ofRandom(-boundingBox, boundingBox), boundingBox, ofRandom(-boundingBox, boundingBox) - 300.f);
		rainMesh.addVertex(tmpPos);
	}
	return;
}
//--------------------------------------------------------------
void ofApp::drawRain(float cameraNear, float cameraFar) {
	ofEnableBlendMode(OF_BLENDMODE_ALPHA);
	rainShader.begin();
	rainShader.setUniform1f("time", ofGetElapsedTimef()*40.0);
	rainShader.setUniform1f("limit", boundingBoxHalf);
	rainShader.setUniform1f("rainDirection", 1.);
	rainShader.setUniform2f("clipPlane", ofVec2f(cameraNear, cameraFar));
	rainMesh.draw();
	rainShader.end();
}
//--------------------------------------------------------------
void ofApp::nextGeneration() {
	placementMap.generate();

	pop.calcFitness(pluieValue, ventValue, soleilValue, humiditeValue);
	herbe.calcFitness(pluieValue, ventValue, soleilValue, humiditeValue);
	arbre.calcFitness(pluieValue, ventValue, soleilValue, humiditeValue);
	herbe2.calcFitness(pluieValue, ventValue, soleilValue, humiditeValue);
	arbre2.calcFitness(pluieValue, ventValue, soleilValue, humiditeValue);

	pop.selection();
	pop.reproduction();

	herbe.selection();
	herbe.reproduction();

	arbre.selection();
	arbre.reproduction();

	herbe2.selection();
	herbe2.reproduction();

	arbre2.selection();
	arbre2.reproduction();

	pluieValue = 1;
	ventValue = 1;
	soleilValue = 1;
	humiditeValue = 1;
	
	for (int i = 0; i < 7; i++) 
	{
		pop.evolvePath();
		arbre.evolvePath();
		arbre2.evolvePath();
	}
	clearFbo(); //-----------------------------------------Not definitive !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
	genNum += 1.;
}
//--------------------------------------------------------------
void ofApp::clearFbo() {
	fboPlante.begin();
	ofClear(255, 255, 127, 0);
	fboPlante.end();

	fboHerbe.begin();
	ofClear(255, 255, 127, 0);
	fboHerbe.end();

	fboArbre.begin();
	ofClear(255, 255, 127, 0);
	arbre.drawPath();
	fboArbre.end();

	fboHerbe2.begin();
	ofClear(255, 255, 127, 0);
	fboHerbe2.end();

	fboArbre2.begin();
	ofClear(255, 255, 127, 0);
	arbre2.drawPath();
	fboArbre2.end();
	
	previz.begin();
	ofClear(255, 255, 127, 0);
	arbre.drawPath();
	arbre2.drawPath();
	previz.end();

	presentation.begin();
	ofClear(255, 255, 127, 0);
	presentation.end();	
}
//--------------------------------------------------------------
void ofApp::computeMesh() {
	vegetationMesh.clear();
	vegetationMesh.setMode(OF_PRIMITIVE_POINTS);
	int numberOfPlant = 256;
	for (int y = 0; y < numberOfPlant; y++)
	{
		for (int x = 0; x < numberOfPlant; x++)
		{
			ofColor color(x,y,0);
			ofVec3f vertexPos = mesh.getVertex((int)floorf((x + y * numberOfPlant)*0.5)); //!!!128*128 vertex on mesh!!!

			float isVertex = (x + y) % 2;
			float offsetX = ofNoise(xoff, zoff)*3.0;
			float offsetZ = ofNoise(zoff, xoff)*3.0;
			ofVec3f tmpPos(vertexPos.x + offsetX, vertexPos.y, vertexPos.z + offsetZ);
			if (isVertex != 0) { tmpPos += ofVec3f(1.5,0.0,2.); };
			
			vegetationMesh.addVertex(tmpPos);
			vegetationMesh.addColor(color);

			xoff += 1;
			zoff += 1;
		}
	}	
}
//--------------------------------------------------------------
void ofApp::drawVegetation(ofCamera* _camera,float cameraNear, float cameraFar) {
	ofEnableBlendMode(OF_BLENDMODE_ALPHA);
	vegetationShader.begin();
	vegetationShader.setUniform1f("timeSecs", ofGetElapsedTimef());
	vegetationShader.setUniform3fv("cameraWorldPos", _camera->getGlobalPosition().getPtr());
	vegetationShader.setUniform1f("stalkHeight", stalkHeight);
	vegetationShader.setUniform1f("animationTimeMaxDifference", swayingTimeMaxDifference);
	vegetationShader.setUniform1f("stalkSwayingMaxAngle", ofDegToRad(swayingMaxAngle) * 0.5f);
	vegetationShader.setUniform1f("grassSwayingTimeScale", swayingTimeScale);
	vegetationShader.setUniform1f("grassSwayingNoiseFrequency", swayingNoiseSpaceFrequency);
	vegetationShader.setUniform1f("sunValueMap", sunValueMap);
	vegetationShader.setUniform2f("clipPlanesNF", ofVec2f(cameraNear,cameraFar));
	vegetationShader.setUniformTexture("tex0", fboPlacementMap, 0);
	vegetationShader.setUniformTexture("tex1", fboPlante, 1);
	vegetationShader.setUniformTexture("tex2", fboHerbe, 2);
	vegetationShader.setUniformTexture("tex3", fboArbre, 3);
	vegetationShader.setUniformTexture("tex4", fboHerbe2, 4);
	vegetationShader.setUniformTexture("tex5", fboArbre2, 5);
	vegetationMesh.draw();
	vegetationShader.end();
}
//--------------------------------------------------------------
void ofApp::keyReleased(int key){

}
//--------------------------------------------------------------
void ofApp::mouseMoved(int x, int y){

}
//--------------------------------------------------------------
void ofApp::mouseDragged(int x, int y, int button){

}
//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button){
}
//--------------------------------------------------------------
void ofApp::mouseReleased(int x, int y, int button){

}
//--------------------------------------------------------------
void ofApp::mouseEntered(int x, int y){

}
//--------------------------------------------------------------
void ofApp::mouseExited(int x, int y){

}
//--------------------------------------------------------------
void ofApp::windowResized(int w, int h){

}
//--------------------------------------------------------------
void ofApp::gotMessage(ofMessage msg){

}
//--------------------------------------------------------------
void ofApp::dragEvent(ofDragInfo dragInfo){ 

}