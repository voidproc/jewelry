#pragma once

class Enemy;

class Kobushi
{
public:
	Kobushi();

	void update();

	void draw() const;

	Optional<RectF> collision() const;

	void hit(Enemy& enemy);

private:
	Timer timerAttack_;
	Vec2 pos_;
	double attackAngle_;
};

