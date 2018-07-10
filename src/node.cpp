#include "node.hpp"

const int Node::MaxGeneration = 13;
const float Node::MaxLengthLimit = 500.0;
const float Node::MinLengthLimit = 10.0;
const float Node::MaxThicknessLimit = 10.0;
const float Node::MinThicknessLimit = 0.0;

Node::Node(const shared_ptr<Node>& parent) : mParent(parent) { setup(); }

Node::Node() { setup(); }

Node::~Node() {}

void Node::setup() {
    if (auto p = mParent.lock()) {
        mEngine.seed(random_device()());

        mGeneration = p->mGeneration + 1;

        mPosition = p->mPosition;

        normal_distribution<float> normalDistribution1(PI / 6.0, PI / 24.0);
        uniform_real_distribution<float> uniformDistribution1(-PI, PI);

        mDirection =
            p->mDirection
                .getRotatedRad(normalDistribution1(mEngine),
                               p->mDirection.getCrossed(ofPoint(1.0, 1.0, 1.0)))
                .getRotatedRad(uniformDistribution1(mEngine), p->mDirection)
                .getNormalized();

        mLength = 0.0;

        mThickness = p->mThickness;

        auto mean1([](int generation) {
            auto a((MaxLengthLimit - MinLengthLimit) * MaxGeneration /
                   (MaxGeneration - 1.0));
            auto b((MinLengthLimit * MaxGeneration - MaxLengthLimit) /
                   (MaxGeneration - 1.0));

            return a / generation + b;
        });

        auto stddev1(
            [mean1](int generation) { return mean1(generation) / 10.0; });

        normal_distribution<float> normalDistribution2(mean1(mGeneration),
                                                       stddev1(mGeneration));

        mLengthLimit = normalDistribution2(mEngine);

        auto mean2([](int generation) {
            auto a((MinThicknessLimit - MaxThicknessLimit) /
                   (MaxGeneration - 1.0));
            auto b((MaxThicknessLimit * MaxGeneration - MinThicknessLimit) /
                   (MaxGeneration - 1.0));

            return a * generation + b;
        });

        auto stddev2(
            [mean2](int generation) { return mean2(generation) / 1000.0; });

        normal_distribution<float> normalDistribution3(mean2(mGeneration),
                                                       stddev2(mGeneration));

        mThicknessLimit = normalDistribution3(mEngine);

        mMesh.setMode(OF_PRIMITIVE_TRIANGLE_STRIP);
    }
}

void Node::update() {
    if (mGeneration <= MaxGeneration) {
        if (mLength < mLengthLimit) {
            grow();
        }

        else if (mChildren.empty()) {
            make();
        }

        for (const auto& child : mChildren) {
            child->update();
        }
    }
}

void Node::draw() const {
    if (mGeneration <= MaxGeneration) {
        mMesh.draw();

        for (const auto& child : mChildren) {
            child->draw();
        }
    }
}

void Node::grow() {
    if (auto p = mParent.lock()) {
        normal_distribution<float> normalDistribution1(4.0, 2.0);

        auto newPosition(mPosition + mDirection * normalDistribution1(mEngine));

        normal_distribution<float> normalDistribution2(0.0, PI / 100.0);
        uniform_real_distribution<float> uniformDistribution2(-PI, PI);

        auto newDirection(mDirection.getRotatedRad(
            normalDistribution2(mEngine),
            mDirection.getCrossed(ofPoint(1.0, 1.0, 1.0))
                .getRotatedRad(uniformDistribution2(mEngine), mDirection)
                .getNormalized()));

        auto newLength(mLength + newPosition.distance(mPosition));

        auto calcThickness([&](float length) {
            return (mThicknessLimit - p->mThickness) / mLengthLimit * length +
                   p->mThickness;
        });

        auto newThickness(calcThickness(newLength));

        auto cylinder(
            ofMesh::cylinder(mThickness, newPosition.y - mPosition.y));

        auto& vertices(cylinder.getVertices());

        for (auto& vertex : vertices) {
            auto center(mPosition.getMiddle(newPosition) +
                        mDirection * (vertex.y / mDirection.y));
            auto thickness(calcThickness(mLength + center.distance(mPosition)));

            vertex =
                center + ofPoint(vertex.x, 0.0, vertex.z).getScaled(thickness);
        }

        mMesh.append(cylinder);

        mPosition = newPosition;
        mDirection = newDirection;
        mLength = newLength;
        mThickness = newThickness;
    }
}

void Node::make() {
    poisson_distribution<int> poissonDistribution1(2);

    generate_n(back_inserter(mChildren), poissonDistribution1(mEngine),
               [&]() { return make_shared<Node>(shared_from_this()); });
}

void Node::setGeneration(int generation) { mGeneration = generation; }

int Node::getGeneration() const { return mGeneration; }

void Node::setLength(float length) { mLength = length; }

float Node::getLength() const { return mLength; }

void Node::setThickness(float thickness) { mThickness = thickness; }

float Node::getThickness() const { return mThickness; }

void Node::setPosition(const ofPoint& position) { mPosition = position; }

ofPoint Node::getPosition() const { return mPosition; }

void Node::setDirection(const ofPoint& direction) { mDirection = direction; }

ofPoint Node::getDirection() const { return mDirection; }
