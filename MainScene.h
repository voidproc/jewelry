#pragma once

#include "Actors.h"

enum class GameState
{
	MainGame,
	GameOver,
};

class MainScene : public App::Scene
{
public:
	MainScene(const InitData& init);
	void update() override;
	void draw() const override;

private:
	Actors actors_;
	Timer timerEnemySpawn_;
	int32 spawnCount_;
	int32 wave_;
	Timer timerReady_;
	Stopwatch time_;
	GameState state_;
	Stopwatch timeGameOver_;
	Stopwatch timeClear_;
	bool playedChiinAudio_;
	Timer timerAdditionalSpawn_;
	int32 hitEnemyCount_;
};
