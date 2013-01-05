#include "testApp.h"

using namespace ofxCv;

void testApp::setup() {
	//画面基本設定
	ofSetVerticalSync(true);
	ofEnableAlphaBlending();
	
	//カメラを初期化
	cam.initGrabber(640, 480);
	
	//合成するイメージのメモリ領域を確保して、読込み
	faceImage.allocate(640, 480, OF_IMAGE_COLOR);
	faceImage.loadImage("kenshiro.jpg");
	
	//カメラ映像のフェイストラッカーのセットアップ
	tracker.setup();
	//合成する顔画像のフェイストラッカーのセットアップ
	imgTracker.setup();
	imgTracker.update(toCv(faceImage));
}

void testApp::update() {
	//カメラ更新
	cam.update();
	if(cam.isFrameNew()) {
		//フェイストラッカーの更新
		//imgTracker.update(toCv(faceImage));
		tracker.update(toCv(cam));
	}
}

void testApp::draw() {
	//カメラ映像を描画
	ofSetColor(255);
	cam.draw(0, 0);
	//フレームレート表示
	ofDrawBitmapString(ofToString((int) ofGetFrameRate()), 10, 20);
	
	//もしカメラの映像に顔が検出されたら以下の処理をする
	if(tracker.getFound()) {
		
		//カメラ映像からメッシュを作成
		ofMesh objectMesh = tracker.getObjectMesh();
		//合成する顔の画像からメッシュを作成
		ofMesh imgMesh = imgTracker.getObjectMesh();
		
		//静止画のメッシュの頂点情報を、カメラから生成したメッシュのものに変換
		//つまり現在の顔の表情を、静止画のメッシュに適用
		for (int i = 0; i < objectMesh.getNumVertices(); i++) {
			imgMesh.setVertex(i, objectMesh.getVertex(i));
		}
		
		//画面の3Dのパースをなしに
		ofSetupScreenOrtho(640, 480, OF_ORIENTATION_DEFAULT, true, -1000, 1000);
		
		//カメラで検出された顔の、位置、大きさ、傾きを取得
		ofVec2f positon = tracker.getPosition();
		float scale = tracker.getScale();
		ofVec3f orientation = tracker.getOrientation();
		
		//静止画のメッシュをカメラの位置、大きさ、傾きにあわせる
		ofPushMatrix();
		ofTranslate(positon.x, positon.y);
		ofScale(scale, scale, scale);
		ofRotateX(orientation.x * 45.0f);
		ofRotateY(orientation.y * 45.0f);
		ofRotateZ(orientation.z * 45.0f);
		
		//静止画から生成メッシュを配置して、合成する画像をマッピング
		ofSetColor(255, 255, 255);
		faceImage.getTextureReference().bind();
		imgMesh.draw();
		faceImage.getTextureReference().unbind();
		ofPopMatrix();
	}
}

void testApp::keyPressed(int key) {
	//トラッカーのリセット
	if(key == 'r') {
		tracker.reset();
		imgTracker.reset();
	}
}