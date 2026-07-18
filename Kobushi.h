#pragma once

class Enemy;

class Kobushi
{
public:
	Kobushi();

	void update(bool canAttack);

	void draw() const;

	Optional<RectF> collision() const;
	Array<RectF> collisions() const;

	void hit(Enemy& enemy);

private:
	Timer timerAttack_;
	Timer timerAttack2_;
	Timer timerPowerup_;
	Vec2 pos_;
	double attackAngle_;
	int score_;
	int hands_;
};

