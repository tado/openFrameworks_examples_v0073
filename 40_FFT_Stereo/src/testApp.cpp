#include "testApp.h"

void testApp::setup(){
    
	//画面基本設定
	ofSetFrameRate(60);
	ofBackground(0, 0, 0);
    ofSetVerticalSync(true);

	//FFTのサイズとバッファサイズを設定
	fft_size = 256;
	buffer_size = fft_size * 2;
	
	//FFTサイズにあわせて出力結果の配列を左右2ch分準備
	left = new float[buffer_size];
	magnitudeL = new float[fft_size];
	phaseL = new float[fft_size];
	powerL = new float[fft_size];

	right = new float[buffer_size];
	magnitudeR = new float[fft_size];
	phaseR = new float[fft_size];
	powerR = new float[fft_size];

	//オーディオストリームの設定
	ofSoundStreamSetup(0, 2, this, 44100, buffer_size, 4);
}

void testApp::update() {
	//オーディオ入力をFFT解析 (左右2ch)
	avg_powerL = 0.0;
	avg_powerR = 0.0;
	myfft.powerSpectrum(0, fft_size, left, buffer_size,	magnitudeL, phaseL, powerL, &avg_powerL);
	myfft.powerSpectrum(0, fft_size, right, buffer_size, magnitudeR, phaseR, powerR, &avg_powerR);
}

void testApp::draw() {

	//FFT解析した結果をもとに、グラフを生成
	float w = (float)ofGetWidth()/ (float)fft_size / 2.0f;
	for (int i = 0; i < fft_size; i++) {
		//色相のグラデーションで色を塗る
		ofColor col;
		col.setHsb(i * 255.0f / (float)fft_size, 255, 255);
		ofSetColor(col);
		
		float lh = magnitudeL[i] * 4.0f;
		float rh = magnitudeR[i] * 4.0f;

		ofRect(ofGetWidth()/2 - w * i, ofGetHeight()-lh, w, lh); //左
		ofRect(ofGetWidth()/2 + w * i, ofGetHeight()-rh, w, rh); //右
	}
}

void testApp::exit(){

}

void testApp::audioIn(float* input, int bufferSize, int nChannels) {

	//入力信号(input)を左右2ch(left, right)に分ける
	for (int i = 0; i < bufferSize; i++){
		left[i]		= input[i*2];
		right[i]	= input[i*2+1];
	}
}
