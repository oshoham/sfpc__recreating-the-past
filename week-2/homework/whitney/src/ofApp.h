#pragma once

#include "ofMain.h"

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
    
        void drawBendingCircle(int radius, ofRectangle boundingBox, float xPosOffset, float xRadiusOffset, float yRadiusOffset);
    
        float initTime;
        int numCircles;
        int circleRadius;
        int offSetFromCenterY;
        
        float wrappingAnimationDuration;
        
        float radiusAnimationDuration;
        float startOfRadiusAnimation;
        float endOfRadiusAnimation;
        
        float secondWrappingAnimationDuration;
        float startOfSecondWrappingAnimation;
        float endOfSecondWrappingAnimation;
        
        float secondRadiusAnimationDuration;
        float startOfSecondRadiusAnimation;
        float endOfSecondRadiusAnimation;
        
        float reverseSecondRadiusAnimationDuration;
        float startOfReverseSecondRadiusAnimation;
        float endOfReverseSecondRadiusAnimation;
        
        float reverseSecondWrappingAnimationDuration;
        float startOfReverseSecondWrappingAnimation;
        float endOfReverseSecondWrappingAnimation;
        
        float reverseRadiusAnimationDuration;
        float startOfReverseRadiusAnimation;
        float endOfReverseRadiusAnimation;
    
        float reverseWrappingAnimationDuration;
    
        float endOfAllAnimations;
};
