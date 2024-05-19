#include "player.h"

Player::Player()
{
	Name = "";

	Ax = Vel = Pos = { 0,0 };

	Money = Rotation = 0;

	Nitro = 10;

	NitroTimer = 0;

	Hp = 100;

	isAtacking = false;
}

Vector2 Player::getPos()
{
	return Pos;
}

float Player::getRotation()
{
	return Rotation;
}

void Player::Atack()
{
	isAtacking = true;
	//for (int i = 0; i < other.asteroids.size(); i++)
	//{
	//	//if ()
	//}
}

void Player::AddRes(int heist[RES_COUNT])
{
	for (int i = 0; i < RES_COUNT; i++)		resourses[i] += heist[i];
}

void Player::UpdatePos(Vector2 dAx)
{
	UpdateVel(dAx);
	UpdateRotation();

	Pos = Vector2Add(Pos, Vector2Scale(Vel, GetFrameTime()));

	if (IsKeyDown(ATACK))	Atack();
}

void Player::UpdateVel(Vector2 dAx)
{
	//Update Y
	if (IsKeyDown(UP)) Ax.y = -Y_AX;
	else if (IsKeyDown(DOWN)) Ax.y = Y_AX;
	else Ax.y = 0;

	//Update X
	if (IsKeyDown(LEFT)) Ax.x = -X_AX;
	else if (IsKeyDown(RIGHT)) Ax.x = X_AX;
	else Ax.x = 0;


	//Updating nitro
	if (IsKeyDown(NITRO))	Ax = Vector2Scale(Ax, NITRO_SCALAR);

	Ax = Vector2Add(Ax, dAx);

	Vel = Vector2Add(Vel, Vector2Scale(Ax, GetFrameTime()));
}

void Player::UpdateRotation()
{
	if (Vel.x != 0)
	{
		Rotation = atanf(Vel.y / Vel.x);
		if (Vel.x < 0)	Rotation += PI;
	}
	else if (Vel.y > 0)	Rotation = PI / 2;
	else if (Vel.y < 0)	Rotation = 3 * PI / 2;
}

void Player::ReturnHome()
{
	Pos = Vel = { 0,0 };
}

void Player::Draw()
{
	//Draw Shield
	DrawCircleV(Pos, SHIELD_SIZE, { 150,150,150,150 });

	/*Vector2 p1 = Vector2Add(Pos, Vector2Scale({ cosf(Rotation), sinf(Rotation) }, TRIANGLE_SIZE)),
			p2 = Vector2Add(Pos, Vector2Scale({ cosf(Rotation + 2 * PI / 3), sinf(Rotation + 2 * PI / 3) }, TRIANGLE_SIZE)),
			p3 = Vector2Add(Pos, Vector2Scale({ cosf(Rotation - 2 * PI / 3), sinf(Rotation - 2 * PI / 3) }, TRIANGLE_SIZE));*/

	Vector2 p1 = Vector2Add(Pos, Vector2Scale({ cosf(Rotation), sinf(Rotation) }, TRIANGLE_SIZE)),
		p2 = Vector2Add(Pos, Vector2Scale({ cosf(Rotation + 3 * PI / 4), sinf(Rotation + 3 * PI / 4) }, TRIANGLE_SIZE)),
		p3 = Vector2Add(Pos, Vector2Scale({ cosf(Rotation - 3 * PI / 4), sinf(Rotation - 3 * PI / 4) }, TRIANGLE_SIZE));

	DrawTriangle(p1, p3, p2, RED);
}
