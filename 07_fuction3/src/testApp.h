#pragma once
#include "ofMain.h"

class testApp : public ofBaseApp{
	
public:
	void setup();
	void update();
	void draw();
	
	void keyPressed  (int key);
	void keyReleased(int key);
	void mouseMoved(int x, int y );
	void mouseDragged(int x, int y, int button);
	void mousePressed(int x, int y, int button);
	void mouseReleased(int x, int y, int button);
	void windowResized(int w, int h);
	void dragEvent(ofDragInfo dragInfo);
	void gotMessage(ofMessage msg);
	
	ofPoint interpolateByPct(float pct, float shaper); // 割合から位置を算出する関数
	
	ofPoint startPos;	// 開始地点
	ofPoint endPos;		// 終了地点
	ofPoint currentPos;	// 現在地点
	float pct;			// 現在位置を示す割合
	float shaper;		// 加速減速の割合
	
};
