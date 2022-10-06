#include "Collision.h";
#include <iostream>

bool Overlap(double c1, float hs1, double c2, float hs2)
{
	if (c1 + hs1 >= c2 - hs2 && c1 - hs1 <= c2 + hs2)
		return true;
	return false;
}

bool Collision::CheckCollision(Shape& shape1, Shape& shape2)
{
	std::vector<double> pos1 = shape1.GetPosition();
	float halfSize1 = shape1.GetHalfSize();

	std::vector<double> pos2 = shape2.GetPosition();
	float halfSize2 = shape2.GetHalfSize();


	if (Overlap(pos1[0], halfSize1, pos2[0], halfSize2) && Overlap(pos1[1], halfSize1, pos2[1], halfSize2))
	{
		return true;
	}

	return false;
}

std::vector<double> Collision::CollisionDirection(Shape& shape1, Shape& shape2)
{
	std::vector<double> pos1 = shape1.GetPosition();
	std::vector<double> vel1 = shape1.GetVelocity();

	std::vector<double> pos2 = shape2.GetPosition();
	std::vector<double> vel2 = shape2.GetVelocity();

	double t = pos1[0] - pos2[0] + pos1[1] - pos2[1];

	std::vector<double> impactDirection;

	if (abs(pos1[0] - pos2[0]) > abs(pos1[1] - pos2[1]))
		impactDirection = { 1 , 0 };
	else
		impactDirection = { 0 , 1 };


	return impactDirection;
}

void Collision::OnUpdate()
{

}


