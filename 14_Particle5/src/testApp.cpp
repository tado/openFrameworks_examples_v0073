#include "testApp.h"

void testApp::setup(){	
	ofSetVerticalSync(true);
	ofSetFrameRate(60);
	ofBackground(0, 0, 0);
}

void testApp::update(){
	for (int i = 0; i < NUM; i++) {
		p[i].resetForce();
		p[i].addForce(0, 0.1);
		p[i].addDampingForce();
		p[i].update();
	}
}

void testApp::draw(){
	ofSetColor(255, 255, 255);
	for (int i = 0; i < NUM; i++) {
		p[i].draw();
	}
}

void testApp::keyPressed  (int key){ 
}

void testApp::keyReleased  (int key){ 
}

void testApp::mouseMoved(int x, int y ){
}

void testApp::mouseDragged(int x, int y, int button){
}

void testApp::mousePressed(int x, int y, int button){    
	for (int i = 0; i < NUM; i++) {
		p[i].setInitialCondition(x, y, ofRandom(-10,10), ofRandom(-10,10));        
	}
}

void testApp::mouseReleased(){
}