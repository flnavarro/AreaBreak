#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
    // Window
    // backgroundColor = ofColor(0, 0, 153, 255);
    backgroundColor = ofColor(0, 0, 0, 255);
    ofBackground(backgroundColor);
    ofSetWindowTitle("Touch Wall v0.1");
    WIDTH=1920;
    HEIGHT=1080;
    fullscreen = true;
    ofSetFullscreen(fullscreen);

    interactiveGraphics.setup(WIDTH, HEIGHT, backgroundColor);
    // computerVision.setup();
}

//--------------------------------------------------------------
void ofApp::update(){
    interactiveGraphics.update();
    // computerVision.update();

}

//--------------------------------------------------------------
void ofApp::draw(){
    interactiveGraphics.draw();
    // computerVision.draw();

}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){
    if(key == 'f' || key == 'F'){
        fullscreen = !fullscreen;
        ofSetFullscreen(fullscreen);
    }
    
    if(key == 'g' || key == 'G'){
        interactiveGraphics.showGUI();
    }
    
    if(key == 'v' || key == 'V'){
        // computerVision.showGUI(!computerVision.drawVisionGUI);
    }
    
    if(key == ' '){
        // computerVision.learnBackground();
    }
    
    if(key == '+'){
        // computerVision.changeThreshold(true);
    }
    
    if(key == '-'){
        // computerVision.changeThreshold(false);
    }
}

//--------------------------------------------------------------
void ofApp::keyReleased(int key){

}

//--------------------------------------------------------------
void ofApp::mouseMoved(int x, int y){
    if(interactiveGraphics.guiIsActive){
        interactiveGraphics.mouseMoved(x, y);
    }
}

//--------------------------------------------------------------
void ofApp::mouseDragged(int x, int y, int button){
    if(interactiveGraphics.guiIsActive){
        interactiveGraphics.mouseDragging(x, y);
    }
}

//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button){
    if(interactiveGraphics.guiIsActive){
        interactiveGraphics.mousePressed(x, y);
    }
}

//--------------------------------------------------------------
void ofApp::mouseReleased(int x, int y, int button){
    // interactiveGraphics.initCircles(x, y);
    interactiveGraphics.initWords(x, y);
    if(interactiveGraphics.guiIsActive){
        interactiveGraphics.mouseReleased();
    }
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