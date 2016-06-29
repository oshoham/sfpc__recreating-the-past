#include "ofApp.h"
#include "data.h"
#include "ofxVoronoi.h"

//--------------------------------------------------------------
void ofApp::setup(){
    for (int i = 0; i < 30; i++){
        for (int j = 0; j < 24; j++){
            float x = data3d[ i * 24 * 3  + j * 3 + 0 ];
            float y = data3d[ i * 24 * 3  + j * 3 + 1 ];
            float z = data3d[ i * 24 * 3  + j * 3 + 2 ];
            frames[i][j].set(x,y,z);
        }
    }
    
    for (int i = 0; i < 30; i++){
        for (int j = 0; j < 24; j++){
            float x = data2d[ i * 24 * 2  + j * 2 + 0 ];
            float y = data2d[ i * 24 * 2  + j * 2 + 1 ];
            frames2d[i][j].set(x,y);
        }
    }
    
    cam.begin();
    cam.end();
}

//--------------------------------------------------------------
void ofApp::update(){
    
}

//--------------------------------------------------------------
void ofApp::draw(){
    ofBackground(0);
    ofSetColor(255);
    
    ofPoint data3d[24];
    ofPoint data2d[24];
    
    int currentFrame = (int)(ofGetFrameNum() * 0.5) % 30;
    for (int i = 0; i < 24; i++) {
        data3d[i] = frames[currentFrame][i];
        data2d[i] = frames2d[currentFrame][i];
    }
    
    lines.clear();
    
    ofxVoronoi voronoi;
    voronoi.setBounds(ofGetCurrentViewport());
    
    for (int i = 0; i < 24; i++){
        ofVec3f screenCoordinates = cam.worldToScreen(data3d[i]);
        voronoi.addPoint(ofPoint(screenCoordinates.x, screenCoordinates.y));
        line tempLine;
        tempLine.a = screenCoordinates;
        tempLine.b = cam.worldToScreen(data3d[(i + 1) % 24]);
        lines.push_back(tempLine);
    }
    
    voronoi.generate();
    vector <ofxVoronoiCell> cells = voronoi.getCells();
    
    for(int i = 0; i < cells.size(); i++) {
        // Draw cell borders
        for(int j=0; j<cells[i].pts.size(); j++) {
            ofPoint lastPt = cells[i].pts[cells[i].pts.size()-1];
            if(j > 0) {
                lastPt = cells[i].pts[j-1];
            }
            ofPoint thisPt = cells[i].pts[j];
            
            if(!voronoi.isBorder(lastPt) || !voronoi.isBorder(thisPt)) {
                line tempLine;
                tempLine.a = lastPt;
                tempLine.b = thisPt;
                lines.push_back(tempLine);
            }
        }
//        ofDrawCircle(cells[i].pt, 1);
    }
    
    ofSeedRandom(0);
    for (int z = 0; z < 3000; z ++){
        int randomLine = ofRandom(0, lines.size());
        float randomPct = ofRandom(0,1);
        
        ofPoint diff = lines[randomLine].b - lines[randomLine].a;
        
        if (diff.length() < 5) continue;
        float angle = atan2(diff.y, diff.x);
        
        if (ofRandom(0,1) > 0.5){
            angle += PI/2;
        } else {
            angle -= PI/2;
        }
        
        float randomAngle = angle + ofRandom(-0.02, 0.02);
        
        
        ofPoint a = lines[randomLine].a + randomPct * (  lines[randomLine].b-  lines[randomLine].a);
        
        ofPoint b = a + 2000 * ofPoint(cos(randomAngle), sin(randomAngle));
        
        
        float shortestIntersection = 1000000;
        ofPoint smallestIntersection;
        
        for (auto line : lines){
            
            ofPoint intersection;
            
            if (ofLineSegmentIntersection(a, b, line.a, line.b, intersection)){
                
                float distance = (intersection - a).length();
                if (distance < shortestIntersection){
                    shortestIntersection = distance;
                    smallestIntersection = intersection;
                }
            }
        }
        
        if (shortestIntersection < 9999){
            b = smallestIntersection;
        }
        
        
        
        line tempLine;
        tempLine.a =a;
        tempLine.b =b;
        lines.push_back(tempLine);
    }
    
    for (auto line : lines){
        ofDrawLine(line.a, line.b);
    }
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){

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
