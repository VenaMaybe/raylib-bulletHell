#pragma once
#include "IShootBehaviour.h"


class AutoShootBehaviour : public IShootBehaviour {
public:
	AutoShootBehaviour(){}
    bool isAuto() const override;
};

class ManualShootBehaviour : public IShootBehaviour { 
public:
    ManualShootBehaviour(){}
    bool isAuto() const override;
};