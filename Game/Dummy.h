#pragma once
class Game;
class Bullet;
class Dummy:public IGameObject
{
public:
	Dummy();
	~Dummy();
	//更新処理
	void Update();
	//描画処理
	void Render(RenderContext& rc);
	//移動処理
	void Move();
	void Spawn();
	//位置情報を取得
	//const_オブジェクトの状態を変更しない
	const Vector3& GetPosition()const { return m_dummyPosition; }

	//メンバ変数
	ModelRender m_dummyRender;	//描画
	Vector3 m_dummyPosition = { 0.0f,-50.0f,0.0f };	//的の位置
	Vector3 m_dummySpawn0 = { 100.0f,100.0f,450.0f };
	Vector3 m_dummySpawn1 = { 300.0f,100.0f,450.0f };
	Vector3 m_dummySpawn2 = { -300.0f,100.0f,450.0f };
	Vector3 m_dummySpawn3 = { 500.0f,100.0f,450.0f };
	Vector3 m_dummySpawn4 = { -500.0f,100.0f,450.0f };
	Bullet* m_bullet;
	int m_probability = 5;
	float m_spawnTimer = 1.0f;
	const float m_spawnInterval = 1.0f;
};

