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
	//注視点から視点までのベクトルを設定。
	m_cameraPosition.Set(0.0f, m_cameraInitY, m_cameraInitZ);
	//プレイヤーのインスタンスを探す。
	m_player = FindGO<Player>("player");

	//カメラのニアクリップとファークリップを設定する。
	g_camera3D->SetNear(m_cameraNearClip);
	g_camera3D->SetFar(m_cameraFarClip);

	return true;
}

void GameCamera::Update()
{
	//カメラを更新。
	//注視点を計算する。
	Vector3 target = m_player->m_playerPosition;
	//プレイヤーの足元からちょっと上を注視点とする。
	target.y += m_cameraTargetOffsetY;

	Vector3 toCameraPosOld = m_cameraPosition;

	//視点を計算する。
	Vector3 pos = target + m_cameraPosition;
	//メインカメラに注視点と支店を設定する。
	g_camera3D->SetTarget(target);
	g_camera3D->SetPosition(pos);

	//カメラの更新。
	g_camera3D->Update();
}