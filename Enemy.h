#pragma once

class Kobushi;
class Suishou;

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
	void hit(Suishou& suishou);

	bool isOffscreen() const;

private:
	void hit_();

	Actors* actors_;
	Vec2 pos_;
	bool mirror_;
	double speed_;
	Vec2 moveDead_;
	EnemyState state_;
	Stopwatch timeHit_;
};

