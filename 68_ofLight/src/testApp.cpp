#include "testApp.h"

void testApp::setup(){
	ofBackgroundHex(0x000000);
	glEnable(GL_DEPTH_TEST);

	// カメラの距離
	cam.setDistance(600);

	// ライティングを使用可能に
	light.enable();
	// スポットライトを配置
	light.setSpotlight();
	// 照明の位置
	light.setPosition(-100, 100, 100);
	// 環境光の色
	light.setAmbientColor(ofFloatColor(0.3, 0.1, 0.1, 1.0));
	// 拡散反射光の色
	light.setDiffuseColor(ofFloatColor(0.3, 0.3, 0.8));
	// 鏡面反射光の色
	light.setSpecularColor(ofFloatColor(1.0, 1.0, 1.0));
}

void testApp::update(){
}

void testApp::draw(){
	// 視点を移動可能にして、物体を描画
	ofTranslate(ofGetWidth()/2, ofGetHeight()/2);
	cam.begin();
	ofSetHexColor(0xffffff);
	ofBox(-150, 0, 0, 200);
	ofSphere(150, 0, 0, 100);
	cam.end();
}