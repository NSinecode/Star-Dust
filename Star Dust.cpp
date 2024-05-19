#include <string>

#include "raylib.h"
#include "raymath.h"
#include "player.h"
#include "enemies.h"
#include "SSystem.h"

#define DEBUG

#define HUB_SIZE		GetScreenHeight() / 36

#define ASTEROID_COUNT	100

#define START			0
#define GAMEHUB			1

#define MAP_SZE			10000
#define STARS_COUNT		3000
#define MIN_BGSTAR_SIZE	1
#define MAX_BGSTAR_SIZE	4

int main()
{
	const int ScreenWidth = GetMonitorWidth(GetCurrentMonitor());
	const int ScreenHeight = GetMonitorHeight(GetCurrentMonitor());

	//Create window
	InitWindow(ScreenWidth, ScreenHeight, "Star dust");

	SetWindowPosition(0, HUB_SIZE);

	//Setup camera
	Camera2D observer;
	observer.offset = { (float)GetScreenWidth() / 2,(float)GetScreenHeight() / 2 };
	observer.rotation = 0;
	observer.target = { 0,0 };
	observer.zoom = 1;

	//Init game scene
	int scene = GAMEHUB;

	//Player initialisaton
	Player main_player;

	//Creating background
	RenderTexture BackGroundR = LoadRenderTexture(2 * GetScreenWidth() + MAP_SZE, 2 * GetScreenHeight() + MAP_SZE);

	BeginTextureMode(BackGroundR);

	ClearBackground(BLACK);
	for (int i = 0; i < STARS_COUNT; i++)
		DrawCircle(GetRandomValue(0, BackGroundR.texture.width), GetRandomValue(0, BackGroundR.texture.height), GetRandomValue(MIN_BGSTAR_SIZE, MAX_BGSTAR_SIZE), { 230,230,255,255 });
	DrawCircleLines(BackGroundR.texture.width / 2, BackGroundR.texture.height / 2, MAP_SZE / 2, RED);

	EndTextureMode();

	//TEsting asteroid
	SolarSystem testSystem;

	for (int i = 0; i < ASTEROID_COUNT; i++)
	{
		testSystem.asteroids.push_back({});
		testSystem.asteroids[i].GenerateTexture();

		testSystem.asteroids[i].RandomPos(2 * GetScreenWidth() + MAP_SZE, 2 * GetScreenHeight() + MAP_SZE);
	}



	SetTargetFPS(144);

	while (!WindowShouldClose())
	{
		if (scene == START)
		{

		}
		else if (scene == GAMEHUB)
		{
			UpdatePlayer_n_System(testSystem, main_player);

			if (!CheckCollisionCircles({ 0,0 }, MAP_SZE / 2, main_player.getPos(), SHIELD_SIZE))	main_player.ReturnHome();

			observer.target = main_player.getPos();

			//Returning him
#ifdef DEBUG
			if (IsKeyPressed(KEY_R)) main_player.ReturnHome();
#endif // DEBUG

			if (IsKeyDown(KEY_SPACE))	testSystem.asteroids[0].SendBreakingTick();

			//testAst.Update();

			BeginDrawing();

			BeginMode2D(observer);

			ClearBackground(BLACK);
			DrawTexture(BackGroundR.texture, -BackGroundR.texture.width / 2, -BackGroundR.texture.height / 2, WHITE);

			for (int i = 0; i < testSystem.asteroids.size(); i++)	testSystem.asteroids[i].Draw();
			//DrawCircleV(testSystem.asteroids[0].getPos(), 10, BLUE);

			main_player.Draw();

			//DrawCircle(0, 0, 8, GREEN);

			//DrawTriangle({ 40,0 }, { -20,-34.64}, { -20,34.64 }, RED);

			EndMode2D();

			DrawFPS(10, HUB_SIZE);
			DrawText(std::to_string(main_player.getRotation()).c_str(), 10, HUB_SIZE * 2, HUB_SIZE * 2 / 3, DARKGREEN);

			DrawText(std::to_string(testSystem.asteroids[0].getPos().x).c_str(), 10, HUB_SIZE * 3, HUB_SIZE * 2 / 3, DARKGREEN);
			DrawText(std::to_string(testSystem.asteroids[0].getPos().y).c_str(), 10, HUB_SIZE * 4, HUB_SIZE * 2 / 3, DARKGREEN);

			EndDrawing();
		}
	}

	UnloadRenderTexture(BackGroundR);

	CloseWindow();

}