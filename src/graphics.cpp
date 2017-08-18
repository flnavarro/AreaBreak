//
//  graphics.cpp
//  areaBreak
//
//  Created by Felipe L. Navarro on 14/08/17.
//
//

#include "graphics.h"


//--------------------------------------------------------------
void graphics::setup(int windowW, int windowH, ofColor bckgrdColor){
    // Window
    WIDTH = windowW;
    HEIGHT = windowH;
    backgroundColor = bckgrdColor;
    
    // System
    state = "savescreen";
    guiIsActive = true;
    setupGUI();
    
    // Savescreen
    savescreenIsSequence = true;
    seqFps = 24;
    loadScreensave();
    
    // Words
    wordMaxFrames = 100;
    loadWords();
    
//    // Lines
//    timeWaiting = 1;
//    initLines();
//    maxWidthWordBox = 500;
//    heightWordBox = 150;
//    wordBoxCenterPos = ofVec2f(300, HEIGHT/2);
//    
//    // Circles
//    circle.load("imgs/ab_circle.png");
//    circleMaxScale = 0.5;
//    maxOpenings = 3;
//    maxRotations = 2;
//    maxDegreeRotation = 120;
//    maxBlinking = 4;
//    blinkingTime = 0.1;
//    initCircles(500, 500);
}

//--------------------------------------------------------------
void graphics::loadScreensave(){
    if(savescreenIsSequence){
        ofDirectory d;
        d.listDir("savescreenSEQ");
        for(int i=0; i<d.size(); i++){
            savescreenSeq.push_back(ofImage());
            savescreenSeq[i].load(d.getPath(i));
        }
        seqFrameIdx = 0;
    } else {
        savescreenVid.load("savescreenVID/savescreen.mp4");
        savescreenVid.setVolume(0);
        savescreenVid.setLoopState(OF_LOOP_NORMAL);
        savescreenVid.play();
    }
}

//--------------------------------------------------------------
void graphics::loadWords(){
    ofDirectory dW;
    ofDirectory dI;
    dW.listDir("wordImgs");
    for(int i=0; i<dW.size(); i++){
        dI.listDir("wordImgs/word_" + ofToString(i+1));
        vector <ofImage> wI;
        for(int j=0; j<dI.size(); j++){
            wI.push_back(ofImage());
            wI[j].load(dI.getPath(j));
        }
        wordImgs.push_back(wI);
    }
}

//--------------------------------------------------------------
void graphics::initWords(int posX, int posY){
    state = "words";
    wordPos.x = posX;
    wordPos.y = posY;
    wordIdx = (int)ofRandom(wordImgs.size());
    wordLetterSpacing = 0;
    wordResizeFactor = 0.35;
    wordAlpha = 255;
    wordFrame = 0;
    if(posX <= WIDTH/2){
        wordRotated = false;
    } else {
        wordRotated = true;
    }
}

//--------------------------------------------------------------
void graphics::update(){
//    if(state == "lines"){
//        updateLines();
//    }
//    else if(state == "circles"){
//        updateCircles();
//    }
    if(state == "savescreen"){
        updateScreensave();
    }
    else if(state == "words"){
        updateScreensave();
        updateWords();
    }
    
    if(guiIsActive){
        updateGUI();
    }
}

//--------------------------------------------------------------
void graphics::updateScreensave(){
    if(savescreenIsSequence){
        seqFrameIdx = (int)(ofGetElapsedTimef() * seqFps) % savescreenSeq.size();
    }
    else {
        savescreenVid.update();
    }
}

//--------------------------------------------------------------
void graphics::updateWords(){
    if(wordFrame<wordMaxFrames){
        if(wordRotated){
            wordLetterSpacing = ofMap(wordFrame, 0, wordMaxFrames, 0, -100);
        } else {
            wordLetterSpacing = ofMap(wordFrame, 0, wordMaxFrames, 0, 100);
        }
        wordAlpha = ofMap(wordFrame, 0, wordMaxFrames, 255, 0);
    } else {
       state = "savescreen";
    }
    wordFrame++;
}

