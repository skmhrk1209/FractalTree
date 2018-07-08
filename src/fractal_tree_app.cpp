#include "fractal_tree_app.hpp"

void FractalTreeApp::setup() { ofBackground(ofColor::black); }

void FractalTreeApp::update() {
    for (auto& tree : mTrees) tree->update();
}

void FractalTreeApp::draw() {
    ofEnableDepthTest();
    ofEnableLighting();

    mCamera.begin();
    mLight.enable();

    for (const auto& tree : mTrees) tree->draw();

    mLight.disable();
    mCamera.end();

    ofDisableDepthTest();
    ofDisableLighting();
}

void FractalTreeApp::keyPressed(int key) {
    if (key == ' ') {
        random_device seed;
        mt19937 generator(seed());
        uniform_real_distribution<float> distribution(-100, 100);

        auto root = make_shared<Node>();
        root->setGeneration(0);
        root->setLength(Node::MaxLengthLimit);
        root->setThickness(Node::MaxThicknessLimit);
        root->setPosition(
            ofPoint(distribution(generator), 0.0, distribution(generator)));
        root->setDirection(ofPoint(0.0, 1.0, 0.0));

        mTrees.push_back(move(root));
    }
}
