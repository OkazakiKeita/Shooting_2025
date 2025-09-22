#include "stdafx.h"
#include "Target.h"
#include "Bullet.h"

Target::Target()
{
	//モデル読み込み
	m_targetRender.Init("Assets/modelData/matoA.tkm");

	//弾のオブジェクトを持ってくる
	m_bullet = FindGO<Bullet>("bullet");

	srand(time(0));
}

Target::~Target()
{

}

//更新処理
void Target::Update()
{
	//移動処理
	Move();

	//絵描き更新処理
	m_targetRender.Update();

	m_spawnTimer += GameTime().GetFrameDeltaTime();

	if (m_spawnTimer >= m_spawnInterval)
	{
		Spawn();
		m_spawnTimer = 0.0f;
	}
}

//移動処理
void Target::Move()
{
	m_targetRender.SetPosition(m_targetPosition);
}

void Target::Spawn()
{
	//srand(time(0));
	int targetSpawn = rand() % m_probability;

	switch(targetSpawn)
	{
	case 0:
		m_targetPosition = m_targetSpawn0;
		break;
	case 1:
		m_targetPosition = m_targetSpawn1;
		break;
	case 2:
		m_targetPosition = m_targetSpawn2;
		break;
	case 3:
		m_targetPosition = m_targetSpawn3;
		break;
	case 4:
		m_targetPosition = m_targetSpawn4;
		break;
	}
}

//描画処理
void Target::Render(RenderContext& rc)
{
	m_targetRender.Draw(rc);
}