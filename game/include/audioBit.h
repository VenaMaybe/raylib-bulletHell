#pragma once

#include "raylib.h"
#include <random>
#include <vector>
class AudioBit {
public:
	~AudioBit();
	AudioBit(const char* audioFile);
	void playSound();
private:
	Sound soundToPlay;
};

inline AudioBit::AudioBit(const char* audioFile) {
	soundToPlay = LoadSound(audioFile);
}

inline AudioBit::~AudioBit() {
	// mindbogglingly horrible but fix later with smart pointers
	UnloadSound(soundToPlay);
}

inline void AudioBit::playSound() {
	int random = GetRandomValue(0, 100);
	float val = (random / 500.f) + 0.9f;
	SetSoundPitch(soundToPlay, 1.0f + val);
	PlaySound(soundToPlay);
} 