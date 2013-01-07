#include "testApp.h"

void testApp::setup(){
	ofBackgroundHex(0x000000);
	// カメラのZ軸上の位置を指定
	cam.setDistance(600);
}

void testApp::update(){
}

void testApp::draw(){
	ofTranslate(ofGetWidth()/2, ofGetHeight()/2);
	// カメラ開始
	cam.begin();
	// 描画色を設定
	ofSetHexColor(0xffffff);
	// 塗り潰し無し(ワイヤーフレーム)
	ofNoFill();
	// 立方体の描画
	ofBox(-150, 0, 0, 200);
	// 球体の描画
	ofSphere(150, 0, 0, 100);
	//カメラ終了
	cam.end();
}
