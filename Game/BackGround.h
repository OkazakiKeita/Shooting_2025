#pragma once
class BackGround:public IGameObject
{
public:
	BackGround();
	~BackGround();

	//�`�揈��
	void Render(RenderContext& rc);

	//�����o�ϐ��B
	ModelRender m_stageRender;	//�`��
	PhysicsStaticObject m_physicsStaticObject;
};

