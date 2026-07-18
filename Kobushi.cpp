#include "Kobushi.h"
#include "Enemy.h"

namespace
{
	constexpr double KobushiSize = 175;
	constexpr double KobushiCollisionSize = 120;
	constexpr double KobushiAttackMove = 96;
}

Kobushi::Kobushi()
	:
	pos_{ Cursor::PosF() },
	attackAngle_{ Math::HalfPi }
{
}

void Kobushi::update()
{
	const Vec2 cursorPos = Cursor::PosF();

	// 画面中央では真下、左右端ではそれぞれ外側へ最大 45 度傾ける
	const double normalizedX = Clamp((cursorPos.x - Scene::CenterF().x) / (Scene::Width() * 0.5), -1.0, 1.0);
	attackAngle_ = Math::HalfPi - normalizedX * (Math::Pi / 4.0);

	if (not timerAttack_.isRunning() || timerAttack_.progress0_1() > 0.5)
	{
		if ((MouseL | MouseR | MouseM).down())
		{
			timerAttack_.restart(0.3s);
		}
	}

	pos_ = cursorPos;

	if (timerAttack_.isRunning())
	{
		const Vec2 attackOffset = Circular{ KobushiAttackMove, attackAngle_ + Math::HalfPi };
		pos_ += attackOffset * EaseOutExpo(timerAttack_.progress1_0());
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

	TextureAsset(U"kobushi")
		.resized(KobushiSize * scale)
		.rotated(attackAngle_)
		.drawAt(pos_ + RandomVec2(r));

	// Debug
	if (collision())
	{
		collision()->drawFrame(1.5, Palette::Red);
	}
}

Optional<RectF> Kobushi::collision() const
{
	if (not timerAttack_.isRunning()) return none;

	return RectF{ Arg::center = pos_, KobushiCollisionSize };
}

void Kobushi::hit(Enemy& enemy)
{
}
