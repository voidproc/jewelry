# include <Siv3D.hpp> // Siv3D v0.6.16

#include "MainScene.h"


void Main()
{
	// 背景真っ白
	Scene::SetBackground(Palette::White);

	// リサイズ可能に
	Scene::SetResizeMode(ResizeMode::Keep);
	Window::SetStyle(WindowStyle::Sizable);

	// アセット
	TextureAsset::Register(U"dorobou", U"image/dorobou.png");
	TextureAsset::Register(U"suishou", U"image/suishou.png");
	TextureAsset::Register(U"suishou_ase1", U"image/suishou_ase1.png");
	TextureAsset::Register(U"suishou_ase2", U"image/suishou_ase2.png");
	TextureAsset::Register(U"kobushi", U"image/kobushi.png");
	TextureAsset::Register(U"ase", U"image/ase.png");
	TextureAsset::Register(U"powerup", U"image/powerup.png");
	TextureAsset::Register(U"yabai", U"image/yabai.png");
	TextureAsset::Register(U"abunai", U"image/abunai.png");
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
