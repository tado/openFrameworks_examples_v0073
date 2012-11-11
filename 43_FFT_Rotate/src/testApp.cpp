#include "testApp.h"

void testApp::setup(){
	
	//画面設定
	ofSetFrameRate(60);
	ofSetVerticalSync(true);
	ofBackground(0, 0, 0);
	ofEnableBlendMode(OF_BLENDMODE_ADD);
	
	//FFTサイズとバッファサイズ設定
	fft_size = 16384;
	buffer_size = fft_size * 2;
	
	//FFTサイズにあわせて出力結果の配列を準備
	audio_input = new float[buffer_size];
	magnitude = new float[fft_size];
	phase = new float[fft_size];
	power = new float[fft_size];
    locOffsetX = new float[fft_size];
    locOffsetY = new float[fft_size];
	magnitude_average = new float[fft_size];
	magnitude_average_snapshot = new float[fft_size];
	circle_phase = new float[fft_size];

	//オーディオストリームの設定
	ofSoundStreamSetup(0, 1, this, 44100, buffer_size, 4);
}

void testApp::update() {
	
	//FFT変換
	float avg_power = 0.0f;
	myfft.powerSpectrum(0, (int)fft_size, audio_input, buffer_size,	magnitude, phase, power, &avg_power);
	
	//値を整える
	for (int i = 0; i < fft_size; i++) {
		magnitude[i] = powf(magnitude[i], 0.5);
	}
	
	for (int i = 0; i < fft_size; i++) {
		float x = 0.1;
		magnitude_average[i] = (magnitude[i] * x) + (magnitude_average[i] * (1 - x));
	}
		
	for (int i = 0; i < fft_size; i++) {
		float v = fabs(magnitude_average[i] - magnitude_average_snapshot[i]);
        circle_phase[i] = v;
	}
}

void testApp::draw() {

	//FFT変換の結果をもとに円を螺旋状に配置
	circleSize = ofGetWidth()/(float)fft_size/4.0;
	ofTranslate(ofGetWidth()/2, ofGetHeight()/2);
    for (int i = 0; i < fft_size; i++){
        ofSetColor((255-255*i/fft_size)/2,100*i/fft_size,255*i/fft_size,200);
        float xx = cos(i/TWO_PI+circle_phase[i]*2.0) * i * circleSize;
		float yy = sin(i/TWO_PI+circle_phase[i]*2.0) * i * circleSize;
		ofCircle(xx, yy, circle_phase[i]*4.0);
    }
}

void testApp::audioIn(float* input, int bufferSize, int nChannels) {

	//入力信号を取得
	memcpy(audio_input, input, sizeof(float) * bufferSize);
}

void testApp::keyPressed(int key){

	//フルスクリーン表示
    if (key == 'f') {
		ofToggleFullscreen();
    }
}