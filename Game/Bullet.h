#pragma once
#include "sound/SoundSource.h"

class Game;
class Player;
class Target;
class Dummy;
class Bullet:public IGameObject
{
public:
	Bullet();
	~Bullet();
	//更新処理
	void Update();
	//描画処理
	void Render(RenderContext& rc);
	//移動処理
	void Move();
	//ステート管理
	void ManageState();

	//メンバ変数
	ModelRender m_bulletRender;	//描画
	Vector3 m_bulletPosition;	//弾の位置
	Vector3 m_bulletDirection;	//弾の方向
	Vector3 m_bulletSpawn;		//弾の発射位置
	Player* m_player;
	Target* m_target=nullptr;
	Dummy* m_dummy = nullptr;
	Game* m_game;
	SoundSource* m_shootSound;
	SoundSource* m_hitSound;
	int m_bulletState = 0;	//ステート管理
	float m_bulletSpeed = 50.0f;
	float m_bulletHeight = 60.0f;
	float m_bulletMaxDiistance = 1000.0f;
	float m_hitDistance = 50.0f;

	static int s_activeBulletCount;	//弾が発射されている数をカウント
	static const int s_maxBulletCount = 3;	//発射される弾の数を２までカウント
};

