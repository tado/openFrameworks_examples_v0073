//BackgroundSubtraction
//背景画像と現在の画像の差分を抽出するクラス

#pragma once

#include "ofMain.h"
#include "ofxOpenCv.h"

typedef enum{
	BG_ABS,
	BG_GREATER,
	BG_LESS
} captureMode;

class BackgroundSubtraction{
	
public:
	void setup(int width, int height);
	void update(unsigned char * pixelsIn, int width, int height );
	void draw(float x, float y);
	void setThreshold(int threshVal);
	void setDifferenceMode(int modeIn);
	void captureBackground();
	
	ofxCvColorImage color;
	ofxCvGrayscaleImage gray;
	ofxCvGrayscaleImage background;
	ofxCvGrayscaleImage thresh;
	ofxCvGrayscaleImage threshSmall;
	
	captureMode mode;
	
	int numFrames;
	float threshAmnt;
};