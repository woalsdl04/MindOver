#pragma once
#include "GScript.h"

class cStage2_Enemy_Poison : public GScript
{

public:

	cStage2_Enemy_Poison();
	~cStage2_Enemy_Poison();

	GameObject* Player_gameobject;
	GameObject* ingame_gameobject = NULL;
	MeMMap_Component* ingame_memmap = NULL;

	GVec3<float> Enemy_Pos = { 0, 0, 0 };
	float J_Speed = 0;
	float J_Time;
	int WorldTime = 0;
	float rot;
	float ang;
	ENEMY_STATE Sel = ENEMY_STATE::ENEMY_IDLE;

	GVec3<float> TarGetPos;
	GameObject* Gas;


	BaseComponent* Instantiate()
	{
		cStage2_Enemy_Poison* ins_cpmp = new cStage2_Enemy_Poison(*this);

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

