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
	//���f���ǂݍ���
	m_bulletRender.Init("Assets/modelData/tama.tkm");

	//�v���C���[�̃I�u�W�F�N�g�������Ă���
	m_player = FindGO<Player>("player");

	//�I�̃I�u�W�F�N�g�������Ă���
	m_target=FindGO<Target>("target");

	//�_�~�[�̃I�u�W�F�N�g�������Ă���
	m_dummy = FindGO<Dummy>("dummy");

	//�����ǂݍ���
	g_soundEngine->ResistWaveFileBank(2, "Assets/sound/shoot.wav");
}

Bullet::~Bullet()
{
	DeleteGO(m_shootSound);
	DeleteGO(m_hitSound);
}

//�X�V����
void Bullet::Update()
{
	//�ړ�����
	Move();

	//�X�e�[�g�Ǘ�
	ManageState();

	//�G�`���X�V����
	m_bulletRender.Update();
}

//�X�e�[�g�Ǘ�
void Bullet::ManageState()
{
	//A�{�^���������ꂽ��
	if (g_pad[0]->IsTrigger(enButtonA)&&m_bulletState==0&&s_activeBulletCount<s_maxBulletCount)
	{
		//�����Đ�
		m_shootSound = NewGO<SoundSource>(2);
		m_shootSound->Init(2);
		m_shootSound->Play(true);
		//�X�e�[�g��1�ɂ���
		m_bulletState = 1;
		s_activeBulletCount++;
		if (m_player != nullptr)
		{
			//�e�̈ʒu���v���C���[�̈ʒu�Ɏ����Ă���
			m_bulletPosition = m_player->GetPosition();
			//�e��y�̈ʒu�������グ��
			m_bulletPosition.y += m_bulletHeight;
			//���ˈʒu�̋L�^
			m_bulletSpawn = m_bulletPosition;

			m_bulletDirection = m_player->GetForward();
			m_bulletDirection.Normalize();
		}
	}
}

//�ړ�����
void Bullet::Move()
{
	
	switch (m_bulletState)
	{
	case 0:
		break;
	case 1:
		m_bulletPosition += m_bulletDirection*m_bulletSpeed;
		m_bulletRender.SetPosition(m_bulletPosition);
		
		//�^�[�Q�b�g�����݂���Ƃ��e�Ƃ̋������v�Z���A���������ȉ��Ȃ�A�^�[�Q�b�g�ƒe���폜
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

		//�e�ƃv���C���[�̋������v�Z���A��苗���ȏ�Ȃ�A�e���폜���A�A�N�e�B�u�e�������炷
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

//�`�揈��
void Bullet::Render(RenderContext& rc)
{
	if (m_bulletState != 0)
	{
		//�`��
		m_bulletRender.Draw(rc);
	}
}