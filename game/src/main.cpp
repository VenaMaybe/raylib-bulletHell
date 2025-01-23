#include <iostream>
#include "raylib.h"
#include "raymath.h"
#include "rlgl.h"
#include "rlImGui.h"
#include "imgui.h"

#include "entityManager.h"
#include "settings.h"
#include "settingsRenderer.h"
#include "player.h"
#include "enemy.h"
#include "gun.h"
#include "gunBehaviors.h"
#include "bulletBehaviors.h"
#include "ammoBehaviors.h"
#include "bulletModifiers.h"
#include "gunEffects.h"

int main() {
	// Move to settings later
	
	// Settings singleton
	Settings& settings = Settings::getInstance();

	// Initialize the window and set up raylib
	SetConfigFlags(FLAG_WINDOW_RESIZABLE);
	InitWindow(settings.getScreenSize().width, settings.getScreenSize().height, "Game");
	InitAudioDevice();
	SetTargetFPS(90);

	// Initialize rlImGui
	rlImGuiSetup(true);

	// Entity Manager
	EntityManager em;

	// create a player
	auto player = std::make_shared<Player>();	// should be moved to em

	// create a specific gun
	auto bulletBehavior = std::make_unique<StraightBulletBehavior>(2000.f);
	auto ammoBehavior = std::make_unique<StandardAmmoBehavior>(444, 444);

	auto gunBehavior = std::make_unique<SingleShotShooting>();
	gunBehavior->addBulletModifier(std::make_unique<AddOwnerVelocityModifier>(0.15f));
	gunBehavior->addEffect(std::make_unique<BloomOnHitEffect>());
	gunBehavior->addEffect(std::make_unique<RecoilEffect>(1.f));
	gunBehavior->addEffect(std::make_unique<SoundOnShootEffect>());

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
	em.giveEnemiesAGun();

	//
	//	Shader for trails
	//

	// GOAL: Move all this to a rendering manager!!!
	// Have a flag if something is to be rendered with a trail or not

	// Load the final grabber
	Shader trailShader = LoadShader(nullptr, "game/shaders/trailImage.fs");
		int bufferLoc_Image = GetShaderLocation(trailShader, "bufferA");
	Shader trailBufferA = LoadShader(nullptr, "game/shaders/trailBufferA.fs");

	WidthHeight const renderTexBufferSize = { settings.getScreenSize().width, settings.getScreenSize().height };
	RenderTexture2D bufferA_Texture2D_Ping = LoadRenderTexture(renderTexBufferSize.width, renderTexBufferSize.height);
	RenderTexture2D bufferA_Texture2D_Pong = LoadRenderTexture(renderTexBufferSize.width, renderTexBufferSize.height);

	Image whiteImage = GenImageColor(renderTexBufferSize.width, renderTexBufferSize.height, ORANGE);
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
			//DrawRectangleLines(GetRenderWidth()*0.3, GetRenderHeight()*0.3, GetRenderWidth()*0.35, GetRenderHeight()*0.35, RAYWHITE  );
			DrawCircleV({200, 500}, 100, RED);
			BeginShaderMode(trailShader);
				SetShaderValueTexture(trailShader, bufferLoc_Image, dstTex->texture);
				// Texture the shader is getting drawn on
				DrawTexture(whiteTexture, 0, 0, ORANGE);
		 	EndShaderMode();

			em.renderPlayer();

			renderSettingsUI(settings);


			DrawFPS(10, 10);
		EndDrawing();
		frame++;
	}

	UnloadShader(trailShader);
	UnloadShader(trailBufferA);
	UnloadRenderTexture(bufferA_Texture2D_Ping);
	UnloadRenderTexture(bufferA_Texture2D_Pong);
	UnloadTexture(whiteTexture);

	rlImGuiShutdown(); // Cleanup
	CloseWindow(); // Close the window
	return 0;
}