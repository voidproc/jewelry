#include "Enemy.h"
#include "Actors.h"

namespace
{
	constexpr double EnemySize = 150;
	constexpr double EnemyCollisionSize = 80;
}

Enemy::Enemy(const Vec2& pos, Actors* actors)
	:
	actors_{ actors },
	pos_{ pos },
	mirror_{},
	speed_{},
	moveDead_{},
	state_{ EnemyState::Active },
	timeHit_{ StartImmediately::No }
{
	speed_ = Random(60.0, 120.0);
}

void Enemy::update()
{
	if (state_ == EnemyState::Active)
	{
		// 水晶に向かってくる
		const auto d = (actors_->suishou.pos() - pos_).withLength(speed_);
		pos_ += d * Scene::DeltaTime();
		mirror_ = (d.x > 0);
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
			.resized(EnemySize * Vec2{ 0.8 + 0.2 * Periodic::Sine0_1(1s), 0.93 + 0.07 * Periodic::Jump0_1(1s) })
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
	}

	// Debug
	if (collision())
	{
		collision()->drawFrame(1.5, Palette::Red);
	}
}

Optional<RectF> Enemy::collision() const
{
	if (state_ == EnemyState::Dead) return none;

	return RectF{ Arg::center = pos_, EnemyCollisionSize };
}

void Enemy::hit(Kobushi& kobushi)
{
	hit_();
}

void Enemy::hit(Suishou& suishou)
{
	hit_();
}

bool Enemy::isOffscreen() const
{
	return not Scene::Rect().stretched(100).intersects(pos_);
}

void Enemy::hit_()
{
	state_ = EnemyState::Dead;
	timeHit_.start();
	moveDead_ = Circular{ Random(400.0, 800.0), Random(Math::TwoPi) };
}
