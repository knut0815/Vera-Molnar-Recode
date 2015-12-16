#pragma once

#include "ofMain.h"

class ofApp : public ofBaseApp 
{

	using LineSegment = pair<ofPoint, ofPoint>;

public:

	void setup();
	void update();
	void draw();
	void keyPressed(int key);
	void generateSegments();

	//--------------------------------------------------------------
	// These are all params that can be animated.
	// Note: generateSegments() will need to be called in
	// order for the changes to be reflected in the drawing.
	int NUM_SEGMENTS_X =			62;
	int NUM_SEGMENTS_Y =			62;
	int NUM_SEGMENTS_TOTAL =		NUM_SEGMENTS_X * NUM_SEGMENTS_Y;
    int NOISE_THRESHOLD =			100;
	int LINE_LENGTH =				8;
	//--------------------------------------------------------------

	ofImage							mNoiseTexture;
	ofImage							mPaperTexture;
	vector<LineSegment>				mLineSegments;
	ofColor							mLineColor;
};
