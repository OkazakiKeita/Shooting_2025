#pragma once
class Game;
class Bullet;
class Dummy:public IGameObject
{
public:
	Dummy();
	~Dummy();
	//�X�V����
	void Update();
	//�`�揈��
	void Render(RenderContext& rc);
	//�ړ�����
	void Move();
	void Spawn();
	//�ʒu�����擾
	//const_�I�u�W�F�N�g�̏�Ԃ�ύX���Ȃ�
	const Vector3& GetPosition()const { return m_dummyPosition; }

	//�����o�ϐ�
	ModelRender m_dummyRender;	//�`��
	Vector3 m_dummyPosition = { 0.0f,-50.0f,0.0f };	//�I�̈ʒu
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