//--------------------------------------------------------------
void graphics::draw(){
//    if(state == "lines"){
//        drawLines();
//    }
//    
//    else if(state == "circles"){
//        drawCircles();
//    }
    
    if( state == "savescreen"){
        drawScreensave();
    }
    else if(state == "words"){
        //drawScreensave();
        drawWords();
    }
    
    if(guiIsActive){
        drawGUI();
    }
}

//--------------------------------------------------------------
void graphics::drawScreensave(){
    if(savescreenIsSequence){
        savescreenSeq[seqFrameIdx].draw(0, 0, WIDTH, HEIGHT);
    } else {
        savescreenVid.draw(0, 0, WIDTH, HEIGHT);
    }
}

//--------------------------------------------------------------
void graphics::drawWords(){
    ofPushStyle();
    ofPushMatrix();
    ofTranslate(wordPos.x, wordPos.y);
    ofScale(wordResizeFactor, wordResizeFactor);
    if(wordRotated){
        ofRotate(180);
    }
    ofPushMatrix();
    ofTranslate(-wordPos.x, -wordPos.y);
    for(int i=0; i<wordImgs[wordIdx].size(); i++){
        ofSetColor(255, 255, 255, wordAlpha);
        if(i==0){
            wordImgs[wordIdx][i].draw(wordPos.x, wordPos.y);
        } else {
            if(wordRotated){
                wordImgs[wordIdx][i].draw(wordPos.x - wordLetterSpacing*i, wordPos.y);
            } else {
                wordImgs[wordIdx][i].draw(wordPos.x + wordLetterSpacing*i, wordPos.y);
            }
        }
    }
    ofPopMatrix();
    ofPopStyle();
}

//--------------------------------------------------------------
void graphics::showGUI(){
    guiIsActive = !guiIsActive;
}

//--------------------------------------------------------------
void graphics::setupGUI(){
    squareSize = 100;
    tablePoints[0][0] = ofVec2f(500, HEIGHT/2-squareSize/2);
    tablePoints[0][1] = ofVec2f(500+squareSize, HEIGHT/2-squareSize/2);
    tablePoints[0][2] = ofVec2f(500+squareSize, HEIGHT/2+squareSize/2);
    tablePoints[0][3] = ofVec2f(500, HEIGHT/2+squareSize/2);
    
    tablePoints[1][0] = ofVec2f(1000, HEIGHT/2-squareSize/2);
    tablePoints[1][1] = ofVec2f(1000+squareSize, HEIGHT/2-squareSize/2);
    tablePoints[1][2] = ofVec2f(1000+squareSize, HEIGHT/2+squareSize/2);
    tablePoints[1][3] = ofVec2f(1000, HEIGHT/2+squareSize/2);
    
    pointsToTables();
    
    cornerCursor[0].load("cursors/resizeUpLeft.png");
    cornerCursor[1].load("cursors/resizeUpRight.png");
    grabCursor[0].load("cursors/grabExtended.png");
    grabCursor[1].load("cursors/grabGrabbing.png");
    cornerCursor[0].resize(30, 30);
    cornerCursor[1].resize(30, 30);
    grabCursor[0].resize(30, 30);
    grabCursor[1].resize(30, 30);
}

//--------------------------------------------------------------
void graphics::pointsToTables(){
    for(int i=0; i<2; i++){
        table[i].clear();
        for(int j=0; j<4; j++) {
            table[i].addVertex(tablePoints[i][j]);
        }
        table[i].addVertex(tablePoints[i][0]);
    }
}

//--------------------------------------------------------------
void graphics::updateGUI(){
    for(int i=0; i<2; i++){
        if(mouseIsPressed){
            if(table[i].inside(mouseDraggingPos.x, mouseDraggingPos.y)){
                cursorInTable = true;
                tableIdx = i;
                break;
            } else {
                cursorInTable = false;
            }
        } else {
            if(table[i].inside(mouseMovePos.x, mouseMovePos.y)){
                cursorInTable = true;
                tableIdx = i;
                break;
            } else {
                cursorInTable = false;
            }
        }
    }
    
    if(cursorInTable){
        ofHideCursor();
    } else {
        ofShowCursor();
    }
}

