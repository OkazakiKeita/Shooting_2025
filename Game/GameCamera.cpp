#include "stdafx.h"
#include "GameCamera.h"
#include "Player.h"

GameCamera::GameCamera()
{

}

GameCamera::~GameCamera()
{

}

bool GameCamera::Start()
{
	//�����_���王�_�܂ł̃x�N�g����ݒ�B
	m_cameraPosition.Set(0.0f, m_cameraInitY, m_cameraInitZ);
	//�v���C���[�̃C���X�^���X��T���B
	m_player = FindGO<Player>("player");

	//�J�����̃j�A�N���b�v�ƃt�@�[�N���b�v��ݒ肷��B
	g_camera3D->SetNear(m_cameraNearClip);
	g_camera3D->SetFar(m_cameraFarClip);

	return true;
}

void GameCamera::Update()
{
	//�J�������X�V�B
	//�����_���v�Z����B
	Vector3 target = m_player->m_playerPosition;
	//�v���C���[�̑������炿����Ə�𒍎��_�Ƃ���B
	target.y += m_cameraTargetOffsetY;

	Vector3 toCameraPosOld = m_cameraPosition;

	//���_���v�Z����B
	Vector3 pos = target + m_cameraPosition;
	//���C���J�����ɒ����_�Ǝx�X��ݒ肷��B
	g_camera3D->SetTarget(target);
	g_camera3D->SetPosition(pos);

	//�J�����̍X�V�B
	g_camera3D->Update();
}