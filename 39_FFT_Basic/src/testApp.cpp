#include "testApp.h"

void testApp::setup(){
	
	//画面基本設定
	ofSetFrameRate(60);
	ofBackground(0, 0, 0);
	
	//FFTのサイズとバッファサイズを設定
	fft_size = 512;
	buffer_size = fft_size * 2;
	
	//FFTサイズにあわせて出力結果の配列を準備
	magnitude = new float[fft_size];
	phase = new float[fft_size];
	power = new float[fft_size];
	input = new float[buffer_size];
	
	//オーディオストリームの設定
	ofSoundStreamSetup(0, 1, this, 44100, buffer_size, 4);
}

void testApp::update() {
	//オーディオ入力をFFT解析
	avg_power = 0.0; //平均パワーを初期化
	myfft.powerSpectrum(0, fft_size, input, buffer_size, magnitude, phase, power, &avg_power);
}

void testApp::draw() {
	
	//FFT解析した結果をもとに、グラフを生成
	float w = (float)ofGetWidth()/ (float)fft_size;
	for (int i = 0; i < fft_size; i++) {
		//色相のグラデーションで色を塗る
		ofColor col;
		col.setHsb(i * 255.0f / (float)fft_size, 255, 255);
		ofSetColor(col);
		float h = magnitude[i] * 4.0f;
		ofRect(w * i, ofGetHeight()-h, w, h);
	}
}

void testApp::audioIn(float* _input, int bufferSize, int nChannels) {
	//入力信号を取得
	input = _input;
}
