#include "Enemy.h"
#include "Actors.h"

Enemy::Enemy(const Vec2& pos, Actors* actors)
	:
	actors_{ actors },
	pos_{ pos },
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
		pos_ += (actors_->suishou.pos() - pos_).withLength(speed_) * Scene::DeltaTime();
	}
	else if (state_ == EnemyState::Dead)
	{
		// ふっとんでる
		const double k = EaseInExpo(Saturate(timeHit_.sF() / 0.3));
		pos_ += k * moveDead_ * Scene::DeltaTime();
	}
}

void Enemy::draw() const
{
	if (state_ == EnemyState::Active)
	{
		TextureAsset(U"dorobou")
			.resized(150 * Vec2{ 0.8 + 0.2 * Periodic::Sine0_1(1s), 0.93 + 0.07 * Periodic::Jump0_1(1s) })
			.rotated(4_deg * Periodic::Sine1_1(0.8s))
			.drawAt(pos_);
	}
	else if (state_ == EnemyState::Dead)
	{
		TextureAsset(U"dorobou")
			.resized(150 * Vec2{ 0.8 + 0.2 * Periodic::Sine0_1(1s), 0.93 + 0.07 * Periodic::Jump0_1(1s) })
			.rotated(timeHit_.sF() * 16.0)
			.drawAt(pos_ + RandomVec2(50.0 * Saturate(1.0 - timeHit_.sF() / 0.3)));
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

	return RectF{ Arg::center = pos_, 80 };
}

void Enemy::hit(Kobushi& kobushi)
{
	state_ = EnemyState::Dead;
	timeHit_.start();
	moveDead_ = Circular{ Random(400.0, 600.0), Random(Math::TwoPi) };
}

bool Enemy::isOffscreen() const
{
	return not Scene::Rect().stretched(100).intersects(pos_);
}
