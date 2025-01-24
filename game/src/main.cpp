#include <iostream>
#include "raylib.h"
#include "raymath.h"
#include "rlgl.h"
#include "rlImGui.h"
#include "imgui.h"

#include "entityManager.h"
#include "settings.h"
#include "settingsRenderer.h"
#include "shaderBuffer.h"
#include "player.h"
#include "enemy.h"
#include "gun.h"
#include "gunBehaviors.h"
#include "bulletBehaviors.h"
#include "ammoBehaviors.h"
#include "bulletModifiers.h"
#include "gunEffects.h"

int main() {	
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
	Shader trailShader = LoadShader(nullptr, "shaders/trailImage.fs");
		int bufferLoc_Image = GetShaderLocation(trailShader, "bufferA");
	Shader trailBufferA = LoadShader(nullptr, "shaders/trailBufferA.fs");

	ShaderBuffer bufferA;
	bufferA.init();

	Image whiteImage = GenImageColor(bufferA.getSize().width, bufferA.getSize().height, ORANGE);
	Texture2D whiteTexture = LoadTextureFromImage(whiteImage);
	UnloadImage(whiteImage);

	// Begin the frame
	while (!WindowShouldClose()) {
		if (IsWindowResized()) {
			std::cout << "Window Resizing" << std::endl;
			// Make sure to update this before referencing it's size!!!
			bufferA.checkAndHandleWindowResizing();
			// Recreate the white texture the shader is getting drawn to
			//		Todo: move this into shader manager when it's done
			Image whiteImageNew = GenImageColor(bufferA.getSize().width, bufferA.getSize().height, ORANGE);
			Texture2D whiteTextureNew = LoadTextureFromImage(whiteImageNew);
			UnloadImage(whiteImageNew);

			UnloadTexture(whiteTexture);
			whiteTexture = whiteTextureNew;
		}


		float dt = GetFrameTime() * settings.getPhysicsSpeed();
		em.updateEntities(dt); // Player, Gun, Bullet, Enemy

		bufferA.update();
		bufferA.beginBufferMode();
		 	ClearBackground(BLANK);

			if(!IsMouseButtonDown(MOUSE_BUTTON_EXTRA)) { // For debugging
			BeginShaderMode(trailBufferA);	// Enable custom shader for next shapes
				// Feed it back into itself, it auto reads to bufferA
				DrawTexture(bufferA.getPriorFrameTexture(), 0, 0, ORANGE);
			EndShaderMode(); }

			// Draw onto the destination so that they're all darkened evenly
			em.renderBullets();
			em.renderEnemies();
		bufferA.endBufferMode();

		// Draw
		BeginDrawing();
			ClearBackground(BLACK);
			//DrawRectangleLines(GetRenderWidth()*0.3, GetRenderHeight()*0.3, GetRenderWidth()*0.35, GetRenderHeight()*0.35, RAYWHITE  );
			DrawCircleV({200, 500}, 100, RED);
			
			BeginShaderMode(trailShader);
				SetShaderValueTexture(trailShader, bufferLoc_Image, bufferA.getCurrentFrameTexture());
				// Texture the shader is getting drawn on
				DrawTexture(whiteTexture, 0, 0, ORANGE);
		 	EndShaderMode();

			em.renderPlayer();

			// Renders all the ImGui settings
			renderSettingsUI(settings);

			DrawFPS(10, 10);
		EndDrawing();
	}

	UnloadShader(trailShader);
	UnloadShader(trailBufferA);
	bufferA.unloadBuffer();
	UnloadTexture(whiteTexture);

	rlImGuiShutdown(); // Cleanup
	CloseWindow(); // Close the window
	return 0;
}