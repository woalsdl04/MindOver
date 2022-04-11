#pragma once
#include "GScript.h"



class cIngame : public GScript
{

public:

	GameObject* MaskBg_gameobject;
	SpriteRenderer_Component* MaskBg_Sc;
	MeMMap_Component* Ingame_MeMMap;
	MeMMap_Component* Ingame_AlphaMeMMap;
	Line_Component*	Ingame_Line;
	int LpNumber = 0;

	cIngame();
	~cIngame();

	BaseComponent* Instantiate()
	{
		cIngame* ins_cpmp = new cIngame(*this);

		ins_cpmp->Original = false;

		return ins_cpmp;

	};

	void MeM2_MaskBg();

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

