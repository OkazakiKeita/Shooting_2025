#pragma once
class Player;
class GameCamera :public IGameObject
{
public:
	GameCamera();
	~GameCamera();
	//�X�^�[�g����
	bool Start();
	//�X�V����
	void Update();

	Player* m_player;
	Vector3 m_cameraPosition;	//�J�����̈ʒu

	float m_cameraInitY = 150.0f;
	float m_cameraInitZ = -250.0f;
	float m_cameraTargetOffsetY = 80.0f;
	float m_cameraNearClip = 1.0f;
	float m_cameraFarClip = 10000.0f;
};


