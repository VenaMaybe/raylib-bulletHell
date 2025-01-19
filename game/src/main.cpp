#include "raylib.h"
#include "raymath.h"
#include "rlgl.h"
#include <iostream>
#include "entityManager.h"
#include "player.h"
#include "enemy.h"
#include "gun.h"
#include "gunBehaviors.h"
#include "bulletBehaviors.h"
#include "ammoBehaviors.h"

int main() {
	const int screenWidth = 800;
	const int screenHeight = 600;
	Vector2 screenRes = { (float)screenWidth, (float)screenHeight };

	// Initialize the window and set up raylib
	SetConfigFlags(FLAG_WINDOW_RESIZABLE);
	InitWindow(screenWidth, screenHeight, "Game");
	InitAudioDevice();
	SetTargetFPS(90);

	// Entity Manager
	EntityManager em;

	// create a player
	auto player = std::make_shared<Player>();	// should be moved to em

	// create a specific gun
	auto gunBehavior = std::make_unique<PistolBehavior>();
	auto bulletBehavior = std::make_unique<ZigzagBulletBehavior>();
	auto ammoBehavior = std::make_unique<StandardAmmoBehavior>(30, 30);
	Gun playerGun(
		std::move(gunBehavior),
		std::move(bulletBehavior), 
		std::move(ammoBehavior),
		player, 
		&em.getBullets()
	);

	em.setPlayer(player.get());
	em.setPlayerGun(&playerGun);
	em.initializeEntities();

	//
	//	Shader for trails
	//

	/* GOAL: Move all this to a rendering manager!!! */
	// Have a flag if something is to be rendered with a trail or not

	// Load the final grabber
	Shader trailShader = LoadShader(nullptr, "game/shaders/trailImage.fs");
		int bufferLoc_Image = GetShaderLocation(trailShader, "bufferA");
	Shader trailBufferA = LoadShader(nullptr, "game/shaders/trailBufferA.fs");

	Vector2 const resolutionScreen = { (float)screenWidth, (float)screenHeight };
	RenderTexture2D bufferA_Texture2D_Ping = LoadRenderTexture(resolutionScreen.x, resolutionScreen.y);
	RenderTexture2D bufferA_Texture2D_Pong = LoadRenderTexture(resolutionScreen.x, resolutionScreen.y);

	Image whiteImage = GenImageColor(resolutionScreen.x, resolutionScreen.y, ORANGE);
	Texture2D whiteTexture = LoadTextureFromImage(whiteImage);
	UnloadImage(whiteImage);

	// Ping pong buffer
	RenderTexture2D* srcTex = nullptr; // Source
	RenderTexture2D* dstTex = nullptr; // Destination

	int frame = 0;

	// Begin the frame
	while (!WindowShouldClose()) {
		float dt = GetFrameTime();
		em.updateEntities(dt); // Player, Gun, Bullet, Enemy

		if (frame % 2 == 0) {
			srcTex = &bufferA_Texture2D_Ping;
			dstTex = &bufferA_Texture2D_Pong;
		} else {
			srcTex = &bufferA_Texture2D_Pong;
			dstTex = &bufferA_Texture2D_Ping;
		}

		// Render the buffer
		BeginBlendMode(BLEND_ALPHA_PREMULTIPLY); // Blending mode so alpha doesn't get fucked
		BeginTextureMode(*dstTex);
		 	ClearBackground(BLANK);

			if(!IsMouseButtonDown(MOUSE_BUTTON_EXTRA)) { // For debugging
			BeginShaderMode(trailBufferA);	// Enable custom shader for next shapes
				// Feed it back into itself, it auto reads to bufferA
				DrawTexture(srcTex->texture, 0, 0, ORANGE);
			EndShaderMode(); }
			// Draw onto the destination so that they're all darkened evenly
			em.renderBullets();
			em.renderEnemies();
		EndTextureMode();
		EndBlendMode();

		// Draw
		BeginDrawing();
			ClearBackground(BLACK);

			DrawCircleV({200, 500}, 100, RED);

			BeginShaderMode(trailShader);
				SetShaderValueTexture(trailShader, bufferLoc_Image, dstTex->texture);
				// Texture the shader is getting drawn on
				DrawTexture(whiteTexture, 0, 0, ORANGE);
		 	EndShaderMode();

			em.renderPlayer();

			DrawFPS(10, 10);
		EndDrawing();
		frame++;
	}

	UnloadShader(trailShader);
	UnloadShader(trailBufferA);
	UnloadRenderTexture(bufferA_Texture2D_Ping);
	UnloadRenderTexture(bufferA_Texture2D_Pong);
	UnloadTexture(whiteTexture);

	CloseWindow(); // Close the window
	return 0;
}