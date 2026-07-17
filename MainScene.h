#pragma once

#include "Actors.h"

class MainScene : public App::Scene
{
public:
	MainScene(const InitData& init);
	void update() override;
	void draw() const override;

private:
	Actors actors_;
	Timer timerEnemySpawn_;
};
