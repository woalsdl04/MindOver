#pragma once
#include "GScript.h"
#include "SpriteRenderer_Component.h"

class cTitle : public GScript
{

public:

	SpriteRenderer_Component* Title_Sc = NULL;
	SpriteRenderer_Component* Button_Sc[3] = { NULL, NULL, NULL };
	TRS_Component* Button_TRS[3] = { NULL, NULL, NULL };

	GameObject* Button[3] = { NULL, NULL, NULL };
	GameObject* T_Font = NULL;
	GameObject* Title_Logo = NULL;
	GameObject* Creadit = NULL;
	GFont* T_Font_FC = NULL;
		
	SoundCLIP_Component* Title_Sound = NULL;

	GVec3<float>* Button_Pos[3] = { &GVec3<float>(0,0,0), &GVec3<float>(0,0,0), &GVec3<float>(0,0,0) };
	bool IsBack = false;
	cTitle();
	~cTitle();

	bool m_Cur[128];
	bool m_Old[128];

	int Sel = 0;

	BaseComponent* Instantiate()
	{
		cTitle* ins_cpmp = new cTitle(*this);

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

