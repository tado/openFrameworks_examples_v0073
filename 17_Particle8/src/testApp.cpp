#include "testApp.h"

void testApp::setup(){	
	ofSetVerticalSync(true);
	ofSetFrameRate(60);
	ofBackground(0, 0, 0);
}

void testApp::update(){
    for (int i = 0; i < particles.size(); i++) {
        particles[i].resetForce();
        particles[i].addDampingForce();
        particles[i].update();
    }
}

void testApp::draw(){

	//画面左上にメッセージを表示
	ofSetColor(255, 255, 255);
	string message = "current particle num = " + ofToString(particles.size(),0);
	ofDrawBitmapString(message, 20, 20);
	
	ofEnableBlendMode(OF_BLENDMODE_ADD);
	ofNoFill();
	ofEnableSmoothing();
	ofBeginShape();
	ofSetColor(255, 255, 255, 100);
	for (int i = 0; i < particles.size(); i++){
		ofCurveVertex(particles[i].pos.x, particles[i].pos.y);
		particles[i].draw();
	}
	ofEndShape();
	ofDisableSmoothing();
}

void testApp::keyPressed  (int key){
	//'c'キーでパーティクルを全部消去
	if (key == 'c') {
		particles.clear();
	}
	//'f'キーでフルスクリーン表示
	if (key == 'f') {
		ofToggleFullscreen();
	}
}

void testApp::keyReleased  (int key){ 
}

void testApp::mouseMoved(int x, int y ){
}

void testApp::mouseDragged(int x, int y, int button){
	//マウスをドラッグするとパーティクルが追加される
	Particle myParticle;
	float vx = ofRandom(-1, 1);
	float vy = ofRandom(-1, 1);
	myParticle.setInitialCondition(x, y, vx, vy);
	particles.push_back(myParticle);
}

void testApp::mousePressed(int x, int y, int button){  
	particles.clear();
}

void testApp::mouseReleased(){
}