#pragma once

#include "Kobushi.h"
#include "Enemy.h"
#include "Suishou.h"

struct Actors
{
	Kobushi kobushi;
	Array<Enemy> enemies;
	Suishou suishou;
};
