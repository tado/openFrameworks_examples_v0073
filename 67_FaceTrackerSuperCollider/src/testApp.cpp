#include "testApp.h"

using namespace ofxCv;

void testApp::setup() {
	// カメラ初期化
	cam.initGrabber(640, 480);
	// フェイストラッカー初期化
	tracker.setup();
	// 認識する際の画像をリスケール(小さくするほど高速)
	tracker.setRescale(.5);
	
	host = "localhost";
	port = 57120;
	osc.setup(host, port);
}

void testApp::clearBundle() {
	bundle.clear();
}

template <>
void testApp::addMessage(string address, ofVec3f data) {
	ofxOscMessage msg;
	msg.setAddress(address);
	msg.addFloatArg(data.x);
	msg.addFloatArg(data.y);
	msg.addFloatArg(data.z);
	bundle.addMessage(msg);
}

template <>
void testApp::addMessage(string address, ofVec2f data) {
	ofxOscMessage msg;
	msg.setAddress(address);
	msg.addFloatArg(data.x);
	msg.addFloatArg(data.y);
	bundle.addMessage(msg);
}

template <>
void testApp::addMessage(string address, float data) {
	ofxOscMessage msg;
	msg.setAddress(address);
	msg.addFloatArg(data);
	bundle.addMessage(msg);
}

template <>
void testApp::addMessage(string address, int data) {
	ofxOscMessage msg;
	msg.setAddress(address);
	msg.addIntArg(data);
	bundle.addMessage(msg);
}

void testApp::sendBundle() {
	osc.sendBundle(bundle);
}

void testApp::update() {
	cam.update();
	if(cam.isFrameNew()) {
		tracker.update(toCv(cam));
		
		clearBundle();
		
		if(tracker.getFound()) {
			addMessage("/found", 1);
			
			ofVec2f position = tracker.getPosition();
			addMessage("/pose/position", position);
			scale = tracker.getScale();
			addMessage("/pose/scale", scale);
			ofVec3f orientation = tracker.getOrientation();
			addMessage("/pose/orientation", orientation);
			
			addMessage("/gesture/mouth/width", tracker.getGesture(ofxFaceTracker::MOUTH_WIDTH));
			addMessage("/gesture/mouth/height", tracker.getGesture(ofxFaceTracker::MOUTH_HEIGHT));
			addMessage("/gesture/eyebrow/left", tracker.getGesture(ofxFaceTracker::LEFT_EYEBROW_HEIGHT));
			addMessage("/gesture/eyebrow/right", tracker.getGesture(ofxFaceTracker::RIGHT_EYEBROW_HEIGHT));
			addMessage("/gesture/eye/left", tracker.getGesture(ofxFaceTracker::LEFT_EYE_OPENNESS));
			addMessage("/gesture/eye/right", tracker.getGesture(ofxFaceTracker::RIGHT_EYE_OPENNESS));
			addMessage("/gesture/jaw", tracker.getGesture(ofxFaceTracker::JAW_OPENNESS));
			addMessage("/gesture/nostrils", tracker.getGesture(ofxFaceTracker::NOSTRIL_FLARE));
		} else {
			addMessage("/found", 0);
		}
		
		sendBundle();
		
		rotationMatrix = tracker.getRotationMatrix();
	}
}

void testApp::draw() {
	ofSetColor(255);
	cam.draw(0, 0);
	
	if(tracker.getFound()) {
		ofDrawBitmapString(ofToString((int) ofGetFrameRate()), 10, 20);
	
		ofSetLineWidth(1);
		//tracker.draw();
		tracker.getImageMesh().drawWireframe();
		
		ofSetupScreenOrtho(camWidth, camHeight, OF_ORIENTATION_UNKNOWN, true, -1000, 1000);
		ofVec2f pos = tracker.getPosition();
		ofTranslate(pos.x, pos.y);
		applyMatrix(rotationMatrix);
		ofScale(10,10,10);
		ofDrawAxis(scale);
	} else {
		ofDrawBitmapString("searching for face...", 10, 20);
	}
}

void testApp::keyPressed(int key) {
	if(key == 'r') {
		tracker.reset();
	}
}