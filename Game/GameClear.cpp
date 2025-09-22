#include "stdafx.h"
#include "GameClear.h"
#include "Title.h"
#include "Game.h"
#include "Target.h"
#include "Dummy.h"
#include "GameCamera.h"
#include "sound/SoundEngine.h"

GameClear::GameClear()
{
	//���U���g��ʓǂݍ���
	m_spriteRender.Init("Assets/sprite/GameEnd.dds", m_spriteWidth, m_spriteHeight);
	//�^�C�g��BGM�ǂݍ���
	g_soundEngine->ResistWaveFileBank(0, "Assets/sound/title.wav");
	//�^�C�g����BGM���Đ��B
	m_titleBgm = NewGO<SoundSource>(0);
	m_titleBgm->Init(0);
	m_titleBgm->Play(true);
}
GameClear::~GameClear()
{
	//BGM�폜
	DeleteGO(m_titleBgm);
}

//�X�V����
void GameClear::Update()
{
	if (g_pad[0]->IsTrigger(enButtonSelect))
	{
		DeleteGO(this);
		NewGO<Title>(0, "title");
	}
}

void GameClear::Initialize(int targetCount)
{
	wchar_t infoText[256];
	swprintf_s(infoText, 256, L"%d�_",targetCount);

	m_fontRender.SetText(infoText);
	m_fontRender.SetPosition(m_setPosition);
	m_fontRender.SetColor(g_vec4Black);
	m_fontRender.SetScale(m_scale);
}

void GameClear::Render(RenderContext& rc)
{
	m_spriteRender.Draw(rc);
	m_fontRender.Draw(rc);
}