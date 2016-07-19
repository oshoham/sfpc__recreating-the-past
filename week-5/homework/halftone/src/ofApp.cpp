#include "ofApp.h"

//--------------------------------------------------------------
bool charWithBrightnessComparator(charWithBrightness & a, charWithBrightness & b) {
    return a.brightness < b.brightness;
}

//--------------------------------------------------------------
void ofApp::setup(){
    grabber.setup(VIDEO_WIDTH, VIDEO_HEIGHT);
    
    font.load("NotoSans-Regular.ttf", SCREEN_ELEMENT_SIZE - 2, true, true, true);
    font.setLineHeight(18.0f);
    font.setLetterSpacing(1.037);
    
    int fboSize = 50;
    fbo.allocate(fboSize, fboSize);
    ofSetColor(0);
    for (int i = 0; i < 255; i++) {
        ofTTFCharacter character = font.getCharacterAsPoints(i);
        fbo.begin();
        ofClear(255, 255, 255, 255);
        character.draw(fbo.getWidth() / 2, fbo.getHeight() / 2);
        fbo.end();
        
        ofPixels pixels;
        fbo.readToPixels(pixels);
        
        float totalBrightness = 0;
        for (int x = 0; x < pixels.getWidth(); x++) {
            for (int y = 0; y < pixels.getHeight(); y++) {
                totalBrightness += pixels.getColor(x, y).getBrightness();
            }
        }
        float averageBrightness = totalBrightness / (float)(fboSize * fboSize);
        
        charWithBrightness cb;
        cb.value = i;
        cb.brightness = averageBrightness;
        charactersByBrightness.push_back(cb);
    }
    
    ofSort(charactersByBrightness, charWithBrightnessComparator);
}

//--------------------------------------------------------------
void ofApp::update(){
    grabber.update();
}

//--------------------------------------------------------------
void ofApp::draw(){
    ofBackground(255);
    ofSetColor(0);
    
    ofRectangle viewport = ofGetCurrentViewport();
    
    ofPixels pixels = grabber.getPixels();
    pixels.mirror(false, true);
    
    for (int i = 0; i < grabber.getWidth(); i+=SCREEN_ELEMENT_SIZE) {
        for (int j = 0; j < grabber.getHeight(); j+=SCREEN_ELEMENT_SIZE) {
            float sum = 0;
            float numPixels = 0;
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
            
            averageLuma = 255 * pow(averageLuma / 255, 3);
            
            charWithBrightness cb = charactersByBrightness[averageLuma];
            ofTTFCharacter character = font.getCharacterAsPoints(cb.value);
            character.draw(i, j);
            
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
