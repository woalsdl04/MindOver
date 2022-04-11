#pragma once
#include "GScript.h"

class cGameOver_Ui : public GScript
{

public:

	cGameOver_Ui();
	~cGameOver_Ui();

	BaseComponent* Instantiate()
	{
		cGameOver_Ui* ins_cpmp = new cGameOver_Ui(*this);

		ins_cpmp->Original = false;

		return ins_cpmp;

	};

	GameObject* GameOver_info = NULL;
	FrameAni_Component* GameOver_Ui_Ani = NULL;

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

