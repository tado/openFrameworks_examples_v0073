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
#include "ofxSCServer.h"

class ofxSCGroup;

class ofxSCNode
{
public:	
	ofxSCNode();
	~ofxSCNode();
	
	void addToHead(ofxSCGroup group);
	void addToHead(unsigned int groupID) { create(0, groupID); }
	void addToHead() { create(0, 1); }
	void addToTail(ofxSCGroup group);
	void addToTail(unsigned int groupID) { create(1, groupID); }
	void addToTail() { create(1, 1); }
	void addBefore(const ofxSCNode& node) { create(2, node.nodeID); }
	void addAfter(const ofxSCNode& node) { create(3, node.nodeID); }
	
	// pure virtual method
	virtual void create(int position = 0, int groupID = 1);
	
	void free();

	static int id_base;
	
	// can't use 'id' as a keyword when mixing with objective-c!
	int nodeID;
		
protected:

	bool created;
	
	ofxSCServer *server;

};
