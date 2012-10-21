#include "testApp.h"

void testApp::setup(){	
	ofSetVerticalSync(true);
	ofSetFrameRate(60);
	ofBackground(0, 0, 0);
}

void testApp::update(){
    for (int i = 0; i < particles.size(); i++) {
        particles[i].resetForce();
        particles[i].addForce(0, 0.1);
        particles[i].addDampingForce();
        particles[i].update();
    }
}

void testApp::draw(){
	ofSetColor(255, 255, 255);
    for (int i = 0; i < particles.size(); i++) {
        particles[i].draw();
    }
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
    particles.clear();
    for (int i = 0; i < NUM; i++) {
		//Particleをインスタンス化 → myParticle
        Particle myParticle;
		//初期化
        float vx = ofRandom(-10, 10);
        float vy = ofRandom(-10, 10);
        myParticle.setInitialCondition(x, y, vx, vy);
		//作成したオブジェクトを配列の末尾に追加
        particles.push_back(myParticle);
    }
}

void testApp::mouseReleased(){
}