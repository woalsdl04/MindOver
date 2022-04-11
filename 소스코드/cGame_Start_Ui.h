#pragma once
#include "GScript.h"

class cGame_Start_Ui : public GScript
{

public:

	cGame_Start_Ui();
	~cGame_Start_Ui();

	BaseComponent* Instantiate()
	{
		cGame_Start_Ui* ins_cpmp = new cGame_Start_Ui(*this);

		ins_cpmp->Original = false;

		return ins_cpmp;

	};

	SpriteRenderer_Component* Gamestart_Ui_Sc = NULL;
	FrameAni_Component* Gamestart_Ui_Ani = NULL;

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

