#pragma once

#include "node.hpp"
#include "ofMain.h"
#include "ofxGui.h"

using namespace std;

class FractalTreeApp : public ofBaseApp {
   public:
    void setup();
    void update();
    void draw();
    void keyPressed(int);

    void cameraPositionUpdated(ofPoint&);
    void lightPositionUpdated(ofPoint&);

    ofxPanel gui;
    ofParameter<ofPoint> cameraPosition;
    ofParameter<ofPoint> lightPosition;

   private:
    ofEasyCam mCamera;
    ofLight mLight;
    shared_ptr<Node> mTree;
};
