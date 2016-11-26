#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
    int nOutputs = 2;
    int nInputs = 2;
    int sampleRate = 44100;
    int bufferSize = 256;
    int nBuffers = 4;
    
    tempBuffer.setSampleRate(sampleRate);
    tempBuffer.setNumChannels(nOutputs);
    
//    onset.setup();
    onset.setup("mkl", 2 * bufferSize, bufferSize, sampleRate);
    ofAddListener(onset.gotOnset, this, &ofApp::onsetEvent);
    gotOnset = false;
    
//    pitch.setup();
    pitch.setup("yinfft", 8 * bufferSize, bufferSize, sampleRate);
    
//    beat.setup();
    beat.setup("default", 2 * bufferSize, bufferSize, sampleRate);
    ofAddListener(beat.gotBeat, this, &ofApp::beatEvent);
    gotBeat = false;
    
    bands.setup();
    
    // might need to make a non-global sound stream
    ofSoundStreamSetup(nOutputs, nInputs, sampleRate, bufferSize, nBuffers);
    
    int start = 0;
    beatGui.setup("ofxAubioBeat", "settings.xml", start + 10, 10);
    beatGui.add(bpm.setup( "bpm", 0, 0, 250));
    
    start += 250;
    onsetGui.setup("ofxAubioOnset", "settings.xml", start + 10, 10);
    onsetGui.add(onsetThreshold.setup( "threshold", 0, 0, 2));
    onsetGui.add(onsetNovelty.setup( "onset novelty", 0, 0, 10000));
    onsetGui.add(onsetThresholdedNovelty.setup( "thr. novelty", 0, -1000, 1000));
    // set default value
    onsetThreshold = onset.threshold;
    
    start += 250;
    pitchGui.setup("ofxAubioPitch", "settings.xml", start + 10, 10);
    pitchGui.add(midiPitch.setup( "midi pitch", 0, 0, 128));
    pitchGui.add(pitchConfidence.setup( "confidence", 0, 0, 1));
    
    bandsGui.setup("ofxAubioMelBands", "settings.xml", start + 10, 115);
    for (int i = 0; i < 40; i++) {
        bandPlot.addVertex( 50 + i * 650 / 40., 240 - 100 * bands.energies[i]);
    }
    cout << bands.energies << endl;
}

//--------------------------------------------------------------
void ofApp::exit(){
    ofSoundStreamStop();
    ofSoundStreamClose();
}

//--------------------------------------------------------------
void ofApp::update(){
    onset.setThreshold(onsetThreshold);
}

//--------------------------------------------------------------
void ofApp::draw(){
//    drawAubioGui();
    ofBackground(0);
    ofNoFill();
    ofSetCircleResolution(100);
    
    int numCircles = 100;
    
    for (int i = 0; i < numCircles; i++) {
        int energyIndex = ofMap(i, 0, numCircles, 0, 10);
        int radius = ofMap(100 * bands.energies[energyIndex], -10, 10, 1, 100);

        ofPushMatrix();
        ofTranslate(ofGetWidth() / 2, ofGetHeight() / 2);
        ofRotate(360 * i / numCircles);
        ofTranslate(0, ofMap(sin(ofGetElapsedTimef()), 0, 1, -100, -175));
        ofDrawCircle(0, 0, sin(ofGetElapsedTimef() / 25 * i) * radius);
        ofPopMatrix();
    }
}

//--------------------------------------------------------------
void ofApp::drawAubioGui() {
    // update beat info
    if (gotBeat) {
        ofSetColor(ofColor::green);
        ofDrawRectangle(90,150,50,50);
        gotBeat = false;
    }
    
    // update onset info
    if (gotOnset) {
        ofSetColor(ofColor::red);
        ofDrawRectangle(250 + 90,150,50,50);
        gotOnset = false;
    }
    onsetNovelty = onset.novelty;
    onsetThresholdedNovelty = onset.thresholdedNovelty;
    
    // update pitch info
    pitchConfidence = pitch.pitchConfidence;
    if (pitch.latestPitch) midiPitch = pitch.latestPitch;
    bpm = beat.bpm;
    
    // draw
    pitchGui.draw();
    beatGui.draw();
    onsetGui.draw();
    
    ofSetColor(ofColor::orange);
    ofSetLineWidth(3.);
    bandsGui.draw();
    //bandPlot.clear();
    for (int i = 0; i < bandPlot.size(); i++) {
        bandPlot[i].y = 240 - 100 * bands.energies[i];
    }
    bandPlot.draw();
}

//--------------------------------------------------------------
void ofApp::audioIn(float * input, int bufferSize, int nChannels) {
    int sampleRate = 44100;
    tempBuffer.copyFrom(input, bufferSize, nChannels, sampleRate);
    
    onset.audioIn(input, bufferSize, nChannels);
    pitch.audioIn(input, bufferSize, nChannels);
    beat.audioIn(input, bufferSize, nChannels);
    bands.audioIn(input, bufferSize, nChannels);
}

//--------------------------------------------------------------
void ofApp::audioOut(ofSoundBuffer & buffer) {
//    buffer.clear();
//    tempBuffer.copyTo(buffer);
//    tempBuffer.clear();
}

//--------------------------------------------------------------
void ofApp::onsetEvent(float & time) {
    gotOnset = true;
}

//--------------------------------------------------------------
void ofApp::beatEvent(float & time) {
    gotBeat = true;
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
