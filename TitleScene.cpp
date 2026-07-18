#include "TitleScene.h"

TitleScene::TitleScene(const InitData& init)
	:
	IScene{ init },
	time_{ StartImmediately::Yes }
{
}

void TitleScene::update()
{
	if (time_ > 0.7s)
	{
		if ((MouseL | MouseR | MouseM).down())
		{
			changeScene(U"MainScene", 0);
		}
	}
}

void TitleScene::draw() const
{
	// BG
	Scene::Rect().draw(Palette::Magenta);

	// タイトルロゴ
	TextureAsset(U"title")
		.resized(500 * (0.9 + 0.2 * Periodic::Sine1_1(0.9s)))
		.drawAt(Scene::CenterF() + Vec2{ 0, -100 });
}
