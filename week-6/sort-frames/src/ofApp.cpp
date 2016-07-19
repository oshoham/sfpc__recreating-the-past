#include "ofApp.h"

//--------------------------------------------------------------
bool bSortFunction(frame & a, frame & b) {
    return a.averageHue < b.averageHue;
}

//--------------------------------------------------------------
void ofApp::setup(){
    ofDirectory dir;
    dir.sort();
    dir.listDir("frames");
    
    for (int i = 0; i< dir.size(); i++){
        string filename = dir.getPath(i);
        cout << filename << endl;
        
        ofImage img;
        img.setUseTexture(false);
        img.load(dir.getPath(i));
        
        float averageHue = 0;
        
        for (int j = 0; j < img.getWidth(); j++){
            for (int k = 0; k < img.getHeight(); k++){
                averageHue += img.getColor(j, k).getHue();
            }
        }
        
        averageHue /= (float)(img.getWidth() * img.getHeight());
        
        frame f;
        f.filename = filename;
        f.averageHue = averageHue;
        frames.push_back(f);
    }
    
    ofSort(frames, bSortFunction);
    
//    ofFbo fbo;
//    fbo.allocate(1024, 1024, GL_RGB);
//    fbo.begin();
//    ofClear(255,255,255, 0);
//    
//    int dim = sqrt(avgs.size());
//    
//    for (int i = 0; i < avgs.size(); i++){
//        ofSetColor(avgs[i]);
//        ofDrawRectangle(50 + (i %dim) *10, 50 + (i/dim) * 10, 10, 10);
//    }
//    fbo.end();
//    
//    ofPixels pixels;
//    pixels.allocate(1024, 1024, OF_IMAGE_COLOR);
//    fbo.readToPixels(pixels);
//    ofSaveImage(pixels, "grand-budapest-average-colors.jpg", OF_IMAGE_QUALITY_BEST);
}

//--------------------------------------------------------------
void ofApp::update(){
    image.load(frames[ofGetFrameNum() % frames.size()].filename);
}

//--------------------------------------------------------------
void ofApp::draw(){
    image.draw(0, 0);
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
