#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup()
{
    bgTimer = 20;
    doStopMotion = false;
    video.loadMovie("fingers.mov");
    video.setLoopState(OF_LOOP_NORMAL);
    staggerUpdate = 5;
    //video.play();

    grab.setDeviceID(0);
    grab.initGrabber(320, 240);

    image.allocate(320, 240, GL_RGB);
    image2.allocate(320, 240, GL_RGB);

    numFrames = 200;
    numSlice = 0;
    CVimage.allocate(320,240);
    grey.allocate(320,240);
    greyBG.allocate(320,240);
    thresh = 80.0;

    haarFinder.setup("haarcascade_frontalface_default.xml");
    bLearnBackground = true;
}

//--------------------------------------------------------------
void ofApp::update()
{ bgTimer --;
staggerUpdate--;

   // video.update();
    if (staggerUpdate<=0){
    grab.update();
    staggerUpdate = 10;

    }
    if (grab.isFrameNew())
    {
        //frames.push_front(grab.getPixelsRef());






    CVimage.setFromPixels(grab.getPixels(),320,240);
    grey=CVimage;

    if(bgTimer <= 0 and doStopMotion){
        bLearnBackground = true;
        bgTimer = 4;

    }

     if(bLearnBackground){
        greyBG= grey;
        bLearnBackground = false;
    }
    greyDiff.absDiff(greyBG,grey);
    greyDiff.threshold(thresh);
    //StopMotion.push_back(greyBG.getPixelsRef());
    //grey.updateTexture();
    countour.findContours(greyDiff,20,(340*240)/3,10,true);

    haarFinder.findHaarObjects(grab.getPixelsRef());

}
}

//--------------------------------------------------------------
void ofApp::draw()
{
    //video.draw(0, 0, video.getWidth(), video.getHeight());
    ofPixels &pixels = greyDiff.getPixelsRef();
    ofPushMatrix();
    //ofTranslate(video.getWidth()+10, 0);

   // ofTranslate(video.width+10,0);
    greyDiff.draw(0,0);
    int sumX,sumY = 0;
    for(int i = 0 ; i < countour.blobs.size(); i++)
    {sumX += countour.blobs[i].boundingRect.x;
    sumY += countour.blobs[i].boundingRect.y;

    }
    if(countour.blobs.size()>0){
    sumX /= countour.blobs.size();
    sumY /= countour.blobs.size();
    }
//thresh = sumX;
        for (int x = 0; x<greyDiff.getWidth(); x++)
    {

        //int pixY = ofMap(sumY, 0, ofGetHeight(), 0, video.getHeight());
        //ofColor c = pixels.getColor(x, pixY);
        //ofSetColor(c);
        //ofLine(x, 0, x, greyDiff.getHeight());
    }

    ofPopMatrix();
    ofSetColor(255);
    ofPushMatrix();
    ofTranslate(0, video.getHeight() + 10);
    grab.draw(0, 0, grab.getWidth(), grab.getHeight());
    for(int i = 0 ; i<haarFinder.blobs.size(); i++)
    {
        haarFinder.blobs[i].draw(0,0);
    }
    if (haarFinder.blobs.size()>0){
        //doStopMotion = true;
    }
    ofSetColor(255);
    ofTranslate(grab.getWidth()+10, 0);
    //image.draw(0, 0);
    ofTranslate(image.getWidth()+10, 0);
    //image2.draw(0,0);
    ofPopMatrix();
}

//--------------------------------------------------------------
ofColor ofApp::getPixelColor( int x, int y)
{
    int pixX = ofMap(mouseX, 0, ofGetWidth(), 0, grab.getWidth());
    int pixY = ofMap(mouseY, 0, ofGetHeight(), 0, grab.getHeight());

    float dist = ofDist(x, y, pixX, pixY);

    float f = dist/2.0;

    int i0 = int(f);
    int i1 = i0 + 1;

    float weight0 = i1 - f;
    float weight1 = 1 - weight0;

    int n = frames.size() - 1;
    i0 = ofClamp(i0, 0, n);
    i1 = ofClamp(i1, 0, n);

    ofColor color0 = frames[i0].getColor(x, y);
    ofColor color1 = frames[i1].getColor(x, y);

    return color0 * weight0 + color1 * weight1;
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key)
{

}

//--------------------------------------------------------------
void ofApp::keyReleased(int key)
{

}

//--------------------------------------------------------------
void ofApp::mouseMoved(int x, int y )
{
    mouseX = x;
    mouseY = y;
    //thresh = ofMap(x ,0,ofGetWidth(),0,255);
}

//--------------------------------------------------------------
void ofApp::mouseDragged(int x, int y, int button)
{

}

//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button)
{
if (button==0){
    doStopMotion = !doStopMotion;
}
}

//--------------------------------------------------------------
void ofApp::mouseReleased(int x, int y, int button)
{

}

//--------------------------------------------------------------
void ofApp::windowResized(int w, int h)
{

}

//--------------------------------------------------------------
void ofApp::gotMessage(ofMessage msg)
{

}

//--------------------------------------------------------------
void ofApp::dragEvent(ofDragInfo dragInfo)
{

}
