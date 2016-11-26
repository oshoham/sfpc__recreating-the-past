#include "ofApp.h"
#include "helix.h"


//--------------------------------------------------------------
void ofApp::setup(){
    int numHelixes = 15;
    
    for (int i = 0; i < numHelixes; i++) {
        helix h(ofPoint(0, 0, 0));
        h.theta = 360 * i / numHelixes;
        helixes.push_back(h);
    }
}

//--------------------------------------------------------------
void ofApp::update(){
    int index = 0;
    for (auto & h : helixes) {
//        h.L = ofMap(sin(ofGetElapsedTimef()), -1, 1, 10, 100);
//        h.theta += ofMap(index, 0, helixes.size(), 0, 0.05);
//        h.L = ofMap(sin(ofGetElapsedTimef() * index / helixes.size()), -1, 1, 10, 100);
        h.update();
        index++;
    }
    cam.setPosition(cam.getPosition() + ofPoint(1, 0, 0));
}

//--------------------------------------------------------------
void ofApp::draw(){
    ofBackground(0);
    ofSetColor(255);
    
    cam.begin();
    
    ofPushMatrix();
    
    ofRotateY(90);
    
    for (auto & h: helixes) {
        h.draw();
    }
    
    ofPopMatrix();
    
    cam.end();
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
