#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
    grabber.setup(640, 480);
    binaryImage.allocate(640, 480, OF_IMAGE_COLOR);
    
    message = "my greatest teachers were ";
    
    for (int i = 0; i < 64; i++) {
        ofPoint pt(i * 10, 20);
        letterPositions.push_back(pt);
        speed.push_back(ofRandom(2, 4));
    }
}

//--------------------------------------------------------------
void ofApp::update(){
    grabber.update();
    
    for (int i = 0; i < 640; i++) {
        for (int j = 0; j < 480; j++) {
            ofColor c = grabber.getPixels().getColor(i, j);
            if (c.getBrightness() > mouseX) {
                binaryImage.setColor(i, j, ofColor::black);
            } else {
                binaryImage.setColor(i, j, ofColor::white);
            }
        }
    }
    binaryImage.update();
    
    // now let's make ART
    for (int i = 0; i < 64; i++) {
        
        if (letterPositions[i].y > 480) {
            letterPositions[i].y = 0;
            speed[i] = ofRandom(2, 4);
        }
        
        // let's be SMART
        
        ofColor c = binaryImage.getColor(letterPositions[i].x, letterPositions[i].y);
        if (c.getBrightness() > 127) {
            // let's do something...
            // we're not going to hang out
            bool bDidWeFindIt = false;
            for (int j = letterPositions[i].y; j >= 0; j--) {
                ofColor c2 = binaryImage.getColor(letterPositions[i].x, j);
                if (c2 .getBrightness() < 127) {
                    // YAY!
                    letterPositions[i].y = j+1;
                    bDidWeFindIt = true;
                    break;
                }
            }
            
            if (!bDidWeFindIt) {
                letterPositions[i].y = 0;
            }
        } else {
            letterPositions[i].y += speed[i];
        }
    }
}

//--------------------------------------------------------------
void ofApp::draw(){
    ofSetColor(255);
    grabber.draw(0, 0);
    binaryImage.draw(640, 0);
    
    ofSetColor(255, 0, 0);
    for (int i = 0; i < letterPositions.size(); i++){
        char c = message[ i % message.size()];
        string toDraw = "";
        toDraw += c;
        ofDrawBitmapString(toDraw, letterPositions[i].x, letterPositions[i].y);
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
