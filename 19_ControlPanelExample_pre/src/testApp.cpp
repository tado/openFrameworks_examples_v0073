#include "testApp.h"

void testApp::setup(){
    ofSetFrameRate(60);
    ofBackgroundHex(0x000000);
}

void testApp::update(){
}

void testApp::draw(){
	float rot_x = 10.0f;
	float rot_y = 20.0f;
	float rot_z = 30.0f;
	float size = 200.0f;
	ofPushMatrix();
    
    ofTranslate(ofGetWidth()/2, ofGetHeight()/2);
    ofRotateX(rot_x);
    ofRotateY(rot_y);
    ofRotateZ(rot_z);

	ofSetHexColor(0x3399ff);
	ofSetRectMode(OF_RECTMODE_CENTER);
    ofRect(0, 0, size, size);

    ofPopMatrix();
}

void testApp::mouseDragged(int x, int y, int button){ }
void testApp::mousePressed(int x, int y, int button){ }
void testApp::mouseReleased(int x, int y, int button){ }
