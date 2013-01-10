#pragma once
#include "ofMain.h"
#include "fft.h"

class testApp : public ofBaseApp {
public:
	void setup();
	void update();
	void draw();
	void keyPressed  (int key);
	void audioIn(float* input, int bufferSize, int nChannels);
	
    // FFTのパラメータ
	int buffer_size;
	int fft_size;
	float circleSize;
    // データ格納用領域
	float *audio_input;
	float *magnitude, *phase, *power;
	float *magnitude_average;
	// FFTクラスのインスタンス
	fft myfft;
    // ばねのパラメータ
    float stiffness, damping, mass;
    //パーティクルの位置とスピード
    ofVec2f *pos, *vec;
};