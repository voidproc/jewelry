#include "Kobushi.h"
#include "Enemy.h"

Kobushi::Kobushi()
	: pos_{ Cursor::PosF() }
{
}

void Kobushi::update()
{
	if ((MouseL | MouseR | MouseM).down() && not timerAttack_.isRunning())
	{
		timerAttack_.restart(0.3s);
	}

	pos_ = Cursor::PosF();

	if (timerAttack_.isRunning())
	{
		pos_ += Vec2{ 96, 0 } * EaseOutExpo(timerAttack_.progress1_0());
	}
}

void Kobushi::draw() const
{
	Vec2 scale{ 1.0, 1.0 };
	double r = 2.5;
	if (timerAttack_.isRunning())
	{
		scale.x = 1.0 + 1.5 * EaseInCubic(timerAttack_.progress1_0());
		scale.y = 1.0 + 1.0 * EaseInSine(timerAttack_.progress1_0());
		r = 2.5 + 8.0 * EaseInCubic(timerAttack_.progress1_0());
	}

	TextureAsset(U"kobushi").resized(150 * scale).drawAt(pos_ + RandomVec2(r));

	// Debug
	if (collision())
	{
		collision()->drawFrame(1.5, Palette::Red);
	}
}

Optional<RectF> Kobushi::collision() const
{
	if (not timerAttack_.isRunning()) return none;

	return RectF{ Arg::center = pos_, 120 };
}

void Kobushi::hit(Enemy& enemy)
{
}
