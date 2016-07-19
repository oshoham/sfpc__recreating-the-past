#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
    grabber.setup(ofGetWidth(), ofGetHeight());
    flowSolver.setup(grabber.getWidth(), grabber.getHeight(), 0.35, 5, 10, 1, 3, 2.25, false, false);
    ofSetBackgroundAuto(false);
    
    for (int i = 0; i < 1000; i++) {
        particle p = particle();
        p.pos.set(ofRandom(0, ofGetWidth()), ofRandom(0, ofGetHeight()));
        p.vel.set(0, 0);
        particles.push_back(p);
        ofPolyline line;
        lines.push_back(line);
    }
}

//--------------------------------------------------------------
void ofApp::update(){
    grabber.update();
    grabber.getPixels().mirror(false, true);
    if (grabber.isFrameNew()) {
        flowSolver.update(grabber);
        
        for (int i = 0; i < particles.size(); i++) {
            particles[i].resetForce();
            particles[i].addForce(0.0, 0.28);
            ofPoint flowVelocity = flowSolver.getVelAtPixel(particles[i].pos.x, particles[i].pos.y);
            particles[i].addForce(flowVelocity.x, flowVelocity.y);
            particles[i].addDampingForce();
            particles[i].update();
            particles[i].wrapAroundWalls();
            lines[i].addVertex(particles[i].pos);
            
            if (lines[i].size() > 2) {
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
        if (viewport.inside(particles[i].pos)) {
            ofSetColor(pixels.getColor(particles[i].pos.x, particles[i].pos.y));
//            particles[i].draw();
            lines[i].draw();
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
