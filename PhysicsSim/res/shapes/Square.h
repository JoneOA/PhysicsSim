#pragma once

#include <math.h>
#include <vector>
#include <queue>
#include <Shape.h>

#include <glm/glm.hpp>

double timeScaling;

class Square : public Shape {
private:
    float m_Size = 50.0f;
    float m_HalfSize = m_Size / 2.0f;
    double m_Mass = 1.0f;

    //Position (centre):    X, Y, and Rotation (Radians)
    double m_vX = 0.0, m_vY = 0.0, m_vR = 0;    //Velocity:             X, Y, and Rotation (Radians / s)
    double m_aX = 0.0, m_aY = 0.0, m_aR = 0.0;  //Accelleration:        X, Y, and Rotation (Radians / s^2)
   
    float lb = 0.0f, rb = 1.0f, bb = 0.0f, tb = 1.0f; //left bounds, right bounds, bottom bounds, top bounds

    bool m_Fixed = false;

    std::queue<Force> appliedForces;

public:

    Square(float x, float y) 
    {
        m_FurthestPointFromC = 35.36f;
        m_vX += x * 0.30;
        m_vY += y * 0.30;

        m_cX = m_HalfSize + x * 500;
        m_cY = 540 + y * 520;
        m_cR = 0;

        lb = (float)m_cX - m_HalfSize;
        bb = (float)m_cY - m_HalfSize;
        rb = (float)m_cX + m_HalfSize;
        tb = (float)m_cY + m_HalfSize;


        //Purely for rendering {
            vertexPos = 
            {
              lb, bb, // 0
              rb, bb, // 1
              rb, tb, // 2
              lb, tb  // 3
            };

            indexPos = 
            {
                0, 2, 3,
                2, 0, 1
            };
        //}
    };

    Square(float x, float y, int o)
    {
        m_FurthestPointFromC = 35.36f;
        m_vX += 0;
        m_vY += 0;

        m_cX = x;
        m_cY = y;

        lb = (float)m_cX - m_HalfSize;
        bb = (float)m_cY - m_HalfSize;
        rb = (float)m_cX + m_HalfSize;
        tb = (float)m_cY + m_HalfSize;


        //Purely for rendering {
        vertexPos =
        {
          lb, bb, // 0
          rb, bb, // 1
          rb, tb, // 2
          lb, tb  // 3
        };

        indexPos =
        {
            0, 2, 3,
            2, 0, 1
        };
        //}
    };

    void OnUpdate(Force& f, int64_t delta) override
    {
        if (!m_Fixed)
        {
            UpdateAccelleration(f, delta);
            UpdateVelocity();
            UpdatePosition();
            UpdateVertex();
        }
    }

    void UpdateVertex() override
    {

        lb = (float)m_cX - m_HalfSize;
        bb = (float)m_cY - m_HalfSize;
        rb = (float)m_cX + m_HalfSize;
        tb = (float)m_cY + m_HalfSize;

        vertexPos =
        {
          lb, bb, // 0
          rb, bb, // 1
          rb, tb, // 2
          lb, tb  // 3
        };

        for (int i =  0; i < 8; i += 2) {
            float tempX = vertexPos[0 + i] - m_cX;
            float tempY = vertexPos[1 + i] - m_cY;
            
            float rotatedX = tempX * cos(m_cR) - tempY * sin(m_cR);
            float rotatedY = tempX * sin(m_cR) + tempY * cos(m_cR);

            vertexPos[0 + i] = rotatedX + m_cX;
            vertexPos[1 + i] = rotatedY + m_cY;
        }
    }

    void Move(std::vector<float> normal, float depth)
    {
        m_cX += normal[0] * depth / 2.0f;
        m_cY += normal[1] * depth / 2.0f;
    }

    void UpdatePosition() override
    {
        if (m_cX + m_vX > 1080 - m_HalfSize) {
            m_vX = -m_vX;      
            m_cX = 1080 - m_HalfSize;
        }
        else if (m_cX + m_vX < 0 + m_HalfSize)
        {
            m_vX = -m_vX;
            m_cX = m_HalfSize;
        }

        if (m_cY + m_vY > 1080 - m_HalfSize) 
        {
            m_vY = -m_vY;
            m_cY = 1080 - m_HalfSize;
        }
        else if(m_cY + m_vY < 0 + (m_HalfSize))
        {
            m_vY = -m_vY * 0.95;
            m_cY = m_HalfSize;
        }

        m_cX += m_vX;
        m_cY += m_vY;
        m_cR += m_vR;

    }

    void UpdateVelocity() override
    {
        m_vX += m_aX;
        m_vY += m_aY;
    }
    
    void UpdateAccelleration(Force& force, int64_t delta) override
    {
        double gravity = -980.0 * m_Mass;

        timeScaling = ((double)delta * 0.000001);

        m_aX = (force.forceX / m_Mass) * timeScaling * timeScaling;
        m_aY = ((force.forceY + gravity) / m_Mass) * timeScaling * timeScaling;
    }

    float GetSize() override
    {
        return m_Size;
    }

    float GetHalfSize()
    {
        return m_HalfSize;
    }

    std::vector<double> GetPosition() override
    {
        return { m_cX, m_cY, m_cR };
    }

    std::vector<double> GetVelocity()
    {
        return { m_vX, m_vY, m_vR };
    }

    double GetMass() override
    {
        return m_Mass;
    }

    void SetVelocity(double newX, double newY) override
    {
        m_vX = newX;
        m_vY = newY;
    }
};