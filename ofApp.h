#pragma once

#include "ofMain.h"
#include "Weather.h"
#include "SpoutInOut.h"
#include "ofxOsc.h"
#include "ofxAssimpModelLoader.h"
#include "GOL.h"
#include "Phenotype.h"
#include "Population.h"
#include "PhenotypeHerbe.h"
#include "PopulationHerbe.h"
#include "PopulationHerbe2.h"
#include "PopulationArbre.h"
#include "PopulationArbre2.h"
#include "DNA_Plante.h"

#define HOST "localhost"
#define PORT 8000

class ofApp : public ofBaseApp{
	public:
		//weather values---------------
		int currentHour;
		int currentMinute;
		int applicationTimeSecs;
		void computeCurrentTime();
		float sunValueMap = 0.0f;
		float testValue;
		Weather weatherInfo;
		//sky-------------------------
		float sunRotation;
		float timeScale;
		//Spout-----------------------
		ofFbo fboPremierPlan;
		ofFbo fboSecondPlan;
		ofFbo fboTroisiemePlan;
		ofFbo fboQuatriemePlan;
		SpoutInOut spout;
		//OSC-------------------------
		ofxOscSender sender;
		void sendMessageOSC();
		//3d scene--------------------
		ofCamera cameraPremier;
		ofCamera cameraSecond;
		ofCamera cameraTroisieme;
		ofCamera cameraQuatrieme;
		ofCamera cameraPluie;
		ofFbo fboPluie;
		//Previz scene--------------------
		ofFbo presentation;
		ofFbo previz;
		//Terrain---------------------
		ofxAssimpModelLoader terrain;
		ofMesh mesh;
		ofLight	light, point, point2;
		ofColor materialColor;
		ofMaterial material;
		ofQuaternion startQuat;
		ofQuaternion targetQuat;
		ofQuaternion tweenedLightQuaternion;
		float x, y, z, r, f;
		float btweenValue;
		ofImage texture;
		ofShader terrainShader;
		//PlacementMap
		GOL placementMap;
		ofFbo fboPlacementMap;
		//Next Generation
		void nextGeneration();
		bool evolve = false;
		//Genetic Algorithm
		int popMax = 4;
		// hight mutation rate, the population is small and we need to enforce variety
		float mutationRatePlante1 = 0.1;
		float mutationRateHerbe1 = 0.08;
		float mutationRateArbre1 = 0.09;
		float mutationRateHerbe2 = 0.08;
		float mutationRateArbre2 = 0.08;
		// create population 
		Population pop;
		Population_Herbe herbe;
		Population_Arbre arbre;
		Population_Herbe2 herbe2;
		Population_Arbre2 arbre2;
		float pluieValue = 1;
		float ventValue = 1;
		float soleilValue = 1;
		float humiditeValue = 1;
		ofFbo fboPlante;
		ofFbo fboHerbe;
		ofFbo fboArbre;
		ofFbo fboHerbe2;
		ofFbo fboArbre2;
		void clearFbo();
		int genNum;
		//draw Vegetation //GeometryShader
		void computeMesh();
		void drawVegetation(ofCamera* _camera, float cameraNear, float cameraFar);
		ofVboMesh	vegetationMesh;
		ofShader	vegetationShader;
		float	placementSize;
		float	placementNoiseSpaceFrequency;
		float	stalkHeight;
		float	swayingMaxAngle;
		float	swayingTimeScale;
		float	swayingNoiseSpaceFrequency;
		float	swayingTimeMaxDifference;
		ofImage imageHeight;
		float xoff, zoff;
		//rain
		ofVboMesh	rainMesh;
		ofShader	rainShader;
		void computeRain(int rainDrops, int boundingBox);
		void drawRain(float cameraNear, float cameraFar);
		int boundingBoxHalf;
		float rainSize;
		int dropNb;
		//global methods
		void setup();
		void update();
		void draw();
		//Events
		void keyPressed(int key);
		void keyReleased(int key);
		void mouseMoved(int x, int y);
		void mouseDragged(int x, int y, int button);
		void mousePressed(int x, int y, int button);
		void mouseReleased(int x, int y, int button);
		void mouseEntered(int x, int y);
		void mouseExited(int x, int y);
		void windowResized(int w, int h);
		void dragEvent(ofDragInfo dragInfo);
		void gotMessage(ofMessage msg);

		ofTrueTypeFont myFont;
};
