#pragma once

#include "ofMain.h"

typedef struct {
    ofPoint a;
    ofPoint b;
    ofPoint normalA;
    ofPoint normalB;
} lineSegment;

class ofApp : public ofBaseApp{
    
public:
    void setup();
    void update();
    void draw();
    
    void keyPressed(int key);
    void keyReleased(int key);
    void mouseMoved(int x, int y );
    void mouseDragged(int x, int y, int button);
    void mousePressed(int x, int y, int button);
    void mouseReleased(int x, int y, int button);
    void mouseEntered(int x, int y);
    void mouseExited(int x, int y);
    void windowResized(int w, int h);
    void dragEvent(ofDragInfo dragInfo);
    void gotMessage(ofMessage msg);
    
    void calcNormals(ofPoint const a, ofPoint const b, ofPoint & norma, ofPoint & normb);
    ofPoint getReflect(ofPoint const incident, ofPoint const norma, ofPoint const normb);
    
    vector<lineSegment> segments;
};
