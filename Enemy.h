#pragma once

class Kobushi;

enum class EnemyState
{
	Active,
	Dead,
};

struct Actors;

class Enemy
{
public:
	Enemy(const Vec2& pos, Actors* actors);

	void update();

	void draw() const;

	Optional<RectF> collision() const;

	void hit(Kobushi& kobushi);

	bool isOffscreen() const;

private:
	Actors* actors_;
	Vec2 pos_;
	double speed_;
	Vec2 moveDead_;
	EnemyState state_;
	Stopwatch timeHit_;
};

