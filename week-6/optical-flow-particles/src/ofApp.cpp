#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
    grabber.setup(ofGetWidth(), ofGetHeight());
    flowSolver.setup(grabber.getWidth(), grabber.getHeight(), 0.35, 5, 10, 1, 3, 2.25, false, false);
    ofSetBackgroundAuto(false);
    
    for (int i = 0; i < 2000; i++) {
        particle p = particle();
        p.pos.set(ofRandom(0, ofGetWidth()), ofRandom(0, ofGetHeight()));
        p.vel.set(0, 0);
        particles.push_back(p);
        lines.push_back(ofPolyline());
        lineWidths.push_back(ofRandom(1, 8));
        lineLengths.push_back(ofRandom(2, 4));
    }
    ofSetFrameRate(15);
}

//--------------------------------------------------------------
void ofApp::update(){
    grabber.update();
    if (grabber.isFrameNew()) {
        ofPixels pixels = grabber.getPixels();
        pixels.mirror(false, true);
        frame.setFromPixels(pixels);
        flowSolver.update(frame);
        
        for (int i = 0; i < particles.size(); i++) {
            particles[i].resetForce();
            particles[i].addForce(0.0, 0.1);
            ofPoint flowVelocity = flowSolver.getVelAtPixel(particles[i].pos.x, particles[i].pos.y) * 0.1;
            particles[i].addForce(flowVelocity.x, flowVelocity.y);
            particles[i].addDampingForce();
            particles[i].update();
            
            if (particles[i].isOutsideWalls()) {
                lines[i].clear();
                particles[i].wrapAroundWalls();
            }
            
            lines[i].addVertex(particles[i].pos);

            if (lines[i].size() > lineLengths[i]) {
                lines[i].getVertices().erase(lines[i].getVertices().begin());
            }
        }
    }
}

//--------------------------------------------------------------
void ofApp::draw(){
    ofPixels pixels = grabber.getPixels();
    pixels.mirror(false, true);
    ofRectangle viewport = ofGetCurrentViewport();
    for (int i = 0; i < particles.size(); i++) {
        ofSetColor(pixels.getColor(particles[i].pos.x, particles[i].pos.y));
        if (lines[i].getVertices().size() > 0) {
            drawLineAsRect(lines[i].getVertices().front(), lines[i].getVertices().back(), lineWidths[i]);
        }
    }
}

//--------------------------------------------------------------
void ofApp::drawLineAsRect(ofPoint startVec, ofPoint endVec, float thickness) {
    float angle = atan((endVec.y-startVec.y)/(endVec.x-startVec.x));
    ofPushMatrix();
    ofTranslate(startVec.x,startVec.y);
    ofRotate(ofRadToDeg(angle));
    float lineLength = (endVec.x - startVec.x)/cos(angle);
    ofDrawRectangle(0, -thickness/2, lineLength, thickness);
    ofPopMatrix();
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