//--------------------------------------------------------------
void graphics::drawGUI(){
    ofPushMatrix();
    ofPushStyle();
    ofSetColor(255, 255, 255, 255);
    table[0].draw();
    table[1].draw();
    if(cursorInTable){
        if(mouseIsPressed){
            grabCursor[1].draw(mouseDraggingPos.x, mouseDraggingPos.y);
        } else {
            grabCursor[0].draw(mouseMovePos.x, mouseMovePos.y);
        }
    }
    ofPopStyle();
    ofPopMatrix();
}

//--------------------------------------------------------------
void graphics::mouseMoved(int x, int y){
    mouseMovePos.x = x;
    mouseMovePos.y = y;
    ofLog() << "mouseMovePos " << mouseMovePos;
}

//--------------------------------------------------------------
void graphics::mousePressed(int x, int y){
    mousePressedPos.x = x;
    mousePressedPos.y = y;
    ofLog() << "mousePressedPos " << mousePressedPos;
    mouseIsPressed = true;
}

//--------------------------------------------------------------
void graphics::mouseReleased(){
    mouseIsPressed = false;
    ofLog() << "mouseReleased ";
}

//--------------------------------------------------------------
void graphics::mouseDragging(int x, int y){
    mouseDraggingPos.x = x;
    mouseDraggingPos.y = y;
    
    if(cursorInTable && mouseIsPressed){
        ofVec2f diff;
        diff.x = mouseDraggingPos.x - mousePressedPos.x;
        diff.y = mouseDraggingPos.y - mousePressedPos.y;
        for(int i=0; i<4; i++){
            tablePoints[tableIdx][i].x += diff.x;
            tablePoints[tableIdx][i].y += diff.y;
        }
        pointsToTables();
    }
    ofLog() << "mouseDraggingPos " << mouseDraggingPos;
}

