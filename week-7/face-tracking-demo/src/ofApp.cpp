#include "ofApp.h"

using namespace ofxCv;

//--------------------------------------------------------------
void ofApp::setup(){
    cam.setup(ofGetWidth(), ofGetHeight());
    tracker.setup();
}

//--------------------------------------------------------------
void ofApp::update(){
    cam.update();
    if(cam.isFrameNew()) {
        tracker.update(toCv(cam));
    }
}

//--------------------------------------------------------------
void ofApp::draw(){
    ofSetColor(255);
    cam.draw(0, 0);
    ofSetLineWidth(2);
    tracker.draw();
    ofPolyline noseBase = tracker.getImageFeature(ofxFaceTracker::NOSE_BASE);
    ofSetColor(ofColor::red);
    noseBase.draw();
    ofDrawCircle(noseBase.getCentroid2D(), 8 * tracker.getScale());
    ofDrawBitmapString(ofToString((int) ofGetFrameRate()), 10, 20);
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){
    if(key == 'r') {
        tracker.reset();
    }
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
