#pragma once
#include "ofMain.h"

class testApp : public ofBaseApp{
	
public:
	void setup();
	void update();
	void draw();
	
	ofEasyCam cam; // カメラ
	ofLight light; // ライト
};
