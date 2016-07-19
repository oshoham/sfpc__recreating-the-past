#pragma once

#include "ofMain.h"

#define VIDEO_WIDTH 640
#define VIDEO_HEIGHT 480
#define SCREEN_ELEMENT_SIZE 8

typedef struct {
    int value;
    float brightness;
} charWithBrightness;

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
        ofTrueTypeFont font;
    
        vector<charWithBrightness> charactersByBrightness;
        ofFbo fbo;
};
