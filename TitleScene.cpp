#include "TitleScene.h"

TitleScene::TitleScene(const InitData& init)
	:
	IScene{ init },
	timeText_{ StartImmediately::Yes },
	time_{ StartImmediately::No }
{
}

void TitleScene::update()
{
	if (not time_.isRunning())
	{
		if ((MouseL | MouseR | MouseM).down())
		{
			time_.start();
			timeText_.set(999s);
		}
	}

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

	if (timeText_.isRunning())
	{
		StringView text = U"これはサンプルのテキストです。これはサンプルのテキストです。これはこれはサンプルのテキストです。これはこれはサンプルのテキストです。これはこれはサンプルのテキストです。これは";

		int len = text.length() * Saturate(timeText_.sF() / 8.0);

		FontAsset(U"text")(text.substr(0, len)).draw(
			RectF{ Arg::center = Scene::CenterF() + Vec2{ 3, 3 }, SizeF{700, 500} },
			ColorF{ 0, 0.6 });
		FontAsset(U"text")(text.substr(0, len)).draw(
			RectF{ Arg::center = Scene::CenterF(), SizeF{ 700, 500 } });
	}

	if (time_.isRunning())
	{
		Scene::Rect().draw(ColorF{ 0, 0.5 * Saturate(time_.sF() / 0.3) });

		// タイトルロゴ
		if (time_ > 0.3s)
		{
			TextureAsset(U"title")
				.resized(500)
				.drawAt(Scene::CenterF() + Vec2{ 0, -100 });
		}

		// 始まるテキスト
		if (time_ > 0.8s)
		{
			TextureAsset(U"start")
				.resized(500 * (0.9 + 0.2 * Periodic::Sine1_1(0.9s)))
				.drawAt(Scene::CenterF() + Vec2{ 0, 120 });
		}
	}



}
