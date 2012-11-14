#include "testApp.h"

void testApp::setup(){
	ofSetFrameRate(60);
	ofBackground(255, 255, 255);
	ofSetRectMode(OF_RECTMODE_CENTER);

	//8段階の文字の濃度を文字列に
	pixelString = " .-+*a&@";
	//640x480 pixelでカメラの映像をキャプチャー
    myVideo.initGrabber(800, 600, true);    
}

void testApp::update(){
	//カメラの取得を更新
    myVideo.update();
}

void testApp::draw(){
	//位置を補整
	int left = (ofGetWidth() - myVideo.width) / 2;
	int top = (ofGetHeight() - myVideo.height) / 2;
	//全てのピクセルの値を取得
	unsigned char * pixels = myVideo.getPixels();
	
	int skip = 8;
	ofTranslate(left, top+skip);
	ofSetColor(0, 0, 0);
	for (int i = 0; i < myVideo.width; i = i + skip){
		for (int j = 0; j < myVideo.height; j = j + skip){
            //RGBごとのピクセルの値を取得
            int r = pixels[j * myVideo.width * 3 + i * 3];
			int g = pixels[j * myVideo.width * 3 + i * 3 + 1];
			int b = pixels[j * myVideo.width * 3 + i * 3 + 2];
			//明度を算出
			float pct = 1.0 - (r + g + b) / 3.0f / 255.0f;
			//濃度の応じた文字をとりだし
			string str = pixelString.substr(int(pct * 8),1);
			//文字を描画
			ofDrawBitmapString(str, i, j);
		}
	}
}