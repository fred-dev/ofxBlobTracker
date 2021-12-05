#pragma once

#include "ofMain.h"

#include "ofxOpenCv.h"
#include "ofxBlobTracker.h"
#include "ofxGui.h"

//#define _USE_LIVE_VIDEO		// uncomment this to use a live camera
								// otherwise, we'll use a movie file

class ofApp : public ofBaseApp{
public:
    void setup();
    void update();
    void draw();
		
    void keyPressed(int key);
    void keyReleased(int key);
    void mouseMoved(int x, int y );
    void mouseDragged(int x, int y, int button);
    void mousePressed(int x, int y, int button);
    void mouseReleased(int x, int y, int button);
    void windowResized(int w, int h);
    void dragEvent(ofDragInfo dragInfo);
    void gotMessage(ofMessage msg);		

    void blobAdded(ofxBlob &_blob);
    void blobMoved(ofxBlob &_blob);
    void blobDeleted(ofxBlob &_blob);
    
    float width, height, drawWidth, drawHeight;
    ofxPanel panel;
    
#ifdef _USE_LIVE_VIDEO
    ofVideoGrabber 		vidGrabber;
#else
    ofVideoPlayer 		vidPlayer;
#endif

    ofxCvColorImage			colorImg;

    ofxCvGrayscaleImage 	grayImage;
    ofxBlobTracker          blobTracker;

    int 				threshold;
};

