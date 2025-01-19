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
	
	SetSoundPitch(soundToPlay, 1.f);
	PlaySound(soundToPlay);
} 

//
//
//

/*
class AudioManager {
public:
	void loadSounds();
	void playGunEx1();
private:
	Sound gunEx1;
};

inline void AudioManager::loadSounds() {
	gunEx1 = LoadSound("game/sounds/gunEx1.wav");
}

inline void AudioManager::playGunEx1() {
	PlaySound(gunEx1);
}
*/