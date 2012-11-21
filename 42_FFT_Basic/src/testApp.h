#pragma once

#include "ofMain.h"
#include "fft.h"

class testApp : public ofBaseApp {
public:
	void setup();
	void update();
	void draw();
	void audioIn(float* input, int bufferSize, int nChannels);

	float *input; //入力信号
	float *power; //パワースペクトラム
	float *magnitude; //マグニチュードスペクトラム
	float *phase; //位相
	float avg_power; //平均のパワー
	int buffer_size; //バッファーサイズ
	int fft_size; //FFTサイズ
		
	fft myfft; //FFTクラスのインスタンス
};
