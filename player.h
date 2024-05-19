#pragma once
#include <string>

#include "raylib.h"
#include "raymath.h"

//controls
#define UP		KEY_W
#define DOWN	KEY_S
#define LEFT	KEY_A
#define RIGHT	KEY_D
#define NITRO	KEY_LEFT_SHIFT
#define ATACK	KEY_SPACE

//Physics
#define NITRO_SCALAR	3
#define Y_AX			20
#define X_AX			20

//Drawing
#define TRIANGLE_SIZE	16
#define SHIELD_SIZE		20


#define RES_COUNT	4


class Player
{
public:
	Player();

	//Getters
	Vector2 getPos();
	float getRotation();

	//Resourses
	void Atack();
	void AddRes(int heist[RES_COUNT]);

	//Movement
	void UpdatePos(Vector2 dAx);
	void UpdateVel(Vector2 dAx);
	void UpdateRotation();
	void ReturnHome();

	//Drwing
	void Draw();

private:
	std::string Name;

	//Movement
	Vector2 Ax, Vel, Pos;

	float Money, Rotation, Nitro;

	double NitroTimer;

	int resourses[RES_COUNT] = { 0,0,0,0 };

	int Hp;

	bool isAtacking;

};