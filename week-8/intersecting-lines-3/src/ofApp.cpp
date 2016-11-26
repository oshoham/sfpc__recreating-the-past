#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
    for (int i = 0; i < 100; i++) {
        ofPoint a(ofRandom(0, ofGetWidth()), ofRandom(0, ofGetHeight()));
        float randomAngle = ofRandom(0, TWO_PI);
        ofPoint b = a + 100 * ofPoint(cos(randomAngle), sin(randomAngle));
        lineSegment segment;
        segment.a = a;
        segment.b = b;
        calcNormals(a, b, segment.normalA, segment.normalB);
        
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
            
            ofPoint dir = ofPoint(mouseX, mouseY) - ofPoint(512, 512);
            dir.normalize();
            ofPoint reflect = getReflect(dir, segments[i].normalA, segments[i].normalB);
            ofSetHexColor(0xFF0099);
            ofDrawLine(closestIntersection, closestIntersection + reflect * 200);
            ofSetColor(255, 255, 255);
        } else {
            ofSetColor(255, 255, 255);
        }
        ofDrawLine(segments[i].a, segments[i].b);
    }
}

//--------------------------------------------------------------
void ofApp::calcNormals(ofPoint const a, ofPoint const b, ofPoint & norma, ofPoint & normb) {
    ofPoint diff = b - a;
    diff.normalize();
    norma = ofPoint(-diff.y, diff.x);
    normb = ofPoint(diff.y, -diff.x);
}

//--------------------------------------------------------------
inline ofPoint getNormalFacing(ofPoint const incident, ofPoint const norma, ofPoint const normb) {
    float a = norma.dot(incident);
    float b = normb.dot(incident);
    if (a < b) return norma;
    else return normb;
}

ofPoint ofApp::getReflect(ofPoint const incident, ofPoint const norma, ofPoint const normb) {
    ofPoint normal = getNormalFacing(incident, norma, normb);
    return incident - normal * 2.f * normal.dot(incident);
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
