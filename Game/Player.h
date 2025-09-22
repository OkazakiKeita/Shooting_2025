#pragma once
class Bullet;
class Player :public IGameObject
{
public:
	Player();
	~Player();

	//更新処理
	void Update();
	//描画処理
	void Render(RenderContext& rc);
	//移動処理
	void Move();
	//回転処理
	void Rotation();
	//ステート管理
	void ManageState();
	//アニメーションの再生
	void PlayerAnimation();
	//プレイヤーの位置の取得
	Vector3 GetPosition();

	Vector3 GetForward();

	//アニメーションクリップ
	enum EnAnimationClip
	{
		enAnimationClip_Idle,
		enAnimationClip_Run,
		enAnimationClip_Num,
	};
	AnimationClip m_animationClips[enAnimationClip_Num];	//アニメーション
	ModelRender m_playerRender;	//描画
	CharacterController m_characterController;	//キャラクターコントローラー
	Vector3 m_playerPosition;	//プレイヤー位置
	Vector3 m_playerMoveSpeed;	//プレイヤー移動
	Quaternion m_playerRotation;	//プレイヤー回転
	int m_playerState = 0;	//プレイヤーステート

	float m_radius = 25.0f;
	float m_height = 75.0f;
	float m_moveSpeed = 800.0f;
	float m_gravity = 20.0f;
	float m_deltaTime = 1.0f / 60.0f;
	float m_rotationThreshold = 0.001f;
};

