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
	//�X�V����
	void Update();
	//�`�揈��
	void Render(RenderContext& rc);
	//�ړ�����
	void Move();
	//�X�e�[�g�Ǘ�
	void ManageState();

	//�����o�ϐ�
	ModelRender m_bulletRender;	//�`��
	Vector3 m_bulletPosition;	//�e�̈ʒu
	Vector3 m_bulletDirection;	//�e�̕���
	Vector3 m_bulletSpawn;		//�e�̔��ˈʒu
	Player* m_player;
	Target* m_target=nullptr;
	Dummy* m_dummy = nullptr;
	Game* m_game;
	SoundSource* m_shootSound;
	SoundSource* m_hitSound;
	int m_bulletState = 0;	//�X�e�[�g�Ǘ�
	float m_bulletSpeed = 50.0f;
	float m_bulletHeight = 60.0f;
	float m_bulletMaxDiistance = 1000.0f;
	float m_hitDistance = 50.0f;

	static int s_activeBulletCount;	//�e�����˂���Ă��鐔���J�E���g
	static const int s_maxBulletCount = 3;	//���˂����e�̐����Q�܂ŃJ�E���g
};

