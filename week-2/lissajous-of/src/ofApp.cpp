#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
    currentColorIndex = 0;
    pointCount = 0;
    counter = 0;
    polylinesWithColors.push_back(ColorPolyline(ofPolyline(), colors[currentColorIndex]));
}

//--------------------------------------------------------------
void ofApp::update(){

}

//--------------------------------------------------------------
void ofApp::draw(){
    ofBackground(ofColor::fromHex(0x192823));
    counter++;
    
    if (counter > 60) {
        currentColorIndex = (currentColorIndex + 1) % (sizeof(colors) / sizeof(colors[0]));
        ofPolyline newPolyline;
        newPolyline.addVertex(polylinesWithColors.back().polyline.getVertices().back());
        polylinesWithColors.push_back(ColorPolyline(newPolyline, colors[currentColorIndex]));
        counter = 0;
    }
    
    ofTranslate(ofGetWidth() / 2, ofGetHeight() / 2);
    
    float x = 250 * cos(ofGetElapsedTimef() * 3.1);
    float y = 250 * sin(ofGetElapsedTimef() * 2.7);
    polylinesWithColors.back().polyline.addVertex(ofPoint(x, y));
    pointCount++;
    
    if (pointCount > 300) {
        polylinesWithColors.front().polyline.getVertices().erase(polylinesWithColors.front().polyline.getVertices().begin());
        if (polylinesWithColors.front().polyline.size() == 0) {
            polylinesWithColors.erase(polylinesWithColors.begin());
        }
    }
    
    for (int i = 0; i < (sizeof(angles) / sizeof(angles[0])); i++) {
        float angle = angles[i];
        ofRotate(angle);
        for (auto& colorPolyline : polylinesWithColors) {
            ofSetColor(colorPolyline.color);
            colorPolyline.polyline.draw();
        }
        ofRotate(-angle);
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
