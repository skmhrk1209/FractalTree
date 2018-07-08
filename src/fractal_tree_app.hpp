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

   private:
    ofEasyCam mCamera;
    ofLight mLight;
    vector<shared_ptr<Node>> mTrees;
};
