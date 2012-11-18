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

#include "ofxSCBus.h"


int ofxSCBus::id_base = 64;


ofxSCBus::ofxSCBus(int rate, int channels, ofxSCServer *server)
{
	this->rate = rate;
	this->channels = channels;
	this->server = server;	
	
	if (this->rate == RATE_CONTROL)
	{
		this->index = server->allocatorBusControl->alloc(this->channels);
	}
	else
	{
		this->index = server->allocatorBusAudio->alloc(this->channels);
	}
}


void ofxSCBus::free()
{
	// nothing is actually allocated server-side,
	// so all we need to do here is reflect the availability of this address
	if (this->rate == RATE_CONTROL)
		server->allocatorBusControl->free(this->index);
	else
		server->allocatorBusAudio->free(this->index);
}