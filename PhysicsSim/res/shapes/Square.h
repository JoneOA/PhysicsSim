#pragma once

#include <math.h>
#include <vector>
#include <Shape.h>

double timeScaling;

class Square : public Shape {
private:
    float m_Size = 100.0f;
    float m_HalfSize = m_Size / 2.0f;
    double m_Mass = 1.0f;


    double m_pX = 490.0, m_pY = 490.0, m_pR = 0; //Position:      X, Y, and Rotation (Radians)
    double m_vX = 0.0,   m_vY = 0.0,   m_vR = 0; //Velocity:      X, Y, and Rotation (Radians / s)
    double m_aX = 0.0,   m_aY = 0.0,   m_aR = 0.0; //Accelleration: X, Y, and Rotation (Radians / s^2)

    double m_cX = m_pX + (double)(m_HalfSize), m_cY = m_pY + (double)(m_HalfSize); // Position of centre

    float lb = 0.0f, rb = 1.0f, bb = 0.0f, tb = 1.0f;

    bool m_Fixed = false;

public:

    Square(float x, float y) 
    {
        m_vX += x;
        m_vY += y;

        m_cX += x;
        m_cY += y;

        lb = m_pX;
        bb = m_pY;
        rb = m_pX + m_Size;
        tb = m_pY + m_Size;


        //Purely for rendering {
            vertexPos = 
            {
              lb, bb, // 0
              rb, bb, // 1
              lb, tb, // 2
              rb, tb  // 3
            };

            indexPos = 
            {
                0, 3, 2,
                3, 0, 1
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
        vertexPos = {
            (float)m_cX - m_HalfSize , (float)m_cY - m_HalfSize,
            (float)m_cX + m_HalfSize , (float)m_cY - m_HalfSize,
            (float)m_cX - m_HalfSize , (float)m_cY + m_HalfSize,
            (float)m_cX + m_HalfSize , (float)m_cY + m_HalfSize
        };

        for (int i =  0; i < 8; i += 2) {
            float tempX = vertexPos[0 + i] - m_cX;
            float tempY = vertexPos[1 + i] - m_cY;
            
            float rotatedX = tempX * cos(m_pR) - tempY * sin(m_pR);
            float rotatedY = tempX * sin(m_pR) + tempY * cos(m_pR);

            vertexPos[0 + i] = rotatedX + m_cX;
            vertexPos[1 + i] = rotatedY + m_cY;
        }
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
            m_cX -= m_vX;
        }

        if (m_cY + m_vY > 1080 - m_HalfSize) 
        {
            m_vY = -m_vY;
            m_cY = 1080 - m_HalfSize;
        }
        else if(m_cY + m_vY < 0 + (m_HalfSize))
        {
            m_vY = -m_vY;
            m_cY -= m_vY;
        }

        m_cX += m_vX;
        m_cY += m_vY;
        m_pR += m_vR;

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
        m_aY = (force.forceY / m_Mass) * timeScaling * timeScaling;
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
        return { m_cX, m_cY, m_pR };
    }

    std::vector<double> GetVelocity()
    {
        return { m_vX, m_vY, m_vR, m_Mass };
    }
};