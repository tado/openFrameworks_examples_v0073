#include "testApp.h"

void testApp::setup(){
	//画面設定
    ofSetBackgroundAuto(false);
	ofBackground(0, 0, 0);
	ofEnableBlendMode(OF_BLENDMODE_ADD);
    ofSetCircleResolution(64);
	//FFTサイズとバッファサイズ設定
    fft_size = 16384;
	buffer_size = fft_size * 2;
	//FFTサイズにあわせて出力結果の配列を準備
	audio_input = new float[buffer_size];
	magnitude = new float[fft_size];
	phase = new float[fft_size];
	power = new float[fft_size];
	magnitude_average = new float[fft_size];
    pos = new ofVec2f[fft_size];
    vec = new ofVec2f[fft_size];
	//オーディオストリームの設定
	ofSoundStreamSetup(0, 1, this, 44100, buffer_size, 4);
    //ばねパラメータ
    stiffness = 0.2;
    damping = 0.99;
    mass = 10.0;
}

void testApp::update() {
	//FFT変換
	float avg_power = 0.0f;
	myfft.powerSpectrum(0, (int)fft_size, audio_input, buffer_size,	magnitude, phase, power, &avg_power);
}

void testApp::draw() {
    //背景をフェード
    ofEnableBlendMode(OF_BLENDMODE_ALPHA);
    ofSetColor(0, 0, 0, 10);
    ofRect(0, 0, ofGetWidth(), ofGetHeight());
    ofEnableBlendMode(OF_BLENDMODE_ADD);
	//FFT変換の結果をもとに円を螺旋状に配置
    ofSetColor(31, 127, 255);
	circleSize = ofGetWidth()/(float)fft_size/4.0;
	ofTranslate(ofGetWidth()/2, ofGetHeight()/2);
    for (int i = 0; i < fft_size; i++){
        //ばねの運動を計算
        float addFroce = magnitude[i];
        float direction = ofRandom(360);
        float addX = cos(direction) * addFroce;
        float addY = sin(direction) * addFroce;
        float forceX = stiffness * -pos[i].x + addX;
        float accelerationX = forceX / mass;
        vec[i].x = damping * (vec[i].x + accelerationX);
        float forceY = stiffness * -pos[i].y + addY;
        float accelerationY = forceY / mass;
        vec[i].y = damping * (vec[i].y + accelerationY);
        pos[i] += vec[i];
        // パーティクル描画
        float r = magnitude[i] * i / 400.0;
        ofColor col;
        int hue = i * 10 / (float)fft_size * 360;
        if (hue > 255) {
            hue = 255;
        }
        col.setHsb(hue, 255, 255);
        ofSetColor(col);
        ofCircle(pos[i].x, pos[i].y, r);
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