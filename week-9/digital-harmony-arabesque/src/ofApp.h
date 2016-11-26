#pragma once

#include "ofMain.h"

#define DEG 0.0174533

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
		
        float stepStart;
        float stepEnd;
        float length;
        float xLeft;
        float yBottom;
        int nPoints;
        int nFrames;
        
        float radius;
        float xCenter;
        float yCenter;
};
