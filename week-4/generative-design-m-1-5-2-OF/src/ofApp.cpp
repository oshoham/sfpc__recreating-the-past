#include "ofApp.h"
#include "agent.h"

//--------------------------------------------------------------
void ofApp::setup(){
    ofSetBackgroundAuto(false);
    ofBackground(255);
    ofEnableSmoothing();
    for (int i = 0; i < 5000; i++) {
        agent a = agent();
        agents.push_back(a);
    }
    
    overlayAlpha = 10;
    agentsAlpha = 100 - overlayAlpha;
    drawMode = 1;
}

//--------------------------------------------------------------
void ofApp::update(){

}

//--------------------------------------------------------------
void ofApp::draw(){
    ofSetColor(ofColor(255, overlayAlpha));
    ofFill();
    ofDrawRectangle(0, 0, ofGetWidth(), ofGetHeight());
    
    ofSetColor(ofColor(0, agentsAlpha));
    for (int i = 0; i < agents.size(); i++) {
        if (drawMode == 1) {
            agents[i].updateAndDraw();
        } else if (drawMode == 2) {
            agents[i].updateAndDraw2();
        }
    }
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){
    if (key == '1') {
        drawMode = 1;
    } else if (key == '2') {
        drawMode = 2;
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
