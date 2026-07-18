#include "Enemy.h"
#include "Actors.h"
#include "Audio.h"

namespace
{
	constexpr double EnemySize = 150;
	constexpr double EnemyCollisionSize = 80;
}

Enemy::Enemy(const Vec2& pos, double time, Actors* actors)
	:
	actors_{ actors },
	pos_{ pos },
	mirror_{},
	speed_{},
	moveDead_{},
	state_{ EnemyState::Active },
	timeHit_{ StartImmediately::No },
	serifuAsset_{ Format(U"s", Random(1, 14)) },
	serifuPos_{},
	type_{ EnemyType::A }
{
	// タイプ決定
	if (RandomBool(0.2))
	{
		type_ = EnemyType::B;
	}

	// ランダムな方向の決定
	if (type_ == EnemyType::B)
	{
		if (pos_.x > Scene::CenterF().x)
		{
			// 右端に生成
			moveDir_ = Circular{ 1.0, 180_deg + Random(45_deg, 135_deg)};
		}
		else
		{
			moveDir_ = Circular{ 1.0, 0_deg + Random(45_deg, 135_deg) };
		}
	}

	// 移動速度
	if (time < 45.0)
	{
		speed_ = Random(60.0, 120.0);
	}
	else if (time < 75.0)
	{
		speed_ = Random(90.0, 180.0);

	}
	else
	{
		speed_ = Random(130.0, 300.0);
	}
}

void Enemy::update()
{
	if (state_ == EnemyState::Active)
	{
		if (type_ == EnemyType::A)
		{
			// 水晶に向かってくる
			const auto d = (actors_->suishou.pos() - pos_).withLength(speed_);
			pos_ += d * Scene::DeltaTime();
			mirror_ = (d.x > 0);
		}
		else if (type_ == EnemyType::B)
		{
			const auto d = moveDir_.withLength(speed_);
			pos_ += d * Scene::DeltaTime();
			mirror_ = (d.x > 0);
		}
	}
	else if (state_ == EnemyState::Dead)
	{
		// ふっとんでる
		const double k = EaseInExpo(Saturate(timeHit_.sF() / 0.15));
		pos_ += k * moveDead_ * Scene::DeltaTime();
	}
}

void Enemy::draw() const
{
	if (state_ == EnemyState::Active)
	{
		TextureAsset(U"dorobou")
			.mirrored(mirror_)
			.resized(EnemySize * Vec2{ 0.8 + 0.4 * Periodic::Sine0_1(0.7s), 0.9 + 0.2 * Periodic::Jump0_1(1s) })
			.rotated(4_deg * Periodic::Sine1_1(0.8s))
			.drawAt(pos_);
	}
	else if (state_ == EnemyState::Dead)
	{
		Color color{};
		if (timeHit_ < 0.5s) color = Palette::White.lerp(Palette::Red, 0.8 * Periodic::Square0_1(0.1s));

		TextureAsset(U"dorobou")
			.resized(EnemySize * Vec2{ 1.0 + 0.3 * Periodic::Sine1_1(0.9s), 1.0 + 0.3 * Periodic::Jump1_1(1.1s) })
			.rotated(timeHit_.sF() * 16.0)
			.drawAt(pos_ + RandomVec2(50.0 * Saturate(1.0 - timeHit_.sF() / 0.3)), color);

		if (timeHit_ < 0.8s && serifuPos_)
		{
			TextureAsset(serifuAsset_)
				.resized(180 * (0.7 + 0.7 * Periodic::Sine0_1(0.25s)))
				.drawAt(*serifuPos_ + Vec2{ 0, -50 } + RandomVec2(2.0));
		}
	}

	// Debug
	//if (collision())
	//{
	//	collision()->drawFrame(1.5, Palette::Red);
	//}
}

Optional<RectF> Enemy::collision() const
{
	if (state_ == EnemyState::Dead) return none;

	return RectF{ Arg::center = pos_, EnemyCollisionSize };
}

void Enemy::hit(Kobushi& kobushi)
{
	hit_(true);
}

void Enemy::hit(Suishou& suishou)
{
	hit_(false);
}

bool Enemy::isOffscreen() const
{
	return not Scene::Rect().stretched(100).intersects(pos_);
}

Vec2 Enemy::pos() const
{
	return pos_;
}

bool Enemy::active() const
{
	return state_ == EnemyState::Active;
}

void Enemy::hit_(bool enableSerifu)
{
	state_ = EnemyState::Dead;
	timeHit_.start();
	moveDead_ = Circular{ Random(400.0, 800.0), Random(Math::TwoPi) };

	serifuPos_ = pos_;
	if (not enableSerifu) serifuPos_ = none;

	PlayAudio(U"damage1");
}
