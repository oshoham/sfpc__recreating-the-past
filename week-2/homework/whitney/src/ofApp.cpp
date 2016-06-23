#include "ofApp.h"
#include "ofxEasing.h"

//--------------------------------------------------------------
void ofApp::setup(){
    initTime = 0;
    
    // we're going to draw numCircles (5) circles evenly spaced out in a pentagonal pattern around the origin
    // each circle will have a radius of circleRadius (100)
    // the center of each circle will be offsetFromCenterY (-175) pixels away from the center
    // offsetFromCenterY is negative so that we get a pentagon arrangement rather than an inverted pentagon
    numCircles = 5;
    circleRadius = 100;
    offSetFromCenterY = -175;
    
    // each animation has a duration, a start time, and an end time
    // each subsequent animation's start time is calculated from the previous animation's end time
    // the animations occur in the order that these variables have been defined
    
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
    
    // loop back to the beginning of the scene once we hit the end of all of the animations
    float now = fmod(ofGetElapsedTimef(), endOfAllAnimations);
    
    // draw from the origin rather than the top left corner
    ofTranslate(ofGetWidth() / 2, ofGetHeight() / 2);
    
    for (int i = 0; i < numCircles; i++) {
        // the timing of the first animations (when the circles appear and fold on themselves) need to
        // timed based on which circle is being drawn, so we define the start and end times here
        float startOfWrappingAnimation = initTime + (i * wrappingAnimationDuration);
        float startOfReverseWrappingAnimation = endOfReverseRadiusAnimation + (numCircles - 1 - i) * reverseWrappingAnimationDuration - ((numCircles - 1 - i) * 2);
        float endOfReverseWrappingAnimation = startOfReverseWrappingAnimation + reverseWrappingAnimationDuration;
        
        // don't draw the circle if it hasn't appeared yet or has already disappeared
        if (now < startOfWrappingAnimation || now >= endOfReverseWrappingAnimation) {
            continue;
        }
        
        float endOfWrappingAnimation = startOfWrappingAnimation + wrappingAnimationDuration;
        
        ofPushMatrix();
        ofRotate(360 * i / numCircles);
        
        // boundingBox defines the horizontal space that the circle will wrap around as it moves/animates
        ofRectangle boundingBox;
        boundingBox.setFromCenter(0, offSetFromCenterY, ofGetWidth() / 3, ofGetHeight() / 3);
        
        // the next part is kinda complicated...sorry :(
        
        // animation works by using an easing function to map the elapsed time
        // to the value of the parameter that we're animating
        float wrappingAnimation = ofxeasing::map_clamp(now, startOfWrappingAnimation, endOfWrappingAnimation, 0, 0.685, &ofxeasing::cubic::easeInOut);
        
        float secondWrappingAnimation = ofxeasing::map_clamp(now, startOfSecondWrappingAnimation, endOfSecondWrappingAnimation, wrappingAnimation, 1.37, &ofxeasing::cubic::easeInOut);
        
        float reverseSecondWrappingAnimation = ofxeasing::map_clamp(now, startOfReverseSecondWrappingAnimation, endOfReverseSecondWrappingAnimation, secondWrappingAnimation, 0.685, &ofxeasing::cubic::easeInOut);
        
        float xPosOffset = ofxeasing::map_clamp(now, startOfReverseWrappingAnimation, endOfReverseWrappingAnimation, reverseSecondWrappingAnimation, 0, &ofxeasing::cubic::easeInOut);
        
        // we can perform multiple animations on the same parameter by doing multiple mappings using different start and end times
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
        
        // draw the weird bending circle thing with the animated parameters that we've calculated
        drawBendingCircle(circleRadius, boundingBox, xPosOffset, xRadiusOffset, yRadiusOffset);
        
        ofPopMatrix();
    }
}

//--------------------------------------------------------------
void ofApp::drawBendingCircle(int radius, ofRectangle boundingBox, float xPosOffset, float xRadiusOffset, float yRadiusOffset){
    // our circle is drawn as a series of ofPolylines
    // we wrap the circle around boundingBox by splitting our circle up into a vector of polylines as we hit the edge of the screen
    // every time the circle wraps around the screen, we add another vector<ofPolyline> to screenSections
    // this ensures that there won't ever be a polyline that has points on both edges of the screen at the
    // same time
    vector<vector<ofPolyline>> screenSections = { { ofPolyline() }, { ofPolyline() } };
    
    // used for calculating whether a point needs to added to a new polyline
    bool prevPointDidWrap = false;
    
    // the resolution of the circle
    int numPoints = 500;
    
    for (int i = 0; i < numPoints; i++){
        // compute a point on the circle
        float angle = ofMap(i, 0, numPoints - 1, 0, TWO_PI) + PI / 2;
        ofPoint center = boundingBox.getCenter();
        ofPoint circle = radius * ofPoint(cos(angle), sin(angle)) * ofPoint(xRadiusOffset, yRadiusOffset);
        ofPoint offset = ofPoint(xPosOffset * ((numPoints - 1) - i), 0);
        ofPoint pt = center + circle + offset;
        
        // wrap across boundingBox
        // this part is complicated...
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
