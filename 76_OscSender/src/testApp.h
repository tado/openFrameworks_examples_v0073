#pragma once

#include "ofMain.h"
#include "ofxOsc.h"

#define HOST "172.21.23.200" // 受信側のIPアドレス
#define PORT 8000 // 受信側のポート番号

class testApp : public ofBaseApp{
    
public:
    void setup();
    void update();
    void draw();
    void mouseMoved(int x, int y );
    void mouseDragged(int x, int y, int button);
    void mousePressed(int x, int y, int button);
    void mouseReleased(int x, int y, int button);
    
    //OSCメッセージの送信者
    ofxOscSender sender;
};

