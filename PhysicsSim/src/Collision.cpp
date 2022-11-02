#include "Collision.h";
#include <iostream>

struct MinMax
{
	float min;
	float max;
};

float Dot(std::vector<float>& vec1, float* vec2)
{
	return { vec1[0] * vec2[0] + vec1[1] * vec2[1] };
}

double operator*(std::vector<float>& vec1, std::vector<double>& vec2)
{
	return { vec1[0] * vec2[0] + vec1[1] * vec2[1] };
}

bool Overlap(double c1, float hs1, double c2, float hs2)
{
	if (c1 + hs1 >= c2 - hs2 && c1 - hs1 <= c2 + hs2)
		return true;
	return false;
}

std::vector<float> Normalise(std::vector<float>& axis, std::vector<float>& vector)
{
	float sqrt = std::sqrt((axis[0] * axis[0]) + (axis[1] * axis[1]));

	return { vector[0] / sqrt, vector[1] / sqrt };
}

float VectorLength(std::vector<float>& vector)
{
	return (std::sqrt((vector[0] * vector[0]) + (vector[1] * vector[1])));
}

MinMax ProjectToNormal(std::vector<float>& normal, std::vector<float>& verticies)
{
	
	float min = INT_MAX;
	float max = INT_MIN;
	float vertex[2] = {0, 0};

	for (int i = 0; i < verticies.size(); i += 2)
	{
		vertex[0] = verticies[0 + i];
		vertex[1] = verticies[1 + i];

		float t = Dot(normal, vertex);

		if (t < min)
			min = t;
		if (t > max)
			max = t;
	}

	return { min, max };
}

bool Collision::SeparateAxisCollision(Shape& shape1, Shape& shape2) 
{
	float depth = INT_MAX;

	for (int i = 0; i < shape1.vertexPos.size() / 2; i += 2)
	{
		MinMax A, B;

		std::vector<float> axis = { shape1.vertexPos[(2 + i) % 8] - shape1.vertexPos[0 + i] , shape1.vertexPos[(3 + i) % 8] - shape1.vertexPos[1 + i] };

		axis = Normalise(axis, axis);

		A = ProjectToNormal(axis, shape1.vertexPos);
		B = ProjectToNormal(axis, shape2.vertexPos);

		if (A.min >= B.max || B.min >= A.max)
			return false;

		float normalDepth = std::min(B.max - A.min, A.max - B.min);

		if (normalDepth < depth)
		{
			depth = normalDepth;
			m_CollisionDepth = normalDepth;
			m_CollisionNormal = axis;
		}
	}

	for (int i = 0; i < shape2.vertexPos.size() / 2; i += 2)
	{
		MinMax A, B;

		std::vector<float> axis = { shape2.vertexPos[(2 + i) % 8] - shape2.vertexPos[0 + i], shape2.vertexPos[(3 + i) % 8] - shape2.vertexPos[1 + i] } ;

		axis = Normalise(axis, axis);

		A = ProjectToNormal(axis, shape1.vertexPos);
		B = ProjectToNormal(axis, shape2.vertexPos);

		if (A.min >= B.max || B.min >= A.max)
			return false;

		float normalDepth = std::min(B.max - A.min, A.max - B.min);

		if (normalDepth < depth)
		{
			depth = normalDepth;
			m_CollisionDepth = normalDepth;
			m_CollisionNormal = axis;
		}
	}

	std::vector<double> shape1Pos = shape1.GetPosition();
	std::vector<double> shape2Pos = shape2.GetPosition();

	std::vector<double> direction = {shape2Pos[0] - shape1Pos[0], shape2Pos[1] - shape1Pos[1]};

	m_CollisionDirection = m_CollisionNormal * direction > 0 ? -1 : 1;

	return true;
}

std::vector<float> Collision::GetCollisionNormal()
{
	return m_CollisionNormal;
}

int Collision::GetCollisionDirection()
{
	return m_CollisionDirection;
}

float Collision::GetCollisionDepth()
{
	return m_CollisionDepth;
}


void Collision::OnUpdate()
{

}


