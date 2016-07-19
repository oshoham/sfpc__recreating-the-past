#include "ofApp.h"

//--------------------------------------------------------------
bool imageWithBrightnessComparator(imageWithBrightness & a, imageWithBrightness & b) {
    return a.brightness < b.brightness;
}

//--------------------------------------------------------------
void ofApp::setup(){
    grabber.setup(VIDEO_WIDTH, VIDEO_HEIGHT);
    
    ofDirectory dir("mosaics");
    dir.allowExt("jpg");
    dir.listDir();
    
//    float imgWidth = 100.0 / 127.0 * SCREEN_ELEMENT_SIZE;
    float imgWidth = SCREEN_ELEMENT_SIZE;
    float imgHeight = SCREEN_ELEMENT_SIZE;

    for (int i = 0; i < dir.size(); i++) {
        string filename = dir.getPath(i);
        ofImage image;
        image.allocate(100, 127, OF_IMAGE_COLOR);
        image.load(filename);
        image.resize(imgWidth, imgHeight);
        
        ofFbo fbo;
        fbo.allocate(imgWidth, imgHeight, GL_RGB);
        fbo.begin();
        ofClear(255,255,255, 0);
        image.draw(0, 0);
        fbo.end();
        preRenderedImages[filename] = fbo;
        
        ofPixels pixels = image.getPixels();
        
        float totalBrightness = 0;
        for (int x = 0; x < pixels.getWidth(); x++) {
            for (int y = 0; y < pixels.getHeight(); y++) {
                totalBrightness += pixels.getColor(x, y).getBrightness();
            }
        }
        float averageBrightness = totalBrightness / (pixels.getWidth() * pixels.getHeight());
        
        imageWithBrightness ib;
        ib.filename = filename;
        ib.brightness = averageBrightness;
        imagesByBrightness.push_back(ib);
    }
    
    ofSort(imagesByBrightness, imageWithBrightnessComparator);
}

//--------------------------------------------------------------
void ofApp::update(){
    grabber.update();
}

//--------------------------------------------------------------
void ofApp::draw(){
    ofBackground(255);
    
    ofRectangle viewport = ofGetCurrentViewport();
    
    ofPixels pixels = grabber.getPixels();
    pixels.mirror(false, true);
    
    for (int i = 0; i < grabber.getWidth(); i+=SCREEN_ELEMENT_SIZE) {
        for (int j = 0; j < grabber.getHeight(); j+=SCREEN_ELEMENT_SIZE) {
            
            float sum = 0;
            int numPixels = 0;
            for (int k = 0; k < SCREEN_ELEMENT_SIZE; k++) {
                for (int l = 0; l < SCREEN_ELEMENT_SIZE; l++) {
                    if (viewport.inside(i + k, j + l)) {
                        ofColor color = pixels.getColor(i + k, j + l);
                        float luma = color.r * 0.2126 + color.g * 0.7152 + color.b * 0.0722;
                        sum += luma;
                        numPixels++;
                    }
                }
            }
            float averageLuma = sum / numPixels;
            
//            averageLuma = 255 * pow(averageLuma / 255, 3);
            
            imageWithBrightness ib = imagesByBrightness[ofMap(averageLuma, 0, 255, 0, imagesByBrightness.size() - 1)];
            preRenderedImages[ib.filename].draw(i, j);
        }
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
