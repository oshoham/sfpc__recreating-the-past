#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
    grabber.setup(640, 480);
    ofSetRectMode(OF_RECTMODE_CENTER);
    
    for (int i = 0; i < grabber.getWidth(); i++) {
        for (int j = 0; j < grabber.getHeight(); j++) {
            pixelColors[i][j] = ofColor::fromHsb((ofRandom(180, 360) / 360.0) * 255, (ofRandom(80, 100) / 100.0) * 255, (ofRandom(50, 90) / 100.0) * 255);
        }
    }
    
    drawMode = 1;
}

//--------------------------------------------------------------
void ofApp::update(){
    grabber.update();
}

//--------------------------------------------------------------
void ofApp::draw(){
    ofBackground(0);
    
    // proper way to mosaic is to average the image, but we're just gonna step by 10
    for (int i = 0; i < grabber.getWidth(); i+=10) {
        for (int j = 0; j < grabber.getHeight(); j+=10) {
            int brightness = grabber.getPixels().getColor(i, j).getBrightness();
            ofColor pixelColor = pixelColors[i][j];
            pixelColor.setBrightness(brightness);
            ofSetColor(pixelColor);
            
            if (drawMode == 1) {
                ofDrawCircle(i, j, ofMap(brightness, 0, 255, 0.5, 3));
            } else if (drawMode == 2) {
                ofPushMatrix();
                ofTranslate(i, j);
                ofRotateZ(ofMap(brightness, 0, 255, 0, 90));
                ofDrawRectangle(0, 0, 8, 3);
                ofPopMatrix();
            }
        }
    }
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){
    if (key == '1') {
        for (int i = 0; i < grabber.getWidth(); i++) {
            for (int j = 0; j < grabber.getHeight(); j++) {
                pixelColors[i][j] = ofColor::fromHsb((ofRandom(360) / 360.0) * 255, (ofRandom(100) / 100.0) * 255, (ofRandom(100) / 100.0) * 255);
            }
        }
    } else if (key == '2') {
        for (int i = 0; i < grabber.getWidth(); i++) {
            for (int j = 0; j < grabber.getHeight(); j++) {
                pixelColors[i][j] = ofColor::fromHsb((ofRandom(360) / 360.0) * 255, (ofRandom(100) / 100.0) * 255, 255);
            }
        }
    } else if (key == '3') {
        for (int i = 0; i < grabber.getWidth(); i++) {
            for (int j = 0; j < grabber.getHeight(); j++) {
                pixelColors[i][j] = ofColor::fromHsb((ofRandom(360) / 360.0) * 255, 255, (ofRandom(100) / 100.0) * 255);
            }
        }
    } else if (key == '4') {
        for (int i = 0; i < grabber.getWidth(); i++) {
            for (int j = 0; j < grabber.getHeight(); j++) {
                pixelColors[i][j] = ofColor::fromHsb(0, 0, (ofRandom(100) / 100.0) * 255);
            }
        }
    } else if (key == '5') {
        for (int i = 0; i < grabber.getWidth(); i++) {
            for (int j = 0; j < grabber.getHeight(); j++) {
                pixelColors[i][j] = ofColor::fromHsb((195 / 360.0) * 255, 255, (ofRandom(100) / 100.0) * 255);
            }
        }
    } else if (key == '6') {
        for (int i = 0; i < grabber.getWidth(); i++) {
            for (int j = 0; j < grabber.getHeight(); j++) {
                pixelColors[i][j] = ofColor::fromHsb((195 / 360.0) * 255, (ofRandom(100) / 100.0) * 255, 255);
            }
        }
    } else if (key == '7') {
        for (int i = 0; i < grabber.getWidth(); i++) {
            for (int j = 0; j < grabber.getHeight(); j++) {
                pixelColors[i][j] = ofColor::fromHsb((ofRandom(180) / 360.0) * 255, 255, (ofRandom(100) / 100.0) * 255);
            }
        }
    } else if (key == '8') {
        for (int i = 0; i < grabber.getWidth(); i++) {
            for (int j = 0; j < grabber.getHeight(); j++) {
                pixelColors[i][j] = ofColor::fromHsb((ofRandom(180, 360) / 360.0) * 255, (ofRandom(80, 100) / 100.0) * 255, (ofRandom(50, 90) / 100.0) * 255);
            }
        }
    } else if (key == '9') {
        for (int i = 0; i < grabber.getWidth(); i++) {
            for (int j = 0; j < grabber.getHeight(); j++) {
                if (i % 2 == 0 || j % 2 == 0) {
                    pixelColors[i][j] = ofColor::fromHsb((ofRandom(360) / 360.0) * 255, 255, (ofRandom(100) / 100.0) * 255);
                } else {
                    pixelColors[i][j] = ofColor::fromHsb((195 / 360.0) * 255, (ofRandom(100) / 100.0) * 255, 255);
                }
            }
        }
    } else if (key == 'c') {
        drawMode = 1;
    } else if (key == 'r') {
        drawMode = 2;
    }
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
