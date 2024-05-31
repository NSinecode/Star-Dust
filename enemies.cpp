#include "enemies.h"

Asteroid::Asteroid()
{
	textureEffect = WHITE;
	Pos = { 300,200 };
	Vel = { (float)GetRandomValue(MIN_AST_VEL,MAX_AST_VEL),(float)GetRandomValue(MIN_AST_VEL,MAX_AST_VEL) };
	Ax = { 0,0 };
	radius = GetRandomValue(MIN_ASTEROID_R, MAX_ASTEROID_R);
	rotation = AngleVel = AngleAx = 0;
	AngleAx = GetRandomValue(-MAX_ASTEROID_AAX*100, MAX_ASTEROID_AAX*100)/100;

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
	Pos = { (float)GetRandomValue(-width,width),(float)GetRandomValue(-heigh,heigh) };
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

	Texture2D Perlin = LoadTextureFromImage(GenImagePerlinNoise(2 * (MAX_ASTEROID_CURVE + radius), 2 * (MAX_ASTEROID_CURVE + radius), 0, 0, 1));

	//Randomly generate texture
	texture = LoadRenderTexture(2 * (MAX_ASTEROID_CURVE + radius), 2 * (MAX_ASTEROID_CURVE + radius));
	BeginTextureMode(texture);
	Vector2 PosText = { MAX_ASTEROID_CURVE + radius,MAX_ASTEROID_CURVE + radius };

	DrawCircleV(PosText, radius, GRAY);
	DrawTextureV(Perlin, { 0,0 }, { 130,130,130,160 });
	/*for (int i = 0; i < CURVES_COUNT; i++)
	{
		float Angle = GetRandomValue(0, 62830);
		DrawCircleV(Vector2Add(PosText, Vector2Scale({ cosf(Angle), sinf(Angle) }, radius)), GetRandomValue(MIN_ASTEROID_CURVE, MAX_ASTEROID_CURVE), col[GetRandomValue(0, 1)]);
	}*/

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

	UnloadTexture(Perlin);
}

void Asteroid::Draw()
{
	//DrawTextureV(texture.texture, Pos, textureEffect);
	Rectangle sourceREC = { 0,0,texture.texture.width,texture.texture.height };
	//Rectangle destRec = { , screenHeight / 2.0f, frameWidth * 2.0f, frameHeight * 2.0f };
	DrawTexturePro(texture.texture, sourceREC, { Pos.x,Pos.y,(float)texture.texture.width,(float)texture.texture.height }, { MAX_ASTEROID_CURVE + radius,MAX_ASTEROID_CURVE + radius }, rotation, textureEffect);
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
