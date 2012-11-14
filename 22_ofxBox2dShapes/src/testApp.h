#pragma once
#include "ofMain.h"
#include "ofxBox2d.h"

class testApp : public ofBaseApp {
	
public:
	
	void setup();
	void update();
	void draw();
	void keyPressed(int key);
	
	ofxBox2d box2d;	// Box2Dの世界を構築
	vector <ofxBox2dCircle> circles;	// Circleを格納する動的配列
};
