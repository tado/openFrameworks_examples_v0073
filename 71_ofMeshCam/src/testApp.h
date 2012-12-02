#pragma once
#define WIDTH 640
#define HEIGHT 480
#define NUM_PARTICLES WIDTH * HEIGHT

#include "ofMain.h"

class testApp : public ofBaseApp{
	
public:
	void setup();
	void update();
	void draw();
	void keyPressed  (int key);

	
	ofEasyCam cam; // カメラ
	ofLight light; // ライト
	ofVbo myVbo; // VBO
	ofVec3f myVerts[NUM_PARTICLES]; // 頂点の座標
	ofFloatColor myColor[NUM_PARTICLES]; // 頂点の色情報	
	ofVideoGrabber myVideo;	// ビデオキャプチャ
};
