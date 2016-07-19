#pragma once

#include "ofMain.h"

#define SQRT1_2 0.7071067811865476

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
        ofPoint poissonDiscSample();
        bool far(int x, int y);
        ofPoint sample(int x, int y);
    
        int k;
        int radius;
        int radius2;
        int R;
        int cellSize;
        int gridWidth;
        int gridHeight;
        vector<ofPoint> grid;
        vector<ofPoint> queue;
        int sampleSize;
    
        vector<ofPoint> points;
        ofVideoGrabber grabber;
};
