#include "testApp.h"

//--------------------------------------------------------------
void testApp::setup() {
    ofSetFrameRate(60);
    ofSoundStreamSetup(2, 0, this, 44100, 2048, 4);
    
    pd.init(2, 0, 44100);
    pd.openPatch("osc.pd");
    pd.start();
}

//--------------------------------------------------------------
void testApp::update() {
    
}

//--------------------------------------------------------------
void testApp::draw() {
    
}

//--------------------------------------------------------------
void testApp::exit() {
    
}

//--------------------------------------------------------------
void testApp::keyPressed(int key) {
    
}

//--------------------------------------------------------------
void testApp::mouseMoved(int x, int y) {}

//--------------------------------------------------------------
void testApp::mouseDragged(int x, int y, int button) {
    //float freq = ofMap(y, 0, ofGetHeight(), 10000, 50);
    //pd.sendFloat("freq", freq);
}

//--------------------------------------------------------------
void testApp::mousePressed(int x, int y, int button) {}

//--------------------------------------------------------------
void testApp::mouseReleased(int x, int y, int button) {}

//--------------------------------------------------------------
void testApp::windowResized(int w, int h) {}

//--------------------------------------------------------------
void testApp::audioReceived(float * input, int bufferSize, int nChannels) {
    //core.audioReceived(input, bufferSize, nChannels);
}

//--------------------------------------------------------------
void testApp::audioRequested(float * output, int bufferSize, int nChannels) {
    //core.audioRequested(output, bufferSize, nChannels);
    pd.audioOut(output, bufferSize, nChannels);
}
