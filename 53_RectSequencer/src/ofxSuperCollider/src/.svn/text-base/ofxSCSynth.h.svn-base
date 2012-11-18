/*-----------------------------------------------------------------------------
 *
 * ofxSuperCollider: a SuperCollider control addon for openFrameworks.
 *
 * Copyright (c) 2009 Daniel Jones.
 *
 *	 <http://www.erase.net/>
 *
 * Distributed under the MIT License.
 * For more information, see ofxSuperCollider.h.
 *
 *---------------------------------------------------------------------------*/

#pragma once

#include <vector>
#include <tr1/unordered_map>

#include "ofxSCNode.h"

typedef std::tr1::unordered_map<string, float> dictionary;

class ofxSCSynth : public ofxSCNode
{
public:	
	ofxSCSynth(string name = "sine", ofxSCServer *server = ofxSCServer::local());
	~ofxSCSynth();

	ofxSCSynth (const ofxSCSynth & other) { copy (other); }
	ofxSCSynth& operator= (const ofxSCSynth & other) { return copy(other); }

	/// for operator= and copy constructor
	ofxSCSynth & copy(const ofxSCSynth & other);
	
	void create(int position = 0, int groupID = 1);
	void grain(int position = 0, int groupID = 1);
	
	void set(string arg, double value);
	void set(string arg, int value);
		
protected:

	string name;
	dictionary args;
};
