#pragma once

class Game;
class Bullet;
class Target:public IGameObject
{
public:
	Target();
	~Target();
	//更新処理
	void Update();
	//描画処理
	void Render(RenderContext& rc);
	//移動処理
	void Move();
	void Spawn();
	//位置情報を取得
	//const_オブジェクトの状態を変更しない
	const Vector3& GetPosition()const { return m_targetPosition; }

	//メンバ変数
	ModelRender m_targetRender;	//描画
	Vector3 m_targetPosition = { 0.0f,-50.0f,0.0f };	//的の位置
	Vector3 m_targetSpawn0 = { 0.0f,100.0f,500.0f };
	Vector3 m_targetSpawn1 = { 200.0f,100.0f,500.0f };
	Vector3 m_targetSpawn2 = { -200.0f,100.0f,500.0f };
	Vector3 m_targetSpawn3 = { 400.0f,100.0f,500.0f };
	Vector3 m_targetSpawn4 = { -400.0f,100.0f,500.0f };
	Bullet* m_bullet;
	int m_probability = 5;
	float m_spawnTimer = 1.0f;
	const float m_spawnInterval = 1.0f;
};

