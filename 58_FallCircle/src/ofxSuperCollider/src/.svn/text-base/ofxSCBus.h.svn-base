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


class ofxSCBus
{
	
public:
	ofxSCBus(int rate = RATE_AUDIO, int channels = 2, ofxSCServer *server = ofxSCServer::local());
	
	void free();
	
	static int id_base;
	
	ofxSCServer *server;
	int rate;
	int index;
	int channels;
	
};
