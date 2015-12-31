#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
	// Use Settings::get() to get the singleton instance
	Settings::get().load("data.json");

	// If you want to save your settings, such as during app exit or on a gui
	// button press...
	// Settings::get().save("data.json");
	// Or disable the default pretty print with..
	// Settings::get().save("data.json", false);

	// Let's use some data from the settings file!
	// You can use the following methods to get your settings...
	// - Settings::getString("key")
	// - Settings::getBool("key")
	// - Settings::getInt("key")
	// - Settings::getFloat("key")
	// - Settings::getDouble("key")
	ofSetFullscreen(Settings::getBool("fullscreen"));

	// You can also get nested keys like so...
	heading.load(Settings::getString("fonts/heading/face"), Settings::getFloat("fonts/heading/size"));
	body.load(Settings::getString("fonts/body/face"), Settings::getFloat("fonts/body/size"));

	// Update or add a setting...
	Settings::getFloat("x-pos") = 100;
	Settings::getFloat("y-pos") = 100;
	Settings::getFloat("size") = 50;
	Settings::getFloat("object/x") = 10;
	Settings::getFloat("object/y") = 20;

	// By default, the delimiter is "/" but you can change it with...
	// Settings::get().setDelimiter("|")

	// If you have classes that want to get notified of when the
	// settings are loaded or saved, i.e. if you need to reload a font
	// when the json file is loaded, you can...
	 ofAddListener(Settings::get().settingsLoaded, this, &ofApp::onSettingsLoaded);
	 ofAddListener(Settings::get().settingsSaved, this, &ofApp::onSettingsSaved);

	// More examples...

	// Set up a hypothetical websocket client
	string host = Settings::getString("server/host");
	int port = Settings::getInt("server/port");
	bool reconnect = Settings::getBool("server/reconnect");
	// websocketClient.setup(host, port, reconnect)

	// Bind settings directly to a GUI that supports variable binding,
	// like ofxUI or ofxDatGui
	// gui->addSlider("X Position", &Settings::getFloat("x-pos"));
	// gui->addSlider("Y Position", &Settings::getFloat("y-pos"));
	// gui->addSlider("Size", &Settings::getFloat("size"));
}

//--------------------------------------------------------------
void ofApp::update(){

}

//--------------------------------------------------------------
void ofApp::draw(){
	heading.drawString("This is my header", 20, 100);
	body.drawString("And this is my body. Not bad...", 20, 150);
}

//--------------------------------------------------------------
void ofApp::onSettingsLoaded(){
	ofLogNotice() << "Settings loaded!";

	// Reload your font here?
}

//--------------------------------------------------------------
void ofApp::onSettingsSaved(){
	ofLogNotice() << "Settings saved!";
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){
	if (key == 'l')
		Settings::get().load("data.json");
	if (key == 's')
		Settings::get().save("data.json");
}
