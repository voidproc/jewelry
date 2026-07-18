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
	Color color = Palette::White;
	if (timerHit_.isRunning())
	{
		hitVibr = RandomVec2(6.0);
		scale = 0.8 + 0.4 * Periodic::Sine0_1(0.07s);
		color = Palette::White.lerp(Palette::Red, 0.8 * Periodic::Square0_1(0.1s));
	}
	else
	{
		scale = 1.0 + 0.1 * Periodic::Sine1_1(1.2s);
	}

	TextureAsset(U"suishou")
		.resized(160 * scale)
		.drawAt(pos_ + hitVibr, color);

	// Debug
	if (collision())
	{
		collision()->drawFrame(1.5, Palette::Red);
	}
}

Optional<Circle> Suishou::collision() const
{
	if (timerHit_.isRunning()) return none;

	return Circle{ pos_, 55 };
}

void Suishou::hit(Enemy& enemy)
{
	hit_();
}

void Suishou::hit(Kobushi& kobushi)
{
	hit_();
}

Vec2 Suishou::pos() const
{
	return pos_;
}

void Suishou::hit_()
{
	if (not timerHit_.isRunning())
	{
		timerHit_.restart(0.4s);
	}
}
