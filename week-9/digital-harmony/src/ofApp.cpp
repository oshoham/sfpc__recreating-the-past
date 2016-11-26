#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
    nPoints = 60;
    nFrames = 3;
    stepStart = 0;
    stepEnd = 1 / 60.0;
    
    length = 170;
    xLeft = 38;
    yBottom = 18;
    
    radius = 60;
    xCenter = 140;
    yCenter = 96;
}

//--------------------------------------------------------------
void ofApp::update(){
    nFrames = ofMap(ofGetMouseX(), 0, ofGetWidth(), 2, 20);
}

//--------------------------------------------------------------
void ofApp::draw(){
    ofBackground(0);

    for (int frame = 1; frame <= nFrames; frame++) {
        float time = (frame - 1) / (float)(nFrames - 1);
        float step = stepStart + (time * (stepEnd - stepStart));
        
        for (int point = 1; point <= nPoints; point++) {
            float a = 360 * step * point;
            
            float x = xCenter + cos(a * DEG) * (point / (float)nPoints) * radius;
            float y = yCenter + sin(a * DEG) * (point / (float)nPoints) * radius;
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
