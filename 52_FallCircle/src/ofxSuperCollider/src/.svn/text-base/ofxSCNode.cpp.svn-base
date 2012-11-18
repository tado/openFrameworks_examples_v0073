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

#include "ofxSCNode.h"
#include "ofxSCGroup.h"

int ofxSCNode::id_base = 2000;

ofxSCNode::ofxSCNode()
{
	nodeID = 0;
	created = false;
	server = ofxSCServer::local();
}

ofxSCNode::~ofxSCNode()
{
}

void ofxSCNode::addToHead(ofxSCGroup group)
{
	this->create(0, group.nodeID);
}

void ofxSCNode::addToTail(ofxSCGroup group)
{
	this->create(1, group.nodeID);
}

void ofxSCNode::free()
{
	ofxOscMessage m;
	m.setAddress("/n_free");
	m.addIntArg(nodeID);
	server->sendMsg(m);
	
	created = false;
}

void ofxSCNode::create(int position, int groupID)
{
}