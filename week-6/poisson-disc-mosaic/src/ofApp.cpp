#include "ofApp.h"
#include "ofxVoronoi.h"

//--------------------------------------------------------------
void ofApp::setup(){
    k = 30;
    radius = 10;
    radius2 = radius * radius;
    R = 3 * radius2;
    cellSize = radius * SQRT1_2;
    gridWidth = ceil(ofGetWidth() / cellSize);
    gridHeight = ceil(ofGetHeight() / cellSize);
    for (int i = 0; i < gridWidth * gridHeight; i++) {
        ofPoint p(-1, -1);
        grid.push_back(p);
    }
    sampleSize = 0;
    
//    for (int i = 0; i < 10000; i++) {
//        ofPoint s = poissonDiscSample();
//        if (s.x != -1 && s.y != -1) {
//            points.push_back(s);
//        }
//    }
    
    grabber.setup(ofGetWidth(), ofGetHeight());
}

// adapted from https://bl.ocks.org/mbostock/19168c663618b7f07158
//--------------------------------------------------------------
ofPoint ofApp::poissonDiscSample() {
    if (!sampleSize) {
        return sample(ofRandom(ofGetWidth()), ofRandom(ofGetHeight()));
    }
    
    while (queue.size()) {
        int i = ofRandom(queue.size());
        ofPoint s = queue[i];
        
        for (int j = 0; j < k; ++j) {
            float a = ofRandom(TWO_PI);
            float r = sqrt(ofRandom(R) + radius2);
            int x = s.x + r * cos(a);
            int y = s.y + r * sin(a);
            
            if (0 <= x && x < ofGetWidth() && 0 <= y && y < ofGetHeight() && far(x, y)) {
                return sample(x, y);
            }
        }
        
        queue.erase(queue.begin() + i);
    }
    
    return ofPoint(-1, -1);
}

//--------------------------------------------------------------
bool ofApp::far(int x, int y) {
    int i = x / cellSize;
    int j = y / cellSize;
    int i0 = max(i - 2, 0);
    int j0 = max(j - 2, 0);
    int i1 = min(i + 3, gridWidth);
    int j1 = min(j + 3, gridHeight);
    
    for (j = j0; j < j1; ++j) {
        int o = j * gridWidth;
        for (i = i0; i < i1; ++i) {
            ofPoint s = grid[o + i];
            if (s.x != -1 && s.y != -1) {
                int dx = s.x - x;
                int dy = s.y - y;
                if (dx * dx + dy * dy < radius2) {
                    return false;
                }
            }
        }
    }
    
    return true;
}

//--------------------------------------------------------------
ofPoint ofApp::sample(int x, int y) {
    ofPoint s = ofPoint(x, y);
    queue.push_back(s);
    grid[gridWidth * ( y / cellSize) + (x / cellSize)] = s;
    sampleSize++;
    return s;
}

//--------------------------------------------------------------
void ofApp::update(){
    grabber.update();
    
    for (int i = 0; i < 10; i++) {
        ofPoint s = poissonDiscSample();
        if (s.x != -1 && s.y != -1) {
            points.push_back(s);
        }
    }

}

//--------------------------------------------------------------
void ofApp::draw(){
    ofBackground(0);
    ofSetColor(255);
    
    ofPixels pixels = grabber.getPixels();
    pixels.mirror(false, true);
    
    ofxVoronoi voronoi;
    voronoi.setBounds(ofGetCurrentViewport());
    
    for (auto & point : points) {
        voronoi.addPoint(point);
    }
    
    voronoi.generate();
    vector <ofxVoronoiCell> cells = voronoi.getCells();
    
    for(int i = 0; i < cells.size(); i++) {
        // Draw cell borders
        ofPolyline line;
        for(int j=0; j<cells[i].pts.size(); j++) {
            ofPoint lastPt = cells[i].pts[cells[i].pts.size()-1];
            if(j > 0) {
                lastPt = cells[i].pts[j-1];
            }
            line.addVertex(lastPt);
            ofPoint thisPt = cells[i].pts[j];
            
            if(!voronoi.isBorder(lastPt) || !voronoi.isBorder(thisPt)) {
                line.addVertex(thisPt);
            }
        }
        
        ofPath path;
        path.setFillColor(pixels.getColor(cells[i].pt.x, cells[i].pt.y));
        path.setStrokeWidth(0);
        for (int j = 0; j < line.getVertices().size(); j++) {
            if (j == 0) {
                path.newSubPath();
                path.moveTo(line.getVertices()[j]);
            } else {
                path.lineTo(line.getVertices()[j]);
            }
        }
        path.draw();
    }
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){
    if (key == ' ') {
        points.clear();
        grid.clear();
        for (int i = 0; i < gridWidth * gridHeight; i++) {
            ofPoint p(-1, -1);
            grid.push_back(p);
        }
        sampleSize = 0;
    }
}

//--------------------------------------------------------------
void ofApp::keyReleased(int key){

}

//--------------------------------------------------------------
void ofApp::mouseMoved(int x, int y ){

}

//--------------------------------------------------------------
void ofApp::mouseDragged(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mouseReleased(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mouseEntered(int x, int y){

}

//--------------------------------------------------------------
void ofApp::mouseExited(int x, int y){

}

//--------------------------------------------------------------
void ofApp::windowResized(int w, int h){

}

//--------------------------------------------------------------
void ofApp::gotMessage(ofMessage msg){

}

//--------------------------------------------------------------
void ofApp::dragEvent(ofDragInfo dragInfo){ 

}
