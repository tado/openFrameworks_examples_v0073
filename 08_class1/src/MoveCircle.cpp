#include "MoveCircle.h"

void MoveCircle::draw() {
	
	ofFill();
	ofSetColor(31,127,255);
	ofCircle(currentPos.x, currentPos.y, 20,20);
	
}
