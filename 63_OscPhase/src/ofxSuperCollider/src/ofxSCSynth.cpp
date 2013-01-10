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

#include "ofxSCSynth.h"

ofxSCSynth::ofxSCSynth(string name, ofxSCServer *server)
{
	ofxSCNode();
	
	this->name = name;
	this->server = server;
}

ofxSCSynth::~ofxSCSynth()
{
}

void ofxSCSynth::create(int position, int groupID)
{
	ofxOscBundle b;
	ofxOscMessage m;

	if (nodeID == 0)
		nodeID = ofxSCNode::id_base++;
	
	m.setAddress("/s_new");
	m.addStringArg(name.c_str());
	m.addIntArg(nodeID);
	m.addIntArg(position);
	m.addIntArg(groupID);
	b.addMessage(m);
	
	for (dictionary::const_iterator it = args.begin(); 
        it != args.end(); ++it)
	{
		string key = it->first;
		float value = it->second;

		m.clear();
		m.setAddress("/n_set");
		m.addIntArg(nodeID);
		m.addStringArg(key.c_str());
		m.addFloatArg(value);
		b.addMessage(m);
	}

	server->sendBundle(b);
	
	created = true;
}

void ofxSCSynth::grain(int position, int groupID)
{
	nodeID = -1;
	create(position, groupID);
}

void ofxSCSynth::set(string arg, double value)
{
	args.insert(dictionary::value_type(arg, value));
	
	if (created)
	{
		ofxOscMessage m;
		m.setAddress("/n_set");
		m.addIntArg(nodeID);
		m.addStringArg(arg);
		m.addFloatArg(value);
		
		server->sendMsg(m);
	}
}

void ofxSCSynth::set(string arg, int value)
{
	args.insert(dictionary::value_type(arg, value));
	
	if (created)
	{
		ofxOscMessage m;
		m.setAddress("/n_set");
		m.addIntArg(nodeID);
		m.addStringArg(arg);
		m.addIntArg(value);
		
		server->sendMsg(m);
	}
}