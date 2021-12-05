/*
 *  ofxBlobTracking.h
 *
 *  Created by Ramsin Khoshabeh on 5/4/08.
 *  Copyright 2008 risenparadigm. All rights reserved.
 *
 * Changelog:
 * 08/15/08 -- Fixed a major bug in the track algorithm
 */

#ifndef OFXBLOBTRACKER
#define OFXBLOBTRACKER

#include "ofxBlob.h"
#include "ofxContourFinder.h"

class ofxBlobTracker{
public:
	ofxBlobTracker();
    ofParameterGroup params;
    ofParameter<int> threshold;
    ofParameter<int> minArea;
    ofParameter<int> maxArea;
    ofParameter<int> nConsidered;
    ofParameter<double> hullPress;
    ofParameter<double> distanceThreshold;
    ofParameter<int> nearsetNeighboursToCheck;
    ofParameter<float> brightness;
    ofParameter<float> contrast;
    ofParameter<int> blur;
    ofParameter<bool> bFindHoles;
    ofParameter<bool> bUseApproximation;
    ofParameter<int>     movementFiltering;
    ofParameter<bool>    bUpdateBackground;
    
    void    update( ofxCvGrayscaleImage& input);
    void    draw( float _x = 0, float _y = 0, float _width = 0, float _height = 0);
    
    int     size(){return trackedBlobs.size(); };
    
    ofxBlob operator[](unsigned int _n){ if ( (_n >= 0U) && (_n < trackedBlobs.size()) ) return trackedBlobs[_n]; };
    
    ofEvent<ofxBlob>    blobAdded;
    ofEvent<ofxBlob>    blobMoved;
    ofEvent<ofxBlob>    blobDeleted;
    


private:
	void    track(ofxContourFinder* newBlobs);
	int     trackKnn(ofxContourFinder *newBlobs, ofxBlob *track);
    
    ofxContourFinder    contourFinder;
    ofxCvGrayscaleImage backgroundImage;
    
	vector<ofxBlob> trackedBlobs;		//tracked blobs
    
	int             IDCounter, numEnter, numLeave, nSize;
    int             width, height;
};

#endif
