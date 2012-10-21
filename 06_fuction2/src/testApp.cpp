#include "testApp.h"

//--------------------------------------------------------------
void testApp::setup(){
	ofBackground(0, 0, 0);
	ofSetFrameRate(60);
	ofSetVerticalSync(true);

	startPos = ofPoint(10, 100);
	endPos = ofPoint(1000, 600);
	pct = 0;
}

//--------------------------------------------------------------
void testApp::update(){
	pct = pct + 0.01;
	
	if (pct > 1.0) {
		pct = 0.0;
	}
	
	currentPos = interpolateByPct(pct);
}

//--------------------------------------------------------------
void testApp::draw(){
	ofSetColor(31, 127, 255);
	ofCircle(currentPos.x, currentPos.y, 20);
}

//--------------------------------------------------------------
ofPoint testApp::interpolateByPct(float _pct){
	
	ofPoint pos;
	pos.x = (1.0 - _pct) * startPos.x + (_pct) * endPos.x;
	pos.y = (1.0 - _pct) * startPos.y + (_pct) * endPos.y;
	
	return pos;
	
}

//--------------------------------------------------------------
void testApp::keyPressed(int key){
	
}

//--------------------------------------------------------------
void testApp::keyReleased(int key){
	
}

//--------------------------------------------------------------
void testApp::mouseMoved(int x, int y ){
	
}

//--------------------------------------------------------------
void testApp::mouseDragged(int x, int y, int button){
	
}

//--------------------------------------------------------------
void testApp::mousePressed(int x, int y, int button){
	
}

//--------------------------------------------------------------
void testApp::mouseReleased(int x, int y, int button){
	
}

//--------------------------------------------------------------
void testApp::windowResized(int w, int h){
	
}

//--------------------------------------------------------------
void testApp::gotMessage(ofMessage msg){
	
}

//--------------------------------------------------------------
void testApp::dragEvent(ofDragInfo dragInfo){ 
	
}