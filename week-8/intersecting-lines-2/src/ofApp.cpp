#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
    for (int i = 0; i < 1000; i++) {
        ofPoint a(ofRandom(0, ofGetWidth()), ofRandom(0, ofGetHeight()));
        float randomAngle = ofRandom(0, TWO_PI);
        ofPoint b = a + 100 * ofPoint(cos(randomAngle), sin(randomAngle));
        lineSegment segment { a, b };
        segments.push_back(segment);
    }
}

//--------------------------------------------------------------
void ofApp::update(){

}

//--------------------------------------------------------------
void ofApp::draw(){
    ofBackground(0);
    
    ofSetColor(255, 0, 0);
    ofDrawLine(512, 512, mouseX, mouseY);
    
    int closestLineIndex = -1;
    float smallestDistance = 1000000;
    ofPoint closestIntersection;
    
    for (int i = 0; i < segments.size(); i++) {
        ofPoint intersection;
        ofPoint a = segments[i].a;
        ofPoint b = segments[i].b;
        
        ofPoint c(512, 512);
        ofPoint d(mouseX, mouseY);
        
        if (ofLineSegmentIntersection(a, b, c, d, intersection)) {
            float distance = (intersection - c).length();
            if (distance < smallestDistance) {
                smallestDistance = distance;
                closestLineIndex = i;
                closestIntersection = intersection;
            }
        }
    }
    
    for (int i = 0; i < segments.size(); i++) {
        if (i == closestLineIndex) {
            ofSetColor(0, 255, 0);
        } else {
            ofSetColor(255, 255, 255);
        }
        ofDrawLine(segments[i].a, segments[i].b);
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
