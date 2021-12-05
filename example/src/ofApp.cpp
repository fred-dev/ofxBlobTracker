#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){

	#ifdef _USE_LIVE_VIDEO
        vidGrabber.setVerbose(true);
        vidGrabber.initGrabber(width,height);
	#else
        vidPlayer.load("4 people slow-close-freestle.mov");
        vidPlayer.play();
        width= vidPlayer.getWidth();
        height= vidPlayer.getHeight();
    cout<<ofToString(width) + " " + ofToString(height)<<endl;
	#endif

    drawWidth = 400;
    drawHeight = drawWidth / width * height;
        cout<<ofToString(drawWidth) + " " + ofToString(drawHeight)<<endl;

    
    colorImg.allocate(width,height);
	grayImage.allocate(width,height);

	threshold = 20;
    
    ofAddListener(blobTracker.blobAdded, this, &ofApp::blobAdded);
    ofAddListener(blobTracker.blobMoved, this, &ofApp::blobMoved);
    ofAddListener(blobTracker.blobDeleted, this, &ofApp::blobDeleted);
    
    panel.setup("Blob manager", "settings.xml", 10, 100);
    panel.add(blobTracker.params);
    panel.loadFromFile( "settings.xml");
}

//--------------------------------------------------------------
void ofApp::update(){
	ofBackground(100,100,100);

    bool bNewFrame = false;

	#ifdef _USE_LIVE_VIDEO
       vidGrabber.update();
	   bNewFrame = vidGrabber.isFrameNew();
    
    #else
        vidPlayer.update();
        bNewFrame = vidPlayer.isFrameNew();
	#endif

	if (bNewFrame){

		#ifdef _USE_LIVE_VIDEO
            colorImg.setFromPixels(vidGrabber.getPixels().getData(), width,height);
	    #else
            colorImg.setFromPixels(vidPlayer.getPixels().getData(), width,height);
        #endif

        grayImage = colorImg;

        blobTracker.update(grayImage);
	}

}

//--------------------------------------------------------------
void ofApp::draw(){

	// draw the incoming, the grayscale, the bg and the thresholded difference
    ofSetColor(255);
    colorImg.draw(20,20, drawWidth, drawHeight);
	grayImage.draw(drawWidth + 40 ,20,drawWidth, drawHeight );

	// then draw the contours:

	blobTracker.draw(20,20,drawWidth, drawHeight);
//
//	// or, instead we can draw each blob individually,
//	// this is how to get access to them:
    ofPushView();
    ofTranslate(drawWidth+40, 20);
    ofPushStyle();
    
    for (int i = 0; i < blobTracker.size(); i++){
        ofFill();
        ofSetColor(255,0,0);
        ofDrawCircle((blobTracker[i].centroid.x) * drawWidth , (blobTracker[i].centroid.y) * drawHeight ,10);
        ofSetColor(0);
        ofDrawBitmapString(ofToString( blobTracker[i].id ),(blobTracker[i].centroid.x) * drawWidth , (blobTracker[i].centroid.y) * drawHeight);
        
    }
    
    ofPopStyle();
    ofPopView();
    panel.draw();
}

void ofApp::blobAdded(ofxBlob &_blob){
    ofLog(OF_LOG_NOTICE, "Blob ID " + ofToString(_blob.id) + " added" );
}

void ofApp::blobMoved(ofxBlob &_blob){
    ofLog(OF_LOG_NOTICE, "Blob ID " + ofToString(_blob.id) + " moved" );
}

void ofApp::blobDeleted(ofxBlob &_blob){
    ofLog(OF_LOG_NOTICE, "Blob ID " + ofToString(_blob.id) + " deleted" );
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){

	switch (key){
		case ' ':
			blobTracker.bUpdateBackground = true;
			break;
		case '+':
			threshold ++;
			if (threshold > 255) threshold = 255;
			break;
		case '-':
			threshold --;
			if (threshold < 0) threshold = 0;
			break;
	}
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
void ofApp::windowResized(int w, int h){

}

//--------------------------------------------------------------
void ofApp::gotMessage(ofMessage msg){

}

//--------------------------------------------------------------
void ofApp::dragEvent(ofDragInfo dragInfo){ 

}
