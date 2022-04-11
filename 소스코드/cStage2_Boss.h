#pragma once
#include "GScript.h"

class cStage2_Boss : public GScript
{

public:

	cStage2_Boss();
	~cStage2_Boss();

	SpriteRenderer_Component* Boss2_Sc;

	GameObject* ingame_gameobject = NULL;
	MeMMap_Component* ingame_memmap = NULL;
	Color_Component* Boss2_Color = NULL;
	TRS_Component* Boss2_Trs = NULL;

	GVec3<float>* J_Pos;
	GVec3<float> Enemy_Pos = { 0, 0, 0 };
	float J_Speed = 0;
	float J_Time;
	int WorldTime = 0;
	bool IsAngry = false;
	ENEMY_STATE Sel = ENEMY_STATE::ENEMY_IDLE;

	GVec3<float> TarGetPos;

	int ang, rotate, BulletCount;
	GameObject* Bullet;
	GameObject* Rocket;

	float Time = 0;
	int Count;

	Animation_Item Boss_Idle = Animation_Item::Animation_Item(L"Idle", 75, 0, 4, true);
	Animation_Item Boss_Attack = Animation_Item::Animation_Item(L"Attack", 75, 5, 13, true);;
	Animation_Item Boss_Reload = Animation_Item::Animation_Item(L"Reload", 75, 14, 17, false);;

	BaseComponent* Instantiate()
	{
		cStage2_Boss* ins_cpmp = new cStage2_Boss(*this);

		ins_cpmp->Original = false;

		return ins_cpmp;

	};

	bool Col_Check(GVec2<float> min, GVec2<float> max, AREA area);

	void NEW();

	void Awake();

	void Start();

	void Notice(Notice_Item* notice);

	void Render();

	void Update();

	void Late_Update();

	void Final_Update();

	void Reload();

	void Change();

	void Release();

};

