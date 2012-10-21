#include "testApp.h"

void testApp::setup(){
    ofSetFrameRate(60);
    ofBackgroundHex(0x000000);
        
	//GUI setup
    gui.setup("control panel test", 0, 0, 340, 400);
    gui.addPanel("panel 1", 1);
    gui.addSlider("rect size", "size", 100, 0, 800, false);
    gui.addSlider("rotate x", "rot_x", 0, 0, 360, false);
    gui.addSlider("rotate y", "rot_y", 0, 0, 360, false);
    gui.addSlider("rotate z", "rot_z", 0, 0, 360, false);
    gui.loadSettings("controlPanel.xml");
}

void testApp::update(){
    gui.update();
}

void testApp::draw(){
	ofPushMatrix();
    
    ofTranslate(ofGetWidth()/2, ofGetHeight()/2);
    ofRotateX(gui.getValueF("rot_x"));
    ofRotateY(gui.getValueF("rot_y"));
    ofRotateZ(gui.getValueF("rot_z"));

	ofSetHexColor(0x3399ff);
	ofSetRectMode(OF_RECTMODE_CENTER);
    ofRect(0, 0, gui.getValueF("size"), gui.getValueF("size"));

    ofPopMatrix();
    
	ofSetRectMode(OF_RECTMODE_CORNER);
    gui.draw();
}

void testApp::mouseDragged(int x, int y, int button){
    gui.mouseDragged(x, y, button);
}

void testApp::mousePressed(int x, int y, int button){
    gui.mousePressed(x, y, button);
}

void testApp::mouseReleased(int x, int y, int button){
    gui.mouseReleased();
}
