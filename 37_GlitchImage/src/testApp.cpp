#include "testApp.h"

void testApp::setup() {
	ofSetFrameRate(60);
	ofSetBackgroundAuto(false);
	//Jpeg圧縮の強度
	quality = OF_IMAGE_QUALITY_WORST;
	//リセット
	reset();
}

void testApp::reset() {
	//元のファイルを読込み
	img.loadImage("input.jpg");
}

void testApp::update() {
	//Jpeg圧縮したデータの保存ファイル名
	string compressedFilename = "compressed.jpg";
	//Jpeg形式でファイルを保存
	img.saveImage(compressedFilename, quality);
	ofBuffer file = ofBufferFromFile(compressedFilename);
	int fileSize = file.size();
	//Jepgファイルをバッファーに読込み
	char * buffer = file.getBinaryBuffer();
	//データを破壊する場所をランダムに決定
	int whichByte = (int) ofRandom(fileSize);
	//ONにするbitをランダムに決定
	int whichBit = ofRandom(8);
	//ビットシフト(データを破壊?)
	char bitMask = 1 << whichBit;
	buffer[whichByte] |= bitMask;
	//glitchしたファイルを保存
	ofBufferToFile(compressedFilename, file);
	//再度読込み
	img.loadImage(compressedFilename);
}

void testApp::draw() {
	//glitchしたイメージを描画
	ofSetColor(255,255,255);
	img.draw(0, 0, ofGetWidth(), ofGetHeight());
}

void testApp::keyPressed  (int key){
	//リセット
	reset();
}

void testApp::mousePressed(int x, int y, int button){
	//リセット
	reset();
}
