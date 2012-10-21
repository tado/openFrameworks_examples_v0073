#pragma once
#include "ofMain.h"

class MoveCircle {
	
public:
	
	void draw();
	void update();
	ofPoint interpolateByPct(float pct);
	
	ofPoint currentPos;
	ofPoint startPos;
	ofPoint endPos;
	float pct;
	float shaper;

};