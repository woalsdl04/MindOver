#pragma once
#include "GScript.h"

class cBg : public GScript
{

public:

	SpriteRenderer_Component* Bg_Sc;

	cBg();
	~cBg();

	BaseComponent* Instantiate()
	{
		cBg* ins_cpmp = new cBg(*this);

		ins_cpmp->Original = false;

		return ins_cpmp;

	};

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

