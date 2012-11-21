#include "testApp.h"

//--------------------------------------------------------------
void testApp::setup(){
    ofSetFrameRate(60);
    ofBackgroundHex(0x000000);
    
    ofxSuperColliderServer::init();
    
    synth = new ofxSCSynth("test_fm");
    synth->set("car", 100);
    synth->set("mod", 777);
    synth->set("index", 1000);
    synth->set("amp", 0.5);
}

//--------------------------------------------------------------
void testApp::update(){

}

//--------------------------------------------------------------
void testApp::draw(){

}

//--------------------------------------------------------------
void testApp::exit(){
    synth->free();
}

//--------------------------------------------------------------
void testApp::keyPressed(int key){
    if (key == 'a') {
        synth->create();
    }
    if (key == 's') {
        synth->free();
    }
}

//--------------------------------------------------------------
void testApp::keyReleased(int key){

}

//--------------------------------------------------------------
void testApp::mouseMoved(int x, int y){

}

//--------------------------------------------------------------
void testApp::mouseDragged(int x, int y, int button){
    int index;
    index = ofMap(x, 0, ofGetHeight(), 10000, 10);
    synth->set("car", y);
    synth->set("index", index);
}

//--------------------------------------------------------------
void testApp::mousePressed(int x, int y, int button){
    //synth->create();
}

//--------------------------------------------------------------
void testApp::mouseReleased(int x, int y, int button){
    //synth->free();
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