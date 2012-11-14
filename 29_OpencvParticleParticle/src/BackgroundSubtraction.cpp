#include "BackgroundSubtraction.h"

void BackgroundSubtraction::setup(int width, int height){
	
	color.allocate(width, height);
	gray.allocate(width, height);
	thresh.allocate(width, height);
	background.allocate(width, height);
	threshSmall.allocate(60, 40);
	
	threshAmnt  = 29;
	numFrames	= 0;
}

void BackgroundSubtraction::update(unsigned char * pixelsIn, int width, int height ){
	color.setFromPixels(pixelsIn, width, height);
	
	gray = color;
	
	if( numFrames < 20 ){
		background = gray;
	}	
	
	if( mode == BG_ABS ){
		thresh.absDiff(gray, background);
	}else if( mode == BG_GREATER ){
		thresh = gray;
		thresh -= background;
	}else if( mode == BG_LESS ){
		thresh = background;
		thresh -= gray;	
	}
	
	threshSmall.scaleIntoMe(thresh);
	threshSmall.blur(5);
	
	thresh.threshold(threshAmnt);
	numFrames++;
}

void BackgroundSubtraction::draw(float x, float y){
	ofSetColor(0xFFFFFF);
	gray.draw(x, y);
	background.draw(x + gray.width,  y);
	thresh.draw(x, y + gray.height);
}

void BackgroundSubtraction::setThreshold(int threshVal){
	threshAmnt = (int)threshVal;
}

void BackgroundSubtraction::captureBackground(){
	background = gray;
}

void BackgroundSubtraction::setDifferenceMode(int modeIn){
	mode = (captureMode)modeIn;
}