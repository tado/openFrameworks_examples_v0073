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

#include "ofxSCGroup.h"

void ofxSCGroup::create(int position, int groupID)
{
	nodeID = ofxSCNode::id_base++;
	
	ofxOscMessage m;
	
	m.setAddress("/g_new");
	m.addIntArg(nodeID);
	m.addIntArg(position);
	m.addIntArg(groupID);
	
	server->sendMsg(m);
	
	created = true;
}
