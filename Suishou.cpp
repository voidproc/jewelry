#include "Suishou.h"
#include "Enemy.h"

namespace
{
	constexpr double SuishouSize = 180;
	constexpr double SuishouCollisionSize = 60;
	constexpr double InitialLife = 100;
}

Suishou::Suishou()
	:
	pos_{},
	timerHit_{},
	life_{ InitialLife },
	timerYabai_{},
	showYabai_{ false },
	timerAbunai_{},
	showAbunai_{ false }
{
}

Suishou::Suishou(const Vec2& pos)
	:
	pos_{ pos },
	timerHit_{},
	life_{ InitialLife },
	timerYabai_{},
	showYabai_{ false },
	timerAbunai_{},
	showAbunai_{ false }
{
}

void Suishou::update()
{
}

void Suishou::draw() const
{
	// ダメージ時の振動、大きさ、色
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
		if (life_ < 70.0) scale = 1.0 + 0.1 * Periodic::Sine1_1(0.9s);
		if (life_ < 40.0) scale = 1.0 + 0.1 * Periodic::Sine1_1(0.5s);

	}

	// 汗
	if (life_ < 70.0)
	{
		Duration aseLoopTime = 0.2s;
		if (life_ < 40.0) aseLoopTime = 0.14s;

		const double t_ase = Periodic::Sawtooth0_1(aseLoopTime);
		if (t_ase < 0.8)
		{
			TextureAsset(U"ase")
				.resized(SuishouSize)
				.drawAt(pos_ + Circular{ 75 + 35 * EaseOutSine(t_ase), 0_deg });
		}
	}

	// 影
	Ellipse{ pos_ + Vec2{ 0, 60 }, 60, 20 }.draw(ColorF{ 0, 0.5 });

	// 水晶
	{
		String asset = U"suishou";
		if (life_ < 70.0) asset = U"suishou_ase1";
		if (life_ < 40.0) asset = U"suishou_ase2";

		TextureAsset(asset)
			.resized(SuishouSize * scale)
			.drawAt(pos_ + hitVibr, color);
	}

	// 吹き出し
	if (timerYabai_.isRunning())
	{
		TextureAsset(U"yabai")
			.resized(200 * (0.7 + 0.5 * Periodic::Sine0_1(0.4s)))
			.drawAt(pos_ + Vec2{ 110, -50 });
	}

	if (timerAbunai_.isRunning())
	{
		TextureAsset(U"abunai")
			.resized(200 * (0.7 + 0.5 * Periodic::Sine0_1(0.25s)))
			.drawAt(pos_ + Vec2{ 110, -50 });
	}


	// Debug
	if (collision())
	{
		collision()->drawFrame(1.5, Palette::Red);
	}
}

Optional<Circle> Suishou::collision() const
{
	if (timerHit_.isRunning()) return none;

	return Circle{ pos_, SuishouCollisionSize };
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
	life_ -= 10.0;

	if (not timerHit_.isRunning())
	{
		timerHit_.restart(0.4s);
	}

	if (not showYabai_ && life_ < 70.0)
	{
		showYabai_ = true;
		timerYabai_.restart(2.5s);
	}

	if (not showAbunai_ && life_ < 40.0)
	{
		showAbunai_ = true;
		timerAbunai_.restart(2.5s);
	}
}
