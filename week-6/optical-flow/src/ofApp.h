#pragma once

#include "ofMain.h"
#include "ofxOpticalFlowFarneback.h"
#include "ofxDelaunay.h"

typedef struct {
    ofPoint center;
    int length;
    float radius;
    int orientation;
    ofColor color;
    int deltaR;
    int deltaG;
    int deltaB;
    float deltaIntensity;
    int deltaOrientation;
} brushStroke;

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
		
        ofVideoGrabber grabber;
        ofxOpticalFlowFarneback flowSolver;
        vector<brushStroke> strokes;
        ofxDelaunay triangulation;
};
