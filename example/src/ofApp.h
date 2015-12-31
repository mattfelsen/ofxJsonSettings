#pragma once

#include "ofMain.h"
#include "ofxJsonSettings.h"

class ofApp : public ofBaseApp{

public:
	void setup();
	void update();
	void draw();

	void onSettingsLoaded();
	void onSettingsSaved();

	void keyPressed(int key);

	ofTrueTypeFont heading, body;

	// Note that you do not have to crete an instance of ofxJsonSettings!
	// It will be automatically be available to any class that includes the
	// header file

};
