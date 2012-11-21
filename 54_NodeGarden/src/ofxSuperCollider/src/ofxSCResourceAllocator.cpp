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

#include "ofxSCResourceAllocator.h"

ofxSCResourceAllocator::ofxSCResourceAllocator(int capacity)
{
	this->capacity = capacity;
	this->pos = 0;
	
	this->resources.reserve(capacity);
	for (int i = 0; i < capacity; i++)
		this->resources[i] = NULL;
						
	this->free_lists.reserve(32);
	for (int i = 0; i < 32; i++)
		this->free_lists[i] = NULL;
}


int ofxSCResourceAllocator::alloc (int resource_size)
{
	ofxSCResource *res = free_lists[resource_size];
	
	// Resource of this size has previously been freed.
	if (res != NULL)
	{
		free_lists[resource_size] = res->next;
		return res->address;
	}
	
	// Not got previously freed resource but some have yet to be allocated.
	if ((pos + resource_size) <= capacity)
	{
		int address;
		resources[pos] = new ofxSCResource(pos, resource_size);
		address = pos;
		pos += resource_size;
		return address;
	}
	
	return -1;
}

void ofxSCResourceAllocator::free (int address)
{
	ofxSCResource *res = resources[address];
	
	if (res != NULL)
	{
		res->next = free_lists[res->size];
		free_lists[res->size] = res;
		// should we set resources[address] = null?
	}
}