//
////--------------------------------------------------------------
//void graphics::initLines(){
//    lineBuilding = true;
//    lineWaiting = false;
//    lineWordBox = false;
//    lineWordBox_open = false;
//    lineOpening = false;
//    lineClosing = false;
//    restart = false;
//    nLines = ofRandom(10,30);
//    separation = (float)HEIGHT/(float)nLines;
//    posLength = 0;
//    negLength = WIDTH;
//    separLineWord = separation;
//    widthWordBox = 0;
//    letterSpacing = 0.0;
//}
//
////--------------------------------------------------------------
//void graphics::initCircles(int posX, int posY){
//    state = "circles";
//    circlePos = ofVec2f(posX-circle.getWidth()/2, posY-circle.getHeight()/2);
//    circleOpening = true;
//    circleRotating = false;
//    circleBlinking = false;
//    circleClosing = false;
//    circleScale = 0.0;
//    nOpening = 0;
//    nRotations = 0;
//    circleRotation = 0;
//    positiveRotation = true;
//    nBlinking = 0;
//    blinkShow = false;
//}
//
////--------------------------------------------------------------
//void graphics::updateLines(){
//    if(lineBuilding){
//        if(posLength+1 < WIDTH && negLength-1 > 0){
//            posLength += 10;
//            negLength -= 10;
//        } else {
//            lineBuilding = false;
//            elapsedWaiting = ofGetElapsedTimef();
//            lineWaiting = true;
//        }
//    }
//    
//    if(lineWaiting){
//        if(ofGetElapsedTimef()-elapsedWaiting>timeWaiting){
//            lineWaiting = false;
//            lineWordBox = true;
//            lineWordBox_open = true;
//            lineWordBox_wait_1 = false;
//            lineWordBox_close = false;
//        }
//    }
//    
//    if(lineWordBox){
//        if(lineWordBox_open){
//            if(widthWordBox>maxWidthWordBox){
//                lineWordBox_open = false;
//                lineWordBox_wait_1 = true;
//                elapsedWaiting = ofGetElapsedTimef();
//            }
//            widthWordBox+=10;
//            //letterSpacing+=0.01;
//        }
//        if(lineWordBox_wait_1){
//            if(ofGetElapsedTimef()-elapsedWaiting>timeWaiting){
//                lineWordBox_wait_1 = false;
//                lineWordBox_close = true;
//            }
//        }
//        if(lineWordBox_close){
//            if(widthWordBox<0){
//                lineWordBox_close = false;
//                lineWordBox = false;
//                lineOpening = true;
//            }
//            widthWordBox-=10;
//        }
//    }
//    
//    if(lineOpening){
//        int sepIncrease = 1;
//        if(separation>HEIGHT/2 && separation<HEIGHT){
//            sepIncrease = 10;
//        } else if(separation>HEIGHT){
//            lineOpening = false;
//            lineClosing = true;
//        }
//        separation += sepIncrease;
//    }
//    
//    if(lineClosing){
//        if(separation < -200){
//            lineClosing = false;
//            restart = true;
//        }
//        separation--;
//    }
//    
//    if(restart){
//        initLines();
//    }
//    
//    ofLog() << "lineOpening " << lineOpening;
//    ofLog() << "separation " << separation;
//}
//
////--------------------------------------------------------------
//void graphics::updateCircles(){
//    if(circleOpening){
//        if(nOpening < maxOpenings){
//            if(circleScale>circleMaxScale){
//                nOpening++;
//                if(nOpening!=maxOpenings){
//                    circleScale = 0.0;
//                }
//            }
//            circleScale += 0.01;
//        } else {
//            circleOpening = false;
//            circleRotating = true;
//        }
//    }
//    
//    if(circleRotating){
//        if(nRotations<maxRotations){
//            if(positiveRotation){
//                if(circleRotation>=maxDegreeRotation){
//                    nRotations++;
//                    positiveRotation = false;
//                }
//                circleRotation += 1.25;
//            }else{
//                if(circleRotation<=0){
//                    nRotations++;
//                    positiveRotation = true;
//                }
//                circleRotation -= 1.25;
//            }
//        } else {
//            circleRotating = false;
//            circleBlinking = true;
//            elapsedBlinking = ofGetElapsedTimef();
//        }
//    }
//    
//    if(circleBlinking){
//        if(nBlinking<maxBlinking){
//            if(ofGetElapsedTimef()-elapsedBlinking>blinkingTime){
//                elapsedBlinking = ofGetElapsedTimef();
//                blinkShow = !blinkShow;
//                nBlinking++;
//            }
//        } else {
//            circleBlinking = false;
//            circleClosing = true;
//        }
//    }
//    
//    if(circleClosing){
//        if(circleScale<0){
//            circleClosing=false;
//            state = "lines";
//            initLines();
//        }
//        circleScale -= 0.01;
//    }
//}
//
////--------------------------------------------------------------
//void graphics::drawLines(){
//    ofPushStyle();
//    ofSetColor(255, 255, 255, 255);
//    ofSetLineWidth(5);
//    float posY = separation/2;
//    for(int i=0; i<nLines; i++){
//        if(i%2 == 0){
//            ofDrawLine(0, posY, posLength, posY);
//        }else{
//            ofDrawLine(WIDTH, posY, negLength, posY);
//        }
//        posY += separation;
//    }
//    ofPopStyle();
//    
//    if(lineWordBox){
//
//        ofPushMatrix();
//        ofPushStyle();
//        ofSetColor(backgroundColor);
//        ofDrawRectangle(wordBoxCenterPos.x-heightWordBox/2, 0, heightWordBox, HEIGHT);
//        ofSetColor(255, 255, 255, 255);
//        wordFont.setLetterSpacing(letterSpacing);
//        ofTranslate(wordBoxCenterPos.x-wordFont.stringWidth("PREMIUM")/2 + wordFont.stringWidth("PREMIUM")/2,
//                    wordBoxCenterPos.y-wordFont.stringHeight("PREMIUM")/2 + wordFont.stringHeight("PREMIUM")/2);
//        ofRotate(90);
//        ofTranslate(-(wordBoxCenterPos.x-wordFont.stringWidth("PREMIUM")/2) - wordFont.stringWidth("PREMIUM")/2,
//                    -(wordBoxCenterPos.y-wordFont.stringHeight("PREMIUM")/2) - wordFont.stringHeight("PREMIUM")/2);
//        wordFont.drawString("PREMIUM", wordBoxCenterPos.x-wordFont.stringWidth("PREMIUM")/2-15,
//                            wordBoxCenterPos.y+100-wordFont.stringHeight("PREMIUM")/2);
//        ofPopStyle();
//        ofPopMatrix();
//        
//        ofPushMatrix();
//        ofPushStyle();
//        ofSetColor(backgroundColor);
//        ofDrawRectangle(wordBoxCenterPos.x-heightWordBox/2, 0, heightWordBox, HEIGHT/2-widthWordBox/2);
//        ofDrawRectangle(wordBoxCenterPos.x-heightWordBox/2, HEIGHT/2+widthWordBox/2, heightWordBox, HEIGHT);
//        ofPopStyle();
//        ofPopMatrix();
//        
//        ofPushMatrix();
//        ofPushStyle();
//        ofSetColor(255, 255, 255, 255);
//        ofSetLineWidth(5);
//        float posY = separation/2;
//        for(int i=0; i<nLines; i++){
//            if(i < (int)(nLines/2)){
//                ofDrawLine(wordBoxCenterPos.x-heightWordBox/2, posY-widthWordBox/2, wordBoxCenterPos.x+heightWordBox/2, posY-widthWordBox/2);
//            } else {
//                ofDrawLine(wordBoxCenterPos.x-heightWordBox/2, posY+widthWordBox/2, wordBoxCenterPos.x+heightWordBox/2, posY+widthWordBox/2);
//            }
//            posY += separation;
//        }
//        ofPopStyle();
//        ofPopMatrix();
//    }
//}
//
////--------------------------------------------------------------
//void graphics::drawCircles(){
//    if(circleOpening){
//        ofPushStyle();
//        ofPushMatrix();
//        ofTranslate(circlePos.x + circle.getWidth()/2, circlePos.y + circle.getHeight()/2);
//        ofScale(circleScale, circleScale);
//        ofPushMatrix();
//        ofTranslate(-circlePos.x - circle.getWidth()/2, -circlePos.y - circle.getHeight()/2);
//        ofSetColor(255, 255, 255, 255);
//        circle.draw(circlePos.x, circlePos.y);
//        ofPopMatrix();
//        ofPopMatrix();
//        ofPopStyle();
//    }
//    
//    if(circleRotating){
//        ofPushStyle();
//        ofPushMatrix();
//        ofTranslate(circlePos.x + circle.getWidth()/2, circlePos.y + circle.getHeight()/2);
//        ofScale(circleScale, circleScale);
//        ofRotate(circleRotation);
//        ofPushMatrix();
//        ofTranslate(-circlePos.x - circle.getWidth()/2, -circlePos.y - circle.getHeight()/2);
//        ofSetColor(255, 255, 255, 255);
//        circle.draw(circlePos.x, circlePos.y);
//        ofPopMatrix();
//        ofPopMatrix();
//        ofPopStyle();
//    }
//    
//    if(circleBlinking){
//        if(blinkShow){
//            ofPushStyle();
//            ofPushMatrix();
//            ofTranslate(circlePos.x + circle.getWidth()/2, circlePos.y + circle.getHeight()/2);
//            ofScale(circleScale, circleScale);
//            ofPushMatrix();
//            ofTranslate(-circlePos.x - circle.getWidth()/2, -circlePos.y - circle.getHeight()/2);
//            ofSetColor(255, 255, 255, 255);
//            circle.draw(circlePos.x, circlePos.y);
//            ofPopMatrix();
//            ofPopMatrix();
//            ofPopStyle();
//        }
//    }
//    
//    if(circleClosing){
//        ofPushStyle();
//        ofPushMatrix();
//        ofTranslate(circlePos.x + circle.getWidth()/2, circlePos.y + circle.getHeight()/2);
//        ofScale(circleScale, circleScale);
//        ofPushMatrix();
//        ofTranslate(-circlePos.x - circle.getWidth()/2, -circlePos.y - circle.getHeight()/2);
//        ofSetColor(255, 255, 255, 255);
//        circle.draw(circlePos.x, circlePos.y);
//        ofPopMatrix();
//        ofPopMatrix();
//        ofPopStyle();
//    }
//}