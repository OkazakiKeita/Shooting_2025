#include "stdafx.h"
#include "Player.h"

Player::Player()
{
	//アニメーション読み込み
	m_animationClips[enAnimationClip_Idle].Load("Assets/animData/idle.tka");
	m_animationClips[enAnimationClip_Idle].SetLoopFlag(true);
	m_animationClips[enAnimationClip_Run].Load("Assets/animData/run.tka");
	m_animationClips[enAnimationClip_Run].SetLoopFlag(true);

	//モデルの初期化
	m_playerRender.Init("Assets/modelData/UnityChan.tkm", m_animationClips, enAnimationClip_Num, enModelUpAxisY);
	//キャラコンの初期化
	m_characterController.Init(m_radius, m_height, m_playerPosition);
}

Player::~Player()
{

}
//更新処理。
void Player::Update()
{
	//移動処理
	Move();

	//回転処理
	Rotation();

	//ステート管理
	ManageState();

	//アニメーションの再生
	PlayerAnimation();

	//絵描き更新処理
	m_playerRender.Update();
}
//移動処理
void Player::Move()
{
	m_playerMoveSpeed.x = 0.0f;
	m_playerMoveSpeed.z = 0.0f;

	Vector3 stickL;
	stickL.x = g_pad[0]->GetLStickXF();
	stickL.y = g_pad[0]->GetLStickYF();

	//カメラの前方向と右方向のベクトルに持ってくる
	Vector3 forward = g_camera3D->GetForward();
	Vector3 right = g_camera3D->GetRight();
	//y方向には移動させない
	forward.y = 0.0f;
	right.y = 0.0f;

	//左スティックの入力量と500.0fを乗算
	right *= stickL.x * m_moveSpeed;
	forward *= stickL.y * m_moveSpeed;

	//移動速度に上記で計算したベクトルを加算
	m_playerMoveSpeed += right + forward;

	//地面に付いていたら
	if (m_characterController.IsOnGround())
	{
		//重力をなくす
		m_playerMoveSpeed.y = 0.0f;
	}
	//地面に付いていなかったら
	else
	{
		//重力を発生
		m_playerMoveSpeed.y -= m_gravity;
	}

	m_playerPosition = m_characterController.Execute(m_playerMoveSpeed, m_deltaTime);

	m_playerRender.SetPosition(m_playerPosition);
}
//回転処理
void Player::Rotation()
{
	//スティック入力があったら
	if (fabsf(m_playerMoveSpeed.x) >= 0.001f || fabsf(m_playerMoveSpeed.z) >= m_rotationThreshold)
	{
		//キャラクターの方向を変える
		m_playerRotation.SetRotationYFromDirectionXZ(m_playerMoveSpeed);
		//絵描きに回転を教える
		m_playerRender.SetRotation(m_playerRotation);
	}
}
//ステート管理
void Player::ManageState()
{
	//地面に付いていたら
	//xかzの移動速度があったら(スティックの入力があったら)
	if (fabsf(m_playerMoveSpeed.x) >= 0.001 || fabsf(m_playerMoveSpeed.z) >= 0.001f)
	{
		//ステートを1にする
		m_playerState = 1;
	}
	else
	{
		m_playerState = 0;
	}
}

//アニメーションの再生
void Player::PlayerAnimation()
{
	switch (m_playerState)
	{
	case 0:
		m_playerRender.PlayAnimation(enAnimationClip_Idle);
		break;
	case 1:
		m_playerRender.PlayAnimation(enAnimationClip_Run);
		break;
	}
}

//プレイヤーの位置の取得
Vector3 Player::GetPosition()
{
	return m_playerPosition;
}

Vector3 Player::GetForward()
{
	Vector3 forward;

	float x = m_playerRotation.x;
	float y = m_playerRotation.y;
	float z = m_playerRotation.z;
	float w = m_playerRotation.w;


	forward.x = 2.0f * (x * z + w * y);
	forward.y = 2.0f * (y * z - w * x);
	forward.z = 1.0f-2.0f * (x * x + y * y);

	forward.Normalize();
	return forward;
}

//描画処理
void Player::Render(RenderContext& rc)
{
	m_playerRender.Draw(rc);
}