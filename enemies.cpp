#include "enemies.h"

Asteroid::Asteroid()
{
	textureEffect = WHITE;
	Pos = { 300,200 };
	Vel = Ax = { 0,0 };
	radius = GetRandomValue(MIN_ASTEROID_R, MAX_ASTEROID_R);
	rotation = AngleVel = AngleAx = 0;
	AngleAx = 0.1;

	mass = powf(radius, 3) * ASTEROID_DENSITY * 900000;

	isBreaking = dead = false;
}

Asteroid::~Asteroid()
{
	UnloadRenderTexture(texture);
}

Vector2 Asteroid::getPos()
{
	return Pos;
}

float Asteroid::getMass()
{
	return mass;
}

void Asteroid::SendBreakingTick()
{
	if (!dead)	isBreaking = true;
}

void Asteroid::Update()
{
	//Updating movement
	UpdatePos();

	//Updating res
	if (isBreaking)		UpdateBreaking();
	if (textureEffect.g == 0);//killed_by_player(other);

	isBreaking = false;
}

void Asteroid::RandomPos(int width, int heigh)
{
	Pos = { (float)GetRandomValue(0,width),(float)GetRandomValue(0,heigh) };
}

//void Asteroid::killed_by_player(Player& other)
//{
//	other.AddRes(resourses);
//	textureEffect = { 50,50,50,255 };
//}

void Asteroid::UpdatePos()
{
	UpdateVel();
	Pos = Vector2Add(Pos, Vector2Scale(Vel, GetFrameTime()));
	UpdateRotation();
}

void Asteroid::UpdateVel()
{
	Vel = Vector2Add(Vel, Vector2Scale(Ax, GetFrameTime()));
}

void Asteroid::UpdateRotation()
{
	AngleVel += AngleAx * GetFrameTime();

	rotation += AngleVel * GetFrameTime();
}

void Asteroid::GenerateTexture()
{
	//Colors
	Color col[2] = { GRAY,BLACK }, ColRes[RES_COUNT] = { {235,240,45,255},DARKGRAY,LIGHTGRAY,GOLD };
	//Res generating
	for (int i = 0; i < RES_COUNT; i++)		resourses[i] = GetRandomValue(0, radius / 4);

	//Randomly generate texture
	texture = LoadRenderTexture(2 * (MAX_ASTEROID_CURVE + radius), 2 * (MAX_ASTEROID_CURVE + radius));
	BeginTextureMode(texture);
	Vector2 PosText = { MAX_ASTEROID_CURVE + radius,MAX_ASTEROID_CURVE + radius };

	DrawCircleV(PosText, radius, GRAY);
	for (int i = 0; i < CURVES_COUNT; i++)
	{
		float Angle = GetRandomValue(0, 62830);
		DrawCircleV(Vector2Add(PosText, Vector2Scale({ cosf(Angle), sinf(Angle) }, radius)), GetRandomValue(MIN_ASTEROID_CURVE, MAX_ASTEROID_CURVE), col[GetRandomValue(0, 1)]);
	}

	//Drawing resourses
	for (int i = 0; i < RES_COUNT; i++)
	{
		for (int j = 0; j < resourses[i]; j++)
		{
			float Angle = GetRandomValue(0, 32000) / 10;
			DrawCircleV(Vector2Add(PosText, Vector2Scale({ cosf(Angle), sinf(Angle) }, GetRandomValue(0, 10 * radius) / static_cast<float>(10))), RES_SIZE, ColRes[i]);
		}
	}

	EndTextureMode();
}

void Asteroid::Draw()
{
	DrawTextureEx(texture.texture, routedPOS(), 0, 1, textureEffect);
}

Vector2 Asteroid::routedPOS()
{
	//Vector2 DRpos = { (radius + MAX_ASTEROID_CURVE) * cosf(-3 * PI / 4), (radius + MAX_ASTEROID_CURVE) * sinf(-3 * PI / 4) };

	//DRpos = Vector2Rotate(DRpos, rotation);

	return { Pos.x - (MAX_ASTEROID_CURVE + radius),Pos.y - (MAX_ASTEROID_CURVE + radius) };
}

void Asteroid::UpdateBreaking()
{
	textureEffect.g--;
	textureEffect.b--;
}
