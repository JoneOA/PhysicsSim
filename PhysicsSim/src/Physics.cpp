#include "Physics.h"
#include <iostream>

int colCount = 0;

Physics::Physics(Collision& collider) :
	m_Collision(collider)
{
}

Physics::~Physics()
{
}

void Physics::OnUpdate(std::vector<Shape*>& shapes, int64_t delta)
{
	
	for (int i = 0; i < shapes.size(); i++)
	{

		std::vector<double> id;

		Force f1 = { 0 , 0 };

		for (int j = i + 1; j < shapes.size(); j++) 
		{
			Force f2 = { 0 , 0 };

			bool colliding = m_Collision.CheckCollision(*shapes[i], *shapes[j]);
			bool alreadyCollidided = false;
			int collisionIndex;

			for (int ii = 0; ii < inProgressCollisions[i].size(); ii++) {
				if (inProgressCollisions[i][ii] == j) {
					alreadyCollidided = true;
					collisionIndex = ii;
					break;
				}
			}

			if (colliding)
			{
				id = m_Collision.CollisionDirection(*shapes[i], *shapes[j]);

				float tvx = abs(shapes[i]->GetVelocity()[0]) + abs(shapes[j]->GetVelocity()[0]);
				float tvy = abs(shapes[i]->GetVelocity()[1]) + abs(shapes[j]->GetVelocity()[1]);
				
				f1.forceX = id[0] * (tvx);
				f1.forceY = id[1] * (tvy);

				f2.forceX = -id[0] * (tvx);
				f2.forceY = -id[1] * (tvy);

				// TODO: Correct reaction impulse forces on colliding shapes

				//inProgressCollisions[i].push_back(j);

				colCount++;
				std::cout << colCount << " : Collision\n";
			}

			shapes[j]->OnUpdate(f2, delta);
			if (!colliding && alreadyCollidided)
				inProgressCollisions[i].erase(inProgressCollisions[i].begin() + collisionIndex);
		}

		shapes[i]->OnUpdate(f1, delta);
	}

}