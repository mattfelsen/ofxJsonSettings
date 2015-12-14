//
//  ofxJsonSettings.cpp
//  ofxJsonSettings
//
//  Created by Matt Felsen on 12/10/15.
//
//

#include "ofxJsonSettings.h"

ofxJsonSettings::ofxJsonSettings() {
	delimiter = "/";
}

void ofxJsonSettings::setDelimiter(string delim) {
	delimiter = delim;
}

void ofxJsonSettings::load(string file) {
	ofxJSON loadData;

	if (loadData.open(file)) {
		jsonStore = loadData;

		// Any values bound to gui are bound to memory address of value
		// inside various cached map objects, so we can't clear() the maps
		// Instead, load new values from new json object to cached maps

		// TODO any keys that were in the old json that have been removed from
		// the new file won't be deleted from the cached maps. Need to compare
		// jsonStore vs loadData objects and remove missing keys?
		for (auto& it : stringMap) {
			string key = it.first;
			stringMap[key] = _stringValFromJson(jsonStore, key);
		}
		for (auto& it : boolMap) {
			string key = it.first;
			boolMap[key] = _boolValFromJson(jsonStore, key);
		}
		for (auto& it : intMap) {
			string key = it.first;
			intMap[key] = _intValFromJson(jsonStore, key);
		}
		for (auto& it : floatMap) {
			string key = it.first;
			floatMap[key] = _floatValFromJson(jsonStore, key);
		}
		for (auto& it : doubleMap) {
			string key = it.first;
			doubleMap[key] = _doubleValFromJson(jsonStore, key);
		}

		ofNotifyEvent(settingsLoaded);
	} else {
		ofLogError("Settings") << "could not load file! " << file;
	}
}

void ofxJsonSettings::save(string file, bool prettyPrint) {
	// Write cached values back to JSON object
	cacheToJson(stringMap, jsonStore);
	cacheToJson(boolMap, jsonStore);
	cacheToJson(intMap, jsonStore);
	cacheToJson(floatMap, jsonStore);
	cacheToJson(doubleMap, jsonStore);

	if (jsonStore.save(file, prettyPrint)) {
		ofNotifyEvent(settingsSaved);
	} else {
		ofLogError("Settings") << "could not save file! " << file;
	}
}

string& ofxJsonSettings::getString(string key) {
	return get()._stringVal(key);
}
bool& ofxJsonSettings::getBool(string key) {
	return get()._boolVal(key);
}
int& ofxJsonSettings::getInt(string key) {
	return get()._intVal(key);
}
float& ofxJsonSettings::getFloat(string key) {
	return get()._floatVal(key);
}
double& ofxJsonSettings::getDouble(string key) {
	return get()._doubleVal(key);
}

string& ofxJsonSettings::_stringVal(string& key) {
	if (!exists(stringMap, key)) {
		stringMap[key] = _stringValFromJson(jsonStore, key);
	}

//    printMap(stringMap, "strings");
	return stringMap[key];
}

bool& ofxJsonSettings::_boolVal(string& key) {
	if (!exists(boolMap, key)) {
		boolMap[key] = _boolValFromJson(jsonStore, key);
	}

//    printMap(boolMap, "bools");
	return boolMap[key];
}

int& ofxJsonSettings::_intVal(string& key) {
	if (!exists(intMap, key)) {
		intMap[key] = _intValFromJson(jsonStore, key);
	}

//    printMap(intMap, "ints");
	return intMap[key];
}

float& ofxJsonSettings::_floatVal(string& key) {
	if (!exists(floatMap, key)) {
		floatMap[key] = _floatValFromJson(jsonStore, key);
	}

//    printMap(floatMap, "floats");
	return floatMap[key];
}

double& ofxJsonSettings::_doubleVal(string& key) {
	if (!exists(doubleMap, key)) {
		doubleMap[key] = _floatValFromJson(jsonStore, key);
	}

//    printMap(doubleMap, "doubles");
	return doubleMap[key];
}

string ofxJsonSettings::_stringValFromJson(ofxJSON& data, string& key) {
	try {
		// For keys like "fonts/face/serif", split the string and do a recursive
		// lookup to find that json element
		if (ofStringTimesInString(key, delimiter)) {
			return getNestedChild(data, key).asString();
		}
		// Otherwise do a direct lookup if the key exists
		else if (data.isMember(key)) {
			return data[key].asString();
		}
		else {
			ofLogWarning("Settings") << "no setting found for: " << key;
			return "";
		}
	} catch (const runtime_error& e) {
		ofLogError("Settings") << "error for key: " << key << ": " << e.what();
		return "";
	}
}

