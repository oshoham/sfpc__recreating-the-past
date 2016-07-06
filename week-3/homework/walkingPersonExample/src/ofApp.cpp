#include "ofApp.h"
#include "data.h"

//--------------------------------------------------------------
void ofApp::setup(){
    // the data is stored in a big flat array, let's copy it into something more managable
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
    
    timef = 0;
}

//--------------------------------------------------------------
void ofApp::update(){

}

//--------------------------------------------------------------
void ofApp::draw(){
    cam.begin();
    cam.end();
    ofBackground(0);

    
    //----------------------------- copy data into array
    ofPoint data3d[24];
    ofPoint data2d[24];

    for (int i = 0; i < 24; i++){
        data3d[i] = frames[ (int)(ofGetFrameNum()*0.5) % 30][i];
        data2d[i] = frames2d[ (int)(ofGetFrameNum()*0.5) % 30][i];
    }
    
    ofSetColor(255);
    
    
    for (int i = 0; i < 24; i++){
        ofPoint pos = cam.worldToScreen(data3d[i]);
        ofPolyline squiggle = squiggles[i];
        squiggle.clear();
        squiggle.addVertex(pos);
        
        for (int j = 0; j < 1000; j++){
            float radius = ofMap(sin(timef * 0.2), -1,1, 25,75);
            float radiusY = ofMap(sin(timef * 0.3), -1,1, 25,75);
            
            pos.set(pos.x + radius * ofSignedNoise(timef, 0) , pos.y + radiusY * ofSignedNoise(timef, 10000));
            
            timef += 0.03;
            
            squiggle.addVertex(pos);
        }
        squiggle.draw();
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
