#pragma once
#include "sound/SoundSource.h"

class Player;
class BackGround;
class GameCamera;
class Target;
class Dummy;
class Bullet;

class Game : public IGameObject
{
public:
	Game();
	~Game();
	//更新処理
	void Update();
	void AddTargetCount();
	void RemoveDummyCount();
	//描画処理
	void Render(RenderContext& rc);

	BackGround* m_backGround;
	Player* m_player;
	GameCamera* m_gameCamera;
	Target* m_target;
	Dummy* m_dummy;
	Bullet* m_bullet;
	SkyCube* m_skyCube;
	SoundSource* m_BGM;

	FontRender m_timeRender;	//制限時間の描画
	FontRender m_targetsRender;	//的に当てた数の描画
	Vector3 m_setTime = {700.0f,500.0f,0.0f};
	Vector3 m_setTarget = { -80.0f,500.0f,0.0f };

	bool m_targetPendingRespawn = false;	//的の生成フラグ
	bool m_dummyPendingRespawn = false;		//ダミーの生成フラグ

	float m_targetRespawnTimer = 0.0f;	//的がリスポーンするまでの時間
	float m_dummyRespawnTimer = 0.0f;	//ダミーがリスポーンするまでの時間

	float m_time = 30.0f;	//制限時間
	int m_targetCount = 0;	//的に当てた数
};

