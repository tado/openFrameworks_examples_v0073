#include "testApp.h"

void testApp::setup(){
	ofBackground(255, 255, 255);
	//ビットマップ画像の読みこみ
	myImage.loadImage("t_hero.png");
	
	//8段階の文字の濃度を文字列に
	pixelString = " .-+*a&@";
	
}

void testApp::update(){	
}

void testApp::draw(){
	int left = (ofGetWidth() - myImage.width) / 2;
	int top = (ofGetHeight() - myImage.height) / 2;
	ofTranslate(left, top);
	unsigned char * pixels = myImage.getPixels();

	int skip = 5;
	ofSetColor(0, 0, 0);
	
	for (int i = 0; i < myImage.width; i = i + skip){
		for (int j = 0; j < myImage.height; j = j + skip){
			int brightness = pixels[j * myImage.width + i];
			float pct = 1.0 - brightness / 255.0;
			//濃度の応じた文字をとりだし
			string str = pixelString.substr(int(pct * 8),1);
			//文字を描画
			ofDrawBitmapString(str, i, j);
		}
	}
}