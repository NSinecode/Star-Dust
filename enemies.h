#pragma once
#include "raylib.h"
#include "raymath.h"

#include <string>
#include <vector>

#define MIN_ASTEROID_R		80
#define MAX_ASTEROID_R		400
#define MIN_ASTEROID_CURVE	1
#define MAX_ASTEROID_CURVE	4
#define CURVES_COUNT		400
#define RES_SIZE			2

#define ASTEROID_DENSITY	2000

//res
#define RES_COUNT	4
#define SERA		0
#define CARBON		1
#define IRON		2
#define GOLDEN		3

class Asteroid
{
public:
	Asteroid();

	~Asteroid();

	Vector2 getPos();
	float getMass();

	//General updating
	void SendBreakingTick();
	void Update();
	void RandomPos(int width, int heigh);
	//void killed_by_player(Player& other);

	//Movement
	void UpdatePos();
	void UpdateVel();
	void UpdateRotation();

	//Drawing
	void GenerateTexture();
	void Draw();
	Vector2 routedPOS();

	//Makes texture more red
	void UpdateBreaking();

private:

	RenderTexture texture;

	Color textureEffect;

	//Movement
	Vector2 Ax, Vel, Pos;

	float mass, radius, rotation, AngleVel, AngleAx;

	//resourses
	int resourses[RES_COUNT];

	bool isBreaking, dead;
};