#pragma once
class Player;
class GameCamera :public IGameObject
{
public:
	GameCamera();
	~GameCamera();
	//スタート処理
	bool Start();
	//更新処理
	void Update();

	Player* m_player;
	Vector3 m_cameraPosition;	//カメラの位置

	float m_cameraInitY = 150.0f;
	float m_cameraInitZ = -250.0f;
	float m_cameraTargetOffsetY = 80.0f;
	float m_cameraNearClip = 1.0f;
	float m_cameraFarClip = 10000.0f;
};


