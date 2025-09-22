#include "stdafx.h"
#include "Dummy.h"
#include "Bullet.h"

Dummy::Dummy()
{
	//モデル読み込み
	m_dummyRender.Init("Assets/modelData/matoB.tkm");

	//弾のオブジェクトを持ってくる
	m_bullet = FindGO<Bullet>("bullet");

	srand(time(0));
}

Dummy::~Dummy()
{

}

//更新処理
void Dummy::Update()
{
	//移動処理
	Move();

	//絵描き更新処理
	m_dummyRender.Update();

	m_spawnTimer += GameTime().GetFrameDeltaTime();

	if (m_spawnTimer >= m_spawnInterval)
	{
		Spawn();
		m_spawnTimer=0.0f;
	}
}

//移動処理
void Dummy::Move()
{
	m_dummyRender.SetPosition(m_dummyPosition);

	//ターゲットを破壊したらカウントをいつ増やす
	/*if (m_bullet != nullptr)
	{
		Vector3 diff = m_bullet->m_bulletPosition - m_targetPosition;
		if (diff.Length() <= 150.0f)
		{
			m_bullet->m_targetCount += 1;
		}
	}*/
}

void Dummy::Spawn()
{
	//srand(time(0));
	int dummySpawn = rand() % m_probability;

	switch (dummySpawn)
	{
	case 0:
		m_dummyPosition = m_dummySpawn0;
		break;
	case 1:
		m_dummyPosition = m_dummySpawn1;
		break;
	case 2:
		m_dummyPosition = m_dummySpawn2;
		break;
	case 3:
		m_dummyPosition = m_dummySpawn3;
		break;
	case 4:
		m_dummyPosition = m_dummySpawn4;
		break;
	}
}

//描画処理
void Dummy::Render(RenderContext& rc)
{
	m_dummyRender.Draw(rc);
}