#pragma once
#include "GScript.h"

class cStage3_Boss : public GScript
{

public:

	cStage3_Boss();
	~cStage3_Boss();

	SpriteRenderer_Component* Boss_Sc;

	GameObject* ingame_gameobject = NULL;
	MeMMap_Component* ingame_memmap = NULL;
	Color_Component* Boss_Color = NULL;
	TRS_Component* Boss_Trs = NULL;

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
	GameObject* Eff;
	float Time = 0;
	int Count;

	int Attack_Count = 0;
	int Attack_Patten;

	BaseComponent* Instantiate()
	{
		cStage3_Boss* ins_cpmp = new cStage3_Boss(*this);

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

