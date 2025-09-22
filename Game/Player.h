#pragma once
class Bullet;
class Player :public IGameObject
{
public:
	Player();
	~Player();

	//�X�V����
	void Update();
	//�`�揈��
	void Render(RenderContext& rc);
	//�ړ�����
	void Move();
	//��]����
	void Rotation();
	//�X�e�[�g�Ǘ�
	void ManageState();
	//�A�j���[�V�����̍Đ�
	void PlayerAnimation();
	//�v���C���[�̈ʒu�̎擾
	Vector3 GetPosition();

	Vector3 GetForward();

	//�A�j���[�V�����N���b�v
	enum EnAnimationClip
	{
		enAnimationClip_Idle,
		enAnimationClip_Run,
		enAnimationClip_Num,
	};
	AnimationClip m_animationClips[enAnimationClip_Num];	//�A�j���[�V����
	ModelRender m_playerRender;	//�`��
	CharacterController m_characterController;	//�L�����N�^�[�R���g���[���[
	Vector3 m_playerPosition;	//�v���C���[�ʒu
	Vector3 m_playerMoveSpeed;	//�v���C���[�ړ�
	Quaternion m_playerRotation;	//�v���C���[��]
	int m_playerState = 0;	//�v���C���[�X�e�[�g

	float m_radius = 25.0f;
	float m_height = 75.0f;
	float m_moveSpeed = 800.0f;
	float m_gravity = 20.0f;
	float m_deltaTime = 1.0f / 60.0f;
	float m_rotationThreshold = 0.001f;
};

