#include "testApp.h"

void testApp::setup(){
	ofSetFrameRate(60);
	
	#ifdef _USE_LIVE_VIDEO
	vidGrabber.setVerbose(true);
	vidGrabber.initGrabber(320,240);
	#else
	vidPlayer.loadMovie("fingers.mov");
	vidPlayer.play();
	#endif
	
    colorImg.allocate(320,240);
	grayImage.allocate(320,240);
	grayBg.allocate(320,240);
	grayDiff.allocate(320,240);
	
	bLearnBakground = true;
	threshold = 80;
}

void testApp::update(){
	ofBackground(100,100,100);
	
    bool bNewFrame = false;
	
	#ifdef _USE_LIVE_VIDEO
	vidGrabber.grabFrame();
	bNewFrame = vidGrabber.isFrameNew();
	#else
	vidPlayer.idleMovie();
	bNewFrame = vidPlayer.isFrameNew();
	#endif
	
	if (bNewFrame){
		#ifdef _USE_LIVE_VIDEO
		colorImg.setFromPixels(vidGrabber.getPixels(), 320,240);
		#else
		colorImg.setFromPixels(vidPlayer.getPixels(), 320,240);
		#endif
		
        grayImage = colorImg;
		if (bLearnBakground == true){
			grayBg = grayImage;
			bLearnBakground = false;
		}
		
		grayDiff.absDiff(grayBg, grayImage);
		grayDiff.threshold(threshold);
		
		contourFinder.findContours(grayDiff, 20, (340*240)/3, 10, true);
	}
}

void testApp::draw(){
	
	ofSetHexColor(0xffffff);
	colorImg.draw(20,20);
	grayImage.draw(360,20);
	grayBg.draw(20,280);
	grayDiff.draw(360,280);
	
	ofFill();
	ofSetHexColor(0x333333);
	ofRect(360,540,320,240);
	
	ofSetHexColor(0xffffff);
	contourFinder.draw(360,540);
	
	ofSetHexColor(0xffffff);
	string repstr;
	repstr = "bg subtraction and blob detection\n";
	repstr += "press space to capture bg\n";
	repstr += "threshold" + ofToString(threshold, 0) + "(press: +/-)\n";
	repstr += "num blobs found " + ofToString(contourFinder.nBlobs, 0) + "\n";
	repstr += "fps: " + ofToString(ofGetFrameRate(), 4);
	ofDrawBitmapString(repstr, 20, 600);
}

void testApp::keyPressed(int key){
	switch (key){
		case ' ':
			bLearnBakground = true;
			break;
		case '+':
			threshold ++;
			if (threshold > 255) threshold = 255;
			break;
		case '-':
			threshold --;
			if (threshold < 0) threshold = 0;
			break;
	}
}
