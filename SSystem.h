#pragma once
#include <vector>

#include "enemies.h"
#include "player.h"

#define G			0.0000000000667428

struct SolarSystem
{
	std::vector<Asteroid> asteroids;

};

void PingAst(SolarSystem& other, int i);

bool CheckCollisionLineCircle(Vector2 Point, float Angle, Vector2 Center, float radius);

void UpdatePlayer_n_System(SolarSystem& system, Player& player);

float getAxGForce(Vector2 obj, Vector2 asteroid, float mass);

Vector2 vecPoints(Vector2 p1, Vector2 p2);