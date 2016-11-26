#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
    for (int i = 0; i < 100; i++) {
        ofPoint a(ofRandom(0, ofGetWidth()), ofRandom(0, ofGetHeight()));
        float randomAngle = ofRandom(0, TWO_PI);
        ofPoint b = a + 10 * ofPoint(cos(randomAngle), sin(randomAngle));
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
    
    ofSetColor(255, 255, 255);
    for (int i = 0; i < segments.size(); i++) {
        ofDrawLine(segments[i].a, segments[i].b);
    }
    
    ofPoint curPos;    // light position
    ofPoint curDir;    // light direction
    
    curPos.set(512, 512);
    curDir = (ofPoint(mouseX, mouseY) - ofPoint(512, 512)).normalize();
    
    // for 10 times
    ofSetHexColor(0x5BDB99);
    for (int z = 0; z < 10; z++) {
        
        // calc closest intersection
        int closestLineIndex = -1;
        float smallestDistance = 1000000;
        ofPoint closestIntersection;
        
        for (int i = 0; i < segments.size(); i++) {
            ofPoint intersection;
            ofPoint a = segments[i].a;
            ofPoint b = segments[i].b;
            ofPoint c = curPos;
            ofPoint d = curPos + curDir * 2000;
            
            if (ofLineSegmentIntersection(a, b, c, d, intersection)) {
                float distance = (intersection - c).length();
                if (distance < smallestDistance) {
                    smallestDistance = distance;
                    closestLineIndex = i;
                    closestIntersection = intersection;
                }
            }
        }
        
        // if we do intersect, YAY!
        // draw  a line from current position to intersect
        if (closestLineIndex != -1) {
            ofDrawLine(curPos, closestIntersection);
            // calc where we go to next
            curDir = getReflect(curDir, segments[closestLineIndex].normalA, segments[closestLineIndex].normalB);
            curPos = closestIntersection + curDir * 0.001; // move curPos a little off of the segment so that we don't intersect with it next time
        } else {
            ofDrawLine(curPos, curPos + curDir * 2000);
        }
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

//--------------------------------------------------------------
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
