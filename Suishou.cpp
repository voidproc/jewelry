#include "Suishou.h"
#include "Enemy.h"

Suishou::Suishou()
	:
	pos_{}
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
	TextureAsset(U"suishou")
		.resized(160)
		.drawAt(pos_);

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

Vec2 Suishou::pos() const
{
	return pos_;
}
