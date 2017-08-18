//
//  graphics.hpp
//  areaBreak
//
//  Created by Felipe L. Navarro on 14/08/17.
//
//

#include "ofMain.h"

class graphics {
    public:
        void setup(int windowW, int windowH, ofColor bckgrdColor);
        void update();
        void draw();
    
        void loadScreensave();
        void updateScreensave();
        void drawScreensave();
    
        void loadWords();
        void initWords(int posX, int posY);
        void updateWords();
        void drawWords();
    
        void showGUI();
        void setupGUI();
        void updateGUI();
        void pointsToTables();
        void drawGUI();
        void mouseMoved(int x, int y);
        void mousePressed(int x, int y);
        void mouseReleased();
        void mouseDragging(int x, int y);
    
        // Window
        int WIDTH;
        int HEIGHT;
        ofColor backgroundColor;
    
        // System
        string state;
        bool guiIsActive;
        ofVec2f mousePressedPos;
        ofVec2f mouseDraggingPos;
        ofVec2f mouseMovePos;
        ofImage cornerCursor[2];
        int cornerCursorIdx;
        int tableIdx;
        int cornerIdx;
        ofImage grabCursor[2];
        int grabCursorIdx;
        bool cursorInCorner;
        bool mouseIsPressed;
        bool cursorInTable;
    
        // Tables
        ofPolyline table[2];
        float squareSize;
        ofVec2f tablePoints[2][4];
    
        // Savescreen
        vector<ofImage> savescreenSeq;
        ofVideoPlayer savescreenVid;
        bool savescreenIsSequence;
        int seqFrameIdx;
        int seqFps;
    
        // Words
        ofVec2f wordPos;
        vector<vector <ofImage>> wordImgs;
        int wordIdx;
        int wordLetterSpacing;
        float wordResizeFactor;
        int wordAlpha;
        int wordFrame;
        int wordMaxFrames;
        bool wordRotated;
    
    
//    // --- FIRST V.---
//    ofTrueTypeFont wordFont;
//    void initLines();
//    void initCircles(int posX, int posY);
//    void updateLines();
//    void updateCircles();
//    void drawLines();
//    void drawCircles();
//    
//        // Lines
//        int nLines;
//        float separation;
//        int posLength;
//        int negLength;
//        bool lineBuilding;
//        bool lineWaiting;
//        bool lineWordBox;
//        bool lineWordBox_open;
//        bool lineWordBox_wait_1;
//        bool lineWordBox_close;
//        bool lineOpening;
//        bool lineClosing;
//        bool restart;
//        float timeWaiting;
//        float elapsedWaiting;
//        float separLineWord;
//        float maxWidthWordBox;
//        float heightWordBox;
//        ofVec2f wordBoxCenterPos;
//        float widthWordBox;
//        float letterSpacing;
//    
//        // Circles
//        ofImage circle;
//        ofVec2f circlePos;
//        float circleMaxScale;
//        float circleScale;
//        int maxOpenings;
//        int nOpening;
//        bool circleOpening;
//        bool circleRotating;
//        bool circleBlinking;
//        bool circleClosing;
//        int maxRotations;
//        int nRotations;
//        float circleRotation;
//        bool positiveRotation;
//        float elapsedBlinking;
//        float blinkingTime;
//        bool blinkShow;
//        int maxBlinking;
//        int nBlinking;
//        float maxDegreeRotation;
};