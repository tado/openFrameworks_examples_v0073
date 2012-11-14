#include "testApp.h"

void testApp::setup(){
    ofSetFrameRate(60);
    ofBackgroundHex(0x000000);
    
    //GUI
    gui.setup("OpenCV control panel", 0, 0, ofGetWidth(), ofGetHeight());
    gui.addPanel("Background subtraction", 3);
    
    gui.setWhichColumn(0);
    gui.addToggle("use live video", "use_live", 0);
    gui.addToggle("draw input video", "draw_input", 0);
    gui.addToggle("grab background", "grab", 0);
    gui.addSlider("threshold", "thresh", 80, 0, 200, true);
    gui.addSlider("particle number", "num", 500, 0, 2000, true);
    
    vector <string> names;
    names.push_back("abs diff");
    names.push_back("greater than");
    names.push_back("less than");
    gui.addTextDropDown("difference mode", "diff_mode", 0, names);
    
    gui.setWhichColumn(1);
    gui.addDrawableRect("Color Image", &bgSub.color, 320, 240);
    gui.addDrawableRect("Gray Background", &bgSub.background, 320, 240);
    
    gui.setWhichColumn(2);
    gui.addDrawableRect("Grayscale Image", &bgSub.gray, 320, 240);
    gui.addDrawableRect("Gray Diffarence", &bgSub.thresh, 320, 240);
    gui.loadSettings("controlPanelSettings.xml");
    
    gui.setupEvents();
    gui.enableEvents();
    ofAddListener(gui.createEventGroup("grab"), this, &testApp::grabBackgroundEvent);
    ofAddListener(gui.createEventGroup("draw_input"), this, &testApp::drawInputEvent);
    ofAddListener(gui.createEventGroup("use_live"), this, &testApp::toggleLiveVideoEvent);
    ofAddListener(gui.createEventGroup("num"), this, &testApp::changeNumEvent);
    
    vidPlayer.loadMovie("fingers.mov");
    
    if (gui.getValueI("draw_input") == 1) {
        drawInputVideo = true;
    } else {
        drawInputVideo = false;
    }
    
    if (gui.getValueI("use_live") == 1) {
        vidPlayer.stop();
        vidGrabber.setVerbose(true);
        vidGrabber.initGrabber(320,240);
        bgSub.setup(vidGrabber.width, vidGrabber.height);
        useLiveVideo = true;
    } else {
        vidGrabber.close();
        vidPlayer.play();
        bgSub.setup(vidPlayer.width, vidPlayer.height);
        useLiveVideo = false;
    }
    
    for (int i = 0; i < gui.getValueI("num"); i++){
        particle myParticle;
        myParticle.setInitialCondition(ofRandom(0,ofGetWidth()),ofRandom(0,ofGetHeight()),0,0);
        particles.push_back(myParticle);
    }
    
    
    VF.setupField(60, 40, ofGetWidth(), ofGetHeight());
    bForceInward = false;
}

void testApp::grabBackgroundEvent(guiCallbackData & data){
    if( data.isElement("grab") && data.getInt(0) == 1 ){
        bgSub.captureBackground();
        gui.setValueB("grab", false);
    }
}

void testApp::drawInputEvent(guiCallbackData &data) {
    if (data.isElement("draw_input") && data.getInt(0) == 1) {
        drawInputVideo = true;
    } else {
        drawInputVideo = false;
    }
}

void testApp::toggleLiveVideoEvent(guiCallbackData & data) {
    bLearnBakground = true;
    if (useLiveVideo) {
        vidGrabber.close();
        vidPlayer.play();
        bgSub.setup(vidPlayer.width, vidPlayer.height);
        useLiveVideo = false;
    } else {
        vidPlayer.stop();
        vidGrabber.setVerbose(true);
        vidGrabber.initGrabber(320,240);
        bgSub.setup(vidGrabber.width, vidGrabber.height);
        useLiveVideo = true;
    }
}

void testApp::changeNumEvent(guiCallbackData & data) {
    particles.clear();
    for (int i = 0; i < data.getInt(0); i++) {
        particle myParticle;
        myParticle.setInitialCondition(ofRandom(0,ofGetWidth()),ofRandom(0,ofGetHeight()),0,0);
        particles.push_back(myParticle);
    }
}

