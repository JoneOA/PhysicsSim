#pragma once

#include "Square.h"

#include <vector>

class Cube {

private:
	float x, y, z;

	bool gravity;

	float xVel, yVel, zVel;
	float xAcc, yAcc, zAcc;
	
public:

	std::vector<float> vertexPos =
	{
		 -0.5f, -0.5f,  0.5f, 1.0f, 0.0f, 0.0f, // 0
		  0.5f, -0.5f,  0.5f, 1.0f, 0.0f, 1.0f, // 1
		 -0.5f,  0.5f,  0.5f, 1.0f, 1.0f, 0.0f, // 2
		  0.5f,  0.5f,  0.5f, 1.0f, 1.0f, 1.0f, // 3
											    
		 -0.5f, -0.5f, -0.5f, 1.0f, 1.0f, 1.0f, // 4
		  0.5f, -0.5f, -0.5f, 0.0f, 1.0f, 0.0f, // 5
		 -0.5f,  0.5f, -0.5f, 0.0f, 0.0f, 1.0f, // 6
		  0.5f,  0.5f, -0.5f, 1.0f, 0.0f, 0.0f  // 7
	};

	std::vector<unsigned int> indexPos =
	{
		//Front
		0, 3, 2,
		3, 0, 1,

		//Right
		1, 7, 3,
		7, 1, 5,

		//Back
		5, 6, 7,
		6, 5, 4,

		//Left
		4, 2, 6,
		2, 4, 0,

		//Top
		2, 7, 6,
		7, 2, 3,

		//Bottom
		4, 1, 0,
		1, 4, 5
	};

	Cube(float x, float y, float z, float size, bool gravity) :
		x(x), y(y), z(z), gravity(gravity), xAcc(0.0f), yAcc(0.0f), zAcc(0.0f), xVel(0.0f), yVel(0.0f), zVel(0.0f)
	{
		for (int i = 0; i < vertexPos.size(); i += 6) {
			vertexPos[i] += x;
			vertexPos[i + 1] += y;
			vertexPos[i + 2] += z;
		}
		if (gravity) {
			yAcc = -9.8f;
		}
	}

	Cube() : 
		x(-1), y(-1), z(1), gravity(false), xAcc(0.0f), yAcc(0.0f), zAcc(0.0f), xVel(0.0f), yVel(0.0f), zVel(0.0f)
	{};

	void OnUpdate()
	{
		x += xVel;
		y += yVel;
		z += zVel;
		xVel += xAcc;
		yVel += yAcc;
		zVel += zAcc;

		for (int i = 0; i < vertexPos.size(); i += 6) {
			vertexPos[i] += xVel;
			vertexPos[i + 1] += yVel;
			vertexPos[i + 2] += zVel;
		}
	}

};
