#pragma once
class BackGround:public IGameObject
{
public:
	BackGround();
	~BackGround();

	//•`‰æˆ—
	void Render(RenderContext& rc);

	//ƒƒ“ƒo•Ï”B
	ModelRender m_stageRender;	//•`‰æ
	PhysicsStaticObject m_physicsStaticObject;
};

