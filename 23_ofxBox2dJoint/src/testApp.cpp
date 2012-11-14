#include "testApp.h"

void testApp::setup() {
	ofSetVerticalSync(true);
	ofBackgroundHex(0x000000);
	
	box2d.init(); // Box2Dの世界の初期化
	box2d.setGravity(0, 0); // 無重力に
	box2d.createBounds(); // 地面を生成
	box2d.setFPS(30.0); // Box2Dの世界でのFPS
	box2d.registerGrabbing(); // 物体に接触可能に
}

void testApp::update() {
	box2d.update(); // Box2Dの更新
}

void testApp::draw() {
	// バネを描く
	for(int i=0; i<joints.size(); i++) {
		ofNoFill();
		ofSetHexColor(0x333333);
		joints[i].draw();
	}
	
	// circlesを描く
	for(int i=0; i<rects.size(); i++) {
		ofFill();
		ofSetHexColor(0x3366ff);
		rects[i].draw();
	}
}

void testApp::mouseReleased(int x, int y, int button) {
	ofxBox2dRect rect; //円
	rect.setPhysics(10.0, 0.99, 0.0);
	
	// Box2dの世界に生成した円を追加
	rect.setup(box2d.getWorld(), x, y, 2, 2);
	rects.push_back(rect); // 動的配列に追加
	
	if (rects.size() > 1) {
		for (int i = 0; i < rects.size()-1; i++) {
			ofxBox2dJoint joint;
			joint.setup(box2d.getWorld(), rects[rects.size()-1].body, rects[i].body);
			joint.setFrequency(0.4);
			joint.setDamping(0.1);
			joint.setLength(200);
			joints.push_back(joint);
		}
	}
}

void testApp::mouseDragged(int x, int y, int button) {
	for (int i = 0; i < rects.size()-1; i++) {
		rects[i].addRepulsionForce(x, y, -1);
	}
}