bool ofxJsonSettings::_boolValFromJson(ofxJSON& data, string& key) {
	// See _stringValFromJson() for explanation
	try {
		if (ofStringTimesInString(key, delimiter)) {
			return getNestedChild(data, key).asBool();
		} else if (data.isMember(key)) {
			return data[key].asBool();
		} else {
			ofLogWarning("Settings") << "no setting found for: " << key;
			return false;
		}
	} catch (const runtime_error& e) {
		ofLogError("Settings") << "error for key: " << key << ": " << e.what();
		return false;
	}
}

int ofxJsonSettings::_intValFromJson(ofxJSON& data, string& key) {
	// See _stringValFromJson() for explanation
	try {
		if (ofStringTimesInString(key, delimiter)) {
			return getNestedChild(data, key).asInt();
		} else if (data.isMember(key)) {
			return data[key].asInt();
		} else {
			ofLogWarning("Settings") << "no setting found for: " << key;
			return 0;
		}
	} catch (const runtime_error& e) {
		ofLogError("Settings") << "error for key: " << key << ": " << e.what();
		return 0;
	}
}

float ofxJsonSettings::_floatValFromJson(ofxJSON& data, string& key) {
	// See _stringValFromJson() for explanation
	try {
		if (ofStringTimesInString(key, delimiter)) {
			return getNestedChild(data, key).asFloat();
		} else if (data.isMember(key)) {
			return data[key].asFloat();
		} else {
			ofLogWarning("Settings") << "no setting found for: " << key;
			return 0;
		}
	} catch (const runtime_error& e) {
		ofLogError("Settings") << "error for key: " << key << ": " << e.what();
		return 0;
	}
}

double ofxJsonSettings::_doubleValFromJson(ofxJSON& data, string& key) {
	// See _stringValFromJson() for explanation
	try {
		if (ofStringTimesInString(key, delimiter)) {
			return getNestedChild(data, key).asDouble();
		} else if (data.isMember(key)) {
			return data[key].asDouble();
		} else {
			ofLogWarning("Settings") << "no setting found for: " << key;
			return 0;
		}
	} catch (const runtime_error& e) {
		ofLogError("Settings") << "error for key: " << key << ": " << e.what();
		return 0;
	}
}

ofxJSON ofxJsonSettings::getNestedChild(ofxJSON data, string key) {
	auto keys = ofSplitString(key, delimiter);
	return getNestedChild(data, keys);
}

ofxJSON ofxJsonSettings::getNestedChild(ofxJSON data, vector<string> keys) {
	// Given a lookup key like "fonts/face/serif", find the corresponding
	// json object data["fonts"]["face"]["serif"]
	// (The other signature of this function actually splits the string into a
	// vector of keys)
	if (keys.size()) {
		string key = keys.front();
		keys.erase(keys.begin());

		if (data.isMember(key)) {
			return getNestedChild(data[key], keys);
		} else {
			ofLogWarning("Settings") << "no setting found for: " << key;
			return ofxJSON();
		}
	}

	return data;
}

template<typename T>
void ofxJsonSettings::setNestedChild(ofxJSON& data, string key, T val) {
	auto keys = ofSplitString(key, delimiter);
	setNestedChild(data, keys, val);
}

template<typename T>
void ofxJsonSettings::setNestedChild(ofxJSON& data, vector<string> keys, T val) {
	// Given a lookup key like "fonts/face/serif", find the corresponding
	// json object data["fonts"]["face"]["serif"] and set its value
	// (The other signature of this function actually splits the string into a
	// vector of keys)
	auto* object = &data;

	if (keys.size() < 2) {
		ofLogError("Settings")
		<< "setNestedChild() malformed key (should be at least object/key): "
		<< ofJoinString(keys, delimiter);
		return;
	}

	while (keys.size()) {
		string key = keys.front();
		if (keys.size() == 1) {
			(*object)[key] = val;
			return;
		} else {
			keys.erase(keys.begin());
			object = (ofxJSON *) &(*object)[key];
		}
	}
}

template<typename T>
void ofxJsonSettings::cacheToJson(T& container, ofxJSON& data) {
	for (auto& it : container) {
		string key = it.first;
		if (ofStringTimesInString(key, delimiter)) {
			setNestedChild(data, key, it.second);
		} else {
			data[key] = container[key];
		}
	}
}

template<typename T>
bool ofxJsonSettings::exists(T& container, const string &key) {
	return container.find(key) != container.end();
}

template<typename T>
void ofxJsonSettings::printMap(T& container, const string& text) {
	for (auto& it : container) {
		ofLogNotice() << text << ": " << it.first << ": " << it.second;
	}
}
