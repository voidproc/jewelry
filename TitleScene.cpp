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
	Scene::Rect().draw(Palette::Royalblue.lerp(Color{ 0 }, 0.3));

	if (timeText_.isRunning())
	{
		StringView text = U"ここはとある街のジュエリーショップ。ここではとても価値のあるすばらしい水晶玉が販売されているので、泥棒に目を付けられているらしい。君にはこのジュエリーショップの警備員となって、襲い来る泥棒たちを正義の鉄拳でたたきのめしてほしい。報酬ははずむので期待してくれたまえ。それに夜間の就労のため割り増しも付くから、文句ないだろう。多少けがをするかもしれないが、君は学生の頃からスポーツ万能だったし、国体にも行ったんだったな。だから多分大丈夫だろ。気を付けて任務にあたってくれ。私は他の業務で忙しいから、電話されても出れないかもしれないから。頼んだよ。期待している。素晴らしい成果を上げてくれ。ここで実績を積めば、さらに責任のある仕事も頼ませてもらうからな。これは君にしか頼めない仕事なんだ。健闘を祈る。";

		int len = text.length() * Saturate(timeText_.sF() / 32.0);

		FontAsset(U"text")(text.substr(0, len)).draw(
			RectF{ Arg::center = Scene::CenterF() + Vec2{ 3, 3 }, SizeF{700, 500} },
			ColorF{ 0, 0.6 });
		FontAsset(U"text")(text.substr(0, len)).draw(
			RectF{ Arg::center = Scene::CenterF(), SizeF{ 700, 500 } });
	}

	if (timeText_ > 8s && not time_.isRunning())
	{
		TextureAsset(U"tobaseru")
			.resized(300 * (1.0 + 0.1 * Periodic::Sine1_1(0.3s)))
			.drawAt(Scene::Rect().br() - Vec2{ 80, 60 });
	}

	if (time_.isRunning())
	{
		Scene::Rect().draw(ColorF{ 0, 0.5 * Saturate(time_.sF() / 0.3) });

		// タイトルロゴ
		if (time_ > 0.3s)
		{
			TextureAsset(U"title")
				.resized(500 * (0.2 + Clamp((time_.sF() - 0.3) / 1.5, 0.0, 2.4)))
				.drawAt(Scene::CenterF() + Vec2{ 0, -100 });
		}

		// 始まるテキスト
		if (time_ > 1.5s)
		{
			TextureAsset(U"start")
				.resized(500 * (0.9 + 0.2 * Periodic::Sine1_1(0.9s)))
				.drawAt(Scene::CenterF() + Vec2{ 0, 120 });
		}
	}



}
