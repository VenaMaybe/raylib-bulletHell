#version 460 core

// Constants
#define TRAIL_LENGTH 0.01 // Larger = shorter

// Input vertex attributes (from vertex shader)
in vec2 fragTexCoord; // Already normalized, aka uv
in vec4 fragColor;

// Input uniform values
uniform sampler2D bufferA;
uniform vec4 colDiffuse;

// Output fragment color
out vec4 finalColor;

void main() {
	vec2 uv = fragTexCoord;
	uv.y *= -1.;

	// Get the prior frame
	vec4 prior = texture(bufferA, uv);

	// This is linear
	prior.a -= TRAIL_LENGTH;

	// Just make sure it doesn't go negative since impossible
	prior.a = clamp(prior.a, 0., 1.);

	// Output to itself
	finalColor = vec4(prior.rgb, prior.a);
}