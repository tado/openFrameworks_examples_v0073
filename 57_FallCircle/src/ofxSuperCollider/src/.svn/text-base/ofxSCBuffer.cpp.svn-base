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

#include "ofxSCBuffer.h"


ofxSCBuffer::ofxSCBuffer(int frames, int channels, ofxSCServer *server)
{
	this->server     = server;
	this->frames     = frames;
	this->channels   = channels;
	
	index = server->allocatorBuffer->alloc(1);
	
	server->buffers[index] = this;
	ready = false;
}

void ofxSCBuffer::read(string path)
{
	// XXX do we need to strncpy this?
	// i think so.
	this->path.assign(path);
	
	ofxOscMessage m;
	m.setAddress("/b_allocRead");
	m.addIntArg(index);
	m.addStringArg(path);
	
	// would be nice to also send a b_query at this point, but
	// ofxOsc does not have support for byte array args
	
	server->sendMsg(m);
}

void ofxSCBuffer::query()
{
	ofxOscMessage m;	
	m.setAddress("/b_query");
	m.addIntArg(index);
	server->sendMsg(m);
}

void ofxSCBuffer::alloc()
{
	ofxOscMessage m;	
	m.setAddress("/b_alloc");
	m.addIntArg(index);
	m.addIntArg(frames);
	m.addIntArg(channels);	
	server->sendMsg(m);
}

void ofxSCBuffer::free()
{
	ofxOscMessage m;	
	m.setAddress("/b_free");
	m.addIntArg(index);
	server->sendMsg(m);
	
	server->allocatorBuffer->free(index);
}
