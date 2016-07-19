#include "ofApp.h"

//--------------------------------------------------------------
bool colorComparator(ofColor & a, ofColor & b) {
    return a.getHue() < b.getHue();
}

//--------------------------------------------------------------
void ofApp::setup(){
    grabber.setup(VIDEO_WIDTH, VIDEO_HEIGHT);
    image.allocate(VIDEO_WIDTH, VIDEO_HEIGHT, OF_IMAGE_COLOR);
}

//--------------------------------------------------------------
void ofApp::update(){
    grabber.update();
    sortedPixels.clear();
    
    ofPixels pixels = grabber.getPixels();
    
    for (int i = 0; i < pixels.getWidth(); i++) {
        for (int j = 0; j < pixels.getHeight(); j++) {
            sortedPixels.push_back(pixels.getColor(i, j));
        }
    }
    
    ofSort(sortedPixels, colorComparator);
    
    for (int i = 0; i < pixels.getWidth(); i++) {
        for (int j = 0; j < pixels.getHeight(); j++) {
            image.setColor(i, j, sortedPixels[ j * pixels.getWidth() + i]);
        }
    }
    image.update();
}

//--------------------------------------------------------------
void ofApp::draw(){
    ofBackground(0);
    image.draw(0, 0);
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
