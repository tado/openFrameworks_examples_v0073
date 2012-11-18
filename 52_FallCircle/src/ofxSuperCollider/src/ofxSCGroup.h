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
#include <tr1/unordered_map>

#include "ofxSCNode.h"
#include "ofxOsc.h"

class ofxSCGroup : public ofxSCNode
{
public:	
	ofxSCGroup() : ofxSCNode() {}
	~ofxSCGroup();

	ofxSCGroup (const ofxSCGroup & other) { copy (other); }
	ofxSCGroup& operator= (const ofxSCGroup & other) { return copy(other); }

	/// for operator= and copy constructor
	ofxSCGroup & copy(const ofxSCGroup & other);
	
	void create(int position = 0, int groupID = 1);
	void freeAll();
		
protected:
};

