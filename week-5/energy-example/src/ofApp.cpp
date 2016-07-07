#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
    for (int i = 0; i < 50; i++){
        for (int j = 0; j < 50; j++){
            energy.push_back(0);
        }
    }
}

//--------------------------------------------------------------
void ofApp::update(){
    for (int i = 0; i < 50; i++){
        for (int j = 0; j < 50; j++){
            energy[j*50+i] *= 0.99;
            
            ofRectangle rect(i*10, j*10, 10, 10);
            if (rect.inside(mouseX, mouseY)){
                energy[j*50+i] = 1;
            }
        }
    }
}

//--------------------------------------------------------------
void ofApp::draw(){
    ofBackground(0);
    
    float timef = ofGetElapsedTimef();
    
    for (int i = 0; i < 50; i++){
        for (int j = 0; j < 50; j++){
            
            float pct = sin(energy[j*50+i] * TWO_PI * 5);
            ofSetColor(127 + 127 * pct);
            ofDrawCircle(i*10, j*10, 5); //energy[j*50+i];
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
