#include "testApp.h"
#include <Poco/Path.h>

//--------------------------------------------------------------
void testApp::setup() {
    ofSetFrameRate(60);
    ofBackgroundHex(0x000000);
    
	ofSoundStreamSetup(2, 0, this, 44100, 2048, 4);
    pd.init(2, 0, 44100);
    pd.stop();
    Patch patch = pd.openPatch("fm.pd");
}

//--------------------------------------------------------------
void testApp::update() {

}

//--------------------------------------------------------------
void testApp::draw() {
    if (ofGetMousePressed()) {
        ofSetHexColor(0x3399ff);
        ofCircle(mouseX, mouseY, 40);
    }
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
    int mod_freq = ofMap(x, 0, ofGetWidth(), 0, 400);
    int mod_index = ofMap(y, 0, ofGetHeight(), 10000, 1);
    pd.sendFloat("mod_freq", mod_freq);
    pd.sendFloat("mod_index", mod_index);
}

//--------------------------------------------------------------
void testApp::mousePressed(int x, int y, int button) {
    pd.start();
}

//--------------------------------------------------------------
void testApp::mouseReleased(int x, int y, int button) {
    pd.stop();
}

//--------------------------------------------------------------
void testApp::windowResized(int w, int h) {}

//--------------------------------------------------------------
void testApp::audioReceived(float * input, int bufferSize, int nChannels) {

}

//--------------------------------------------------------------
void testApp::audioRequested(float * output, int bufferSize, int nChannels) {
    pd.audioOut(output, bufferSize, nChannels);
}
