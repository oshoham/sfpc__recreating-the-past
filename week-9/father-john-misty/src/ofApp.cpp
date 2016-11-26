#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
    colors = {
        ofColor::fromHex(0x31E5CC),
        ofColor::fromHex(0xEC65E5),
        ofColor::fromHex(0xEA535C),
        ofColor::fromHex(0xE3FD00),
        ofColor::fromHex(0xE3FD00),
        ofColor::fromHex(0x7023F4),
        ofColor::fromHex(0xC8FFB5),
        ofColor::fromHex(0xF5ACFD),
        ofColor::fromHex(0xA09AF1),
        ofColor::fromHex(0x22A48C),
        ofColor::fromHex(0x1A4F7C),
        ofColor::fromHex(0xF4DDF2),
        ofColor::fromHex(0xFCE390),
        ofColor::fromHex(0xA67AF9),
        ofColor::fromHex(0x288DF0),
    };
    
    ofSetBackgroundAuto(false);
    ofBackground(255);
    numCircles = 0;
}

//--------------------------------------------------------------
void ofApp::update(){

}

//--------------------------------------------------------------
void ofApp::draw(){
//    if (numCircles < 100000) {
        for(int i = 0; i < 100; i++) {
            ofPoint point(ofRandom(ofGetWidth()), ofRandom(ofGetHeight()));
            ofSetColor(colors[floor(ofRandom(colors.size()))]);
            ofDrawCircle(point, ofRandom(4, 7));
            numCircles++;
        }
//    }
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
