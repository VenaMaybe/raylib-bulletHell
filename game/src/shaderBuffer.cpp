#include "shaderBuffer.h"
#include "settings.h"

ShaderBuffer::ShaderBuffer()
	: frame(0), srcTex(nullptr), dstTex(nullptr), renderTexBufferSize(Settings::getInstance().getScreenSize())
{}

void ShaderBuffer::init() {
	bufferA_Texture2D_Ping = LoadRenderTexture(renderTexBufferSize.width, renderTexBufferSize.height);
	bufferA_Texture2D_Pong = LoadRenderTexture(renderTexBufferSize.width, renderTexBufferSize.height);
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
	unloadBuffer();
	setSize(s);
	init();
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
	BeginBlendMode(BLEND_ALPHA_PREMULTIPLY); // Blending mode so alpha doesn't get fucked
	BeginTextureMode(*dstTex);
}

void ShaderBuffer::endBufferMode() {
	EndTextureMode();
	EndBlendMode();
}