#include "testApp.h"

//--------------------------------------------------------------
void testApp::setup(){
    ofSetFrameRate(60);
    ofBackgroundHex(0x000000);
    
    // Create new synth by SynthDef name
    synth = new ofxSCSynth("test_fm");
    synth->set("car", 50);
}

//--------------------------------------------------------------
void testApp::update(){

}

//--------------------------------------------------------------
void testApp::draw(){
    ofSetHexColor(0x3399ff);
    if (ofGetMousePressed()) {
        ofCircle(mouseX, mouseY, 40);
    }
}

//--------------------------------------------------------------
void testApp::exit(){
    // Free synth
    synth->free();
}

//--------------------------------------------------------------
void testApp::keyPressed(int key){

}

//--------------------------------------------------------------
void testApp::keyReleased(int key){

}

//--------------------------------------------------------------
void testApp::mouseMoved(int x, int y){

}

//--------------------------------------------------------------
void testApp::mouseDragged(int x, int y, int button){
    // map params by mouseX, mouseY
    
    int mod, index;
    mod = ofMap(x, 0, ofGetWidth(), 20, 8000); //mod: 20Hz - 8000Hz
    index = ofMap(y, 0, ofGetHeight(), 1000, 0); //index: 1000 - 0
    synth->set("mod", mod);
    synth->set("index", index);
}

//--------------------------------------------------------------
void testApp::mousePressed(int x, int y, int button){
    // Play Synth
    synth->create();
}

//--------------------------------------------------------------
void testApp::mouseReleased(int x, int y, int button){
    // Free Synth
    synth->free();
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