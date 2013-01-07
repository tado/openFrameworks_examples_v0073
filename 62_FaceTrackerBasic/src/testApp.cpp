#include "testApp.h"

using namespace ofxCv;

void testApp::setup() {
	// カメラ初期化
	cam.initGrabber(640, 480);
	
	// フェイストラッカー初期化
	tracker.setup();
	// 認識する際の画像をリスケール(小さくするほど高速)
	tracker.setRescale(.2);
}

void testApp::update() {
	// カメラをアップデート
	cam.update();
	if(cam.isFrameNew()) {
		// フェイストラッカーをアップデート
		tracker.update(toCv(cam));
	}
}

void testApp::draw() {
	ofSetColor(255);
	cam.draw(0, 0);
	// フレームレートを表示
	ofDrawBitmapString(ofToString((int) ofGetFrameRate()), 10, 20);
	
	// 左目、右目、顔の輪郭の線を抽出
	ofPolyline leftEye = tracker.getImageFeature(ofxFaceTracker::LEFT_EYE);
	ofPolyline rightEye = tracker.getImageFeature(ofxFaceTracker::RIGHT_EYE);
	ofPolyline faceOutline = tracker.getImageFeature(ofxFaceTracker::FACE_OUTLINE);
	
	// 顔を分析して、3Dメッシュを描画
	ofSetLineWidth(1);
	ofSetColor(255);
	tracker.getImageMesh().drawWireframe();
	
	// 左目、右目、輪郭を描画
	ofSetLineWidth(2);
	ofSetColor(ofColor::red);
	leftEye.draw();
	ofSetColor(ofColor::green);
	rightEye.draw();
	ofSetColor(ofColor::blue);
	faceOutline.draw();
}

void testApp::keyPressed(int key) {
	// フェイストラッカーをリセット
	if(key == 'r') {
		tracker.reset();
	}
}