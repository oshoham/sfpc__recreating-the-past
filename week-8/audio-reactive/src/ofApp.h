#pragma once

#include "ofMain.h"
#include "ofxAubio.h"
#include "ofxGui.h"

class ofApp : public ofBaseApp{

	public:
		void setup();
		void update();
		void draw();
        void exit();

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
    
        void audioIn(float * input, int bufferSize, int nChannels);
        void audioOut(ofSoundBuffer & buffer);
    
        void onsetEvent(float & time);
        void beatEvent(float & time);
    
        void drawAubioGui();
    
        ofxAubioOnset onset;
        ofxAubioPitch pitch;
        ofxAubioBeat beat;
        ofxAubioMelBands bands;
    
        bool gotOnset;
        bool gotBeat;
    
        ofSoundBuffer tempBuffer;
    
        ofxPanel pitchGui;
        ofxFloatSlider midiPitch;
        ofxFloatSlider pitchConfidence;
        
        ofxPanel beatGui;
        ofxFloatSlider bpm;
        
        ofxPanel onsetGui;
        ofxFloatSlider onsetThreshold;
        ofxFloatSlider onsetNovelty;
        ofxFloatSlider onsetThresholdedNovelty;
        
        ofxPanel bandsGui;
        ofPolyline bandPlot;
};
