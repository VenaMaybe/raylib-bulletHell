#pragma once

#include "com_comps.h"
#include <stdexcept>


// This will be a centralized setting and debug class [ Not thread safe, no mutex ]
// Singleton moment *gulp*
class Settings {
private:
	/*	Some settings can be stored in settings itself
	 *
	***/
	const int screenWidth = 1200;
	const int screenHeight = 1000;
	const ScreenSize screenRes = { screenWidth, screenHeight };

	/*	But for most, rather than holding the value itself in the singleton, the singleton can instead be the manager
	 *		of pointers to values to be "watched" which have been created elsewhere.
	 *
	***/
	int* _playerHp = nullptr;

public:
	// Simple Settings Getters
	ScreenSize getScreenSize() const { return screenRes; }

	// Da reference getters, expects whatever to be gotten to be initalized correctly
	int& getPlayerHp() {
		if (_playerHp == nullptr) {
			throw std::runtime_error("Player Hp pointer is null stupid");
		} 
		return *_playerHp;
	}

	// Call in constructor of holding class
	void setPlayerHpPointer(int* hpPtr) { _playerHp = hpPtr; }

	// Accessing the single instance
	static Settings& getInstance() { // Apparently maybe static is thread safe?
		static Settings instance;
		return instance;
	}

	// Delete the copy and assignment constructors so no oopsies 
	Settings(Settings &other) = delete; // Non-cloneable
	void operator=(const Settings&) = delete; // Non-assignable

private:
	Settings() = default; // Private constructor so no construction possibility with new
	~Settings() = default; // Private destructor so no delete
};

/* Make it thread safe later from:
 *	https://refactoring.guru/design-patterns/singleton/cpp/example#example-1
 *
 * Also, make a general templated version of this maybe in a future project
 *
***/