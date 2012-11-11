#pragma once

#include "ofMain.h"
#include "fft.h"

class testApp : public ofBaseApp {
public:
	void setup();
	void update();
	void draw();
    void exit();

	void audioIn(float* input, int bufferSize, int nChannels);

	float *left, *right;
	float *magnitudeL, *phaseL, *powerL;
	float *magnitudeR, *phaseR, *powerR;
	float avg_powerL, avg_powerR;

	int buffer_size;
	int fft_size;
	
	fft myfft;
    
};
