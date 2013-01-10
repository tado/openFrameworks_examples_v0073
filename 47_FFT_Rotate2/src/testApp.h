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
	
	int buffer_size;
	int fft_size;
	float circleSize;
	float *audio_input;
	float *magnitude, *phase, *power;
	float *magnitude_average, *magnitude_average_snapshot; 
	float *circle_phase;
	float *locOffsetX, *locOffsetY;
	
	fft myfft; //FFTクラスのインスタンス	
};