//
//  agent.cpp
//  generative-design-m-1-5-2-OF
//
//  Created by Oren Shoham on 7/5/16.
//
//

#include "agent.h"
#include "ofMain.h"

float noiseScale = 300;
float noiseStrength = 100;
float strokeWidth = 0.3;

//------------------------------------------------------------
agent::agent() {
    pos.set(ofRandom(ofGetWidth()), ofRandom(ofGetHeight()));
    prevPos.set(pos);
    stepSize = ofRandom(1, 5);
}

void agent::updateAndDraw() {
    float angle = ofNoise(pos.x / noiseScale, pos.y / noiseScale) * noiseStrength;
    pos.x += cos(angle) * stepSize;
    pos.y += sin(angle) * stepSize;
    
    bool isOutside = pos.x < -10 || pos.x > ofGetWidth() + 10 || pos.y < -10 || pos.y > ofGetHeight() + 10;
    if (isOutside) {
        pos.set(ofRandom(ofGetWidth()), ofRandom(ofGetHeight()));
        prevPos.set(pos);
    }
    
    ofSetLineWidth(strokeWidth * stepSize);
    ofDrawLine(prevPos, pos);
    prevPos.set(pos);
}

void agent::updateAndDraw2() {
    float angle = ofNoise(pos.x / noiseScale, pos.y / noiseScale) * 24;
    angle = (angle - int(angle)) * noiseStrength;
    
    pos.x += cos(angle) * stepSize;
    pos.y += sin(angle) * stepSize;
    
    bool isOutside = pos.x < -10 || pos.x > ofGetWidth() + 10 || pos.y < -10 || pos.y > ofGetHeight() + 10;
    if (isOutside) {
        pos.set(ofRandom(ofGetWidth()), ofRandom(ofGetHeight()));
        prevPos.set(pos);
    }
    
    ofSetLineWidth(strokeWidth * stepSize);
    ofDrawLine(prevPos, pos);
    prevPos.set(pos);
}