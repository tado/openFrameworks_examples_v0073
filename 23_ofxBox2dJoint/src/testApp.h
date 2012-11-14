#pragma once
#include "ofMain.h"
#include "ofxBox2d.h"

class testApp : public ofBaseApp {
	
public:
	
	void setup();
	void update();
	void draw();
	//void keyPressed(int key);
	void mouseReleased(int x, int y, int button);
	void mouseDragged(int x, int y, int button);
	
	ofxBox2d box2d;	// Box2Dの世界を構築
	vector <ofxBox2dRect> rects;	// Circleを格納する動的配列
	vector <ofxBox2dJoint> joints; // バネの配列
};
