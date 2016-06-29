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
    
    for (int i = 0; i < 24; i++){
        angleSmooth[i] = 0;
    }
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
    
    int currentFrame = (int)(ofGetFrameNum()*0.5) % 30;
    for (int i = 0; i < 24; i++) {
        data3d[i] = frames[currentFrame][i];
        data2d[i] = frames2d[currentFrame][i];
    }
    
    ofxVoronoi voronoi;
    voronoi.setBounds(ofGetCurrentViewport());
    
    ofColor cellColors[24];

    for (int i = 0; i < 24; i++){
        ofVec3f screenCoordinates = cam.worldToScreen(data3d[i]);
        voronoi.addPoint(ofPoint(screenCoordinates.x, screenCoordinates.y));
        
        ofPoint velocity = screenCoordinates - cam.worldToScreen(prevFrame[i]);
        float angle = atan2(screenCoordinates.y, screenCoordinates.x);
        
        angleSmooth[i] = 0.98f * angleSmooth[i] + 0.02 * angle;
        ofColor c;
        c.setHsb(ofMap(angleSmooth[i], -PI, PI, 0, 255), 180, 180);
        cellColors[i] = c;
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
        path.setFillColor(cellColors[i % 20]);
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
        
        // Draw cell points
        ofSetColor(0);
        ofFill();
        ofDrawCircle(cells[i].pt, 1);
    }
    
    for (int i = 0; i < 24; i++) {
        prevFrame[i] = data3d[i];
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
