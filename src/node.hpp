#pragma once

#include <algorithm>
#include <memory>
#include <random>
#include <vector>
#include "ofMain.h"

using namespace std;

class Node : public enable_shared_from_this<Node> {
   public:
    static const int MaxGeneration;
    static const float MaxLengthLimit;
    static const float MinLengthLimit;
    static const float MaxThicknessLimit;
    static const float MinThicknessLimit;

   private:
    weak_ptr<Node> mParent;
    vector<shared_ptr<Node>> mChildren;

    ofMesh mMesh;

    int mGeneration;
    float mLengthLimit;
    float mThicknessLimit;

    float mLength;
    float mThickness;

    ofPoint mPosition;
    ofPoint mDirection;

    mt19937 mEngine;

    void grow();
    void make();

   public:
    Node(const shared_ptr<Node>&);

    Node();
    ~Node();

    Node(const Node&) = default;
    Node(Node&&) = default;

    Node& operator=(const Node&) = default;
    Node& operator=(Node&&) = default;

    void setup();
    void update();
    void draw() const;

    void setGeneration(int);
    int getGeneration() const;

    void setLength(float);
    float getLength() const;

    void setThickness(float);
    float getThickness() const;

    void setPosition(const ofPoint&);
    ofPoint getPosition() const;

    void setDirection(const ofPoint&);
    ofPoint getDirection() const;
};
