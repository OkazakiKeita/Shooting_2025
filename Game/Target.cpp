#include "stdafx.h"
#include "Target.h"
#include "Bullet.h"

Target::Target()
{
	//���f���ǂݍ���
	m_targetRender.Init("Assets/modelData/matoA.tkm");

	//�e�̃I�u�W�F�N�g�������Ă���
	m_bullet = FindGO<Bullet>("bullet");

	srand(time(0));
}

Target::~Target()
{

}

//�X�V����
void Target::Update()
{
	//�ړ�����
	Move();

	//�G�`���X�V����
	m_targetRender.Update();

	m_spawnTimer += GameTime().GetFrameDeltaTime();

	if (m_spawnTimer >= m_spawnInterval)
	{
		Spawn();
		m_spawnTimer = 0.0f;
	}
}

//�ړ�����
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

//�`�揈��
void Target::Render(RenderContext& rc)
{
	m_targetRender.Draw(rc);
}