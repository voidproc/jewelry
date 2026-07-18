# include <Siv3D.hpp> // Siv3D v0.6.16

#include "MainScene.h"
#include "TitleScene.h"

void Main()
{
	Scene::SetBackground(Palette::White);
	Scene::SetResizeMode(ResizeMode::Keep);
	Window::SetStyle(WindowStyle::Sizable);
	Window::SetTitle(U"水晶泥棒 v1.1.0");
	System::SetTerminationTriggers(UserAction::CloseButtonClicked);

	// アセット
	TextureAsset::Register(U"dorobou", Resource(U"image/dorobou.png"));
	TextureAsset::Register(U"suishou", Resource(U"image/suishou.png"));
	TextureAsset::Register(U"suishou_ase1", Resource(U"image/suishou_ase1.png"));
	TextureAsset::Register(U"suishou_ase2", Resource(U"image/suishou_ase2.png"));
	TextureAsset::Register(U"kobushi", Resource(U"image/kobushi.png"));
	TextureAsset::Register(U"ase", Resource(U"image/ase.png"));
	TextureAsset::Register(U"powerup", Resource(U"image/powerup.png"));
	TextureAsset::Register(U"yabai", Resource(U"image/yabai.png"));
	TextureAsset::Register(U"abunai", Resource(U"image/abunai.png"));
	TextureAsset::Register(U"kanban", Resource(U"image/kanban.png"));
	TextureAsset::Register(U"oiharae", Resource(U"image/oiharae.png"));
	TextureAsset::Register(U"gauge", Resource(U"image/gauge.png"));
	TextureAsset::Register(U"title", Resource(U"image/title.png"));
	TextureAsset::Register(U"start", Resource(U"image/start.png"));
	TextureAsset::Register(U"gameover", Resource(U"image/gameover.png"));
	TextureAsset::Register(U"asondene", Resource(U"image/asondene.png"));
	TextureAsset::Register(U"danger1", Resource(U"image/danger1.png"));
	TextureAsset::Register(U"danger2", Resource(U"image/danger2.png"));
	TextureAsset::Register(U"danger3", Resource(U"image/danger3.png"));
	TextureAsset::Register(U"clear", Resource(U"image/clear.png"));
	TextureAsset::Register(U"arigatou", Resource(U"image/arigatou.png"));
	TextureAsset::Register(U"tobaseru", Resource(U"image/tobaseru.png"));
	TextureAsset::Register(U"num", Resource(U"image/num.png"));
	TextureAsset::Register(U"s1", Resource(U"image/s1.png"));
	TextureAsset::Register(U"s2", Resource(U"image/s2.png"));
	TextureAsset::Register(U"s3", Resource(U"image/s3.png"));
	TextureAsset::Register(U"s4", Resource(U"image/s4.png"));
	TextureAsset::Register(U"s5", Resource(U"image/s5.png"));
	TextureAsset::Register(U"s6", Resource(U"image/s6.png"));
	TextureAsset::Register(U"s7", Resource(U"image/s7.png"));
	TextureAsset::Register(U"s8", Resource(U"image/s8.png"));
	TextureAsset::Register(U"s9", Resource(U"image/s9.png"));
	TextureAsset::Register(U"s10", Resource(U"image/s10.png"));
	TextureAsset::Register(U"s11", Resource(U"image/s11.png"));
	TextureAsset::Register(U"s12", Resource(U"image/s12.png"));
	TextureAsset::Register(U"s13", Resource(U"image/s13.png"));
	TextureAsset::Register(U"s14", Resource(U"image/s14.png"));
	TextureAsset::Register(U"room", Resource(U"image/room_yuka_flooring.png"));

	AudioAsset::Register(U"swing1",  Resource(U"sound/swing1.ogg"));
	AudioAsset::Register(U"swing2",  Resource(U"sound/swing2.ogg"));
	AudioAsset::Register(U"damage1", Resource(U"sound/damage1.ogg"));
	AudioAsset::Register(U"damage2", Resource(U"sound/damage2.ogg"));
	AudioAsset::Register(U"powerup", Resource(U"sound/powerup.ogg"));
	AudioAsset::Register(U"chiin", Resource(U"sound/chiin.ogg"));

	FontAsset::Register(U"text", FontMethod::MSDF, 32, Resource(U"font/GenEiAntiqueNv6-M.ttf"));
	FontAsset::Load(U"text", U"ここはとある街のジュエリーショップ。ここではとても価値のあるすばらしい水晶玉が販売されているので、泥棒に目を付けられているらしい。君にはこのジュエリーショップの警備員となって、襲い来る泥棒たちを正義の鉄拳でたたきのめしてほしい。報酬ははずむので期待してくれたまえ。それに夜間の就労のため割り増しも付くから、文句ないだろう。多少けがをするかもしれないが、君は学生の頃からスポーツ万能だったし、国体にも行ったんだったな。だから多分大丈夫だろ。気を付けて任務にあたってくれ。私は他の業務で忙しいから、電話されても出れないかもしれないから。頼んだよ。期待している。素晴らしい成果を上げてくれ。ここで実績を積めば、さらに責任のある仕事も頼ませてもらうからな。これは君にしか頼めない仕事なんだ。健闘を祈る。");

	FontAsset::Register(U"text2", FontMethod::MSDF, 32, Resource(U"font/KodomoRounded.otf"), FontStyle::Bold);


	App app;
	app.add<TitleScene>(U"TitleScene");
	app.add<MainScene>(U"MainScene");
	app.init(U"TitleScene", 0s);

	while (System::Update())
	{
		if (not app.updateScene())
		{
			break;
		}

		app.drawScene();
	}
}
