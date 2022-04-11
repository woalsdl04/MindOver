#pragma once
#include "GScript.h"
#include "cPlayer.h"

class cGameClear_info : public GScript
{

public:

	cGameClear_info();
	~cGameClear_info();

	bool IsGameClear;

	GameObject* Score_Ui = NULL;
	GFont* Score_Ui_Font = NULL;

	GameObject* Arrow_obj;
	GVec3<float> J_Pos;
	
	GameObject* Number = NULL;
	SpriteRenderer_Component* Number_Sc = NULL;
	int Sel;

	BaseComponent* Instantiate()
	{
		cGameClear_info* ins_cpmp = new cGameClear_info(*this);

		ins_cpmp->Original = false;

		return ins_cpmp;

	};

	void GameInfo(bool Isgameclear);

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

