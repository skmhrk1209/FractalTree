#include "fractal_tree_app.hpp"

void FractalTreeApp::setup() {
    ofBackground(ofColor::black);
    
    gui.setup();
    gui.add(cameraPosition.set("camera position", ofPoint(0, 0, 0), ofPoint(0, 0, 0), ofPoint(1000, 1000, 1000)));
    gui.add(lightPosition.set("light position", ofPoint(0, 0, 0), ofPoint(0, 0, 0), ofPoint(1000, 1000, 1000)));

    cameraPosition.addListener(this, &FractalTreeApp::cameraPositionUpdated);
    lightPosition.addListener(this, &FractalTreeApp::lightPositionUpdated);
}

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

    gui.draw();
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

void FractalTreeApp::cameraPositionUpdated(ofPoint& cameraPosition) 
{
    mCamera.setPosition(cameraPosition);
    mCamera.setTarget(ofPoint(0, 1000, 0));
}

void FractalTreeApp::lightPositionUpdated(ofPoint& lightPosition) 
{
    mLight.setPosition(lightPosition);
}