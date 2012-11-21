#include "testApp.h"

//--------------------------------------------------------------
void testApp::setup() {
    ofSetFrameRate(60);
    ofSoundStreamSetup(2, 1, this, 44100, 2048, 4);
    pd.init(2, 1, 44100);
    Patch patch = pd.openPatch("osc.pd");
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
void testApp::mouseDragged(int x, int y, int button) {}

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
