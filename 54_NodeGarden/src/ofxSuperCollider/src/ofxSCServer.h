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

#include "ofxOsc.h"
#include "ofxSCResourceAllocator.h"

class ofxSCBuffer;


class ofxSCServer
{
public:	
	ofxSCServer(string hostname, unsigned int port);
	~ofxSCServer();

	static ofxSCServer     *local();
	
	void process();
	void _process(ofEventArgs &e);
	void notify();
	
	void sendMsg(ofxOscMessage& message);
	void sendBundle(ofxOscBundle& bundle);	
	
	ofxSCResourceAllocator *allocatorBusAudio;
	ofxSCResourceAllocator *allocatorBusControl;
	ofxSCResourceAllocator *allocatorBuffer;
	ofxSCResourceAllocator *allocatorSynth;

	ofxSCBuffer *buffers[1024];
	
protected:

#ifdef _ofxOscSENDERRECEIVER_H
	ofxOscSenderReceiver   osc;
#else
	ofxOscSender           osc;
#endif
	
	static ofxSCServer *plocal;
	string hostname;
	unsigned int port;
};

