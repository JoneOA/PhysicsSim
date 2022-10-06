#pragma once

#include <vector>
#include <unordered_map>
#include <Shape.h>
#include <chrono>

#include "Collision.h"

class Physics {

private:

	std::unordered_map<int, std::vector<int>> inProgressCollisions;

	Collision m_Collision;

public:

	Physics(Collision& collider);

	~Physics();

	void OnUpdate(std::vector<Shape*>& shape, int64_t delta);
	
};