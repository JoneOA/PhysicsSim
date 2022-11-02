#include "Physics.h"
#include "PhySiMaths.h"
#include <vector>
#include <iostream>

std::vector<float> operator-(std::vector<float> vec1) 
{
	return { -vec1[0], -vec1[1] };
}

//std::vector<double> operator*(double scalar, std::vector<double> vec)
//{
//	return { vec[0] * scalar, vec[1] * scalar };
//}

//std::vector<float> operator*(int scalar, std::vector<float> vec)
//{
//	return { vec[0] * (float)scalar, vec[1] * (float)scalar };
//}

Physics::Physics(Collision& collider) :
	m_Collision(collider)
{
}

Physics::~Physics()
{
}

double Physics::ResolveImpulse(Shape& object1, Shape& object2, int64_t delta)
{
	std::vector<float> collisionDir = m_Collision.GetCollisionNormal();
	std::vector<double> collisionVel = { object1.GetVelocity()[0] - object2.GetVelocity()[0], object1.GetVelocity()[1] - object2.GetVelocity()[1] };
	
	double e = 0;

	double topLine =  -(1 + e) * collisionVel * collisionDir;
	double bottomLine = collisionDir * collisionDir * ((1 / object1.GetMass()) + (1 / object2.GetMass()));

	double j = topLine / bottomLine;

	return j;
}

void Physics::OnUpdate(std::vector<Shape*>& shapes, int64_t delta)
{

	Force f1 = { 0 , 0 };

	for (int i = 0; i < shapes.size(); i++)
	{
		Shape* shape1 = shapes[i];

		for (int j = i + 1; j < shapes.size(); j++) 
		{
			Shape* shape2 = shapes[j];

			float lh = pow(shape1->m_FurthestPointFromC + shape2->m_FurthestPointFromC, 2);
			float rh1 = pow(shape1->m_cX - shape2->m_cX, 2);
			float rh2 = pow(shape1->m_cY - shape2->m_cY, 2);

			if (lh < rh1 + rh2)
			{
				continue;
			}

			bool colliding = m_Collision.SeparateAxisCollision(*shapes[i], *shapes[j]);

			if (colliding)
			{
				int collisionDirection = m_Collision.GetCollisionDirection();
				std::vector<float> collisionNormal = m_Collision.GetCollisionNormal();
				float collisionDepth = m_Collision.GetCollisionDepth();
			
				double scale = ResolveImpulse(*shapes[i], *shapes[j], delta);
				
				shape1->Move( collisionNormal,  collisionDirection * collisionDepth);
				shape2->Move( collisionNormal, -collisionDirection * collisionDepth);

				std::vector<double> shape1V = shape1->GetVelocity();
				double shape1M = shape1->GetMass();

				std::vector<double> shape2V = shape2->GetVelocity();
				double shape2M = shape2->GetMass();


				shape1->SetVelocity(shape1V[0] + (scale / shape1M) * collisionNormal[0], shape1V[1] + (scale / shape1M) * collisionNormal[1]);
				shape2->SetVelocity(shape2V[0] - (scale / shape2M) * collisionNormal[0], shape2V[1] - (scale / shape2M) * collisionNormal[1]);
				
				//std::cout << "HIT" << "\n";
			}

		}

	}

	for (int i = 0; i < shapes.size(); i++) {
		shapes[i]->OnUpdate(f1, delta);
	}
	
}