#pragma once

#include "ofMain.h"
#include "ofxOpenCv.h"
#include "ofxControlPanel.h"
#include "BackgroundSubtraction.h"
#include "vectorField.h"
#include "particle.h"

class testApp : public ofBaseApp{
	
public:
	void setup();
	void update();
	void draw();

	void keyPressed  (int key);
	void mouseDragged(int x, int y, int button);
	void mousePressed(int x, int y, int button);
	void mouseReleased(int x, int y, int button);
	
	void grabBackgroundEvent(guiCallbackData & data);
	void drawInputEvent(guiCallbackData & data);
	void toggleLiveVideoEvent(guiCallbackData & data);
	
	ofVideoGrabber vidGrabber;
	ofVideoPlayer vidPlayer;
	
	BackgroundSubtraction bgSub;
	ofxCvContourFinder contourFinder;
	
	int threshold;
	bool bLearnBakground;
	
	ofxControlPanel gui;
	bool useLiveVideo;
	bool drawInputVideo;
	
	vectorField VF;
	bool bForceInward;
	vector <particle> particles;
};

