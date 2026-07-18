#include "MainScene.h"
#include "Suishou.h"

MainScene::MainScene(const InitData& init)
	:
	IScene{ init },
	actors_{},
	timerEnemySpawn_{},
	spawnCount_{ 0 },
	wave_{ 0 },
	timerReady_{ 2s, StartImmediately::Yes },
	time_{ StartImmediately::No }
{
	actors_.enemies.reserve(128);

	actors_.suishou = Suishou{ Scene::CenterF() };
}

void MainScene::update()
{
	// ゲーム開始時の演出待ち
	if (timerReady_.reachedZero() && not time_.isRunning())
	{
		time_.start();
	}

	actors_.kobushi.update();

	actors_.suishou.update();

	// 敵スポーン
	if (time_.isRunning())
	{
		if (not timerEnemySpawn_.isRunning())
		{
			std::pair<double, double> spawnTime;
			if (time_ < 50s)
			{
				spawnTime = std::make_pair(0.7, 2.0);
			}
			else if (time_ < 75s)
			{
				spawnTime = std::make_pair(0.4, 1.0);
			}
			else
			{
				spawnTime = std::make_pair(0.1, 0.4);
			}

			timerEnemySpawn_.restart(Duration{ SecondsF{ Random(0.5, 2.0) } });

			if (RandomBool())
			{
				actors_.enemies.push_back(Enemy{ Scene::Rect().rightCenter() + Vec2{ 0, Random(-250, 250) }, time_.sF(), &actors_});
			}
			else
			{
				actors_.enemies.push_back(Enemy{ Scene::Rect().leftCenter() + Vec2{ 0, Random(-250, 250) }, time_.sF(), &actors_ });
			}

			spawnCount_ += 1;
		}
	}

	for (auto& e : actors_.enemies)
	{
		e.update();
	}

	// 衝突判定（敵 vs こぶし）
	for (auto& coll_k : actors_.kobushi.collisions())
	{
		for (auto& e : actors_.enemies)
		{
			if (not e.collision()) continue;

			if (e.collision()->intersects(coll_k))
			{
				e.hit(actors_.kobushi);
				actors_.kobushi.hit(e);
			}
		}
	}

	// 衝突判定（水晶 vs こぶし）
	for (auto& coll_k : actors_.kobushi.collisions())
	{
		if (actors_.suishou.collision())
		{
			if (coll_k.intersects(*actors_.suishou.collision()))
			{
				actors_.suishou.hit(actors_.kobushi);
			}
		}
	}

	// 衝突判定（水晶 vs 敵）
	for (auto& e : actors_.enemies)
	{
		if (not e.collision()) continue;
		if (not actors_.suishou.collision()) continue;

		if (e.collision()->intersects(*actors_.suishou.collision()))
		{
			e.hit(actors_.suishou);
			actors_.suishou.hit(e);
		}
	}


	// 範囲外に出た敵を削除
	actors_.enemies.remove_if([](const Enemy& e) { return e.isOffscreen(); });
}

void MainScene::draw() const
{
	// BG
	Scene::Rect().draw(Palette::White);
	TextureAsset(U"room").resized(Scene::Size() * 1.2).drawAt(Scene::CenterF(), AlphaF(0.8));

	// 看板
	TextureAsset(U"kanban").resized(250).drawAt(Scene::Rect().topCenter() + Vec2{-100, 125});


	// 水晶
	actors_.suishou.draw();

	// ゲーム開始時の「追い払え」
	if (timerReady_.isRunning())
	{
		TextureAsset(U"oiharae")
			.resized(250 * (1.0 + 0.1 * Periodic::Sine1_1(0.7s)))
			.drawAt(actors_.suishou.pos() + Vec2{ 160, -130 });
	}

	// 敵
	for (const auto& e : actors_.enemies)
	{
		// 影
		if (e.active())
		{
			Ellipse{ e.pos() + Vec2{ 0, 60 }, 60, 20 }.draw(ColorF{ 0, 0.5 });
		}

		// 本体
		e.draw();
	}


	// こぶし
	actors_.kobushi.draw();

	// ゲージ
	RectF{ Scene::Rect().bottomCenter() + Vec2{-128, -71}, SizeF{(450. * 877 / 1200), (450. * 112 / 1200)} }
		.draw(ColorF{1.0, 0.3});
	RectF{ Scene::Rect().bottomCenter() + Vec2{-128, -71}, SizeF{(450. * 877 / 1200) * actors_.suishou.life() / 100.0, (450. * 112 / 1200)} }
		.rounded(3.0)
		.draw(Palette::Green.lerp(Palette::Lime, 0.3 + 0.2 * Periodic::Sine0_1(1.2s)));
	TextureAsset(U"gauge").resized(450).drawAt(Scene::Rect().bottomCenter() + Vec2{0, -50});
}
