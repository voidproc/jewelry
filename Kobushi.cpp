#include "Kobushi.h"
#include "Enemy.h"
#include "Audio.h"

namespace
{
	constexpr double KobushiSize = 175;
	constexpr double KobushiCollisionSize = 120;
	constexpr double KobushiAttackMove = 120;

}

Kobushi::Kobushi()
	:
	timerAttack_{},
	timerAttack2_{},
	pos_{ Cursor::PosF() },
	attackAngle_{ Math::HalfPi },
	score_{},
	hands_{ 1 }
{
}

void Kobushi::update(bool canAttack)
{
	const Vec2 cursorPos = Cursor::PosF();

	// 画面中央では真下、左右端ではそれぞれ外側へ最大 45 度傾ける
	const double normalizedX = Clamp((cursorPos.x - Scene::CenterF().x) / (Scene::Width() * 0.5), -1.0, 1.0);
	attackAngle_ = Math::HalfPi - normalizedX * (Math::Pi / 4.0);

	if (canAttack && (not timerAttack_.isRunning() || timerAttack_.progress0_1() > 0.5))
	{
		if ((MouseL | MouseR | MouseM).down())
		{
			timerAttack_.restart(0.3s);
			timerAttack2_.restart(0.24s);

			PlayAudioSwing();

			attackOffsetScale_[0] = Random(0.3, 1.5);
			attackOffsetScale_[1] = Random(0.3, 1.5);
			attackOffsetScale_[2] = Random(0.3, 1.5);
		}
	}

	pos_ = cursorPos;
	posList_[0] = posList_[1] = posList_[2] = pos_;

	if (timerAttack_.isRunning())
	{
		const Vec2 pos = pos_;
		const Vec2 attackOffset = Circular{ KobushiAttackMove, attackAngle_ + Math::HalfPi };
		pos_ = pos + attackOffset * EaseOutElastic(timerAttack2_.progress1_0());

		posList_[0] = pos + attackOffset * attackOffsetScale_[0] * EaseOutElastic(timerAttack2_.progress1_0());
		posList_[1] = pos + attackOffset * attackOffsetScale_[1] * EaseOutElastic(timerAttack2_.progress1_0());
		posList_[2] = pos + attackOffset * attackOffsetScale_[2] * EaseOutElastic(timerAttack2_.progress1_0());
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

	if (hands_ == 1)
	{
		TextureAsset(U"kobushi")
			.resized(KobushiSize * scale)
			.rotated(attackAngle_)
			.drawAt(posList_[0] + RandomVec2(r));
	}
	else if (hands_ == 2)
	{
		TextureAsset(U"kobushi")
			.resized(KobushiSize * scale)
			.rotated(attackAngle_)
			.drawAt(posList_[0] + Circular{60, attackAngle_} + RandomVec2(r));

		TextureAsset(U"kobushi")
			.resized(KobushiSize * scale)
			.rotated(attackAngle_)
			.drawAt(posList_[1] + Circular{ 60, attackAngle_ + 180_deg } + RandomVec2(r));
	}
	else if (hands_ == 3)
	{
		TextureAsset(U"kobushi")
			.resized(KobushiSize * scale)
			.rotated(attackAngle_)
			.drawAt(posList_[0] + RandomVec2(r));

		TextureAsset(U"kobushi")
			.resized(KobushiSize * scale)
			.rotated(attackAngle_)
			.drawAt(posList_[1] + Circular{ 100, attackAngle_ } + RandomVec2(r));

		TextureAsset(U"kobushi")
			.resized(KobushiSize * scale)
			.rotated(attackAngle_)
			.drawAt(posList_[2] + Circular{ 100, attackAngle_ + 180_deg } + RandomVec2(r));
	}

	// パワーアップ
	if (timerPowerup_.isRunning())
	{
		TextureAsset(U"powerup")
			.resized(400 * (0.5 + 1.5 * timerPowerup_.progress0_1() * Periodic::Sine0_1(0.6s)))
			.drawAt(Scene::CenterF() + Vec2{ 0, -200 });
	}

	// Debug
	if (collision())
	{
		for (const auto& c : collisions())
		{
			c.drawFrame(1.5, Palette::Red);
		}
	}
}

Optional<RectF> Kobushi::collision() const
{
	if (not timerAttack_.isRunning()) return none;
	if (timerAttack_.progress0_1() > 0.7) return none;

	return RectF{ Arg::center = pos_, KobushiCollisionSize };
}

Array<RectF> Kobushi::collisions() const
{
	Array<RectF> c;
	if (not timerAttack_.isRunning()) return c;
	if (timerAttack_.progress0_1() > 0.7) return c;

	if (hands_ == 1)
	{
		c.push_back(RectF{ Arg::center = posList_[0], KobushiCollisionSize});
	}
	else if (hands_ == 2)
	{
		c.push_back(RectF{ Arg::center = posList_[0] + Circular{ 60, attackAngle_ } , KobushiCollisionSize });
		c.push_back(RectF{ Arg::center = posList_[1] + Circular{ 60, attackAngle_ + 180_deg } , KobushiCollisionSize });

	}
	else if (hands_ == 3)
	{
		c.push_back(RectF{ Arg::center = posList_[0], KobushiCollisionSize });
		c.push_back(RectF{ Arg::center = posList_[1] + Circular{ 100, attackAngle_ } , KobushiCollisionSize });
		c.push_back(RectF{ Arg::center = posList_[2] + Circular{ 100, attackAngle_ + 180_deg } , KobushiCollisionSize });

	}

	return c;
}

void Kobushi::hit(Enemy& enemy)
{
	score_ += 1;

	if (score_ == 13)
	{
		timerPowerup_.restart(2.5s);
		hands_ = 2;
		PlayAudio(U"powerup");
	}
	else if (score_ == 24)
	{
		timerPowerup_.restart(2.5s);
		hands_ = 3;
		PlayAudio(U"powerup");
	}
}
