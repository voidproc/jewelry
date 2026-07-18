#include "Suishou.h"
#include "Enemy.h"

Suishou::Suishou()
	:
	pos_{},
	timerHit_{}
{
}

Suishou::Suishou(const Vec2& pos)
	:
	pos_{ pos }
{
}

void Suishou::update()
{
}

void Suishou::draw() const
{
	Vec2 hitVibr{};
	double scale = 1.0;
	if (timerHit_.isRunning())
	{
		hitVibr = RandomVec2(6.0);
		scale = 0.8 + 0.4 * Periodic::Sine0_1(0.07s);
	}

	TextureAsset(U"suishou")
		.resized(160 * scale)
		.drawAt(pos_ + hitVibr);

	// Debug
	if (collision())
	{
		collision()->drawFrame(1.5, Palette::Red);
	}
}

Optional<Circle> Suishou::collision() const
{
	return Circle{ pos_, 55 };
}

void Suishou::hit(Enemy& enemy)
{
}

void Suishou::hit(Kobushi& kobushi)
{
	if (not timerHit_.isRunning())
	{
		timerHit_.restart(0.4s);
	}
}

Vec2 Suishou::pos() const
{
	return pos_;
}
