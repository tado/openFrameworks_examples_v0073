#pragma once

#include "ofMain.h"

class testApp : public ofBaseApp{
	
public:
	void setup();
	void update();
	void draw();
	void keyPressed  (int key);
	
	ofEasyCam cam; // カメラ
	ofMesh mesh; // 3Dメッシュ
	int w, h; // メッシュの幅と高さ
};
