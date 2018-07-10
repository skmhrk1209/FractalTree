#include "fractal_tree_app.hpp"

void FractalTreeApp::setup() { ofBackground(ofColor::black); }

void FractalTreeApp::update() {
    if (mTree) {
        mTree->update();
    }
}

void FractalTreeApp::draw() {
    ofEnableDepthTest();
    ofEnableLighting();

    mCamera.begin();
    mLight.enable();

    if (mTree) {
        mTree->draw();
    }

    mLight.disable();
    mCamera.end();

    ofDisableDepthTest();
    ofDisableLighting();
}

void FractalTreeApp::keyPressed(int key) {
    if (key == ' ') {
        mTree = make_shared<Node>();
        mTree->setGeneration(0);
        mTree->setLength(Node::MaxLengthLimit);
        mTree->setThickness(Node::MaxThicknessLimit);
        mTree->setPosition(ofPoint(0.0, 0.0, 0.0));
        mTree->setDirection(ofPoint(0.0, 1.0, 0.0));
    }
}
