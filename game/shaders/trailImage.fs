#version 460 core

// Input vertex attributes (from vertex shader)
in vec2 fragTexCoord; // Already normalized, aka uv
in vec4 fragColor;

// Input uniform values
uniform sampler2D texture0;
uniform vec4 colDiffuse;

// Output fragment color
out vec4 finalColor;

uniform sampler2D bufferA; // like shaderToy

// Main shader
void main() {
    // Normalized pixel coordinates (from 0 to 1)
    vec2 uv = fragTexCoord;
	uv.y *= -1.;

    // Output to screen
    vec4 bufferA = texture(bufferA, uv);

    finalColor = bufferA;

//	finalColor = vec4(uv.x, uv.y, 0., 1.);
//	finalColor = vec4(0., 0., 1., uv.x);
//	finalColor = vec4(bufferA.rgb, uv.x);
}