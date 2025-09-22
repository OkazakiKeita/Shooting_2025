#include "stdafx.h"
#include "Bullet.h"
#include "Player.h"
#include "Target.h"
#include "Dummy.h"
#include "Game.h"
#include "sound/SoundEngine.h"

int Bullet::s_activeBulletCount=0;
Bullet::Bullet()
{
	//モデル読み込み
	m_bulletRender.Init("Assets/modelData/tama.tkm");

	//プレイヤーのオブジェクトを持ってくる
	m_player = FindGO<Player>("player");

	//的のオブジェクトを持ってくる
	m_target=FindGO<Target>("target");

	//ダミーのオブジェクトを持ってくる
	m_dummy = FindGO<Dummy>("dummy");

	//撃つ音読み込み
	g_soundEngine->ResistWaveFileBank(2, "Assets/sound/shoot.wav");
}

Bullet::~Bullet()
{
	DeleteGO(m_shootSound);
	DeleteGO(m_hitSound);
}

//更新処理
void Bullet::Update()
{
	//移動処理
	Move();

	//ステート管理
	ManageState();

	//絵描き更新処理
	m_bulletRender.Update();
}

//ステート管理
void Bullet::ManageState()
{
	//Aボタンを押されたら
	if (g_pad[0]->IsTrigger(enButtonA)&&m_bulletState==0&&s_activeBulletCount<s_maxBulletCount)
	{
		//撃つ音再生
		m_shootSound = NewGO<SoundSource>(2);
		m_shootSound->Init(2);
		m_shootSound->Play(true);
		//ステートを1にする
		m_bulletState = 1;
		s_activeBulletCount++;
		if (m_player != nullptr)
		{
			//弾の位置をプレイヤーの位置に持ってくる
			m_bulletPosition = m_player->GetPosition();
			//弾のyの位置を少し上げる
			m_bulletPosition.y += m_bulletHeight;
			//発射位置の記録
			m_bulletSpawn = m_bulletPosition;

			m_bulletDirection = m_player->GetForward();
			m_bulletDirection.Normalize();
		}
	}
}

//移動処理
void Bullet::Move()
{
	
	switch (m_bulletState)
	{
	case 0:
		break;
	case 1:
		m_bulletPosition += m_bulletDirection*m_bulletSpeed;
		m_bulletRender.SetPosition(m_bulletPosition);
		
		//ターゲットが存在するとき弾との距離を計算し、距離が一定以下なら、ターゲットと弾を削除
		if (m_target != nullptr)
		{
			Vector3 targetPosition = m_target->GetPosition();
			float distanceTarget = (m_bulletPosition - targetPosition).Length();
			if (distanceTarget <= m_hitDistance)
			{
				m_game = FindGO<Game>("game");
				if (m_game != nullptr)
				{
					m_game->AddTargetCount();
				}
				s_activeBulletCount--;
				DeleteGO(m_target);
				DeleteGO(this);
				return;
			}
		}
		if (m_dummy != nullptr)
		{
			Vector3 dummyPosition = m_dummy->GetPosition();
			float distanceDummy = (m_bulletPosition - dummyPosition).Length();
			if (distanceDummy <= m_hitDistance)
			{
				m_game = FindGO<Game>("game");
				if (m_game != nullptr)
				{
					m_game->RemoveDummyCount();
				}
				s_activeBulletCount--;
				DeleteGO(m_dummy);
				DeleteGO(this);
				return;
			}
		}

		//弾とプレイヤーの距離を計算し、一定距離以上なら、弾を削除し、アクティブ弾数を減らす
		if (m_player != nullptr)
		{
			float distance = (m_bulletPosition - m_bulletSpawn).Length();
			if (distance >= m_bulletMaxDiistance)
			{
				s_activeBulletCount--;
				DeleteGO(this);
			}
		}
		break;
	}
}

//描画処理
void Bullet::Render(RenderContext& rc)
{
	if (m_bulletState != 0)
	{
		//描画
		m_bulletRender.Draw(rc);
	}
}