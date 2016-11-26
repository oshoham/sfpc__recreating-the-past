#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
    image.load("coney.jpg");
    
    ofSetWindowShape(image.getWidth(), image.getHeight());
    
    ofSetFrameRate(30);
    
    // allocate the vector field with the desired spacing
    vectorField.setup(image.getWidth(), image.getHeight(), 10);
    
    // create the vector field using perlin noise
    //vectorField.randomize();
    
    // create the vector field from an image
    vectorField.setFromImage(image);
    
    // adjust the vector field by normalizing, scaling, biasing & blurring (to make it look nice)
    vectorField.normalize();
    vectorField.scale(5);
    vectorField.bias(0, 0.5);
    vectorField.blur();
    
    for (int i = 0; i < 1000; i++) {
        particle newParticle;
        ofVec2f pos( ofGetWidth()/2 + ofRandom( -200, 200), ofGetHeight()/2 + ofRandom( -200, 200));
        newParticle.pos.set(pos);
        newParticle.trailWidth = ofRandom(1, 15);
        particles.push_back(newParticle);
    }
    
    ofSetBackgroundAuto(false);
}

//--------------------------------------------------------------
void ofApp::update(){
    for( int i=0; i<particles.size(); i++){
        ofVec2f frc = vectorField.getVectorInterpolated(particles[i].pos.x, particles[i].pos.y, ofGetWidth(), ofGetHeight());
        particles[i].resetForce();
//        particles[i].addForce(0.0, 0.001);
        particles[i].addForce(frc.x * 0.1, frc.y * 0.1);
        particles[i].addDampingForce();
        particles[i].update();
        
        if (particles[i].isOutsideWalls()) {
            particles[i].trail.clear();
            particles[i].wrapAroundWalls();
        }
        
        particles[i].trail.addVertex(particles[i].pos);
        
        if (particles[i].trail.size() > 3) {
            particles[i].trail.getVertices().erase(particles[i].trail.getVertices().begin());
        }
    }
}

//--------------------------------------------------------------
void ofApp::draw(){
//    ofBackground(0);
    
//    ofSetColor(255);
//    image.draw(0, 0);
    
//    vectorField.draw();
    
    for( int i=0; i<particles.size(); i++){
        ofSetLineWidth(particles[i].trailWidth);
        ofSetColor(image.getColor(particles[i].pos.x, particles[i].pos.y));
        particles[i].trail.draw();
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
