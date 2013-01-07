#pragma once

#include "ofMain.h"
#include "ofxPd.h"
#include "fft.h"

class testApp : public ofBaseApp{
    
public:
    
    void setup();
    void update();
    void draw();
    void exit();
    
    void keyPressed  (int key);
    void mouseMoved(int x, int y );
    void mouseDragged(int x, int y, int button);
    void mousePressed(int x, int y, int button);
    void mouseReleased(int x, int y, int button);
    void windowResized(int w, int h);
    
    void audioReceived(float * input, int bufferSize, int nChannels);
    void audioRequested(float * output, int bufferSize, int nChannels);
    
    // ofxPd関連のプロパティ
    ofxPd pd;
    vector<float> pd_input;
    vector<float> pd_output;
    float loop_dur;
    float feedback;
    
    // 左右2chのFFTの入出力の値を確保
	float *left, *right;
	float *magnitudeL, *phaseL, *powerL;
	float *magnitudeR, *phaseR, *powerR;
	float avg_powerL, avg_powerR;
	//バッファーサイズとFFTサイズ
	int buffer_size;
	int fft_size;
	
	fft myfft; //FFTクラスのインスタンス
    
};
