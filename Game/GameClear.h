#pragma once
#include "sound/SoundSource.h"

class Game;
class GameClear:public IGameObject
{
public:
	GameClear();
	~GameClear();
	//XVˆ—
	void Update();
	void Initialize(int targetCount);
	//•`‰æˆ—
	void Render(RenderContext& rc);

	SoundSource* m_titleBgm;

	Vector3 m_setPosition = { 90.0f,-65.0f,0.0f };
	SpriteRender m_spriteRender;
	int m_targetCount = 0;
	FontRender m_fontRender;

	float m_spriteWidth = 1920.0f;
	float m_spriteHeight = 1080.0f;
	float m_scale = 3.0f;
};

