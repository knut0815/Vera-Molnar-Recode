#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup()
{
	// Create a vector of line segments based on our global parameters
	generateSegments();

	// Canvas settings
	ofBackground(ofColor::white);
	mLineColor.set(40);
	mPaperTexture.load("paper.jpg");
}

//--------------------------------------------------------------
void ofApp::generateSegments()
{
	mLineSegments.clear();

	// Vars for correctly positioning our lines on the canvas
	const float BORDER_X = 20.0f;
	const float BORDER_Y = 20.0f;
	float xSpacing = (ofGetWidth() - LINE_LENGTH - BORDER_X * 2) / NUM_SEGMENTS_X;
	float ySpacing = (ofGetHeight() - LINE_LENGTH - BORDER_Y * 2) / NUM_SEGMENTS_Y;

	// Use a noise value to decide whether to draw this line or not
	auto testAgainstNoise = [&](float x, float y) -> bool
	{
		bool pass = true;

		float a = x * 0.01f;
		float b = y * 0.01f;
		float c = ofGetFrameNum() / 50.0f;

		float threshold = 150.0f;
		float noise = ofNoise(a, b, c) * 255.0f;
		float noiseRGB = noise > threshold ? ofMap(noise, threshold, 255.0f, 0.0f, 255.0f) : 0.0f;

		pass = (noiseRGB > NOISE_THRESHOLD);

		// Occasionally, we choose to ignore the test completely
		float pct = ofRandomf();
		if (pct > 0.9f)
			pass = !pass;

		return pass;
	};

	for (int i = 0; i < NUM_SEGMENTS_TOTAL; ++i)
	{
		// Create a center point from which to 'anchor' our segments
		ofPoint center(xSpacing * (i % NUM_SEGMENTS_X),
					   ySpacing * (i / NUM_SEGMENTS_X));

		// Center the scene in the canvas
		center.x += LINE_LENGTH + BORDER_X;
		center.y += LINE_LENGTH + BORDER_Y;

		if (testAgainstNoise(center.x, center.y))
			continue;

		// Add a random rotation 
		float theta = ofRandom(0, TWO_PI);
		mLineSegments.emplace_back(ofPoint(center.x + cos(theta) * LINE_LENGTH,
										   center.y + sin(theta) * LINE_LENGTH),
								   ofPoint(center.x + cos(theta + PI) * LINE_LENGTH,
										   center.y + sin(theta + PI) * LINE_LENGTH));
	}
}

//--------------------------------------------------------------
void ofApp::update()
{
}

//--------------------------------------------------------------
void ofApp::draw()
{
	// Draw our lines on top of the paper texture
	if (mPaperTexture.isAllocated())
	{
		ofSetColor(ofColor::white);
		mPaperTexture.draw(0, 0);
	}

	ofSetColor(mLineColor);
	for (const auto &seg : mLineSegments)
	{
		ofLine(seg.first, seg.second);
	}
}

void ofApp::keyPressed(int key)
{
	if (key == 's' || key == 'S')
		ofSaveScreen("screenshots/molnar_" + ofGetTimestampString() + ".jpg");
}