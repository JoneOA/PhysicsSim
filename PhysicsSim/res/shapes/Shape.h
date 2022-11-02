#pragma once

#include <vector>
#include <array>
#include <chrono>

struct Force {
    float forceX;
    float forceY;
};

class Shape {
private:

public:

    float m_FurthestPointFromC;

    double m_cX, m_cY, m_cR;

    std::vector<float> vertexPos;
    std::vector<unsigned int> indexPos;

    virtual void OnUpdate(Force& f, int64_t delta) {
        UpdateAccelleration(f, delta);
        UpdateVelocity();
        UpdatePosition();
        UpdateVertex();
    };

    virtual void UpdateVertex() = 0;

    virtual void UpdatePosition() = 0;

    virtual void UpdateVelocity() = 0;

    virtual void UpdateAccelleration(Force& force, int64_t delta) = 0;

    virtual float GetSize() = 0;

    virtual float GetHalfSize() = 0;

    virtual std::vector<double> GetPosition() = 0;

    virtual std::vector<double> GetVelocity() = 0;

    virtual void Move(std::vector<float> normal, float depth) = 0;

    virtual double GetMass() = 0;

    virtual void SetVelocity(double newX, double newY) = 0;
};