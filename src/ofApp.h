#pragma once

#include "ofMain.h"
#include "ofxOpenCv.h"
#include "ofxCvHaarFinder.h"


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


    ofVideoPlayer video;

    ofVideoGrabber grab;
vector<ofImage> StopMotion;
    deque<ofPixels>frames;
    //deque<ofImage>StopMotion;

    int numFrames;
    int numSlice;

    ofPixels imagePixels, imagePixels2;
    ofTexture image, image2;

    int mouseX, mouseY;

    ofColor getPixelColor( int x, int y);

    ofxCvColorImage CVimage;

    ofxCvGrayscaleImage grey;
    ofxCvGrayscaleImage greyBG;
    ofxCvGrayscaleImage greyDiff;
    //ofxCvGrayscaleImage StopMotion;
    bool doStopMotion;
    int staggerUpdate;
    ofxCvContourFinder countour;
    float thresh;
    bool  bLearnBackground;
    int bgTimer;


ofxCvHaarFinder haarFinder;

};




















