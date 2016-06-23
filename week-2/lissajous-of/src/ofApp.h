#pragma once

#include "ofMain.h"
#include "ColorPolyline.h"

class ofApp : public ofBaseApp{
    
private:
    vector<ColorPolyline> polylinesWithColors;
    ofColor colors [6] = {
        ofColor::fromHex(0xDD1E2F),
        ofColor::fromHex(0xEBB035),
        ofColor::fromHex(0x06A2CB),
        ofColor::fromHex(0x218559),
        ofColor::fromHex(0xD0C6B1),
//        ofColor::fromHex(0x192823)
    };
    float angles [4] = {0.0, 90.0, 180.0, 270.0};
    int currentColorIndex;
    int pointCount;
    int counter;

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
		
};
