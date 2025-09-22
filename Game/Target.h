#pragma once

class Game;
class Bullet;
class Target:public IGameObject
{
public:
	Target();
	~Target();
	//�X�V����
	void Update();
	//�`�揈��
	void Render(RenderContext& rc);
	//�ړ�����
	void Move();
	void Spawn();
	//�ʒu�����擾
	//const_�I�u�W�F�N�g�̏�Ԃ�ύX���Ȃ�
	const Vector3& GetPosition()const { return m_targetPosition; }

	//�����o�ϐ�
	ModelRender m_targetRender;	//�`��
	Vector3 m_targetPosition = { 0.0f,-50.0f,0.0f };	//�I�̈ʒu
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

