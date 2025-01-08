#include "raylib.h"
#include "raymath.h"
#include "rlgl.h"

#include <iostream>
#include "player.h"
#include "enemy.h"
#include "gun.h"

int main() {
	const int screenWidth = 800;
    const int screenHeight = 600;
	Vector2 screenRes = { (float)screenWidth, (float)screenHeight };

	// Initialize the window and set up raylib
	SetConfigFlags(FLAG_WINDOW_RESIZABLE);
	InitWindow(screenWidth, screenHeight, "Game");
	SetTargetFPS(90);

	// Create a vector of enemies
    std::vector<Enemy> enemies = {
        Enemy({100, 100}, {50, 50}, 20, RED),
        Enemy({200, 200}, {50, 50}, 20, BLUE),
        Enemy({300, 300}, {50, 50}, 20, GREEN)
    };

	// create a player
	auto player = std::make_shared<Player>();

	GunSpecificEx gunSpecific_Pistol;
	Gun playerGun(
		[&gunSpecific_Pistol](Gun& gun) { gunSpecific_Pistol.shoot(gun); },
	/* Depends on this pointer & specific instance
	   gunSpecific,shoot hasa a type pointer-to-member-function
	   and thus needs an instance.

	   We wrap it in a lambda to supply the instance,
	   The lambda has the correct signature: void(Gun&)
	   thus it is assigned to the callback
	*/
		player
	);

	// Set all enemies to focus the player
	for (Enemy& enemy : enemies) {
		enemy.focusPlayer(player.get());
	}

	//
	//	Shader for trails
	//

	/* GOAL: Move all this to a rendering manager!!!
	*/

	// Load the final grabber
	Shader trailShader = LoadShader(nullptr, "game/shaders/trailImage.fs");
		int bufferLoc_Image = GetShaderLocation(trailShader, "bufferA");

	Shader trailBufferA = LoadShader(nullptr, "game/shaders/trailBufferA.fs");
		int selfLoc_BufferA = GetShaderLocation(trailBufferA, "bufferA");

	int frame = 0;
	Vector2 const resolutionScreen = { (float)screenWidth, (float)screenHeight };
	RenderTexture2D bufferA_Texture2D_Ping = LoadRenderTexture(resolutionScreen.x, resolutionScreen.y);
	RenderTexture2D bufferA_Texture2D_Pong = LoadRenderTexture(resolutionScreen.x, resolutionScreen.y);
	RenderTexture2D inputToTrailShader = LoadRenderTexture(resolutionScreen.x, resolutionScreen.y);

	Image whiteImage = GenImageColor(resolutionScreen.x, resolutionScreen.y, ORANGE);
	Texture2D whiteTexture = LoadTextureFromImage(whiteImage);

	UnloadImage(whiteImage);

	// Begin the frame
	while (!WindowShouldClose()) {
		float dt = GetFrameTime();

		player.get()->update(dt);	
		playerGun.update(dt);	// Move this to the end of the loop for a cool gun wiggle

		RenderTexture2D srcTex;
		RenderTexture2D dstTex; // Destination

		if (frame % 2 == 0) {
			srcTex = bufferA_Texture2D_Ping;
			dstTex = bufferA_Texture2D_Pong;
		} else {
			srcTex = bufferA_Texture2D_Pong;
			dstTex = bufferA_Texture2D_Ping;
		}

		BeginTextureMode(inputToTrailShader);
			ClearBackground(BLANK);
			DrawCircleV({200, 200}, 100, RED);
			// You can draw stuff in here
		EndTextureMode();

		// Render the buffer
		BeginTextureMode(dstTex);
		 	ClearBackground(BLACK);

			if(!IsMouseButtonDown(MOUSE_BUTTON_EXTRA)) { // For debugging

			BeginShaderMode(trailBufferA);	// Enable custom shader for next shapes
				// Feed it back into itself
				SetShaderValueTexture(trailBufferA, selfLoc_BufferA, srcTex.texture);

				// Actually orange lol
				DrawTexture(inputToTrailShader.texture, 0, 0, WHITE);
			EndShaderMode();

			}

			// Draw after so that they're all darkened evenly
			playerGun.renderBullets();
		EndTextureMode();


		// Draw
		BeginDrawing();
			ClearBackground(BLACK);

			BeginShaderMode(trailShader);
				SetShaderValueTexture(trailShader, bufferLoc_Image, dstTex.texture);
				// Texture is getting drawn on
				DrawTexture(whiteTexture, 0, 0, WHITE);

		 	EndShaderMode();

			player.get()->render();
			playerGun.render();

//			playerGun.renderBullets();


//			player.get()->render();

//			for (Enemy& enemy : enemies) {
//				enemy.Update(dt);
//				enemy.Draw();
//			}

			DrawFPS(10, 10);
		EndDrawing();


		frame++;
	}

	CloseWindow(); // Close the window
	return 0;
}