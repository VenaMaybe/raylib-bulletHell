#version 460 core

// Constants
#define TRAIL_LENGTH 0.03 // Larger = shorter

// Input vertex attributes (from vertex shader)
in vec2 fragTexCoord; // Already normalized, aka uv
in vec4 fragColor;

// Input uniform values
uniform sampler2D texture0;
uniform vec4 colDiffuse;

// Output fragment color
out vec4 finalColor;

uniform sampler2D bufferA;

void main() {
	vec2 uv = fragTexCoord;
	uv.y *= -1.;

	// Get the prior frame
	vec4 prior = texture(bufferA, uv);
	// Get the current frame
	vec4 current = texture(texture0, uv);

	current.rgba = prior.rgba;
	
	// This is linear
	current.a -= TRAIL_LENGTH;

	// Just make sure it doesn't go negative since impossible
	current.a = clamp(current.a, 0., 1.);

	// Output to itself
	finalColor = vec4(current.rgb, current.a);
}

//
//	Ignore everything below
//

/* Random functions useful for later

// not being used rn, from: https://www.reddit.com/r/opengl/comments/6nghtj/glsl_mix_implementation_incorrect/
vec3 srgb_to_linear(vec3 color) {
  // note: some people use an approximation for the gamma of 2.0, for efficiency, but 2.2 is more correct
	return pow(color, vec3(2.2));
}

vec3 linear_to_srgb(vec3 color) {
  // note: if using gamma of 2.0, instead can use 0.5 as the value here
	return pow(color, vec3(1.0/2.2));
}

*/

/* Old pre Cornus

void main() {
	vec2 uv = fragTexCoord;
	uv.y *= -1.;s

	// Get the prior frame
	vec4 prior = texture(bufferA, uv);
	// Get the current frame
	vec4 current = texture(texture0, uv);

	current.rgb = mix(current.rgb, prior.rgb, 0.99);

//	current.rgba = mix(current.rgba, prior.rgba, 0.99); // Lerp without linear component

	// Mix the current frame with the prior frame
//	current.rgb = mix(current.rgb, prior.rgb, TRAIL_LENGTH); // Lerp without linear component
//	current.a = mix(current.a, prior.a, 0.9); // Lerp without linear component


//	// Threshold close to black
//	if (all(lessThan(abs(current.rgb - prior.rgb), vec3(0.005))))
//    	current = texture(texture0, uv);


	// Threshold close to black
//	if (prior.a < 0.5)
//    	current.rgb = vec3(0., 0., 1.); //= texture(texture0, uv);

	// Output to itself
	finalColor = vec4(current);
}

*/

/* Old: Cool

void main() {
	vec2 uv = fragTexCoord;
	uv.y *= -1.;

	// Get the prior frame
	vec4 prior = texture(bufferA, uv);
	// Get the current frame
	vec4 current = texture(texture0, uv);

	vec4 final;

	final.rgb = mix(current.rgb, prior.rgb, 0.99);
//	final.a = prior.a;

//	current.rgba = mix(current.rgba, prior.rgba, 0.99); // Lerp without linear component

	// Mix the current frame with the prior frame
//	current.rgb = mix(current.rgb, prior.rgb, TRAIL_LENGTH); // Lerp without linear component
//	current.a = mix(current.a, prior.a, 0.9); // Lerp without linear component


//	// Threshold close to black
//	if (all(lessThan(abs(current.rgb - prior.rgb), vec3(0.005))))
//    	current = texture(texture0, uv);


	// Threshold close to black
//	if (prior.a < 0.5)
//    	current.rgb = vec3(0., 0., 1.); //= texture(texture0, uv);

	// Output to itself
	finalColor = vec4(final);
}

*/

/* Old but cool:

void main() {
	vec2 uv = fragTexCoord;
	uv.y *= -1.;
	vec2 tuv = fragTexCoord;

	vec3 prior = texture(bufferA, uv).rgb;
	
	// Get the current frame
	vec3 current = texture(texture0, uv).rgb;

	// Mix the current frame with the prior frame
	current = mix(current, prior, .99); // Lerp without linear component

	// Threshold close to black
	if (all(lessThan(abs(current - prior), vec3(0.005))))
    	current = texture(texture0, uv).rgb;

	// Output to itself
	finalColor = vec4(vec3(current), 1.);
}

*/

/* Old, permanently doesn't fade:

	// Decrease the alpha of the old color
	prior.a *= 0.9; // fade out

	// Then just “overlay” the current color
	vec4 final = prior + current; // or do an additive, or use some blend mode

*/

/* Old:


void main() {
	vec2 uv = fragTexCoord;
	uv.y *= -1.;
	vec2 tuv = fragTexCoord;

	vec3 prior = texture(bufferA, uv).rgb;
	
	// Set it to black
//	vec3 col = vec3(0., 1., 1.); 
	// Get the current frame
	vec3 col = texture(texture0, uv).rgb;

	// Mix the current frame with the prior frames

	col = mix(col, prior, .9); // Lerp without linear component
//	col = mix(col, prior, .9) - vec3(0.01); // Lerp with;
//	col = col - vec3(0.01);

//	if (all(lessThan(abs(col - prior), vec3(0.01)))) // Threshold close to black
//    	col = texture(texture0, uv).rgb;

	// Output to itself
	finalColor = vec4(vec3(col), 1.);
//	finalColor = vec4(uv.x, uv.y, 0., 1.);
//	finalColor = vec4(vec3(0., 1., 1.), 1.);
}

*/