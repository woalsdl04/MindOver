#pragma once
#include "GScript.h"

class cStage1_Enemy : public GScript
{

public:

	cStage1_Enemy();
	~cStage1_Enemy();

	GameObject* Player_gameobject;
	GameObject* ingame_gameobject = NULL;
	MeMMap_Component* ingame_memmap = NULL;

	GVec3<float> Joo_Pos = { 0, 0, 0 };
	GVec3<float> Enemy_Pos = { 0, 0, 0 };
	float J_Speed = 0;
	float J_Time;
	float ang;
	int WorldTime = 0;
	ENEMY_STATE Sel = ENEMY_STATE::ENEMY_IDLE;

	GVec3<float> TarGetPos;

	Animation_Item Enemy_Walking = Animation_Item::Animation_Item(L"Walking", 75, 0, 4, true);
	Animation_Item Enemy_Attack = Animation_Item::Animation_Item(L"Attack", 75, 5, 9, true);

	BaseComponent* Instantiate()
	{
		cStage1_Enemy* ins_cpmp = new cStage1_Enemy(*this);

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

