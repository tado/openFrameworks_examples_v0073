#pragma once
#include "ofMain.h"
#include "ofxOpenCv.h"

#define _USE_LIVE_VIDEO

class testApp : public ofBaseApp{
public:
	void setup();
	void update();
	void draw();
	void keyPressed(int key);
	
	#ifdef _USE_LIVE_VIDEO
	ofVideoGrabber vidGrabber;
	#else
	ofVideoPlayer vidPlayer;
	#endif
	
	ofxCvColorImage colorImg;
	ofxCvGrayscaleImage grayImage;
	ofxCvGrayscaleImage grayBg;
	ofxCvGrayscaleImage grayDiff;
	ofxCvContourFinder contourFinder;
	
	int threshold;
	bool bLearnBakground;
};

