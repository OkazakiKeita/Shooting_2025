#pragma once
#include "sound/SoundSource.h"
class Game;
class Title:public IGameObject
{
public:
	Title();
	~Title();
	//�X�V����
	void Update();
	//�`��֐�
	void Render(RenderContext& rc);

	//�X�v���C�g�����_�[
	SpriteRender m_titleRender;
};