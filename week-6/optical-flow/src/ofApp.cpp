#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
    // try setting the frame rate to 10-15 fps if it looks too "real"
    
    grabber.setup(ofGetWidth(), ofGetHeight());
    flowSolver.setup(grabber.getWidth(), grabber.getHeight(), 0.35, 5, 10, 1, 3, 2.25, false, false);
    
    ofPixels pixels = grabber.getPixels();
    for (int i = 0; i < grabber.getWidth(); i+=2) {
        for (int j = 0; j < grabber.getHeight(); j+=2) {
            brushStroke stroke;
            stroke.center = ofPoint(i, j);
            stroke.length = ofRandom(4, 10);
            stroke.radius = ofRandom(1.5, 2.0);
            stroke.color = pixels.getColor(stroke.center.x, stroke.center.y);
            stroke.deltaR = ofRandom(-15, 15);
            stroke.deltaG = ofRandom(-15, 15);
            stroke.deltaB = ofRandom(-15, 15);
            stroke.deltaIntensity = ofRandom(0.85, 1.15);
            stroke.deltaOrientation = ofRandom(-15, 15);
            stroke.orientation = 45 + stroke.deltaOrientation;
            strokes.push_back(stroke);
        }
    }
    
    std::random_shuffle(strokes.begin(), strokes.end());

}

//--------------------------------------------------------------
void ofApp::update(){
    grabber.update();
    grabber.getPixels().mirror(false, true);
    if (grabber.isFrameNew()) {
        flowSolver.update(grabber);
        
        triangulation.reset();
        vector<ofPoint> corners = {
            ofPoint(0, 0),
            ofPoint(ofGetWidth(), 0),
            ofPoint(0, ofGetHeight()),
            ofPoint(ofGetWidth(), ofGetHeight())
        };
        triangulation.addPoints(corners);
        for (auto & stroke : strokes) {
            triangulation.addPoint(stroke.center);
        }
        triangulation.triangulate();
        
        ofPixels pixels = grabber.getPixels();
        for (int i = 0; i < strokes.size(); i++) {
            brushStroke stroke = strokes[i];
            stroke.center += flowSolver.getVelAtPixel(stroke.center.x, stroke.center.y);
            ofColor pixelColor = pixels.getColor(stroke.center.x, stroke.center.y);
            float r = ofClamp((pixelColor.r + stroke.deltaR) * stroke.deltaIntensity, 0, 255);
            float g = ofClamp((pixelColor.g + stroke.deltaG) * stroke.deltaIntensity, 0, 255);
            float b = ofClamp((pixelColor.b + stroke.deltaB) * stroke.deltaIntensity, 0, 255);
            stroke.color = pixelColor;
            strokes[i] = stroke;
        }
    }
}

//--------------------------------------------------------------
void ofApp::draw(){
    ofBackground(0);
//    flowSolver.drawColored(grabber.getWidth(), grabber.getHeight(), 10, 3);
    
    // draw strokes
    for (auto & stroke : strokes) {
        ofSetLineWidth(stroke.radius);
        ofSetColor(stroke.color);
        ofDrawLine(stroke.center.x + (stroke.length / 2) * cos(stroke.orientation), stroke.center.y + (stroke.length / 2) * sin(stroke.orientation), stroke.center.x - (stroke.length / 2) * cos(stroke.orientation), stroke.center.y - (stroke.length / 2) * sin(stroke.orientation));
    }
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){
    if(key == 'p') { flowSolver.setPyramidScale(ofClamp(flowSolver.getPyramidScale() - 0.01,0.0,1.0)); }
    else if(key == 'P') { flowSolver.setPyramidScale(ofClamp(flowSolver.getPyramidScale() + 0.01,0.0,1.0)); }
    else if(key == 'l') { flowSolver.setPyramidLevels(MAX(flowSolver.getPyramidLevels() - 1,1)); }
    else if(key == 'L') { flowSolver.setPyramidLevels(flowSolver.getPyramidLevels() + 1); }
    else if(key == 'w') { flowSolver.setWindowSize(MAX(flowSolver.getWindowSize() - 1,1)); }
    else if(key == 'W') { flowSolver.setWindowSize(flowSolver.getWindowSize() + 1); }
    else if(key == 'i') { flowSolver.setIterationsPerLevel(MAX(flowSolver.getIterationsPerLevel() - 1,1)); }
    else if(key == 'I') { flowSolver.setIterationsPerLevel(flowSolver.getIterationsPerLevel() + 1); }
    else if(key == 'a') { flowSolver.setExpansionArea(MAX(flowSolver.getExpansionArea() - 2,1)); }
    else if(key == 'A') { flowSolver.setExpansionArea(flowSolver.getExpansionArea() + 2); }
    else if(key == 's') { flowSolver.setExpansionSigma(ofClamp(flowSolver.getExpansionSigma() - 0.01,0.0,10.0)); }
    else if(key == 'S') { flowSolver.setExpansionSigma(ofClamp(flowSolver.getExpansionSigma() + 0.01,0.0,10.0)); }
    else if(key == 'f') { flowSolver.setFlowFeedback(false); }
    else if(key == 'F') { flowSolver.setFlowFeedback(true); }
    else if(key == 'g') { flowSolver.setGaussianFiltering(false); }
    else if(key == 'G') { flowSolver.setGaussianFiltering(true); }
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
