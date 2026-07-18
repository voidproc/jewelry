# include <Siv3D.hpp> // Siv3D v0.6.16

#include "MainScene.h"


void Main()
{
	// 背景真っ白
	Scene::SetBackground(Palette::White);

	// リサイズ可能に
	Window::SetStyle(WindowStyle::Sizable);

	// アセット
	TextureAsset::Register(U"dorobou", U"image/dorobou.png");
	TextureAsset::Register(U"suishou", U"image/suishou.png");
	TextureAsset::Register(U"suishou_ase1", U"image/suishou_ase1.png");
	TextureAsset::Register(U"kobushi", U"image/kobushi.png");
	TextureAsset::Register(U"ase", U"image/ase.png");
	TextureAsset::Register(U"room", U"image/room_yuka_flooring.png");

	App app;
	app.add<MainScene>(U"MainScene");
	app.init(U"MainScene", 0s);

	while (System::Update())
	{
		if (not app.updateScene())
		{
			break;
		}

		app.drawScene();
	}
}
