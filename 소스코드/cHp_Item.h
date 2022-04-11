#pragma once
#include "GScript.h"

class cHp_Item : public GScript
{

public:

	cHp_Item();
	~cHp_Item();

	BaseComponent* Instantiate()
	{
		cHp_Item* ins_cpmp = new cHp_Item(*this);

		ins_cpmp->Original = false;

		return ins_cpmp;

	};
	SpriteRenderer_Component* Hp_Item_Sc = NULL;
	
	GameObject* ingame_gameobject = NULL;
	MeMMap_Component* ingame_memmap = NULL;

	GameObject* Player = NULL;
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

