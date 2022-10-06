#pragma once

class Triangle {
public:
    float vertexPos[6] = {
     -0.7f, -0.7f, // 0
     -0.5f, -0.5f, // 1
     -0.7f, -0.5f, // 2
    };

    unsigned int indexPos[3] = {
        0, 2, 1

    };

    float trianglePos[2];

    Triangle(float x, float y) {
        trianglePos[0] = x;
        trianglePos[1] = y;
    }
};
