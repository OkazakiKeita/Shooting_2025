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
	//�X�V����
	void Update();
	void AddTargetCount();
	void RemoveDummyCount();
	//�`�揈��
	void Render(RenderContext& rc);

	BackGround* m_backGround;
	Player* m_player;
	GameCamera* m_gameCamera;
	Target* m_target;
	Dummy* m_dummy;
	Bullet* m_bullet;
	SkyCube* m_skyCube;
	SoundSource* m_BGM;

	FontRender m_timeRender;	//�������Ԃ̕`��
	FontRender m_targetsRender;	//�I�ɓ��Ă����̕`��
	Vector3 m_setTime = {700.0f,500.0f,0.0f};
	Vector3 m_setTarget = { -80.0f,500.0f,0.0f };

	bool m_targetPendingRespawn = false;	//�I�̐����t���O
	bool m_dummyPendingRespawn = false;		//�_�~�[�̐����t���O

	float m_targetRespawnTimer = 0.0f;	//�I�����X�|�[������܂ł̎���
	float m_dummyRespawnTimer = 0.0f;	//�_�~�[�����X�|�[������܂ł̎���

	float m_time = 30.0f;	//��������
	int m_targetCount = 0;	//�I�ɓ��Ă���
};

