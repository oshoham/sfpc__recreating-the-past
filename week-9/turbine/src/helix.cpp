#include "helix.h"
#include "ofMain.h"


//--------------------------------------------------------------
helix::helix(ofPoint pos) {
    L = 100;
    theta = 0;
    omega = PI;
    
    hubPos = pos;
    tipPos = hubPos + L * ofPoint(cos(theta), sin(theta), 0);
}

//--------------------------------------------------------------
void helix::update() {
    float dt = 0.01;
    tipPos = hubPos + L * ofPoint(cos(theta), sin(theta), 0);
    theta += omega * dt;
    hubPos += ofPoint(0, 0, 1);
    trail.addVertex(tipPos);
}

//--------------------------------------------------------------
void helix::draw() {
//    ofDrawSphere(hubPos, 2);
    ofDrawSphere(tipPos, 2);
    
    ofPushMatrix();
    ofTranslate((hubPos + tipPos) * 0.5);
    ofRotate(theta / TWO_PI * 360 + 88);
    ofDrawCylinder(ofPoint(0, 0, 0), 0.5, L);
    ofPopMatrix();
    
    trail.draw();
}