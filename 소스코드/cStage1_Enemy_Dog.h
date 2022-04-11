#pragma once
#include "GScript.h"

class cStage1_Enemy_Dog : public GScript
{

public:

	cStage1_Enemy_Dog();
	~cStage1_Enemy_Dog();

	GameObject* Player_gameobject;
	GameObject* ingame_gameobject = NULL;
	MeMMap_Component* ingame_memmap = NULL;

	GVec3<float> Enemy_Pos = { 0, 0, 0 };
	float J_Speed = 0;
	float J_Time;
	int WorldTime = 0;
	float rot;
	float ang;
	bool IsStage3 = false;
	ENEMY_STATE Sel = ENEMY_STATE::ENEMY_IDLE;

	GVec3<float> TarGetPos;


	BaseComponent* Instantiate()
	{
		cStage1_Enemy_Dog* ins_cpmp = new cStage1_Enemy_Dog(*this);

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

