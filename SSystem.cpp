#include "SSystem.h"

void PingAst(SolarSystem& other, int i)
{
	other.asteroids[i].SendBreakingTick();
}

bool CheckCollisionLineCircle(Vector2 Point, float Angle, Vector2 Center, float radius)
{
	return false;
}

void UpdatePlayer_n_System(SolarSystem& system, Player& player)
{
	//Making GForce to player
	Vector2 Player_dAx = { 0,0 };
	for (unsigned int i = 0; i < system.asteroids.size(); i++)
	{
		float dAxLen = getAxGForce(player.getPos(), system.asteroids[i].getPos(), system.asteroids[i].getMass());
		Player_dAx = Vector2Add(Player_dAx, Vector2Scale(vecPoints(player.getPos(), system.asteroids[i].getPos()), dAxLen / Vector2Length(vecPoints(player.getPos(), system.asteroids[i].getPos()))));
	}
	//Updating player
	player.UpdatePos(Player_dAx);

	//Updating SS
	for (int i = 0; i < system.asteroids.size(); i++)
	{
		system.asteroids[i].Update();
	}
}

float getAxGForce(Vector2 obj, Vector2 asteroid, float mass)
{
	return G * mass / Vector2DistanceSqr( obj, asteroid);
}

Vector2 vecPoints(Vector2 p1, Vector2 p2)
{
	return { p2.x - p1.x,p2.y - p1.y };
}
