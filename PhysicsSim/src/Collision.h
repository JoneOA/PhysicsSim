#pragma once
#include "Shape.h";

class Collision {
private:

public:

	Collision() {};

	~Collision() {};

	bool CheckCollision(Shape& shape1, Shape& shape2);

	std::vector<double> CollisionDirection(Shape& shape1, Shape& shape2);

	void OnUpdate();


};