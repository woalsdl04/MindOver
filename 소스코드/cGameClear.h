#pragma once
#include "GScript.h"

class cGameClear : public GScript
{

public:

	cGameClear();
	~cGameClear();


	GameObject* GameClear_info = NULL;
	FrameAni_Component* GameClear_Ani = NULL;

	BaseComponent* Instantiate()
	{
		cGameClear* ins_cpmp = new cGameClear(*this);

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

