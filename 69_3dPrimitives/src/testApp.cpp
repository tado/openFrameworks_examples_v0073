#include "testApp.h"

void testApp::setup(){
	ofBackgroundHex(0x000000);
}

void testApp::update(){
}

void testApp::draw(){
	// 画面全体の座標を画面の中心へ
	ofTranslate(ofGetWidth()/2, ofGetHeight()/2, 0);
	// 描画色を設定
	ofSetHexColor(0xffffff);
	// 塗り潰し無し(ワイヤーフレーム)
	ofNoFill();
	// 立方体の描画
	ofBox(-150, 0, 0, 200);
	// 球体の描画
	ofSphere(150, 0, 0, 100);
}