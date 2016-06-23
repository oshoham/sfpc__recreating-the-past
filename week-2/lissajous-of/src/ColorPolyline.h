//
//  ColorPolyline.hpp
//  lissajous-of
//
//  Created by Oren Shoham on 6/16/16.
//
//

#ifndef ColorPolyline_h
#define ColorPolyline_h

#include "ofMain.h"

class ColorPolyline {
    public:
        ofPolyline polyline;
        ofColor color;
        ColorPolyline(ofPolyline polyline, ofColor color);
};

#endif /* ColorPolyline_h */
