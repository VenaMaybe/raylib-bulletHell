#pragma once
#include "raylib.h"
#include "com_comps.h"

class ShaderBuffer {
public:
	ShaderBuffer();
	void init();								// Call this to initialize textures to be drawn
	void checkAndHandleWindowResizing();		// Call update to update if resized
	void update();								// Updates by swapping the frames
	void unloadBuffer();						// Unloads both textures
	void setSize(ScreenSize s);					// Sets the buffer size
	WidthHeight getSize() const;				// Returns the size of the buffer
	Texture2D getPriorFrameTexture() const; 	// Returns a Texture2D of the prior frame
	Texture2D getCurrentFrameTexture() const; 	// Return a Texture2D of the current frame

	void beginBufferMode(BlendMode blendMode = BLEND_ALPHA_PREMULTIPLY); // Default blend mode
	void endBufferMode();

private:
	size_t frame;							// Keep track of the frame
	void reinit(ScreenSize s);				// Call this when reinitializing due to a new size

	/*	The idea is some effects want the previous frame's information. 
	 *	By alternating which texture is read from and which one is written to,
	 *		avoid overwriting data we still need to read (double buffering).
	 *
	***/
	WidthHeight renderTexBufferSize; //= { settings.getScreenSize().width, settings.getScreenSize().height };
	RenderTexture2D bufferA_Texture2D_Ping; //= LoadRenderTexture(renderTexBufferSize.width, renderTexBufferSize.height);
	RenderTexture2D bufferA_Texture2D_Pong; //= LoadRenderTexture(renderTexBufferSize.width, renderTexBufferSize.height);

	/*	Each frame, we want to decide which texture will be the source (prior
	 *		frame data that was our storage) and which will be the destination
	 *		(frame currently being drawn)
	 *
	***/
	RenderTexture2D* srcTex; // Source ptr
	RenderTexture2D* dstTex; // Destination ptr
};