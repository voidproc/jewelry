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
	TextureAsset::Register(U"kanban", U"image/kanban.png");
	TextureAsset::Register(U"oiharae", U"image/oiharae.png");
	TextureAsset::Register(U"s1", U"image/s1.png");
	TextureAsset::Register(U"s2", U"image/s2.png");
	TextureAsset::Register(U"s3", U"image/s3.png");
	TextureAsset::Register(U"s4", U"image/s4.png");
	TextureAsset::Register(U"s5", U"image/s5.png");
	TextureAsset::Register(U"s6", U"image/s6.png");
	TextureAsset::Register(U"s7", U"image/s7.png");
	TextureAsset::Register(U"s8", U"image/s8.png");
	TextureAsset::Register(U"s9", U"image/s9.png");
	TextureAsset::Register(U"s10", U"image/s10.png");
	TextureAsset::Register(U"s11", U"image/s11.png");
	TextureAsset::Register(U"s12", U"image/s12.png");
	TextureAsset::Register(U"s13", U"image/s13.png");
	TextureAsset::Register(U"s14", U"image/s14.png");
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
