#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
    nPoints = 100;
    nFrames = 9;
    stepStart = 0.0;
    stepEnd = 1 / (float)nPoints;
    
    length = 170;
    xLeft = 38;
    yBottom = 18;
    
    radius = 180;
    xCenter = ofGetWidth() / 2;
    yCenter = ofGetHeight() / 2;
}

//--------------------------------------------------------------
void ofApp::update(){
    nFrames = ofMap(ofGetMouseX(), 0, ofGetWidth(), 2, 20);
    stepEnd += 1/(float)nPoints * 0.005;
}

//--------------------------------------------------------------
void ofApp::draw(){
    ofBackground(0);
    
    for (int frame = 1; frame <= nFrames; frame++) {
        float time = (frame - 1) / (float)(nFrames - 1);
        float step = stepStart + (time * (stepEnd - stepStart));
        
        for (int point = 1; point <= nPoints; point++) {
            float a = -90 + 360 * point / nPoints;
            float r = 3 * radius;
            
            float x = cos(a * DEG) * radius + point * step * r;
            x = xCenter - (r / 2) + ((int)round(x + (r / 2)) % (int)round(r));
            float y = yCenter + sin(a * DEG) * radius;
            ofDrawCircle(round(x), round(y), 1);
        }
    }
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){

}

//--------------------------------------------------------------
void ofApp::keyReleased(int key){

}

//--------------------------------------------------------------
void ofApp::mouseMoved(int x, int y ){

}

//--------------------------------------------------------------
void ofApp::mouseDragged(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mouseReleased(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mouseEntered(int x, int y){

}

//--------------------------------------------------------------
void ofApp::mouseExited(int x, int y){

}

//--------------------------------------------------------------
void ofApp::windowResized(int w, int h){

}

//--------------------------------------------------------------
void ofApp::gotMessage(ofMessage msg){

}

//--------------------------------------------------------------
void ofApp::dragEvent(ofDragInfo dragInfo){ 

}
