#include "testApp.h"

void testApp::setup(){	
	ofSetVerticalSync(true);
	ofSetFrameRate(60);
	ofBackground(0, 0, 0);
}

void testApp::update(){
	p.resetForce();
	p.addDampingForce();
	p.update();
    
}

void testApp::draw(){
	ofSetColor(255, 255, 255);
	p.draw();
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
	p.setInitialCondition(x,y,ofRandom(-10,10), ofRandom(-10,10));
}

void testApp::mouseReleased(){
}