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

#include "ofxSuperCollider.h"
#include "ofxSCServer.h"

class ofxSCBuffer
{
	
public:
	ofxSCBuffer(int frames = 0, int channels = 0, ofxSCServer *server = ofxSCServer::local());
	
	void read(string path);
	void query();
	void alloc();
	
//	void write(...);
//	void close();
	
	void free();
	
//	set, setn, get, getn, zero...
	
	static int id_base;
	
	ofxSCServer *server;

	int index;
	int frames;
	int channels;
	float sampleRate;
	bool ready;
	
	string path;
	
};
