#include "testApp.h"

void testApp::setup(){
	
	// 画面の設定
	ofBackgroundHex(0x000000);
	ofEnableBlendMode(OF_BLENDMODE_ADD);
	glEnable(GL_DEPTH_TEST);
	cam.setDistance(100);
	
	// メッシュの幅と高さ
	w = 200;
	h = 200;
	
	// 頂点の色を初期化
	for (int i = 0; i < w; i++) {
		for (int j = 0; j < h; j++) {
			mesh.addColor(ofFloatColor(0.5, 0.8, 1.0));
		}
	}
}

void testApp::update(){
	// まず全ての頂点情報を削除
	mesh.clearVertices();
	
	// 全ての頂点の位置を更新して頂点情報として追加
	for (int i = 0; i < w; i++) {
		for (int j = 0; j < h; j++) {
			float x = sin(i * 0.1 + ofGetElapsedTimef())*10.0;
			float y = sin(j*0.15 + ofGetElapsedTimef()) * 10.0;
			float z = x + y;
			mesh.addVertex(ofVec3f(i - w/2, j - h/2, z));
		}
	}
}

void testApp::draw(){
	// メッシュの描画
	ofSetHexColor(0xffffff);
	ofPushMatrix();
	ofTranslate(ofGetWidth()/2, ofGetHeight()/2);
	cam.begin();
	// 頂点の位置をドットで表示
	glPointSize(2.0);
	glEnable(GL_POINT_SMOOTH);
	mesh.drawVertices();
	cam.end();
	ofPopMatrix();
	
	// ログの表示
	string info;
	info = "Vertex num = " + ofToString(w * h, 0) + "\n";
	info += "FPS = " + ofToString(ofGetFrameRate(), 2);
	ofDrawBitmapString(info, 30, 30);
}

void testApp::keyPressed(int key){
	// fキーでフルスクリーン表示
	if (key == 'f') {
		ofToggleFullscreen();
	}
}