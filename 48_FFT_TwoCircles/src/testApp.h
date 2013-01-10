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

	//左右2chのFFTの入出力の値を確保
	float *left, *right;
	float *magnitudeL, *phaseL, *powerL;
	float *magnitudeR, *phaseR, *powerR;
	float avg_powerL, avg_powerR;

	//バッファーサイズとFFTサイズ
	int buffer_size;
	int fft_size;
	
	fft myfft; //FFTクラスのインスタンス
};