void testApp::update(){
    VF.externalWidth = ofGetWidth();
    VF.externalHeight = ofGetHeight();
    
    bool bNewFrame = false;
    
    if (useLiveVideo) {
        vidGrabber.grabFrame();
        bNewFrame = vidGrabber.isFrameNew();
    } else {
        vidPlayer.idleMovie();
        bNewFrame = vidPlayer.isFrameNew();		
    }
    
    if (bNewFrame){
        if (useLiveVideo) {
            bgSub.update(vidGrabber.getPixels(), vidGrabber.width, vidGrabber.height);
        } else {
            bgSub.update(vidPlayer.getPixels(), vidPlayer.width, vidPlayer.height);
        }
        
        bgSub.setDifferenceMode(gui.getValueI("diff_mode"));;
        bgSub.setThreshold(gui.getValueI("thresh"));
        VF.setFromPixels(bgSub.threshSmall.getPixels(), bForceInward, 0.02f);
    }
    
    if (gui.minimize) {
        for (int i = 0; i < particles.size(); i++){
            computeBinPosition( particles[i].pos.x, particles[i].pos.y,  &(particles[i].bitFlagW), &(particles[i].bitFlagH));
        }
        
        for (int i = 0; i < particles.size(); i++){
            particles[i].resetForce();
        }
        
        for (int i = 0; i < particles.size(); i++){
            particles[i].resetForce();
            // get the force from the vector field: 
            ofVec2f frc;
            frc = VF.getForceFromPos(particles[i].pos.x, particles[i].pos.y);
            particles[i].addForce(frc.x, frc.y);
            particles[i].addDampingForce();
            particles[i].update();
            
        }
        
        // particle v particle
        for (int i = 0; i < particles.size(); i++){
            unsigned int bitFlagH_pta = particles[i].bitFlagH;
            unsigned int bitFlagW_pta = particles[i].bitFlagW;
            for (int j = 0; j < i; j++){
                unsigned int bitFlagH_ptb = particles[j].bitFlagH;
                unsigned int bitFlagW_ptb = particles[j].bitFlagW;
                if ((bitFlagW_pta & bitFlagW_ptb) && (bitFlagH_pta & bitFlagH_ptb)){
                    particles[i].addRepulsionForce( particles[j],20,0.7);
                }
            }
        }
        
        for (int i = 0; i < particles.size(); i++){
            //particles[i].addAttractionForce( 500,500,1500,0.01);
            particles[i].addAttractionForce(ofGetWidth()/2, ofGetHeight()/2, 1500, 0.01);
            particles[i].addForce(0,0.02f);
            particles[i].addDampingForce();
            particles[i].bounceOffWalls();
            particles[i].update();
        }
    }
    
    gui.update();	
}

void testApp::draw(){
    if (gui.minimize) {
        ofFill();
        ofSetHexColor(0xffffff);
        glPushMatrix();
        glScalef((float) ofGetWidth() / (float)bgSub.thresh.width, (float) ofGetHeight() / (float)bgSub.thresh.height, 1.0f);
        if (drawInputVideo) {
            bgSub.color.draw(0, 0);
        }
        ofPopMatrix();
        
        ofSetHexColor(0x999999);
        VF.draw();
        
        ofSetHexColor(0x3399ff);
        ofEnableBlendMode(OF_BLENDMODE_ADD);
        for (int i = 0; i < particles.size(); i++){
            particles[i].draw();
        }
    }
    
    gui.draw();	
}

void testApp::keyPressed  (int key){ 
    if (key == 'f') {
        ofToggleFullscreen();
    }
    if (key == ' ') {
        for (int i = 0; i < particles.size(); i++){
            particles[i].setInitialCondition(ofRandom(0,ofGetWidth()), ofRandom(0,ofGetHeight()), 0,0);
        }
    }
}

void testApp::mouseDragged(int x, int y, int button){
    gui.mouseDragged(x, y, button);
}

void testApp::mousePressed(int x, int y, int button){
    gui.mousePressed(x, y, button);
}

void testApp::mouseReleased(int x, int y, int button){
    gui.mouseReleased();
}