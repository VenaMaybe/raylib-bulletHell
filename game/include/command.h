#pragma once

/*
 *	From:
 *		https://gameprogrammingpatterns.com/command.html
 * 
 **/

#include "audioManager.h"

class Command {
public:
	virtual ~Command() = default;
	virtual void execute() = 0;
};

//
//	Maybe use later, smt to think about
//