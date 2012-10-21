#include "testApp.h"

void testApp::setup(){
	ofSetFrameRate(60);
	ofBackgroundHex(0x000000);
	
    colorImg.allocate(320,240); 
	grayImage.allocate(320,240);
	grayBg.allocate(320,240);
	grayDiff.allocate(320,240);
	
	bLearnBakground = true;
	
	// GUI
	gui.setup("OpenCV control panel", 0, 0, ofGetWidth(), ofGetHeight());
	gui.addPanel("Background subtraction", 3);

	gui.setWhichColumn(0);
	gui.addToggle("use live video", "use_live", 0);
	gui.addToggle("draw input video", "draw_input", 0);
	gui.addToggle("grab background", "grab", 0);
	gui.addSlider("threshold", "thresh", 80, 0, 200, true);
	
	gui.setWhichColumn(1);
	gui.addDrawableRect("Color Image", &colorImg, 320, 240);
	gui.addDrawableRect("Gray Background", &grayBg, 320, 240);
	
	gui.setWhichColumn(2);
	gui.addDrawableRect("Grayscale Image", &grayImage, 320, 240);
	gui.addDrawableRect("Gray Diffarence", &grayDiff, 320, 240);
	gui.loadSettings("controlPanelSettings.xml");

	gui.setupEvents();
	gui.enableEvents();
	ofAddListener(gui.createEventGroup("grab"), this, &testApp::grabBackgroundEvent);
	ofAddListener(gui.createEventGroup("draw_input"), this, &testApp::drawInputEvent);
    ofAddListener(gui.createEventGroup("use_live"), this, &testApp::toggleLiveVideoEvent);
	
	vidPlayer.loadMovie("fingers.mov");
	
	if (gui.getValueI("draw_input") == 1) {
		drawInputVideo = true;
	} else {
		drawInputVideo = false;
	}

    if (gui.getValueI("use_live") == 1) {
		vidPlayer.stop();
		vidGrabber.setVerbose(true);
		vidGrabber.initGrabber(320,240);
		useLiveVideo = true;
	} else {
		vidGrabber.close();
		vidPlayer.play();	
		useLiveVideo = false;
	}
}

void testApp::grabBackgroundEvent(guiCallbackData & data){
	if( data.isElement("grab") && data.getInt(0) == 1 ){
		bLearnBakground = true;
		gui.setValueB("grab", false);
	}
}

void testApp::drawInputEvent(guiCallbackData &data) {
	if (data.isElement("draw_input") && data.getInt(0) == 1) {
		drawInputVideo = true;
	} else {
		drawInputVideo = false;
	}
}

void testApp::toggleLiveVideoEvent(guiCallbackData & data) {
	bLearnBakground = true;
	if (useLiveVideo) {
		vidGrabber.close();
		vidPlayer.play();
		useLiveVideo = false;
	} else {
		vidPlayer.stop();
		vidGrabber.setVerbose(true);
		vidGrabber.initGrabber(320,240);
		useLiveVideo = true;
	}
}

void testApp::update(){
    bool bNewFrame = false;
	
	if (useLiveVideo) {
		vidGrabber.grabFrame();
		bNewFrame = vidGrabber.isFrameNew();
	} else {
		vidPlayer.idleMovie();
		bNewFrame = vidPlayer.isFrameNew();		
	}
	
	if (bNewFrame){
		if (useLiveVideo) {
			colorImg.setFromPixels(vidGrabber.getPixels(), 320,240);
		} else {
			colorImg.setFromPixels(vidPlayer.getPixels(), 320,240);			
		}
		
        grayImage = colorImg;
		if (bLearnBakground == true){
			grayBg = grayImage;
			bLearnBakground = false;
		}
		
		grayDiff.absDiff(grayBg, grayImage);
		grayDiff.threshold(gui.getValueI("thresh"));

		contourFinder.findContours(grayDiff, 20, (340*240)/3, 10, true);
	}

	gui.update();	
}

void testApp::draw(){
	ofFill();
	ofSetHexColor(0xffffff);
	
	glPushMatrix();
	glScalef((float) ofGetWidth() / (float)grayDiff.width, (float) ofGetHeight() / (float)grayDiff.height, 1.0f);
	
	if (drawInputVideo) {
		colorImg.draw(0, 0);
	}

	contourFinder.draw();
	ofPopMatrix();

	gui.draw();	
}

void testApp::mouseDragged(int x, int y, int button){
	gui.mouseDragged(x, y, button);
}

void testApp::mousePressed(int x, int y, int button){
	gui.mousePressed(x, y, button);
}

void testApp::mouseReleased(int x, int y, int button){
	gui.mouseReleased();
}