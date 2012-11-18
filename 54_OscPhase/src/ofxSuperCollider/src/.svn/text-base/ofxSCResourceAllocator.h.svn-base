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

class ofxSCResource
{

public:
	
	ofxSCResource(int address, int size)
	{
		this->address = address;
		this->size = size;
		this->next = NULL;
	}
	
	int address;
	int size;
	
	// pointer to next resource in free list
	ofxSCResource *next;	
};

class ofxSCResourceAllocator
{
public:
	ofxSCResourceAllocator(int capacity);
	
	int alloc (int resource_size);
	void free (int address);
	
	int capacity;
	int pos;
	std::vector <ofxSCResource *> resources;
	std::vector <ofxSCResource *> free_lists;
};