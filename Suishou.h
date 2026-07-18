#pragma once

class Enemy;
class Kobushi;

class Suishou
{
public:
	Suishou();
	Suishou(const Vec2& pos);

	void update();

	void draw() const;

	Optional<Circle> collision() const;

	void hit(Enemy& enemy);
	void hit(Kobushi& kobushi);

	Vec2 pos() const;

private:
	void hit_();

	Vec2 pos_;
	Timer timerHit_;
	double life_;
};
