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

#include "ofxSCServer.h"
#include "ofxSCBuffer.h"
#include "ofxOsc.h"

#define LISTEN_PORT 57150

ofxSCServer *ofxSCServer::plocal = NULL;

ofxSCServer::ofxSCServer(string hostname = "localhost", unsigned int port = 57110)
{
	this->hostname = hostname;
	this->port = port;

#ifdef _ofxOscSENDERRECEIVER_H
	
	osc.setup(LISTEN_PORT, hostname, port);
	ofAddListener(ofEvents.draw, this, &ofxSCServer::_process);
	
#else
	
	osc.setup(hostname, port);
	
#endif
	
	allocatorBusAudio = new ofxSCResourceAllocator(512);
	allocatorBusAudio->pos = 64;
	
	allocatorBusControl = new ofxSCResourceAllocator(512);
	allocatorBuffer = new ofxSCResourceAllocator(512);
	
	if (plocal == 0)
		plocal = this;
}

ofxSCServer::~ofxSCServer()
{
}

ofxSCServer *ofxSCServer::local()
{
	if (plocal == 0)
	{
		plocal = new ofxSCServer;
	}
	
	return plocal;
}

// dummy method for oF event notification system
void ofxSCServer::_process(ofEventArgs &e)
{
	this->process();
}

void ofxSCServer::process()
{
	
#ifdef _ofxOscSENDERRECEIVER_H			

	while(osc.hasWaitingMessages())
	{
		ofxOscMessage m;
		osc.getNextMessage(&m);
		printf("** got OSC! %s\n", m.getAddress().c_str());
		
		/*-----------------------------------------------------------------------------
		 * /done
		 *  - buffer read completed
		 /*---------------------------------------------------------------------------*/
		if (m.getAddress() == "/done")
		{
			string cmd = m.getArgAsString(0);
			int index = m.getArgAsInt32(1);
			printf("** buffer read completed, ID %d\n", index);
			buffers[index]->ready = true;
		}

		/*-----------------------------------------------------------------------------
		 * /b_info
		 *  - information on buffer size and channels
		/*---------------------------------------------------------------------------*/
		else if (m.getAddress() == "/b_info")
		{
			int index = m.getArgAsInt32(0);
			buffers[index]->frames = m.getArgAsInt32(1);
			buffers[index]->channels = m.getArgAsInt32(2);
			buffers[index]->sampleRate = m.getArgAsFloat(3);
			buffers[index]->ready = true;			
		}
		
		// buffer alloc/read failed
		else if (m.getAddress() == "/fail")
		{
		}
	}
	
#else
	
	fprintf(stderr, "This version of ofxOsc does not have support for sender/receive objects. Please update to enable receiving responses from SuperCollider.\n");
	
#endif
	
}

void ofxSCServer::notify()
{
	ofxOscMessage m;
	m.setAddress("/notify");
	m.addIntArg(1);
	osc.sendMessage(m);
}

void ofxSCServer::sendMsg(ofxOscMessage& m)
{
	osc.sendMessage(m);
}

void ofxSCServer::sendBundle(ofxOscBundle& b)
{
	osc.sendBundle(b);
}
