#pragma once
#include "Shape.h";
#include <array>
#include <math.h>

class Collision {
private:

	std::vector<float> m_CollisionNormal;
	float m_CollisionDepth;
	int m_CollisionDirection;
	
public:

	Collision() {};

	~Collision() {};

	bool SeparateAxisCollision(Shape& shape1, Shape& shape2);

	std::vector<float> GetCollisionNormal();

	int GetCollisionDirection();

	float GetCollisionDepth();

	void OnUpdate();


};