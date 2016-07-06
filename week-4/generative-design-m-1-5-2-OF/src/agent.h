//
//  agent.h
//  generative-design-m-1-5-2-OF
//
//  Created by Oren Shoham on 7/5/16.
//
//

#ifndef agent_h
#define agent_h

#include "ofMain.h"

class agent {
    public:
//        float noiseScale;
//        float noiseStrength;
//        float strokeWidth;
    
        ofPoint pos;
        ofPoint prevPos;
        float stepSize;
    
        agent();
    
        void updateAndDraw();
        void updateAndDraw2();
};

#endif /* agent_h */
