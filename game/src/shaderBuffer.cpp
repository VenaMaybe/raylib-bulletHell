#include "shaderBuffer.h"
#include "settings.h"

ShaderBuffer::ShaderBuffer()
	: frame(0), srcTex(nullptr), dstTex(nullptr), renderTexBufferSize(Settings::getInstance().getScreenSize())
{}

void ShaderBuffer::init() {
	bufferA_Texture2D_Ping = LoadRenderTexture(renderTexBufferSize.width, renderTexBufferSize.height);
	bufferA_Texture2D_Pong = LoadRenderTexture(renderTexBufferSize.width, renderTexBufferSize.height);
	if (bufferA_Texture2D_Ping.id == 0 || bufferA_Texture2D_Pong.id == 0) {
		throw std::runtime_error("Failed to load render textures");
	}
}

void ShaderBuffer::checkAndHandleWindowResizing() {
	reinit({GetScreenWidth(), GetScreenHeight()});
}

void ShaderBuffer::update() {
	if (frame % 2 == 0) {
		srcTex = &bufferA_Texture2D_Ping;
		dstTex = &bufferA_Texture2D_Pong;
	} else {
		srcTex = &bufferA_Texture2D_Pong;
		dstTex = &bufferA_Texture2D_Ping;
	}

	frame++;
}

void ShaderBuffer::reinit(ScreenSize s) {
	// To prevent glitching, we need to save the prior frame before resizing
	Image priorFrameSave = { 0 };
	if (srcTex != nullptr) {
		priorFrameSave = LoadImageFromTexture(srcTex->texture);
	}

	// Now we safely unload
	unloadBuffer();

	// Resize the buffers with the new screen size
	setSize(s);
	init();

	frame = 0;
	srcTex = &bufferA_Texture2D_Ping;
	dstTex = &bufferA_Texture2D_Pong;

	if (priorFrameSave.data != nullptr) {
		ImageResizeCanvas(&priorFrameSave, s.width, s.height, 0, 0, BLANK);

		UpdateTexture(srcTex->texture, priorFrameSave.data);
		UnloadImage(priorFrameSave);
	}
}

void ShaderBuffer::unloadBuffer() {
	UnloadRenderTexture(bufferA_Texture2D_Ping);
	UnloadRenderTexture(bufferA_Texture2D_Pong);
}

void ShaderBuffer::setSize(ScreenSize s) { renderTexBufferSize = s; }
WidthHeight ShaderBuffer::getSize() const { return renderTexBufferSize; }
Texture2D ShaderBuffer::getPriorFrameTexture() const { return srcTex->texture; }
Texture2D ShaderBuffer::getCurrentFrameTexture() const { return dstTex->texture; }


void ShaderBuffer::beginBufferMode(BlendMode blendMode) {
	BeginBlendMode(blendMode); // Blending mode so alpha doesn't get fucked
	BeginTextureMode(*dstTex);
}

void ShaderBuffer::endBufferMode() {
	EndTextureMode();
	EndBlendMode();
}