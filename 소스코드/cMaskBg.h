#pragma once
#include "GScript.h"

class cMaskBg : public GScript
{

public:

	GameObject* ingame_gameobject = NULL;
	MeMMap_Component* ingame_memmap = NULL;

	SpriteRenderer_Component* MaskBg_Sc;

	//bool IsMaskUpdate = false;
	cMaskBg();
	~cMaskBg();

	BaseComponent* Instantiate()
	{
		cMaskBg* ins_cpmp = new cMaskBg(*this);

		ins_cpmp->Original = false;

		return ins_cpmp;

	};

	void UpdateMaskTexture();

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

