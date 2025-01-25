	Todo:

Muzzle Shooting		- Done, scuffed-ish
Use WASD			- Done
Add vel to bullets	- Done with scuffed oop, no ECS sobbing
Shader for trails	- Done
Recoil				- Done
Added sound effects	- Done, scuffed destructor
Fix sound effects	- Done, made entity manager use smart pointers
Fix trail gaps		- Done, by filling with spline between pts
Fix Gun Structure	- Done, Strategy pattern
Bullet Magazine		- Done, Redesigned to be modular
Raylib ImGui 		- Done, from: https://github.com/raylib-extras/rlImGui
Settings singleton	- Done
FIX: -> Window Resizing / ShaderTextureResizing		- Done


Shader Manager		- WIP
Clean up main		- WIP


Abstract stuff into IGunBehavior
Make automatic gun behavior

Make random pixels in trail shader go to alpha 0!!!! (Like image Gev sent)
Make bullet's percentOfOwnerVelocity depend on speed of bullet too

FIX: -> Enemy spawn timers don't seem to be scaled by dt
FIX: -> Gun timing not based on dt so doesn't slow correctly (For both player and enemies)
FIX: -> No sound playing on final enemy hit
FIX: -> Drawing screen down 


	Todo Jaguar:
Enemies Shooting Things	- Done
Enemies Hp + Dying		- Done
Player Hp				- Done


	Vena Thoughts:

Dash
Train cars
Interesting power up circle / level up circle that teleports around and you have to go to

Maybe add Gamma for real time audio mods/synthesis


Gun visual effects
Triggered when:
	Bullet is shot
	as bullet is being rendered
	when bullet hits



>
	Bird Thoughts:

Change color of enemies depending on "environment" or how many you killed










```
Cool:
Texture2D whiteTexture;
	// Citrine scope trick
	{
		Image whiteImage = GenImageColor(bufferA.getSize().width, bufferA.getSize().height, ORANGE);
		whiteTexture = LoadTextureFromImage(whiteImage);
		UnloadImage(whiteImage);
	}
```