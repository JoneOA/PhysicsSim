#pragma once

class Square {
private:

public:
    float vertexPos[8] = {
        -0.5f, -0.5f, // 0
         0.5f,  0.5f, // 1
        -0.5f,  0.5f, // 2
         0.5f, -0.5f  // 3
    };

    unsigned int indexPos[6] = {
        0, 2, 1,
        0, 1, 3
    };

    float cubePos[2];

    Square(float x, float y) {
        cubePos[0] = x;
        cubePos[1] = y;
    };

};