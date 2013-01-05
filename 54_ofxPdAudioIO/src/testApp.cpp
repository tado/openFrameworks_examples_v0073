#include "testApp.h"

//--------------------------------------------------------------
void testApp::setup() {
    ofBackground(0);

    // オーディオ初期設定
    int bufferSize = 2048;
    ofSoundStreamSetup(2, 1, this, 44100, bufferSize, 4);
    
    // 波形表示用データ初期化
    pd_input.assign(bufferSize, 0.0);
    pd_output.assign(bufferSize, 0.0);
    
    // ofxPdの初期化
    pd.init(2, 1, 44100);
    pd.openPatch("delayloop.pd");
    pd.start();
}

//--------------------------------------------------------------
void testApp::update() {
    
}

//--------------------------------------------------------------
void testApp::draw() {

    // input波形表示
    ofSetColor(255);
    ofDrawBitmapString("input", ofGetWidth()-50, 20);
    for (int i = 0; i < pd_input.size(); i++) {
        ofPushMatrix();
		ofTranslate(0, ofGetHeight()/4, 0);
        float x = ofMap(i, 0, pd_input.size(), 0, ofGetWidth());
        float y = ofMap(pd_input[i], -1.0, 1.0, -ofGetHeight()/4.0, ofGetHeight()/4.0);
		ofSetColor(245, 58, 135);
        ofRect(x, y, 2, 2);
		ofPopMatrix();
    }
    
    // output波形表示
    ofSetColor(255);
    ofDrawBitmapString("ouput", ofGetWidth()-50, ofGetHeight()/2 + 20);
    for (int i = 0; i < pd_output.size(); i++) {
        ofPushMatrix();
		ofTranslate(0, ofGetHeight()/4 * 3, 0);
        float x = ofMap(i, 0, pd_output.size(), 0, ofGetWidth());
        float y = ofMap(pd_output[i], -1.0, 1.0, -ofGetHeight()/4.0, ofGetHeight()/4.0);
		ofSetColor(135, 58, 245);
        ofRect(x, y, 2, 2);
		ofPopMatrix();
    }
    
    // 現在のパラメータ(loop duration, feedback)を表示
    ofSetColor(255);
    ofDrawBitmapString("loop duration = " + ofToString(loop_dur) + ", feedback = " + ofToString(feedback), 10, 20);
}

//--------------------------------------------------------------
void testApp::exit() {
    
}

//--------------------------------------------------------------
void testApp::keyPressed(int key) {
    // キー入力でフルスクリーン表示 on/off
    ofToggleFullscreen();
}

//--------------------------------------------------------------
void testApp::mouseMoved(int x, int y) {}

//--------------------------------------------------------------
void testApp::mouseDragged(int x, int y, int button) {
    
    // マウスのX座標を、loop_durに送出
    loop_dur = ofMap(x, 0, ofGetWidth(), 1, 1000);
    pd.sendFloat("loop_dur", loop_dur);
    
    // マウスのY座標を、feedbackに送出
    feedback = ofMap(y, 0, ofGetHeight(), 0.999, 0);
    pd.sendFloat("feedback", feedback);
}

//--------------------------------------------------------------
void testApp::mousePressed(int x, int y, int button) {}

//--------------------------------------------------------------
void testApp::mouseReleased(int x, int y, int button) {}

//--------------------------------------------------------------
void testApp::windowResized(int w, int h) {}

//--------------------------------------------------------------
void testApp::audioReceived(float * input, int bufferSize, int nChannels) {
    // オーディオ入力を波形表示用の配列へ格納
    pd.audioIn(input, bufferSize, nChannels);
    for (int i = 0; i < bufferSize; i++) {
        pd_input[i] = input[i];
    }
}

//--------------------------------------------------------------
void testApp::audioRequested(float * output, int bufferSize, int nChannels) {
    // オーディオ出力を波形表示用の配列へ格納
    pd.audioOut(output, bufferSize, nChannels);
    for (int i = 0; i < bufferSize; i++) {
        pd_output[i] = output[i];
    }
}
