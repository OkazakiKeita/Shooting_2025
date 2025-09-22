#include "stdafx.h"
#include "Title.h"
#include "Game.h"
#include "sound/SoundEngine.h"

Title::Title()
{
	//�摜��ǂݍ���
	m_titleRender.Init("Assets/sprite/Title.dds",1920.0f,1080.0f);
}

Title::~Title()
{

}

void Title::Update()
{
	if (g_pad[0]->IsTrigger(enButtonStart))
	{
		DeleteGO(this);
		NewGO<Game>(0, "game");
	}
}

void Title::Render(RenderContext& rc)
{
	m_titleRender.Draw(rc);
}