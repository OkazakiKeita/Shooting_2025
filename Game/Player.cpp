#include "stdafx.h"
#include "Player.h"

Player::Player()
{
	//�A�j���[�V�����ǂݍ���
	m_animationClips[enAnimationClip_Idle].Load("Assets/animData/idle.tka");
	m_animationClips[enAnimationClip_Idle].SetLoopFlag(true);
	m_animationClips[enAnimationClip_Run].Load("Assets/animData/run.tka");
	m_animationClips[enAnimationClip_Run].SetLoopFlag(true);

	//���f���̏�����
	m_playerRender.Init("Assets/modelData/UnityChan.tkm", m_animationClips, enAnimationClip_Num, enModelUpAxisY);
	//�L�����R���̏�����
	m_characterController.Init(m_radius, m_height, m_playerPosition);
}

Player::~Player()
{

}
//�X�V�����B
void Player::Update()
{
	//�ړ�����
	Move();

	//��]����
	Rotation();

	//�X�e�[�g�Ǘ�
	ManageState();

	//�A�j���[�V�����̍Đ�
	PlayerAnimation();

	//�G�`���X�V����
	m_playerRender.Update();
}
//�ړ�����
void Player::Move()
{
	m_playerMoveSpeed.x = 0.0f;
	m_playerMoveSpeed.z = 0.0f;

	Vector3 stickL;
	stickL.x = g_pad[0]->GetLStickXF();
	stickL.y = g_pad[0]->GetLStickYF();

	//�J�����̑O�����ƉE�����̃x�N�g���Ɏ����Ă���
	Vector3 forward = g_camera3D->GetForward();
	Vector3 right = g_camera3D->GetRight();
	//y�����ɂ͈ړ������Ȃ�
	forward.y = 0.0f;
	right.y = 0.0f;

	//���X�e�B�b�N�̓��͗ʂ�500.0f����Z
	right *= stickL.x * m_moveSpeed;
	forward *= stickL.y * m_moveSpeed;

	//�ړ����x�ɏ�L�Ōv�Z�����x�N�g�������Z
	m_playerMoveSpeed += right + forward;

	//�n�ʂɕt���Ă�����
	if (m_characterController.IsOnGround())
	{
		//�d�͂��Ȃ���
		m_playerMoveSpeed.y = 0.0f;
	}
	//�n�ʂɕt���Ă��Ȃ�������
	else
	{
		//�d�͂𔭐�
		m_playerMoveSpeed.y -= m_gravity;
	}

	m_playerPosition = m_characterController.Execute(m_playerMoveSpeed, m_deltaTime);

	m_playerRender.SetPosition(m_playerPosition);
}
//��]����
void Player::Rotation()
{
	//�X�e�B�b�N���͂���������
	if (fabsf(m_playerMoveSpeed.x) >= 0.001f || fabsf(m_playerMoveSpeed.z) >= m_rotationThreshold)
	{
		//�L�����N�^�[�̕�����ς���
		m_playerRotation.SetRotationYFromDirectionXZ(m_playerMoveSpeed);
		//�G�`���ɉ�]��������
		m_playerRender.SetRotation(m_playerRotation);
	}
}
//�X�e�[�g�Ǘ�
void Player::ManageState()
{
	//�n�ʂɕt���Ă�����
	//x��z�̈ړ����x����������(�X�e�B�b�N�̓��͂���������)
	if (fabsf(m_playerMoveSpeed.x) >= 0.001 || fabsf(m_playerMoveSpeed.z) >= 0.001f)
	{
		//�X�e�[�g��1�ɂ���
		m_playerState = 1;
	}
	else
	{
		m_playerState = 0;
	}
}

//�A�j���[�V�����̍Đ�
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

//�v���C���[�̈ʒu�̎擾
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

//�`�揈��
void Player::Render(RenderContext& rc)
{
	m_playerRender.Draw(rc);
}