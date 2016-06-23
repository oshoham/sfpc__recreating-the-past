#include "ofApp.h"
#include "ofxEasing.h"

//--------------------------------------------------------------
void ofApp::setup(){
    initTime = 0;
    numCircles = 5;
    circleRadius = 100;
    offSetFromCenterY = -175;
    
    wrappingAnimationDuration = 5;
    
    radiusAnimationDuration = 5;
    startOfRadiusAnimation = initTime + (numCircles * wrappingAnimationDuration);
    endOfRadiusAnimation = startOfRadiusAnimation + radiusAnimationDuration;
    
    secondWrappingAnimationDuration = 5;
    startOfSecondWrappingAnimation = endOfRadiusAnimation;
    endOfSecondWrappingAnimation = startOfSecondWrappingAnimation + secondWrappingAnimationDuration;
    
    secondRadiusAnimationDuration = 3;
    startOfSecondRadiusAnimation = endOfSecondWrappingAnimation;
    endOfSecondRadiusAnimation = startOfSecondRadiusAnimation + secondRadiusAnimationDuration;
    
    reverseSecondRadiusAnimationDuration = 3;
    startOfReverseSecondRadiusAnimation = endOfSecondRadiusAnimation;
    endOfReverseSecondRadiusAnimation = startOfReverseSecondRadiusAnimation + reverseSecondRadiusAnimationDuration;
    
    reverseSecondWrappingAnimationDuration = 5;
    startOfReverseSecondWrappingAnimation = endOfReverseSecondRadiusAnimation;
    endOfReverseSecondWrappingAnimation = startOfReverseSecondWrappingAnimation + reverseSecondWrappingAnimationDuration;
    
    reverseRadiusAnimationDuration = 5;
    startOfReverseRadiusAnimation = endOfReverseSecondWrappingAnimation;
    endOfReverseRadiusAnimation = startOfReverseRadiusAnimation + reverseRadiusAnimationDuration;
    
    reverseWrappingAnimationDuration = 3;
    
    endOfAllAnimations = endOfReverseRadiusAnimation + (numCircles * reverseWrappingAnimationDuration - numCircles);
}

//--------------------------------------------------------------
void ofApp::update(){
    
}

//--------------------------------------------------------------
void ofApp::draw(){
    ofBackground(0);
    ofSetColor(255,255,255);
    
    float now = fmod(ofGetElapsedTimef(), endOfAllAnimations);
    
    ofTranslate(ofGetWidth() / 2, ofGetHeight() / 2);
    
    for (int i = 0; i < numCircles; i++) {
        float startOfWrappingAnimation = initTime + (i * wrappingAnimationDuration);
        float startOfReverseWrappingAnimation = endOfReverseRadiusAnimation + (numCircles - 1 - i) * reverseWrappingAnimationDuration - ((numCircles - 1 - i) * 2);
        float endOfReverseWrappingAnimation = startOfReverseWrappingAnimation + reverseWrappingAnimationDuration;
        
        if (now < startOfWrappingAnimation || now >= endOfReverseWrappingAnimation) {
            continue;
        }
        
        float endOfWrappingAnimation = startOfWrappingAnimation + wrappingAnimationDuration;
        
        ofPushMatrix();
        ofRotate(360 * i / numCircles);
        
        ofRectangle boundingBox;
        boundingBox.setFromCenter(0, offSetFromCenterY, ofGetWidth() / 3, ofGetHeight() / 3);
        
        float wrappingAnimation = ofxeasing::map_clamp(now, startOfWrappingAnimation, endOfWrappingAnimation, 0, 0.685, &ofxeasing::cubic::easeInOut);
        float secondWrappingAnimation = ofxeasing::map_clamp(now, startOfSecondWrappingAnimation, endOfSecondWrappingAnimation, wrappingAnimation, 1.37, &ofxeasing::cubic::easeInOut);
        float reverseSecondWrappingAnimation = ofxeasing::map_clamp(now, startOfReverseSecondWrappingAnimation, endOfReverseSecondWrappingAnimation, secondWrappingAnimation, 0.685, &ofxeasing::cubic::easeInOut);
        float xPosOffset = ofxeasing::map_clamp(now, startOfReverseWrappingAnimation, endOfReverseWrappingAnimation, reverseSecondWrappingAnimation, 0, &ofxeasing::cubic::easeInOut);
        
        float xRadiusOffset = ofxeasing::map_clamp(
                                                   now,
                                                   startOfReverseRadiusAnimation,
                                                   endOfReverseRadiusAnimation,
                                                   ofxeasing::map_clamp(
                                                                        now,
                                                                        startOfRadiusAnimation,
                                                                        endOfRadiusAnimation,
                                                                        1,
                                                                        -1,
                                                                        &ofxeasing::linear::easeNone
                                                                        ),
                                                   1,
                                                   &ofxeasing::linear::easeNone
                                                   );
        float yRadiusOffset = ofxeasing::map_clamp(
                                                   now,
                                                   startOfReverseSecondRadiusAnimation,
                                                   endOfReverseSecondRadiusAnimation,
                                                   ofxeasing::map_clamp(
                                                                        now,
                                                                        startOfSecondRadiusAnimation,
                                                                        endOfSecondRadiusAnimation,
                                                                        1,
                                                                        0,
                                                                        &ofxeasing::linear::easeInOut
                                                                        ),
                                                   1,
                                                   &ofxeasing::linear::easeInOut);
        drawBendingCircle(circleRadius, boundingBox, xPosOffset, xRadiusOffset, yRadiusOffset);
        
        ofPopMatrix();
    }
}

//--------------------------------------------------------------
void ofApp::drawBendingCircle(int radius, ofRectangle boundingBox, float xPosOffset, float xRadiusOffset, float yRadiusOffset){
    vector<vector<ofPolyline>> screenSections = { { ofPolyline() }, { ofPolyline() } };
    
    bool prevPointDidWrap = false;
    
    int numPoints = 500;
    
    for (int i = 0; i < numPoints; i++){
        float angle = ofMap(i, 0, numPoints - 1, 0, TWO_PI) + PI / 2;
        ofPoint center = boundingBox.getCenter();
        ofPoint circle = radius * ofPoint(cos(angle), sin(angle)) * ofPoint(xRadiusOffset, yRadiusOffset);
        ofPoint offset = ofPoint(xPosOffset * ((numPoints - 1) - i), 0);
        ofPoint pt = center + circle + offset;
        
        if (pt.x < boundingBox.getRight()) {
            screenSections[0].back().addVertex(pt);
            if (prevPointDidWrap) {
                screenSections[1].push_back(ofPolyline());
            }
            prevPointDidWrap = false;
        } else {
            int numWraps = 0;
            while (pt.x >= boundingBox.getRight()) {
                pt.x = pt.x - boundingBox.getWidth();
                numWraps++;
            }
            while (numWraps >= screenSections.size()) {
                vector<ofPolyline> section;
                section.push_back(ofPolyline());
                screenSections.push_back(section);
            }
            screenSections[numWraps-1].push_back(ofPolyline());
            screenSections[numWraps].back().addVertex(pt);
            prevPointDidWrap = true;
        }
    }
    
    for (auto section: screenSections) {
        for (auto line: section) {
            line.draw();
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
