#pragma once
#include "GScript.h"

class cSpeedUp_Item : public GScript
{

public:

	cSpeedUp_Item();
	~cSpeedUp_Item();

	BaseComponent* Instantiate()
	{
		cSpeedUp_Item* ins_cpmp = new cSpeedUp_Item(*this);

		ins_cpmp->Original = false;

		return ins_cpmp;

	};
	SpriteRenderer_Component* SpeedUp_Item_Sc = NULL;

	GameObject* ingame_gameobject = NULL;
	MeMMap_Component* ingame_memmap = NULL;

	int SpeedUpPer;
	int WorldTime;
	int J_time;
	GVec3<float> Item_Pos = { 0, 0, 0 };
	ITEMSTATE Sel;

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

