//
//  ofxJsonSettings.h
//  ofxJsonSettings
//
//  Created by Matt Felsen on 12/7/15.
//
//

#pragma once

#include "ofMain.h"

// helper for shorter syntax
class ofxJsonSettings;
typedef ofxJsonSettings Settings;

class ofxJsonSettings {
public:
	ofxJsonSettings();

	// Singleton..
	static ofxJsonSettings& get() {
		static ofxJsonSettings instance;
		return instance;
	}

	void setDelimiter(string delim);
	bool load(string file = "settings.json");
	bool save(string file = "settings.json", bool prettyPrint = true);

	string getAsJsonString(); //in case you want to print / read

	// Use this to get values
	// These return references, so you can bind directly to a GUI library that
	// supports variable binding
	static string& getString(string key);
	static bool& getBool(string key);
	static int& getInt(string key);
	static float& getFloat(string key);
	static double& getDouble(string key);
	static ofVec2f& getVec2(string key);
	static ofVec3f& getVec3(string key);
	static ofVec4f& getVec4(string key);
	static ofColor& getColor(string key);
	static ofJson getJson(string key);

	// Use this to check if a key exists
	static bool exists(string key);

	static bool remove(string key);

	ofEvent<void> settingsLoaded;
	ofEvent<void> settingsSaved;

protected:
	string& _stringVal(string& key);
	bool& _boolVal(string& key);
	int& _intVal(string& key);
	float& _floatVal(string& key);
	double& _doubleVal(string& key);
	ofVec2f& _vec2Val(string& key);
	ofVec3f& _vec3Val(string& key);
	ofVec4f& _vec4Val(string& key);
	ofColor& _colorVal(string& key);
	ofJson _jsonVal(string& key);

	string _stringValFromJson(ofJson& data, string& key);
	bool _boolValFromJson(ofJson& data, string& key);
	int _intValFromJson(ofJson& data, string& key);
	float _floatValFromJson(ofJson& data, string& key);
	double _doubleValFromJson(ofJson& data, string& key);
	ofVec2f _vec2ValFromJson(ofJson& data, string& key);
	ofVec3f _vec3ValFromJson(ofJson& data, string& key);
	ofVec4f _vec4ValFromJson(ofJson& data, string& key);
	ofColor _colorValFromJson(ofJson& data, string& key);

	bool _exists(string key);
	bool _remove(string key);

	ofJson getNestedChild(ofJson data, string key, bool supressWarning = false);
	ofJson getNestedChild(ofJson data, vector<string> keys, bool supressWarning = false);

	template<typename T>
	void setNestedChild(ofJson& data, string key, T val);

	template<typename T>
	void setNestedChild(ofJson& data, vector<string> keys, T val);

	template<typename T>
	void cacheToJson(T& container, ofJson& data);

	void cacheToJson(unordered_map<string,ofVec2f>& container, ofJson& data);
	void cacheToJson(unordered_map<string,ofVec3f>& container, ofJson& data);
	void cacheToJson(unordered_map<string,ofVec4f>& container, ofJson& data);
	void cacheToJson(unordered_map<string,ofColor>& container, ofJson& data);

	template<typename T>
	bool exists(T& container, const string &key);

	template<typename T>
	void printMap(T& container, const string& text = "");

	ofJson jsonStore;
	unordered_map<string,string> stringMap;
	unordered_map<string,int> intMap;
	unordered_map<string,bool> boolMap;
	unordered_map<string,float> floatMap;
	unordered_map<string,double> doubleMap;
	unordered_map<string,ofVec2f> vec2Map;
	unordered_map<string,ofVec3f> vec3Map;
	unordered_map<string,ofVec4f> vec4Map;
	unordered_map<string,ofColor> colorMap;

	string delimiter;

private:
	// make sure there are no copies
	ofxJsonSettings(ofxJsonSettings const&);
	void operator=(ofxJsonSettings const&);
};
