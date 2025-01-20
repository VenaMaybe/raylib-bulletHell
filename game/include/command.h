#pragma once

// Represents a triggerable game command
class Command {
public:
	virtual ~Command() = default;

	// We want this to take in something
	virtual void execute() = 0;
};

//

class ShootCommand : public Command {
public:
	// 
	virtual void execute();
};

void ShootCommand::execute() {
	// Shoot() pew pew
}