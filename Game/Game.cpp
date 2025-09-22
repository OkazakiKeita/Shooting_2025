#include "stdafx.h"
#include "Game.h"
#include "BackGround.h"
#include "Player.h"
#include "GameCamera.h"
#include "Target.h"
#include "Dummy.h"
#include "Bullet.h"
#include "GameClear.h"
#include "sound/SoundEngine.h"

Game::Game()
{
	//�X�e�[�W
	m_backGround = NewGO<BackGround>(0, "stage");
	//�L�����N�^�[
	m_player = NewGO<Player>(0, "player");
	//�J����
	m_gameCamera = NewGO<GameCamera>(0, "GameCamera");
	//�I
	m_target = NewGO<Target>(0, "target");
	//�_�~�[
	m_dummy = NewGO<Dummy>(0, "dummy");
	//��̃I�u�W�F�N�g
	m_skyCube = NewGO<SkyCube>(0, "skycube");
	//BGM�ǂݍ���
	g_soundEngine->ResistWaveFileBank(1, "Assets/sound/BGM.wav");
	//BGM�Đ�
	m_BGM = NewGO<SoundSource>(1);
	m_BGM->Init(1);
	m_BGM->Play(true);
}

Game::~Game()
{
	//�폜
	DeleteGO(m_backGround);
	DeleteGO(m_player);
	DeleteGO(m_gameCamera);
	DeleteGO(m_target);
	DeleteGO(m_dummy);
	DeleteGO(m_skyCube);
	if (m_bullet != nullptr)
	{
		DeleteGO(m_bullet);
	}
	DeleteGO(m_BGM);
}

void Game::Update()
{
	//�e
	if (g_pad[0]->IsTrigger(enButtonA))
	{
		m_bullet = NewGO<Bullet>(0, "bullet");
	}

	if (m_targetPendingRespawn)
	{
		m_targetRespawnTimer += g_gameTime->GetFrameDeltaTime();
		if (m_targetRespawnTimer >= 1.0f)
		{
			NewGO<Target>(0, "target");
			m_targetPendingRespawn = false;
			m_targetRespawnTimer;
		}
	}

	if (m_dummyPendingRespawn)
	{
		m_dummyRespawnTimer += g_gameTime->GetFrameDeltaTime();
		if (m_dummyRespawnTimer >= 1.0f)
		{
			NewGO<Dummy>(0, "dummy");
			m_dummyPendingRespawn = false;
			m_dummyRespawnTimer;
		}
	}

	m_time -= g_gameTime->GetFrameDeltaTime();
	int sec = (int)m_time;

	wchar_t text[256];
	swprintf_s(text, 256, L"�c��:%03d�b", sec);
	m_timeRender.SetText(text);
	m_timeRender.SetPosition(m_setTime);
	m_timeRender.SetColor(g_vec4Black);

	char text2[256];
	if (m_bullet != nullptr)
	{
		sprintf_s(text2, sizeof(text2), "Target:%d", m_targetCount);
	}
	else
	{
		sprintf_s(text2, sizeof(text2), "Target:0");
	}
	wchar_t text3[256];
	mbstowcs(text3, text2, 256);
	m_targetsRender.SetText(text3);
	m_targetsRender.SetPosition(m_setTarget);
	m_targetsRender.SetColor(g_vec4Black);

	if (m_time < 0)
	{
		auto gameClear=NewGO<GameClear>(0, "gameclear");
		gameClear->Initialize(m_targetCount);
		DeleteGO(this);
	}
}

void Game::AddTargetCount()
{
	m_targetCount++;
	m_targetPendingRespawn = true;
	m_targetRespawnTimer;
}

void Game::RemoveDummyCount()
{
	m_targetCount--;
	m_dummyPendingRespawn = true;
	m_dummyRespawnTimer;
}

void Game::Render(RenderContext& rc)
{
	m_timeRender.Draw(rc);
	m_targetsRender.Draw(rc);
}