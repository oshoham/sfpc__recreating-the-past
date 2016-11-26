#ifndef helix_h
#define helix_h

#include "ofMain.h"

class helix {
    public:
//        helix();
        helix(ofPoint pos);
    
        void update();
        void draw();
    
        int L;
        float theta;
        float omega;
        ofPoint hubPos;
        ofPoint tipPos;
        ofPolyline trail;
};

#endif /* helix_h */
