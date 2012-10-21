#include "MoveCircle.h"

void MoveCircle::draw() {

	ofFill();
	ofSetColor(31,127,255);
    ofCircle(currentPos.x, currentPos.y, 20, 20);
	
}

void MoveCircle::update() {

	pct += 0.01f;
	if (pct > 1) {
		pct = 0;
	}
	
	currentPos = interpolateByPct(pct);
	
}

ofPoint MoveCircle::interpolateByPct(float _pct){
	
	float shapedPct = powf(_pct, shaper);
	
	ofPoint pos;
	pos.x = (1 - shapedPct) * startPos.x + shapedPct * endPos.x;
	pos.y = (1 - shapedPct) * startPos.y + shapedPct * endPos.y;
	
	return pos;
	
}